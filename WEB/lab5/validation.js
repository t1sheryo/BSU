function initValidation() {
    const form = document.getElementById('TestForm');
    if (!form) {
        console.log('Форма не найдена, повторная попытка...');
        setTimeout(initValidation, 100);
        return;
    }

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

    function validateField(field) {
        if (!field.name || !validationRules[field.name]) return true;
        
        const rules = validationRules[field.name];
        const errorElement = document.getElementById(`${field.name}Error`);
        let isValid = true;

        if (!errorElement) return true;

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

    form.querySelectorAll('input').forEach(input => {
        input.addEventListener('input', function() {
            validateField(this);
        });
        
        input.addEventListener('blur', function() {
            validateField(this);
        });
    });

    form.addEventListener('submit', function(event) {
        event.preventDefault();
        let isFormValid = true;
    
        Object.keys(validationRules).forEach(fieldName => {
            const field = form.querySelector(`[name="${fieldName}"]`);
            if (field && !validateField(field)) {
                isFormValid = false;
            }
        });
    
        console.log('Проверка формы. Валидна:', isFormValid); // Добавьте для отладки
        
        if (isFormValid) {
            console.log('Форма валидна, можно отправлять');
            this.submit(); // Используем this вместо form для надежности
        } else {
            console.log('Форма содержит ошибки');
            document.querySelectorAll('.error-message').forEach(el => {
                if (el.textContent) {
                    el.style.display = 'block';
                    el.previousElementSibling.style.borderColor = 'red';
                }
            });
        }
    });
}

// Запускаем валидацию после загрузки DOM
document.addEventListener('DOMContentLoaded', initValidation);