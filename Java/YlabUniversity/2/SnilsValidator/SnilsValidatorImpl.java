/**
 * SnilsValidatorImpl
 */
public class SnilsValidatorImpl implements SnilsValidator{

    public boolean validate(String snils) {
        String snilsDigits = snils.replaceAll("[^\\d]", "");
        if (snilsDigits.length() != 11) return false;

        int controlSum = 0;
        for (int i = 0; i < 9; i++) {
            int digit = Character.getNumericValue(snilsDigits.charAt(i));
            controlSum += digit*(9-i);
        }

        int calculatedControlNumber = 0;
        if (controlSum < 100) calculatedControlNumber = 0;
        else if (controlSum == 100 || controlSum == 101) calculatedControlNumber = 0;
        else calculatedControlNumber = controlSum % 101;

        int controlNumber = Integer.parseInt(snilsDigits.substring(9));
        return calculatedControlNumber == controlNumber;
    }
}