const express = require('express');
const path = require('path');
const app = express();
const port = 3000;

<<<<<<< HEAD
// Middleware для статических файлов
app.use(express.static(path.join(__dirname, 'public')));

// Маршруты
=======
app.use(express.static(path.join(__dirname, 'public')));

>>>>>>> 297429ed2abbca66ebd83300ce5b5a0089309e7f
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

app.get('/home.html', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'home.html'));
});

app.get('/menu.html', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'menu.html'));
});

<<<<<<< HEAD
app.get('/data.json', (req, res) => {
    res.download(path.join(__dirname, 'public', 'data.json'));
});

// Запуск сервера
=======
// Используем res.download() для принудительной загрузки
app.get('/data.json', (req, res) => {
    res.download(
        path.join(__dirname, 'public', 'data.json'),
        'data.json', // Имя файла при скачивании (необязательно)
        (err) => {
            if (err) {
                console.error('Ошибка при скачивании файла:', err);
                res.status(500).send('Ошибка загрузки файла');
            }
        }
    );
});

>>>>>>> 297429ed2abbca66ebd83300ce5b5a0089309e7f
app.listen(port, () => {
    console.log(`Сервер запущен на http://localhost:${port}`);
});