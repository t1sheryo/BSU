document.addEventListener('DOMContentLoaded', function() {
    const homeBtn = document.getElementById('home-btn');
    const menuBtn = document.getElementById('menu-btn');
    const jsonBtn = document.getElementById('json-btn');
    const content = document.getElementById('content');
    const jsonDataDiv = document.getElementById('json-data');
    
    loadHomePage();
    
    homeBtn.addEventListener('click', loadHomePage);
    menuBtn.addEventListener('click', loadMenuPage);
    jsonBtn.addEventListener('click', loadJsonData);
    
    function loadHomePage() {
        fetch('/home.html')
            .then(response => response.text())
            .then(html => {
                content.innerHTML = html;
            })
            .catch(error => {
                console.error('Error loading home page:', error);
                content.innerHTML = '<p>Ошибка загрузки страницы</p>';
            });
    }
    
    function loadMenuPage() {
        fetch('/menu.html')
            .then(response => response.text())
            .then(html => {
                content.innerHTML = html;
            })
            .catch(error => {
                console.error('Error loading menu page:', error);
                content.innerHTML = '<p>Ошибка загрузки страницы</p>';
            });
    }
    
<<<<<<< HEAD
    function loadJsonData() {
        fetch('/data.json')
            .then(response => response.json())
            .then(data => {
                let table = '<table border="1"><tr><th>Название</th><th>Описание</th><th>Цена</th></tr>';
                for (const [name, details] of Object.entries(data)) {
                    table += `<tr><td>${name}</td><td>${details.description}</td><td>${details.price} ₽</td></tr>`;
                }
                table += '</table>';
                jsonDataDiv.innerHTML = table;
            })
            .catch(error => {
                console.error('Error loading JSON data:', error);
                jsonDataDiv.innerHTML = '<p>Ошибка загрузки данных</p>';
            });
    }
=======
    // function loadJsonData() {
    //     fetch('/data.json')
    //         .then(response => response.json())
    //         .then(data => {
    //             let table = '<table border="1"><tr><th>Название</th><th>Описание</th><th>Цена</th></tr>';
    //             for (const [name, details] of Object.entries(data)) {
    //                 table += `<tr><td>${name}</td><td>${details.description}</td><td>${details.price} ₽</td></tr>`;
    //             }
    //             table += '</table>';
    //             jsonDataDiv.innerHTML = table;
    //         })
    //         .catch(error => {
    //             console.error('Error loading JSON data:', error);
    //             jsonDataDiv.innerHTML = '<p>Ошибка загрузки данных</p>';
    //         });
    // }

    function loadJsonData() {
        fetch('/data.json')
            .then(response => response.blob()) 
            .then(blob => {
                const url = URL.createObjectURL(blob); 
                const link = document.createElement('a');
                link.href = url;
                link.download = 'data.json'; 
                link.click(); 
                URL.revokeObjectURL(url); 
            })
            .catch(error => {
                console.error('Ошибка загрузки:', error);
                alert('Не удалось скачать файл!');
            });
        }   
>>>>>>> 297429ed2abbca66ebd83300ce5b5a0089309e7f
});