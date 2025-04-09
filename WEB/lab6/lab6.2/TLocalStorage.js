class TLocalStorage {
    constructor(storageKey = 'cafesStorage') {
      this.storageKey = storageKey;
    }
  
    Reset() {
      window.localStorage.removeItem(this.storageKey);
      console.log("LocalStorage был успешно очищен!");
    }
  
    Add() {
      let cafeName = prompt("Введите название кафе:");
      let cafeInfo = prompt("Введите информацию о кафе:");
      
      if (cafeName && cafeInfo) {
        const storageData = this.getAllItems();
        storageData[cafeName] = cafeInfo;
        window.localStorage.setItem(this.storageKey, JSON.stringify(storageData));
        console.log(`Кафе "${cafeName}" было добавлено в LocalStorage!`);
      } else {
        alert("Название и информация о кафе обязательны!");
      }
    }
  
    GetValue() {
      let cafeName = prompt("Введите название кафе:");
      
      if (cafeName) {
        const storageData = this.getAllItems();
        if (cafeName in storageData) {
          console.log(storageData[cafeName]);
        } else {
          console.log("Кафе не найдено в LocalStorage!");
        }
      } else {
        alert("Название кафе обязательно!");
      }
    }
  
    Delete() {
      let cafeNameToDelete = prompt("Введите название кафе для удаления:");
      
      if (cafeNameToDelete) {
        const storageData = this.getAllItems();
        if (cafeNameToDelete in storageData) {
          delete storageData[cafeNameToDelete];
          window.localStorage.setItem(this.storageKey, JSON.stringify(storageData));
          console.log(`Кафе "${cafeNameToDelete}" было удалено из LocalStorage!`);
        } else {
          console.log("Кафе не найдено в LocalStorage!");
        }
      } else {
        alert("Название кафе обязательно!");
      }
    }
  
    GetKeys() {
      const storageData = this.getAllItems();
      const size = Object.keys(storageData).length;
      
      if (size === 0) {
        console.log("В LocalStorage нет кафе!");
      } else {
        let i = 1;
        for (let cafeName in storageData) {
          console.log(`Кафе ${i}: ${cafeName} - ${storageData[cafeName]}`);
          i++;
        }
      }
    }
  
    getAllItems() {
      const storedData = window.localStorage.getItem(this.storageKey);
      return storedData ? JSON.parse(storedData) : {};
    }
  }