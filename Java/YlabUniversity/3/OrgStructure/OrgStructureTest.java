package OrgStructure;

import java.io.File;
import java.io.IOException;

public class OrgStructureTest {

    public static void main(String[] args) {
        File csvFile = new File("/Users/umpabook/portfolio/Java/YlabUniversity/3/OrgStructure/csvFile.csv");
        try {
            // Employee employee = new Employee();
            OrgStructureParserImpl orgStructParser = new OrgStructureParserImpl();
            Employee boss = orgStructParser.parseStructure(csvFile);
            boss.print();
            System.out.println();

            boss.setSubordinate(csvFile);
            boss.getSubordinate();
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}