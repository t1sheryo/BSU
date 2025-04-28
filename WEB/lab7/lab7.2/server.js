const express = require('express');
const path = require('path');
const app = express();
const port = 3000;

app.use(express.static(path.join(__dirname, 'public')));

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

app.get('/home.html', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'home.html'));
});

app.get('/menu.html', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'menu.html'));
});

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

app.listen(port, () => {
    console.log(`Сервер запущен на http://localhost:${port}`);
});