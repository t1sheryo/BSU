const {app, BrowserWindow} = require('electron');
const path = require('path');

const createWindow = () => {

  const wind = new BrowserWindow({
    width : 400,
    height : 600,
    resizable : false,
  })

  wind.setTitle('Color Models');
  wind.loadFile('src/index.html');
  wind.setMenuBarVisibility(false);
  wind.webContents.openDevTools();
}

app.whenReady().then(() => {
  createWindow();

  app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) createWindow();
  });
});
app.on('window-all-closed', () => app.quit());