package OrgStructure;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Employee implements OrgStructureParser {

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
        return subordinate;
    }

    public Employee parseStructure(File csvFile) throws IOException {
        List<String> str = new ArrayList<>();

        try (BufferedReader reader = new BufferedReader(new FileReader(csvFile))) {

            String line = reader.readLine(); // заполнение коллекции
            while (line != null) {
                line = reader.readLine();
                str.add(line);
            }

            for (String string : str) { // считывание строки и превращение в работника(employee)
                String[] strArr = string.split(";");
                Long id = Long.parseLong(strArr[0]);
                if (!strArr[1].isEmpty()) {
                    Long bossId = Long.parseLong(strArr[1]);
                } else {
                    String name = strArr[2];
                    String position = strArr[3];
                    Employee boss = new Employee(id, null, name, position);
                    return boss;
                }

                // Employee employee = new Employee(id, bossId, name, position);
                // subordinate.add(employee);
                // return employee;
            }
        } catch (IOException e) {
            System.out.println(e.getClass().getSimpleName());
        }
        return null;
    }

    public void printEmployee(Employee employee) {
        System.out.println(employee.getId() + " "
                + employee.getBossId() + " "
                + employee.getName() + " "
                + employee.getPosition());
    }
}