package OrgStructure;

import java.io.File;
import java.io.IOException;

public class OrgStructureTest {

    public static void main(String[] args) {
        File csvFile = new File("/Users/umpabook/portfolio/Java/YlabUniversity/3/OrgStructure/csvFile.csv");
        try {
            Employee employee = new Employee();
            Employee boss = employee.parseStructure(csvFile);
            employee.printEmployee(boss);
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}