import { CreateForm } from './func.js';

var formArr = [
    { label: 'Имя пользователя:', elemtype: 'text1line', name: 'username', width: 200 },
    { label: 'Пароль:', elemtype: 'password', name: 'password', width: 200 },
    { label: 'Электронная почта:', elemtype: 'email', name: 'email', width: 250 },
    { label: 'Возраст:', elemtype: 'number', name: 'age', width: 100 },
    { label: 'Дата рождения:', elemtype: 'date', name: 'birthdate' },
    { label: 'Пол:', elemtype: 'radio', name: 'gender', options: ['Мужской', 'Женский'] },
    { label: 'Страна:', elemtype: 'select', name: 'country', options: ['Россия', 'США', 'Германия', 'Франция'] },
    { label: 'О себе:', elemtype: 'textarea', name: 'bio', rows: 4, cols: 50 },
    { label: 'Подписаться на рассылку:', elemtype: 'check', name: 'subscribe' },
    { label: 'Отправить:', elemtype: 'button', value: 'Отправить' },
    { label: 'Сбросить:', elemtype: 'button', value: 'Сбросить' }
];

CreateForm('TestForm', formArr);