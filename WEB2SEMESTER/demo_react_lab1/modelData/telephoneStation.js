"use strict";

/*
 * Load the model data for lab1. We load into the property
 * lab1models.telephoneStationModel a function that returns an array of strings with the
 * names of the available telephone services.
 */

var lab1models;

if (lab1models === undefined) {
  lab1models = {};
}

lab1models.telephoneStationModel = function () {
  return [
    "Голосовая почта",
    "Конференц-связь",
    "Переадресация вызовов",
    "Определение номера",
    "Блокировка номера",
    "Ожидание вызова",
    "Трехсторонняя связь",
    "Автоответчик",
    "Горячая линия",
    "Информационная служба",
    "Служба поддержки",
    "Техническая поддержка",
    "Бронирование",
    "Заказ такси",
    "Справочная служба",
    "Экстренная служба",
    "Междугородная связь",
    "Международная связь",
    "Мобильный интернет",
    "SMS-сервис",
    "MMS-сервис",
    "USSD-сервис",
    "Роуминг",
    "Виртуальный номер",
    "Факс-сервис"
  ];
};
