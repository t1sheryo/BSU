const store = require('./store');

module.exports = function(app) {
    app.set('view engine', 'ejs');

    // Create
    app.post('/api/menu', (req, res) => {
        try {
            const data = store.readData();

            // Проверяем, есть ли уже блюдо с таким именем
            if (data.find(item => item.name === req.body.name)) {
                return res.status(400).json({ error: 'Блюдо с таким названием уже существует' });
            }

            const newItem = {
                name: req.body.name,
                description: req.body.description || '',
                price: parseFloat(req.body.price),
                category: req.body.category || 'Другое'
            };

            if (!newItem.name || isNaN(newItem.price)) {
                return res.status(400).json({ error: 'Название и корректная цена обязательны' });
            }

            data.push(newItem);
            store.saveData(data);
            res.status(201).json(newItem);
        } catch (err) {
            console.error('Error adding menu item:', err);
            res.status(500).json({ error: 'Ошибка сервера' });
        }
    });

    // Read All with pagination, sorting and search
    app.get('/api/menu', (req, res) => {
        try {
            const data = store.readData();
            const page = parseInt(req.query.page) || 1;
            const limit = parseInt(req.query.limit) || 5;
            const search = req.query.search || '';
            const sort = req.query.sort || 'name';
            const order = req.query.order || 'asc';

            // Поиск
            let filteredData = data;
            if (search) {
                filteredData = data.filter(item => 
                    item.name.toLowerCase().includes(search.toLowerCase())
                );
            }

            // Сортировка
            filteredData.sort((a, b) => {
                if (order === 'asc') {
                    return a[sort] > b[sort] ? 1 : -1;
                } else {
                    return a[sort] < b[sort] ? 1 : -1;
                }
            });

            // Пагинация
            const startIndex = (page - 1) * limit;
            const endIndex = page * limit;
            const paginatedData = filteredData.slice(startIndex, endIndex);

            res.json({
                items: paginatedData,
                total: filteredData.length,
                page,
                totalPages: Math.ceil(filteredData.length / limit)
            });
        } catch (err) {
            res.status(500).json({ error: 'Ошибка загрузки меню' });
        }
    });

    // Read One by name
    app.get('/api/menu/:name', (req, res) => {
        try {
            const data = store.readData();
            const item = data.find(item => item.name === req.params.name);
            if (item) {
                res.json(item);
            } else {
                res.status(404).json({ error: 'Блюдо не найдено' });
            }
        } catch (err) {
            res.status(500).json({ error: 'Ошибка сервера' });
        }
    });

    // Update by name
    app.put('/api/menu/:name', (req, res) => {
        try {
            let data = store.readData();
            const index = data.findIndex(item => item.name === req.params.name);

            if (index === -1) {
                return res.status(404).json({ error: 'Блюдо не найдено' });
            }

            const updatedItem = {
                ...data[index],
                name: req.body.name || data[index].name,
                description: req.body.description || data[index].description,
                price: req.body.price ? parseFloat(req.body.price) : data[index].price,
                category: req.body.category || data[index].category
            };

            if (!updatedItem.name || isNaN(updatedItem.price)) {
                return res.status(400).json({ error: 'Название и корректная цена обязательны' });
            }

            // Проверка на изменение имени и конфликт с другим блюдом
            if (updatedItem.name !== req.params.name && data.find(item => item.name === updatedItem.name)) {
                return res.status(400).json({ error: 'Блюдо с таким названием уже существует' });
            }

            data[index] = updatedItem;
            store.saveData(data);
            res.json(updatedItem);
        } catch (err) {
            console.error('Error updating item:', err);
            res.status(500).json({ error: 'Ошибка сервера' });
        }
    });

    // Delete by name
    app.delete('/api/menu/:name', (req, res) => {
        try {
            let data = store.readData();
            const initialLength = data.length;
            data = data.filter(item => item.name !== req.params.name);

            if (data.length < initialLength) {
                store.saveData(data);
                res.json({ message: 'Блюдо удалено' });
            } else {
                res.status(404).json({ error: 'Блюдо не найдено' });
            }
        } catch (err) {
            res.status(500).json({ error: 'Ошибка сервера' });
        }
    });

    // Главная страница
    app.get('/', (req, res) => {
        try {
            const data = store.readData();
            res.render('index', { 
                menu: data,
                currentPage: 1,
                totalPages: Math.ceil(data.length / 5)
            });
        } catch (err) {
            console.error('Error loading page:', err);
            res.status(500).send('Ошибка загрузки страницы');
        }
    });
};
