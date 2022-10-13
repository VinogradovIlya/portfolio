Console.Clear();
Console.WriteLine("1 2 3 == 3 2 1?");

int n = Convert.ToInt32(Console.ReadLine());
string name = string.Empty;
string str = string.Empty;
string[] team = new string[3];
for (int i = 0; i < n; i++) {
    name = Console.ReadLine();
    team[i] = name.ToUpper(); // ставит все буквы в верхний регистр (ToLower в нижний)
    str = str + team[i] + ' ';
}

/*
1 2 3
------------
1 3 2
3 2 1
3 1 2
2 1 3
2 3 1
*/

int result = 0;

// суть метода: если команда совпадает (какая команда?) с тремя словами из строчки, то max++
void Proverka(string text, string sub) {
    string[] allTeams = str.Split(' ');
    // идет по командам
    for (int i = 0; i < n; i++) {
        //вариации
        string teamVersion1 = allTeams[i+0] + ' ' + allTeams[i+1] + ' ' + allTeams[i+2];
        string teamVersion2 = allTeams[i+0] + ' ' + allTeams[i+2] + ' ' + allTeams[i+1];
        string teamVersion3 = allTeams[i+1] + ' ' + allTeams[i+0] + ' ' + allTeams[i+2];
        string teamVersion4 = allTeams[i+1] + ' ' + allTeams[i+2] + ' ' + allTeams[i+0];
        string teamVersion5 = allTeams[i+2] + ' ' + allTeams[i+1] + ' ' + allTeams[i+0];
        string teamVersion6 = allTeams[i+2] + ' ' + allTeams[i+0] + ' ' + allTeams[i+1];
        if (team[i] == teamVersion1) max++;
        if (team[i] == teamVersion2) max++;
        if (team[i] == teamVersion3) max++;
        if (team[i] == teamVersion4) max++;
        if (team[i] == teamVersion5) max++;
        if (team[i] == teamVersion6) max++;
    }
}