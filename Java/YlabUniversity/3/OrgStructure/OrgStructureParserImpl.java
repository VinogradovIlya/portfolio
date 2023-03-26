package OrgStructure;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

/**
 * OrgStructureParserImpl
 */
public class OrgStructureParserImpl implements OrgStructureParser {

    public Employee parseStructure(File csvFile) throws IOException {
        try (BufferedReader reader = new BufferedReader(new FileReader(csvFile))) {

            String line = reader.readLine();
            while (line != null | !line.isEmpty()) {
                line = reader.readLine();
                String[] strArr = line.split(";");

                if (!strArr[1].isEmpty()) {
                    continue;
                } else {
                    Long id = Long.parseLong(strArr[0]);
                    String name = strArr[2];
                    String position = strArr[3];
                    Employee boss = new Employee(id, null, name, position);
                    return boss;
                }
            }
        } catch (IOException e) {
            System.out.println(e.getClass().getSimpleName());
        }
        return null;
    }

}