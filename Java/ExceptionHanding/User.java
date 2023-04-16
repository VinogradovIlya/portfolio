import java.math.BigInteger;
import java.time.LocalDate;
import java.util.NoSuchElementException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.management.RuntimeErrorException;

public class User {

    private String secondName;
    private String name;
    private String patronymic;

    private LocalDate dob;

    private BigInteger number;

    private char sex;

    public void setSecondName(String input) {
        try {
            Pattern pattern = Pattern.compile("^[a-zA-Zа-яА-Я]+$");
            Matcher matcher = pattern.matcher(input);
            if (!matcher.matches()) {
                throw new RuntimeException("фамилия содержит недопустимые символы");
            } else {
                this.secondName = input;
            }
        } catch (NoSuchElementException ex) {
            System.out.println("странная у него фамилия...");
        }
    }

    public String getSecondName() {
        return secondName;
    }

    public void setName(String name) {
        try {
            Pattern pattern = Pattern.compile("^[a-zA-Zа-яА-Я]+$");
            Matcher matcher = pattern.matcher(name);
            if (!matcher.matches()) {
                throw new RuntimeException("имя содержит недопустимые символы");
            }
            this.name = name;
        } catch (NoSuchElementException ex) {
            System.out.println("ошибка в имени");
        }
    }

    public String getName() {
        return name;
    }

    public void setPatronymic(String patronymic) {
        try {
            Pattern pattern = Pattern.compile("^[a-zA-Zа-яА-Я]+$");
            Matcher matcher = pattern.matcher(patronymic);
            if (!matcher.matches()) {
                throw new RuntimeException("отчество содержит недопустимые символы");
            }
            this.patronymic = patronymic;
        } catch (NoSuchElementException ex) {
            System.out.println("ошибка в отчестве");
        }
    }

    public String getPatronymic() {
        return patronymic;
    }

    public void setDob(LocalDate dob) {
        this.dob = dob;
    }

    public LocalDate getDob() {
        return dob;
    }

    public void setNumber(BigInteger number) {
        Pattern pattern = Pattern.compile("^[0-9]+$");
        Matcher matcher = pattern.matcher(number.toString());
        if (!matcher.matches()) {
            throw new RuntimeException("ошибка в символах номера телефона");
        }
        if (number.toString().length() != 11 | number.toString().isEmpty()) {
            throw new RuntimeException("ошибка в количестве символов номера телефона");
        }
        this.number = number;
    }

    public BigInteger getNumber() {
        return number;
    }

    public void setSex(char sex) {
        // в таком виде в любом случае выдает ошибку
        if (sex == 'm' || sex == 'M' || sex == 'f' || sex == 'F') {
            this.sex = sex;
        } else {
            throw new RuntimeException("ошибка в гендере работника");
        }
    }

    public char getSex() {
        return sex;
    }
}