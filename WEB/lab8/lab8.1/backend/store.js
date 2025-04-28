const fs = require('fs');
const path = require('path');

const filePath = path.join(__dirname, 'menu.json');

// Чтение данных
function readData() {
  const rawData = fs.readFileSync(filePath);
  return JSON.parse(rawData);
}

// Сохранение данных
function saveData(data) {
  fs.writeFileSync(filePath, JSON.stringify(data, null, 2));
}

module.exports = { readData, saveData };