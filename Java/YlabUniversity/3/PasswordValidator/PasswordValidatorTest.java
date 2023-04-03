package PasswordValidator;

import java.util.Scanner;

public class PasswordValidatorTest {

    public static void main(String[] args) {

        try (Scanner scan = new Scanner(System.in)) {

            System.out.println(PasswordValidator.input("i_love_java",
                    "vasya_123",
                    "vasya_123"));

            System.out.println(PasswordValidator.input("vasya_12",
                    "i_love_java",
                    "vasya_123"));
        } 
    }
}