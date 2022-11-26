public class Lexer
{
    private string input;
    private List<Token> tokens;
    private int pos, length;

    public Lexer(string input) {
        this.input = input;

        tokens = new ArrayList<>();
    }

    public List<Token> tokenize() {
        while (pos < length) {
            char current = peek(0);
            if (character.isDigit(current)) tokenizeNumber();
            else if (current == '=') {
                tokenizeOperator();
            } else {
                next();
            }
        }
        return tokens;
    }

    private void tokenizeNumber(){
        stringBuilder buffer = new stringBuilder();
        char current = peek(0);
        while (Character.isDigit(current)) {
            buffer.append(current);
            current = next();
        }
        addToken(TokenType.NUMBER, buffer.toString());
    }

    private void tokenizeOperator(){
        int position = peek(0);
        next();
    }

    private char next() {
        pos++;
        return peek(0);
    }

    private char peek(int relativePosition) {
        int position = pos + relativePosition;
        if (position >= length) return '\0';
        return input.charAt(position);
    }

    private void addToken(TokenType type) {
        addToken(type, "");
    }

    private void addToken(TokenType type, string text) {
        tokens.add(new Token(type, text));
    }
}