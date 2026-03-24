#include <stdio.h>
#include <string.h>
#define MAX 20
char grammar[MAX][MAX];
int n;
char first[MAX][MAX], follow[MAX][MAX];
int firstCount[MAX], followCount[MAX];
int isNonTerminal(char c) {
    return (c >= 'A' && c <= 'Z');
}
void addToSet(char set[MAX], int *count, char val) {
    for (int i = 0; i < *count; i++)
        if (set[i] == val)
            return;
    set[(*count)++] = val;
}
void findFirst(char c, int idx) {
    for (int i = 0; i < n; i++) {
        if (grammar[i][0] == c) {
            if (grammar[i][2] == '#') {
                addToSet(first[idx], &firstCount[idx], '#');
            } else {
                char next = grammar[i][2];
                if (!isNonTerminal(next)) {
                    addToSet(first[idx], &firstCount[idx], next);
                } else {
                    findFirst(next, next - 'A');
                    for (int k = 0; k < firstCount[next - 'A']; k++)
                        addToSet(first[idx], &firstCount[idx], first[next - 'A'][k]);
                }}}}}
void findFollow() {
    addToSet(follow[grammar[0][0] - 'A'], &followCount[grammar[0][0] - 'A'], '$');

    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < n; i++) {
            char A = grammar[i][0];
            for (int j = 2; j < strlen(grammar[i]); j++) {
                char B = grammar[i][j];
                if (isNonTerminal(B)) {
                    if (grammar[i][j + 1] != '\0') {
                        char beta = grammar[i][j + 1];
                        if (!isNonTerminal(beta)) {
                            addToSet(follow[B - 'A'], &followCount[B - 'A'], beta);
                        } else {
                            for (int k = 0; k < firstCount[beta - 'A']; k++) {
                                if (first[beta - 'A'][k] != '#')
                                    addToSet(follow[B - 'A'], &followCount[B - 'A'], first[beta - 'A'][k]);
                            }
                        }
                    } else {
                        for (int k = 0; k < followCount[A - 'A']; k++)
                            addToSet(follow[B - 'A'], &followCount[B - 'A'], follow[A - 'A'][k]);
                    }}}}}}
int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("Enter productions (Example: E=TR or E=#):\n");
    for (int i = 0; i < n; i++)
        scanf("%s", grammar[i]);
    for (int i = 0; i < n; i++)
        findFirst(grammar[i][0], grammar[i][0] - 'A');
    findFollow();
    printf("\nNON-TERMINAL\tFIRST\t\tFOLLOW\n");
    for (int i = 0; i < n; i++) {
        char nt = grammar[i][0];
        printf("%c\t\t{ ", nt);
        for (int j = 0; j < firstCount[nt - 'A']; j++)
            printf("%c ", first[nt - 'A'][j]);
        printf("}\t{ ");
        for (int j = 0; j < followCount[nt - 'A']; j++)
            printf("%c ", follow[nt - 'A'][j]);
        printf("}\n");
    }
    return 0;
}
