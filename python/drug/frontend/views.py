# from django.shortcuts import render, redirect
# from django.contrib import messages
# from .services.api_client import APIClient

# SESSION_TOKEN_KEY = 'api_token'


# def register_view(request):
#     if request.method == "POST":
#         data = {
#             "first_name": request.POST.get("first_name"),
#             "surname": request.POST.get("surname"),
#             "patronimic": request.POST.get("patronimic"),
#             "email": request.POST.get("email"),
#             "phone": request.POST.get("phone"),
#             "password": request.POST.get("password"),
#             "password_confirm": request.POST.get("password_confirm"),
#         }

#         if not all([data['email'], data['password'], data['password_confirm']]):
#             messages.error(request, "Заполните все обязательные поля")
#             return render(request, "web/register.html", {'data': data})

#         if data['password'] != data['password_confirm']:
#             messages.error(request, "Пароли не совпадают")
#             return render(request, "web/register.html", {'data': data})

#         api_client = APIClient()
#         response = api_client.register(data)

#         if response.status_code == 201:
#             login_resp = api_client.login(data['email'], data['password'])
#             if login_resp.status_code == 200:
#                 request.session[SESSION_TOKEN_KEY] = login_resp.json().get(
#                     "token")
#                 messages.success(
#                     request, "Регистрация и вход выполнены успешно!")
#                 return redirect("web:profile-view")
#             else:
#                 messages.error(
#                     request, "Регистрация прошла, но автоматический вход не удался. Попробуйте войти вручную.")
#                 return redirect("web:login-view")
#         else:
#             # Обработка ошибок API
#             try:
#                 errors = response.json()
#                 if isinstance(errors, dict):
#                     for field, error_list in errors.items():
#                         if isinstance(error_list, list):
#                             for error in error_list:
#                                 messages.error(request, f"{field}: {error}")
#                         else:
#                             messages.error(request, f"{field}: {error_list}")
#                 else:
#                     messages.error(request, str(errors))
#             except:
#                 messages.error(
#                     request, f"Ошибка регистрации (код {response.status_code})")

#             return render(request, "web/register.html", {'data': data})

#     return render(request, "web/register.html")


# def login_view(request):
#     if request.method == "POST":
#         email = request.POST.get("email")
#         password = request.POST.get("password")

#         if not email or not password:
#             messages.error(request, "Введите email и пароль")
#             return render(request, "web/login.html", {'email': email})

#         api_client = APIClient()
#         response = api_client.login(email, password)

#         if response.status_code == 200:
#             token = response.json().get("token")
#             if token:
#                 request.session[SESSION_TOKEN_KEY] = token
#                 messages.success(request, "Успешный вход!")
#                 return redirect("web:profile-view")
#             else:
#                 messages.error(
#                     request, "Не удалось получить токен аутентификации")
#         else:
#             try:
#                 error_data = response.json()
#                 error_message = error_data.get("error", {})
#                 if isinstance(error_message, dict):
#                     for field, errors in error_message.items():
#                         if isinstance(errors, list):
#                             messages.error(
#                                 request, f"{field}: {', '.join(errors)}")
#                         else:
#                             messages.error(request, f"{field}: {errors}")
#                 else:
#                     messages.error(request, "Неверный email или пароль")
#             except:
#                 messages.error(request, "Ошибка входа. Проверьте данные.")

#         return render(request, "web/login.html", {'email': email})

#     return render(request, "web/login.html")


# def profile_view(request):
#     """Страница профиля пользователя"""
#     token = request.session.get(SESSION_TOKEN_KEY)
#     if not token:
#         messages.info(
#             request, "Для доступа к профилю необходимо войти в систему")
#         return redirect("web:login-view")

#     api_client = APIClient(token)
#     profile = api_client.get_profile()

#     if profile:
#         return render(request, "web/profile.html", {"profile": profile})
#     else:
#         messages.error(
#             request, "Не удалось загрузить профиль. Возможно, сессия истекла.")
#         request.session.pop(SESSION_TOKEN_KEY, None)
#         return redirect("web:login-view")


# def logout_view(request):
#     """Выход из системы"""
#     token = request.session.get(SESSION_TOKEN_KEY)

#     if token:
#         api_client = APIClient(token)
#         try:
#             api_client.logout()
#         except:
#             pass

#     # Очищаем сессию
#     request.session.pop(SESSION_TOKEN_KEY, None)
#     messages.success(request, "Вы успешно вышли из системы")
#     return redirect("web:login-view")
