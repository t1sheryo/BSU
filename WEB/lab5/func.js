export function CreateForm(formName, formData) {
    var form = document.createElement('form');
    form.name = formName;
    form.id = formName;

    formData.forEach(elem => {
        var block = document.createElement('div');

        if (elem.label && elem.elemtype !== 'button' && elem.elemtype !== 'radio') {
            var label = document.createElement('label');
            label.textContent = elem.label;
            label.htmlFor = elem.name;
            block.appendChild(label);
        }

        var input;
        switch (elem.elemtype) {
            case 'text1line':
                input = document.createElement('input');
                input.type = 'text';
                input.name = elem.name;
                input.id = elem.name;
                if (elem.width) input.style.width = elem.width + 'px';
                break;

            case 'textarea':
                input = document.createElement('textarea');
                input.name = elem.name;
                input.id = elem.name;
                if (elem.rows) input.rows = elem.rows;
                if (elem.cols) input.cols = elem.cols;
                break;

            case 'check':
                input = document.createElement('input');
                input.type = 'checkbox';
                input.name = elem.name;
                input.id = elem.name;
                break;

            case 'radio':
                elem.options.forEach(option => {
                    var radioInput = document.createElement('input');
                    radioInput.type = 'radio';
                    radioInput.name = elem.name;
                    radioInput.id = option;
                    radioInput.value = option;

                    var radioLabel = document.createElement('label');
                    radioLabel.textContent = option;
                    radioLabel.htmlFor = option;

                    block.appendChild(radioInput);
                    block.appendChild(radioLabel);
                });
                break;

            case 'select':
                input = document.createElement('select');
                input.name = elem.name;
                input.id = elem.name;
                elem.options.forEach(option => {
                    var optionElement = document.createElement('option');
                    optionElement.value = option;
                    optionElement.textContent = option;
                    input.appendChild(optionElement);
                });
                break;

            case 'password':
                input = document.createElement('input');
                input.type = 'password';
                input.name = elem.name;
                input.id = elem.name;
                if (elem.width) input.style.width = elem.width + 'px';
                break;

            case 'email':
                input = document.createElement('input');
                input.type = 'email';
                input.name = elem.name;
                input.id = elem.name;
                if (elem.width) input.style.width = elem.width + 'px';
                break;

            case 'number':
                input = document.createElement('input');
                input.type = 'number';
                input.name = elem.name;
                input.id = elem.name;
                if (elem.width) input.style.width = elem.width + 'px';
                break;

            case 'date':
                input = document.createElement('input');
                input.type = 'date';
                input.name = elem.name;
                input.id = elem.name;
                break;

            case 'button':
                    case 'button':
                    input = document.createElement('button');
                    input.type = (elem.value === 'Отправить') ? 'submit' : 'reset';
                    input.textContent = elem.value;
                    break;

            default:
                console.error('Неизвестный тип элемента:', elem.elemtype);
                return;
        }

        if (input) {
            block.appendChild(input);

            if (elem.name) {
                var errorElement = document.createElement('div');
                errorElement.id = `${elem.name}Error`;
                errorElement.className = 'error-message';
                errorElement.style.color = 'red';
                block.appendChild(errorElement);
            }

            form.appendChild(block);
        }
    });

    document.getElementById('formContainer').appendChild(form);
}