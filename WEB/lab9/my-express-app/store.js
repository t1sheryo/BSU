const fs = require('fs');
const path = require('path');

const dataPath = path.join(__dirname, 'data/store.json');

function ensureFileExists() {
    if (!fs.existsSync(dataPath)) {
        fs.writeFileSync(dataPath, '[]', 'utf8');
    }
}

function readData() {
    try {
        ensureFileExists();
        const rawData = fs.readFileSync(dataPath, 'utf8');
        // Проверка на пустой файл
        if (!rawData.trim()) {
            return [];
        }
        return JSON.parse(rawData);
    } catch (err) {
        console.error('Error reading data file:', err);
        return [];
    }
}

function saveData(data) {
    try {
        ensureFileExists();
        fs.writeFileSync(dataPath, JSON.stringify(data, null, 2), 'utf8');
    } catch (err) {
        console.error('Error writing data file:', err);
    }
}

function findItem(id) {
    const data = readData();
    return data.find(item => item.id === id);
}

module.exports = {
    readData,
    saveData,
    findItem
};