class Parser
{
    public static void Main() {
        string input = "2=2";
        List<Token> tokens = new Lexer(input).tokenize();
        foreach (Token token in tokens)
        {
            Console.WriteLine(token.getType());
        }
    } 
}