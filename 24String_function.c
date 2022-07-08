#include <stdio.h>

int main() {
    char info[100];
    char dept[] = "HR";
    int emp = 75;
    sprintf(info, "The %s dept has %d emppoyees.", dept, emp);
    printf("%s\n", info);
    return 0;
}

void() {
    char info[] = "snoqualmie WA 13190";
    char city[50];
    char state[50];
    int population;
    sscanf(info, "%s %s %d", city, state, &population);
    printf("%d people live in %s, %s.", population, city, state);
}