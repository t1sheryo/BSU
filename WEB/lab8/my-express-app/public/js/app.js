let currentPage = 1;
let currentSort = 'name';
let currentOrder = 'asc';
let currentSearch = '';

document.addEventListener('DOMContentLoaded', () => {
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
        
        const tbody = document.querySelector('tbody');
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

        // Обновляем информацию о страницах
        document.getElementById('pageInfo').textContent = `Страница ${data.page} из ${data.totalPages}`;
        document.getElementById('prevPage').disabled = data.page <= 1;
        document.getElementById('nextPage').disabled = data.page >= data.totalPages;
    } catch (error) {
        console.error('Ошибка при обновлении таблицы:', error);
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