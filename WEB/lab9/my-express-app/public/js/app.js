import { fromEvent, of, combineLatest, BehaviorSubject } from 'rxjs';
import { ajax } from 'rxjs/ajax';
import { 
    map, 
    switchMap, 
    debounceTime, 
    distinctUntilChanged,
    catchError,
    tap,
    filter
} from 'rxjs/operators';

// Состояние приложения как BehaviorSubject
const state$ = new BehaviorSubject({
    currentPage: 1,
    currentSort: 'name',
    currentOrder: 'asc',
    currentSearch: ''
});

// Создаем Observable для элементов управления
const createControlObservables = () => {
    const searchInput = document.getElementById('searchInput');
    const sortSelect = document.getElementById('sortSelect');
    const sortOrderBtn = document.getElementById('sortOrderBtn');
    const prevPageBtn = document.getElementById('prevPage');
    const nextPageBtn = document.getElementById('nextPage');
    const menuForm = document.getElementById('menuForm');

    // Observable для поиска
    const search$ = fromEvent(searchInput, 'input').pipe(
        map(e => e.target.value),
        debounceTime(300),
        distinctUntilChanged(),
        tap(value => {
            const currentState = state$.getValue();
            state$.next({
                ...currentState,
                currentSearch: value,
                currentPage: 1
            });
        })
    );

    // Observable для сортировки
    const sort$ = fromEvent(sortSelect, 'change').pipe(
        map(e => e.target.value),
        tap(value => {
            const currentState = state$.getValue();
            state$.next({
                ...currentState,
                currentSort: value
            });
        })
    );

    // Observable для порядка сортировки
    const sortOrder$ = fromEvent(sortOrderBtn, 'click').pipe(
        tap(() => {
            const currentState = state$.getValue();
            const newOrder = currentState.currentOrder === 'asc' ? 'desc' : 'asc';
            state$.next({
                ...currentState,
                currentOrder: newOrder
            });
            sortOrderBtn.textContent = newOrder === 'asc' ? '↑' : '↓';
        })
    );

    // Observable для пагинации
    const prevPage$ = fromEvent(prevPageBtn, 'click').pipe(
        tap(() => {
            const currentState = state$.getValue();
            if (currentState.currentPage > 1) {
                state$.next({
                    ...currentState,
                    currentPage: currentState.currentPage - 1
                });
            }
        })
    );

    const nextPage$ = fromEvent(nextPageBtn, 'click').pipe(
        tap(() => {
            const currentState = state$.getValue();
            state$.next({
                ...currentState,
                currentPage: currentState.currentPage + 1
            });
        })
    );

    // Observable для формы
    const formSubmit$ = fromEvent(menuForm, 'submit').pipe(
        tap(e => e.preventDefault()),
        map(() => {
            const name = document.getElementById('name').value.trim();
            const description = document.getElementById('description').value.trim();
            const price = document.getElementById('price').value;
            const category = document.getElementById('category').value;

            if (!name || !price) {
                throw new Error('Название и цена обязательны для заполнения');
            }

            return {
                name,
                description,
                price: parseFloat(price),
                category
            };
        })
    );

    return {
        search$,
        sort$,
        sortOrder$,
        prevPage$,
        nextPage$,
        formSubmit$
    };
};

// Функция для обновления таблицы
const updateMenuTable = (data) => {
    const tbody = document.querySelector('tbody');
    if (!tbody) return;
    
    tbody.innerHTML = '';
    
    data.items.forEach(item => {
        const row = document.createElement('tr');
        row.innerHTML = `
            <td>${item.name}</td>
            <td>${item.description}</td>
            <td>${item.price} руб.</td>
            <td>${item.category}</td>
            <td>
                <button onclick="editItem('${item.name}')">Изменить</button>
                <button onclick="deleteItem('${item.name}')">Удалить</button>
            </td>
        `;
        tbody.appendChild(row);
    });

    const pageInfo = document.getElementById('pageInfo');
    const prevPageBtn = document.getElementById('prevPage');
    const nextPageBtn = document.getElementById('nextPage');

    if (pageInfo) {
        pageInfo.textContent = `Страница ${data.page} из ${data.totalPages}`;
    }
    if (prevPageBtn) {
        prevPageBtn.disabled = data.page <= 1;
    }
    if (nextPageBtn) {
        nextPageBtn.disabled = data.page >= data.totalPages;
    }
};

// Функция для загрузки данных
const loadMenuData = () => {
    const state = state$.getValue();
    const queryParams = new URLSearchParams({
        page: state.currentPage,
        limit: 5,
        sort: state.currentSort,
        order: state.currentOrder,
        search: state.currentSearch
    });

    return ajax.getJSON(`/api/menu?${queryParams}`).pipe(
        tap(updateMenuTable),
        catchError(error => {
            console.error('Ошибка при загрузке данных:', error);
            return of({ items: [], page: 1, totalPages: 1 });
        })
    );
};

// Инициализация приложения
document.addEventListener('DOMContentLoaded', () => {
    const controls = createControlObservables();

    // Подписываемся на изменения состояния
    state$.pipe(
        switchMap(() => loadMenuData())
    ).subscribe();

    // Объединяем все Observable для обновления данных
    combineLatest([
        controls.search$,
        controls.sort$,
        controls.sortOrder$,
        controls.prevPage$,
        controls.nextPage$
    ]).subscribe();

    // Обработка отправки формы
    controls.formSubmit$.pipe(
        switchMap(data => {
            const url = `/api/menu/${encodeURIComponent(data.name)}`;
            return ajax({
                url,
                method: 'PUT',
                headers: { 'Content-Type': 'application/json' },
                body: data
            }).pipe(
                catchError(() => {
                    return ajax({
                        url: '/api/menu',
                        method: 'POST',
                        headers: { 'Content-Type': 'application/json' },
                        body: data
                    });
                })
            );
        }),
        tap(() => {
            const menuForm = document.getElementById('menuForm');
            if (menuForm) {
                menuForm.reset();
            }
            state$.next(state$.getValue());
        }),
        catchError(error => {
            console.error('Ошибка:', error);
            alert(`Ошибка: ${error.message}`);
            return of(null);
        })
    ).subscribe();

    // Начальная загрузка данных
    loadMenuData().subscribe();
});

// Глобальные функции для редактирования и удаления
window.editItem = (name) => {
    if (!name) return;
    
    ajax.getJSON(`/api/menu/${encodeURIComponent(name)}`).pipe(
        tap(item => {
            const nameInput = document.getElementById('name');
            const descriptionInput = document.getElementById('description');
            const priceInput = document.getElementById('price');
            const categoryInput = document.getElementById('category');

            if (nameInput) nameInput.value = item.name;
            if (descriptionInput) descriptionInput.value = item.description;
            if (priceInput) priceInput.value = item.price;
            if (categoryInput) categoryInput.value = item.category;
        }),
        catchError(error => {
            console.error('Ошибка при загрузке блюда:', error);
            return of(null);
        })
    ).subscribe();
};

window.deleteItem = (name) => {
    if (!name) {
        console.error('Название блюда не определено');
        return;
    }
    
    if (confirm('Вы уверены, что хотите удалить это блюдо?')) {
        ajax({
            url: `/api/menu/${encodeURIComponent(name)}`,
            method: 'DELETE'
        }).pipe(
            tap(() => state$.next(state$.getValue())),
            catchError(error => {
                console.error('Ошибка удаления блюда:', error);
                return of(null);
            })
        ).subscribe();
    }
};