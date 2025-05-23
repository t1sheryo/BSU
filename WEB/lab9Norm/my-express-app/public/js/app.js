let currentPage = 1;
let currentSort = 'name';
let currentOrder = 'asc';
let currentSearch = '';

function createPageStructure() {
    const app = document.getElementById('app');
    app.innerHTML = `
        <h1>Управление меню кафе</h1>
        
        <div class="container">
            <form id="menuForm">
                <input type="hidden" id="dishId">
                <input type="text" id="name" placeholder="Название блюда" required>
                <textarea id="description" placeholder="Описание"></textarea>
                <input type="number" id="price" placeholder="Цена" required>
                <select id="category">
                    <option value="Салаты">Салаты</option>
                    <option value="Горячие блюда">Горячие блюда</option>
                    <option value="Десерты">Десерты</option>
                    <option value="Напитки">Напитки</option>
                </select>
                <button type="submit">Сохранить</button>
            </form>

            <div class="controls">
                <div class="search-box">
                    <input type="text" id="searchInput" placeholder="Поиск по названию...">
                </div>
                <div class="sort-controls">
                    <select id="sortSelect">
                        <option value="name">По названию</option>
                        <option value="price">По цене</option>
                        <option value="category">По категории</option>
                    </select>
                    <button id="sortOrderBtn">↑</button>
                </div>
            </div>
            
            <table>
                <thead>
                    <tr>
                        <th>Название</th>
                        <th>Описание</th>
                        <th>Цена</th>
                        <th>Категория</th>
                        <th>Действия</th>
                    </tr>
                </thead>
                <tbody id="menuTableBody">
                </tbody>
            </table>

            <div class="pagination">
                <button id="prevPage" disabled>←</button>
                <span id="pageInfo">Страница 1 из 1</span>
                <button id="nextPage" disabled>→</button>
            </div>
        </div>
    `;
}

document.addEventListener('DOMContentLoaded', () => {
    createPageStructure();
    const form = document.getElementById('menuForm');
    const searchInput = document.getElementById('searchInput');
    const sortSelect = document.getElementById('sortSelect');
    const sortOrderBtn = document.getElementById('sortOrderBtn');
    const prevPageBtn = document.getElementById('prevPage');
    const nextPageBtn = document.getElementById('nextPage');

    // Обработчик поиска
    searchInput.addEventListener('input', debounce(() => {
        currentSearch = searchInput.value;
        currentPage = 1;
        updateMenuTable();
    }, 300));

    // Обработчик сортировки
    sortSelect.addEventListener('change', () => {
        currentSort = sortSelect.value;
        updateMenuTable();
    });

    // Обработчик порядка сортировки
    sortOrderBtn.addEventListener('click', () => {
        currentOrder = currentOrder === 'asc' ? 'desc' : 'asc';
        sortOrderBtn.textContent = currentOrder === 'asc' ? '↑' : '↓';
        updateMenuTable();
    });

    // Обработчики пагинации
    prevPageBtn.addEventListener('click', () => {
        if (currentPage > 1) {
            currentPage--;
            updateMenuTable();
        }
    });

    nextPageBtn.addEventListener('click', () => {
        currentPage++;
        updateMenuTable();
    });

    form.addEventListener('submit', async (e) => {
        e.preventDefault();

        const name = document.getElementById('name').value.trim();
        const description = document.getElementById('description').value.trim();
        const price = document.getElementById('price').value;
        const category = document.getElementById('category').value;

        if (!name || !price) {
            alert('Название и цена обязательны для заполнения');
            return;
        }

        const data = {
            name,
            description,
            price: parseFloat(price),
            category
        };

        try {
            const existingResponse = await fetch(`/api/menu/${encodeURIComponent(name)}`);
            if (existingResponse.ok) {
                const response = await fetch(`/api/menu/${encodeURIComponent(name)}`, {
                    method: 'PUT',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify(data)
                });

                if (!response.ok) {
                    const error = await response.json();
                    throw new Error(error.error || 'Ошибка обновления');
                }

                const result = await response.json();
                console.log('Блюдо обновлено:', result);
            } else if (existingResponse.status === 404) {
                const response = await fetch('/api/menu', {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify(data)
                });

                if (!response.ok) {
                    const error = await response.json();
                    throw new Error(error.error || 'Ошибка создания');
                }

                const result = await response.json();
                console.log('Блюдо создано:', result);
            } else {
                throw new Error('Ошибка при проверке существования блюда');
            }

            form.reset();
            await updateMenuTable();
        } catch (error) {
            console.error('Ошибка:', error);
            alert(`Ошибка: ${error.message}`);
        }
    });
});

// Функция для предотвращения частых вызовов при вводе
function debounce(func, wait) {
    let timeout;
    return function executedFunction(...args) {
        const later = () => {
            clearTimeout(timeout);
            func(...args);
        };
        clearTimeout(timeout);
        timeout = setTimeout(later, wait);
    };
}

async function updateMenuTable() {
    try {
        const queryParams = new URLSearchParams({
            page: currentPage,
            limit: 5,
            sort: currentSort,
            order: currentOrder,
            search: currentSearch
        });

        const response = await fetch(`/api/menu?${queryParams}`);
        const data = await response.json();
        
        const tbody = document.getElementById('menuTableBody');
        tbody.innerHTML = '';
        
        if (data.items && data.items.length > 0) {
            data.items.forEach(item => {
                const row = document.createElement('tr');
                row.innerHTML = `
                    <td>${item.name}</td>
                    <td>${item.description}</td>
                    <td>${item.price} руб.</td>
                    <td>${item.category}</td>
                    <td>
                        <button onclick="editItem('${item.name.replace(/'/g, "\\'")}')">Изменить</button>
                        <button onclick="deleteItem('${item.name.replace(/'/g, "\\'")}')">Удалить</button>
                    </td>
                `;
                tbody.appendChild(row);
            });
        } else {
            tbody.innerHTML = `
                <tr>
                    <td colspan="5" style="text-align: center;">Нет данных для отображения</td>
                </tr>
            `;
        }

        // Обновляем информацию о страницах
        document.getElementById('pageInfo').textContent = `Страница ${data.page} из ${data.totalPages}`;
        document.getElementById('prevPage').disabled = data.page <= 1;
        document.getElementById('nextPage').disabled = data.page >= data.totalPages;
    } catch (error) {
        console.error('Ошибка при обновлении таблицы:', error);
        const tbody = document.getElementById('menuTableBody');
        tbody.innerHTML = `
            <tr>
                <td colspan="5" style="text-align: center; color: red;">Ошибка загрузки данных</td>
            </tr>
        `;
    }
}

function editItem(name) {
    fetch(`/api/menu/${encodeURIComponent(name)}`)
        .then(res => res.json())
        .then(item => {
            document.getElementById('name').value = item.name;
            document.getElementById('description').value = item.description;
            document.getElementById('price').value = item.price;
            document.getElementById('category').value = item.category;
        });
}

function deleteItem(name) {
    if (!name) {
        console.error('Название блюда не определено');
        return;
    }
    fetch(`/api/menu/${encodeURIComponent(name)}`, {
        method: 'DELETE'
    })
    .then(response => {
        if (response.ok) {
            console.log(`Блюдо "${name}" удалено`);
            updateMenuTable();
        } else {
            console.error('Ошибка удаления блюда');
        }
    })
    .catch(err => console.error('Ошибка сети:', err));
}

// Инициализация таблицы при загрузке страницы
updateMenuTable();