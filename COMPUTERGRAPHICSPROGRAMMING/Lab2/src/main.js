const { app, BrowserWindow } = require('electron');
const path = require('path');

// Создание окна приложения
function createWindow() {
    const win = new BrowserWindow({
        width: 800,
        height: 600,
        webPreferences: {
            //preload: path.join(__dirname, 'app.js'), // Подключение логики
            nodeIntegration: true, // Позволяет использовать Node.js в рендере
            contextIsolation: false // Отключение изоляции контекста для работы с require
        },
    });

    win.webContents.openDevTools();
    win.loadFile('src/index.html'); // Загрузка интерфейса
}

app.whenReady().then(() => {
    createWindow();

    app.on('activate', () => {
        if (BrowserWindow.getAllWindows().length === 0) {
            createWindow();
        }
    });
});

app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') {
        app.quit();
    }
});
