package PasswordValidator;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class PasswordValidator {

    static boolean input(String login, String password, String confirmPassword) {

        try {
            Pattern pattern = Pattern.compile("^[a-zA-Z0-9_]+$");
            Matcher matcher = pattern.matcher(login);
            if (!matcher.matches()) {
                throw new WrongLoginException("Логин содержит недопустимые символы");
            }
            if (login.length() > 20) {
                throw new WrongLoginException("Логин слишком длинный");
            }

            matcher = pattern.matcher(confirmPassword);
            if (!matcher.matches()) {
                throw new WrongPasswordException("Пароль содержит недопустимые символы");
            }
            if (password.length() > 20) {
                throw new WrongPasswordException("Пароль слишком длинный");
            }

            if (!password.equals(confirmPassword)) {
                throw new WrongPasswordException("Пароль и подтверждение не совпадает");
            }
            return true;
        } catch (WrongLoginException e) {
            System.out.println(e.getMessage());
            return false;
        } catch (WrongPasswordException e) {
            System.out.println(e.getMessage());
            return false;
        }
    }
}