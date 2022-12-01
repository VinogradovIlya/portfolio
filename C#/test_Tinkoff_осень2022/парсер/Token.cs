public class Token
{
    private string text; // для хранения названия переменных
    private TokenType type;

    public Token() {
    }

    public Token(TokenType type, string text) {
        this.type = type;
        this.text = text;
    }

    public TokenType getType() {
        return type;
    }

    public void setType(TokenType type) {
        this.type = type;
    }

    public TokenType getText() {
        return text;
    }

    public TokenType setText(string text) {
        this.text = text;
    }
}