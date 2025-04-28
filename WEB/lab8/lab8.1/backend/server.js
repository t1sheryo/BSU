const express = require('express');
const bodyParser = require('body-parser');
const restApi = require('./rest');

const app = express();
const port = 3000;

app.use(bodyParser.json());
app.use('/api', restApi);

app.listen(port, () => {
  console.log(`Сервер запущен: http://localhost:${port}`);
});