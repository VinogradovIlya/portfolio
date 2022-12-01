int CountRep(string text, string sub ) {
    int count = 0;
    int pos = 0;
    while (true) {
        pos = text.IndexOf(sub, pos);
        if (pos != -1) {
            count++;
            pos++;
        } else {
            break;
        }
    }
    return count;
}
 Console.WriteLine("abc:" + CountRep("abc, oiejf, kojre, oeijrf, ekrj", "abc")); // ?
