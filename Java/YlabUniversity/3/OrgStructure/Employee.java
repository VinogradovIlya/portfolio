package OrgStructure;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Employee {

    private Long id;
    private Long bossId;
    private String name;
    private String position;
    private Employee boss;
    private List<Employee> subordinate = new ArrayList<>();

    public Employee() {
    }

    public Employee(Long id, Long bossId, String name, String position) {
        setId(id);
        setBossId(bossId);
        setName(name);
        setPosition(position);
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public Long getBossId() {
        return bossId;
    }

    public void setBossId(Long bossId) {
        this.bossId = bossId;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPosition() {
        return position;
    }

    public void setPosition(String position) {
        this.position = position;
    }

    public Employee getBoss() {
        return boss;
    }

    public void setBoss(Employee boss) {
        this.boss = boss;
    }

    public List<Employee> getSubordinate() {
        for (Employee employee : subordinate) {
            employee.print();
        }
        return subordinate;
    }

    public void setSubordinate(File csvFile) {
        try (BufferedReader reader = new BufferedReader(new FileReader(csvFile))) {
            String line = reader.readLine();
            while (line != null) {
                Employee employee = new Employee();
                line = reader.readLine();

                String[] parameters = line.split(";");
                employee.setId(Long.parseLong(parameters[0]));
                if (parameters[1].isEmpty()) {
                    continue;
                }
                employee.setBossId(Long.parseLong(parameters[1]));
                employee.setName(parameters[2]);
                employee.setPosition(parameters[3]);
                subordinate.add(employee);
            }
            } catch (NullPointerException e) {
            System.out.println(e.getClass().getSimpleName());
        } catch (IOException e) {
            System.out.println(e.getStackTrace());
        }
    }

    public void print() {
        System.out.println(getId() + " " + getBossId() + " " + getName() + " " + getPosition());
    }
}