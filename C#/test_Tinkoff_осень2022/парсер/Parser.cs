// https://www.youtube.com/watch?v=ot-IMy_4ENg&list=PL81SFGIHr5IJFsoWX0qTeQ9_-MFBE552C&index=1

public class Parser
{
    public static void Main() {
        string input = "2 + 2";
        List<Token> tokens = new Lexer(input).tokenize();
        foreach (Token token in tokens)
        {
            Console.WriteLine(token.getType());
        }
    } 
}