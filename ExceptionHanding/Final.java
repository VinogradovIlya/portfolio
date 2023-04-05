import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Final {

    public static void main(String[] args) {

        String input = null;
        List<User> users = new ArrayList<>();

        try (Scanner scan = new Scanner(System.in)) {
            System.out.println("введите данные (Ф И О dd.mm.yyyy НомерТелефона Пол)");
            while (!(input = scan.nextLine()).isEmpty()) {
                String[] information = input.split(" ");

                User user = new User();
                user.setSecondName(information[0]);
                user.setName(information[1]);
                user.setPatronymic(information[2]);

                DateTimeFormatter format = DateTimeFormatter.ofPattern("dd.MM.yyyy");
                LocalDate date = LocalDate.parse(information[3], format);
                user.setDob(date);

                user.setNumber(new BigInteger(information[4]));

                user.setSex(information[5].toCharArray()[0]);

                users.add(user);
            }
        } catch (DateTimeParseException dtpEx) {
            System.out.println("ошибка в дате рождения");
        } catch (NumberFormatException numFormEx) {
            System.out.println("поле телефон пустое");
        } finally {
            try (PrintWriter writer = new PrintWriter(new FileWriter("catalog.txt"))) {
                for (User user : users) {
                    writer.print("<" + user.getSecondName() + ">");
                    writer.print("<" + user.getName() + ">");
                    writer.print("<" + user.getPatronymic() + ">");
                    writer.print("<" + user.getDob() + ">");
                    writer.print("<" + user.getNumber() + ">");
                    writer.print("<" + user.getSex() + ">\n");
                }
            } catch (IOException ioEx) {
                ioEx.printStackTrace();
            }
        }
    }
}