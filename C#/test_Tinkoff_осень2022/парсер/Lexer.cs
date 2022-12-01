public class Lexer
{
    private string input;
    private List<Token> tokens;
    private int pos, length;

    private static string OPERATOR_CHARS = "+-*/";
    private static TokenType[] OPERATOR_TOKENS = {
        TokenType.PLUS, TokenType.MINUS, 
        TokenType.STAR, TokenType.SLASH
    };

    public Lexer(string input) {
        this.input = input;
        length = input.Length;

        tokens = new ArrayList<>();
    }

    public List<Token> tokenize() {
        while (pos < length) {
            char current = peek(0);
            if (char.isDigit(current)) tokenizeNumber();
            else if (OPERATOR_CHARS.IndexOf(current) != -1) {
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
        int position = OPERATOR_CHARS.IndexOf(peek(0));
        addToken(OPERATOR_TOKENS[position]);
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