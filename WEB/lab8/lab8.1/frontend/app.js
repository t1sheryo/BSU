const API_URL = "http://localhost:3000/api/menu";

// Загрузить меню
async function loadMenu() {
  const response = await fetch(API_URL);
  const menu = await response.json();
  
  const menuList = document.getElementById("menu-list");
  menuList.innerHTML = Object.entries(menu).map(([name, dish]) => `
    <div class="dish">
      <h3>${name} (${dish.price} ₽)</h3>
      <p>${dish.description} (${dish.category})</p>
      <button onclick="editDish('${name}')">✏️</button>
      <button onclick="deleteDish('${name}')">❌</button>
    </div>
  `).join("");
}

// Добавить/Изменить блюдо
document.getElementById("dish-form").addEventListener("submit", async (e) => {
  e.preventDefault();
  const name = document.getElementById("dish-name").value;
  const description = document.getElementById("dish-desc").value;
  const price = document.getElementById("dish-price").value;
  const category = document.getElementById("dish-category").value;
  
  await fetch(API_URL, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ name, description, price, category }),
  });
  
  loadMenu();
});

// Удалить блюдо
async function deleteDish(name) {
  await fetch(`${API_URL}/${name}`, { method: "DELETE" });
  loadMenu();
}

// Загрузить данные при старте
loadMenu();