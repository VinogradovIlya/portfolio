document.addEventListener('DOMContentLoaded', function () {
    // Auto-hide messages after 5 seconds
    autoHideMessages();

    // Form validation
    initFormValidation();

    // Mobile menu toggle (если добавишь мобильное меню)
    initMobileMenu();
});

/**
 * Auto-hide success messages
 */
function autoHideMessages() {
    const messages = document.querySelectorAll('.message');

    messages.forEach(message => {
        // Только успешные сообщения скрываем автоматически
        if (message.classList.contains('message--success')) {
            setTimeout(() => {
                message.style.opacity = '0';
                setTimeout(() => {
                    if (message.parentNode) {
                        message.remove();
                    }
                }, 300);
            }, 5000);
        }

        // Добавляем кнопку закрытия для всех сообщений
        addCloseButton(message);
    });
}

/**
 * Add close button to messages
 */
function addCloseButton(message) {
    const closeBtn = document.createElement('button');
    closeBtn.innerHTML = '×';
    closeBtn.style.cssText = `
        position: absolute;
        top: 0.5rem;
        right: 0.75rem;
        background: none;
        border: none;
        font-size: 1.5rem;
        cursor: pointer;
        color: inherit;
        opacity: 0.7;
    `;

    closeBtn.addEventListener('click', () => {
        message.style.opacity = '0';
        setTimeout(() => message.remove(), 300);
    });

    message.style.position = 'relative';
    message.appendChild(closeBtn);
}

/**
 * Basic form validation
 */
function initFormValidation() {
    const forms = document.querySelectorAll('form');

    forms.forEach(form => {
        form.addEventListener('submit', function (e) {
            if (!validateForm(form)) {
                e.preventDefault();
            }
        });

        // Real-time validation
        const inputs = form.querySelectorAll('.form__input');
        inputs.forEach(input => {
            input.addEventListener('blur', () => validateField(input));
            input.addEventListener('input', () => clearFieldError(input));
        });
    });
}

/**
 * Validate entire form
 */
function validateForm(form) {
    const inputs = form.querySelectorAll('.form__input[required]');
    let isValid = true;

    inputs.forEach(input => {
        if (!validateField(input)) {
            isValid = false;
        }
    });

    // Password confirmation check
    const password = form.querySelector('input[name="password"]');
    const passwordConfirm = form.querySelector('input[name="password_confirm"]');

    if (password && passwordConfirm) {
        if (password.value !== passwordConfirm.value) {
            showFieldError(passwordConfirm, 'Пароли не совпадают');
            isValid = false;
        }
    }

    return isValid;
}

/**
 * Validate individual field
 */
function validateField(input) {
    const value = input.value.trim();
    const type = input.type;
    let isValid = true;
    let errorMessage = '';

    // Required field check
    if (input.required && !value) {
        errorMessage = 'Это поле обязательно для заполнения';
        isValid = false;
    }

    // Email validation
    else if (type === 'email' && value) {
        const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
        if (!emailRegex.test(value)) {
            errorMessage = 'Введите корректный email адрес';
            isValid = false;
        }
    }

    // Phone validation (простая проверка)
    else if (input.name === 'phone' && value) {
        const phoneRegex = /^[\+]?[0-9\s\-\(\)]{10,}$/;
        if (!phoneRegex.test(value)) {
            errorMessage = 'Введите корректный номер телефона';
            isValid = false;
        }
    }

    // Password validation
    else if (type === 'password' && value) {
        if (value.length < 8) {
            errorMessage = 'Пароль должен содержать минимум 8 символов';
            isValid = false;
        }
    }

    if (!isValid) {
        showFieldError(input, errorMessage);
    } else {
        clearFieldError(input);
    }

    return isValid;
}

/**
 * Show field error
 */
function showFieldError(input, message) {
    input.classList.add('form__input--error');

    // Remove existing error
    const existingError = input.parentNode.querySelector('.form__error');
    if (existingError) {
        existingError.remove();
    }

    // Add new error
    const errorDiv = document.createElement('div');
    errorDiv.className = 'form__error';
    errorDiv.textContent = message;
    input.parentNode.appendChild(errorDiv);
}

/**
 * Clear field error
 */
function clearFieldError(input) {
    input.classList.remove('form__input--error');
    const error = input.parentNode.querySelector('.form__error');
    if (error) {
        error.remove();
    }
}

/**
 * Mobile menu (placeholder for future)
 */
function initMobileMenu() {
    // Пока пусто, можешь добавить позже
}

/**
 * Utility: Show loading state on buttons
 */
function showButtonLoading(button) {
    button.disabled = true;
    const originalText = button.textContent;
    button.innerHTML = '<span class="loading"></span> Загрузка...';

    return () => {
        button.disabled = false;
        button.textContent = originalText;
    };
}

/**
 * Utility: Format phone number input
 */
function formatPhoneInput(input) {
    input.addEventListener('input', function (e) {
        let value = e.target.value.replace(/\D/g, '');

        if (value.length > 0) {
            if (value[0] === '8') {
                value = '7' + value.slice(1);
            }
            if (value[0] === '7') {
                value = value.slice(0, 11);
                value = '+7 (' + value.slice(1, 4) + ') ' +
                    value.slice(4, 7) + '-' +
                    value.slice(7, 9) + '-' +
                    value.slice(9, 11);
            }
        }

        e.target.value = value;
    });
}

document.addEventListener('DOMContentLoaded', function () {
    const phoneInputs = document.querySelectorAll('input[name="phone"]');
    phoneInputs.forEach(formatPhoneInput);
});