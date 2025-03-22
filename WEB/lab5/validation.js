document.addEventListener('DOMContentLoaded', function () {
    const form = document.getElementById('TestForm');

    // Правила валидации для каждого поля
    const validationRules = {
        username: {
            required: true,
            minLength: 3,
            maxLength: 20,
            message: 'Имя пользователя должно быть от 3 до 20 символов.'
        },
        email: {
            required: true,
            pattern: /^[^\s@]+@[^\s@]+\.[^\s@]+$/,
            message: 'Введите корректный email.'
        },
        password: {
            required: true,
            minLength: 6,
            message: 'Пароль должен быть не менее 6 символов.'
        },
        age: {
            required: true,
            min: 18,
            max: 100,
            message: 'Возраст должен быть от 18 до 100 лет.'
        }
    };

    // Функция для валидации одного поля
    function validateField(field) {
        const rules = validationRules[field.name];
        const errorElement = document.getElementById(`${field.name}Error`);
        let isValid = true;

        if (rules.required && !field.value.trim()) {
            errorElement.textContent = 'Это поле обязательно для заполнения.';
            isValid = false;
        } else if (rules.minLength && field.value.length < rules.minLength) {
            errorElement.textContent = rules.message;
            isValid = false;
        } else if (rules.maxLength && field.value.length > rules.maxLength) {
            errorElement.textContent = rules.message;
            isValid = false;
        } else if (rules.pattern && !rules.pattern.test(field.value)) {
            errorElement.textContent = rules.message;
            isValid = false;
        } else if (rules.min && parseInt(field.value) < rules.min) {
            errorElement.textContent = rules.message;
            isValid = false;
        } else if (rules.max && parseInt(field.value) > rules.max) {
            errorElement.textContent = rules.message;
            isValid = false;
        } else {
            errorElement.textContent = '';
        }

        return isValid;
    }

    // Валидация при изменении значения поля
    form.querySelectorAll('input').forEach(input => {
        input.addEventListener('input', function () {
            validateField(this);
        });
    });

    // Валидация при отправке формы
    form.addEventListener('submit', function (event) {
        let isFormValid = true;

        form.querySelectorAll('input').forEach(input => {
            if (!validateField(input)) {
                isFormValid = false;
            }
        });

        if (!isFormValid) {
            event.preventDefault(); // Отмена отправки формы
        }
    });
});