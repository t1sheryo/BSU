var MenuA = [
    {
        name: 'Пункт 1',
        submenu: [
            {
                name: 'Пункт 1.1',
                submenu: [
                    { name: 'Пункт 1.1.1', url: 'https://av.by/' },
                    { name: 'Пункт 1.1.2 длинный', url: 'https://av.by/' }
                ]
            },
            { name: 'Пункт 1.2', url: 'https://av.by/' },
            {
                name: 'Пункт 1.3 длинный',
                submenu: [
                    { name: 'Пункт 1.3.1', url: 'https://av.by/' },
                    { name: 'Пункт 1.3.2', url: 'https://av.by/' },
                    { name: 'Пункт 1.3.3', url: 'https://av.by/' },
                    { name: 'Пункт 1.3.4 длинный', url: 'https://av.by/' }
                ]
            }
        ]
    },
    { name: 'Пункт 2 длинный', url: 'https://av.by/' },
    {
        name: 'Пункт 3',
        submenu: [
            { name: 'Пункт 3.1 длинный', url: 'https://av.by/' },
            { name: 'Пункт 3.2', url: 'https://av.by/' }
        ]
    }
];

function createMenu(menuData, parentElement) {
    menuData.forEach(function(item) {
        var li = document.createElement('li');
        li.className = 'menu-item';
        if (item.submenu) li.classList.add('has-submenu');
        
        if (item.url) {
            var a = document.createElement('a');
            a.href = item.url;
            a.textContent = item.name;
            li.appendChild(a);
        } else {
            li.textContent = item.name;
        }
        
        parentElement.appendChild(li);
        
        if (item.submenu) {
            var submenu = document.createElement('ul');
            submenu.className = 'submenu';
            createMenu(item.submenu, submenu);
            li.appendChild(submenu);
            
            li.addEventListener('click', function(e) {
                if (e.target.tagName === 'A') return;
                
                e.stopPropagation();
                submenu.style.display = submenu.style.display === 'block' ? 'none' : 'block';
                
                var siblings = li.parentElement.children;
                for (var i = 0; i < siblings.length; i++) {
                    if (siblings[i] !== li) {
                        var otherSubmenu = siblings[i].querySelector('.submenu');
                        if (otherSubmenu) otherSubmenu.style.display = 'none';
                    }
                }
            });
        }
    });
}

    document.addEventListener('DOMContentLoaded', function() {
    var mainMenu = document.getElementById('mainMenu');
    createMenu(MenuA, mainMenu);
    
    document.addEventListener('click', function(e) {
        if (!e.target.closest('.menu-item')) {
            document.querySelectorAll('.submenu').forEach(function(menu) {
                menu.style.display = 'none';
            });
        }
    });
});