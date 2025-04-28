const express = require('express');
const { readData, saveData } = require('./store');
const router = express.Router();

// Получить всё меню (GET /api/menu)
router.get('/menu', (req, res) => {
  const menu = readData();
  res.json(menu);
});

// Добавить блюдо (POST /api/menu)
router.post('/menu', (req, res) => {
  const menu = readData();
  const { name, description, price, category } = req.body;
  
  menu[name] = { description, price, category };
  saveData(menu);
  
  res.status(201).json({ success: true });
});

// Обновить блюдо (PUT /api/menu/:name)
router.put('/menu/:name', (req, res) => {
  const menu = readData();
  const oldName = req.params.name;
  const { name, description, price, category } = req.body;
  
  delete menu[oldName];
  menu[name] = { description, price, category };
  saveData(menu);
  
  res.json({ success: true });
});

// Удалить блюдо (DELETE /api/menu/:name)
router.delete('/menu/:name', (req, res) => {
  const menu = readData();
  const name = req.params.name;
  
  delete menu[name];
  saveData(menu);
  
  res.json({ success: true });
});

module.exports = router;