/***********************

Ввод
thats=zero 
a=10 
ten=a 
aboba=ten 
ten=-10
{
b=a
a=1337
c=a
{
d=a 
e=aboba
}
}
lol=a

Вывод
0
10
10
10
1337
1337
10
10


Environment.Exit(0);

https://www.youtube.com/watch?v=ot-IMy_4ENg&list=PL81SFGIHr5IJFsoWX0qTeQ9_-MFBE552C&index=1


***********************/

public class Program
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
