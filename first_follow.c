#include <stdio.h>
#include <string.h>

#define MAX 20

char prod[MAX][MAX];
char first[26][MAX], follow[26][MAX];
int fcnt[26], flcnt[26];
int n;

int isNT(char c) {
    return c >= 'A' && c <= 'Z';
}

void add(char s[MAX], int *cnt, char c) {
    for (int i = 0; i < *cnt; i++)
        if (s[i] == c) return;
    s[(*cnt)++] = c;
}

void FIRST(char c) {
    int idx = c - 'A';
    for (int i = 0; i < n; i++) {
        if (prod[i][0] == c) {
            char x = prod[i][2];
            if (x == '#') add(first[idx], &fcnt[idx], '#');
            else if (!isNT(x)) add(first[idx], &fcnt[idx], x);
            else {
                FIRST(x);
                for (int k = 0; k < fcnt[x - 'A']; k++)
                    add(first[idx], &fcnt[idx], first[x - 'A'][k]);
            }
        }
    }
}

void FOLLOW(char start) {
    add(follow[start - 'A'], &flcnt[start - 'A'], '$');

    for (int i = 0; i < n; i++) {
        for (int j = 2; j < strlen(prod[i]); j++) {
            if (isNT(prod[i][j])) {
                if (prod[i][j + 1] != '\0')
                    add(follow[prod[i][j] - 'A'],
                        &flcnt[prod[i][j] - 'A'],
                        prod[i][j + 1]);
            }
        }
    }
}int main() {
    char NT, terminal, prod[20];

    printf("Enter Non-Terminal: ");
    scanf(" %c", &NT);

    printf("Enter Terminal: ");
    scanf(" %c", &terminal);

    printf("Enter Production: ");
    scanf("%s", prod);

    printf("\nParsing Table Entry:\n");
    printf("M[%c , %c] = %s\n", NT, terminal, prod);

    return 0;
}