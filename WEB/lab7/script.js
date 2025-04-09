document.addEventListener('DOMContentLoaded', function() {
    const homeBtn = document.getElementById('home-btn');
    const menuBtn = document.getElementById('menu-btn');
    const content = document.getElementById('content');
    
    loadHomePage();
    
    homeBtn.addEventListener('click', loadHomePage);
    menuBtn.addEventListener('click', loadMenuPage);
    
    function loadHomePage() {
        content.innerHTML = `
            <section class="home-content">
                <h2>Добро пожаловать в наше уютное кафе!</h2>
                <p>Мы предлагаем вам место, где можно насладиться вкусной едой, ароматным кофе и приятной атмосферой.</p>
                <p>Наше кафе работает с 8:00 до 22:00 без выходных.</p>
                <p>Нажмите кнопку "Наше меню", чтобы увидеть, чем мы можем вас порадовать сегодня!</p>
                <img src="https://images.unsplash.com/photo-1555396273-367ea4eb4db5?ixlib=rb-1.2.1&auto=format&fit=crop&w=500&q=60" alt="Интерьер кафе" style="max-width: 100%; border-radius: 8px; margin-top: 1rem;">
            </section>
        `;
    }
    
    function loadMenuPage() {
        content.innerHTML = `
            <section class="menu-content">
                <h2>Наше меню</h2>
                
                <div class="menu-item">
                    <h3>Эспрессо</h3>
                    <p>Крепкий черный кофе, приготовленный под давлением.</p>
                    <span class="price">120 ₽</span>
                </div>
                
                <div class="menu-item">
                    <h3>Капучино</h3>
                    <p>Эспрессо с молочной пеной и небольшим количеством молока.</p>
                    <span class="price">150 ₽</span>
                </div>
                
                <div class="menu-item">
                    <h3>Круассан</h3>
                    <p>Свежая слоеная выпечка с маслом.</p>
                    <span class="price">90 ₽</span>
                </div>
                
                <div class="menu-item">
                    <h3>Сэндвич с курицей</h3>
                    <p>Свежий хлеб, куриная грудка, листья салата и соус.</p>
                    <span class="price">180 ₽</span>
                </div>
                
                <div class="menu-item">
                    <h3>Чизкейк</h3>
                    <p>Классический десерт из творожного сыра на песочной основе.</p>
                    <span class="price">160 ₽</span>
                </div>
            </section>
        `;
    }
});