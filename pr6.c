#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char production[MAX][MAX];
char first[MAX][MAX];
char follow[MAX][MAX];
char table[MAX][MAX][MAX];

int count;
char nonterminals[MAX];

int nt_count=0;

int isNonTerminal(char c){
    if(c>='A' && c<='Z') return 1;
    return 0;
}

int getIndex(char c){
    for(int i=0;i<nt_count;i++){
        if(nonterminals[i]==c) return i;
    }
    return -1;
}

void addToSet(char *set, char val){
    for(int i=0;set[i]!='\0';i++){
        if(set[i]==val) return;
    }
    int len=strlen(set);
    set[len]=val;
    set[len+1]='\0';
}

void findFirst(char c){
    int idx=getIndex(c);

    for(int i=0;i<count;i++){
        if(production[i][0]==c){
            if(!isNonTerminal(production[i][2])){
                addToSet(first[idx], production[i][2]);
            }else{
                int j=2;
                while(production[i][j]!='\0'){
                    if(!isNonTerminal(production[i][j])){
                        addToSet(first[idx], production[i][j]);
                        break;
                    }
                    else{
                        int id=getIndex(production[i][j]);
                        findFirst(production[i][j]);

                        for(int k=0;first[id][k]!='\0';k++){
                            if(first[id][k]!='#')
                                addToSet(first[idx], first[id][k]);
                        }

                        int hasEpsilon=0;
                        for(int k=0;first[id][k]!='\0';k++){
                            if(first[id][k]=='#') hasEpsilon=1;
                        }

                        if(!hasEpsilon) break;
                        else j++;
                    }
                }
            }
        }
    }
}

void findFollow(char c){
    if(production[0][0]==c)
        addToSet(follow[getIndex(c)], '$');

    for(int i=0;i<count;i++){
        for(int j=2;production[i][j]!='\0';j++){
            if(production[i][j]==c){
                if(production[i][j+1]!='\0'){
                    if(!isNonTerminal(production[i][j+1])){
                        addToSet(follow[getIndex(c)], production[i][j+1]);
                    }else{
                        int id=getIndex(production[i][j+1]);
                        for(int k=0;first[id][k]!='\0';k++){
                            if(first[id][k]!='#')
                                addToSet(follow[getIndex(c)], first[id][k]);
                        }

                        int hasEpsilon=0;
                        for(int k=0;first[id][k]!='\0';k++){
                            if(first[id][k]=='#') hasEpsilon=1;
                        }

                        if(hasEpsilon && production[i][0]!=c){
                            findFollow(production[i][0]);
                            int id2=getIndex(production[i][0]);
                            for(int k=0;follow[id2][k]!='\0';k++){
                                addToSet(follow[getIndex(c)], follow[id2][k]);
                            }
                        }
                    }
                }else{
                    if(production[i][0]!=c){
                        findFollow(production[i][0]);
                        int id2=getIndex(production[i][0]);
                        for(int k=0;follow[id2][k]!='\0';k++){
                            addToSet(follow[getIndex(c)], follow[id2][k]);
                        }
                    }
                }
            }
        }
    }
}

void constructTable(){
    int conflict=0;

    for(int i=0;i<count;i++){
        char A=production[i][0];
        int row=getIndex(A);

        char rhs[MAX];
        strcpy(rhs, &production[i][2]);

        int epsilon=1;

        for(int j=0;rhs[j]!='\0';j++){
            if(!isNonTerminal(rhs[j])){
                epsilon=0;
                int col=rhs[j];
                if(table[row][col][0]!='\0'){
                    printf("\nConflict at [%c,%c]\n",A,rhs[j]);
                    conflict=1;
                }
                strcpy(table[row][col], production[i]);
                break;
            }else{
                int id=getIndex(rhs[j]);
                epsilon=0;
                for(int k=0;first[id][k]!='\0';k++){
                    if(first[id][k]!='#'){
                        int col=first[id][k];
                        if(table[row][col][0]!='\0'){
                            printf("\nConflict at [%c,%c]\n",A,first[id][k]);
                            conflict=1;
                        }
                        strcpy(table[row][col], production[i]);
                    }
                }

                int hasEps=0;
                for(int k=0;first[id][k]!='\0';k++){
                    if(first[id][k]=='#') hasEps=1;
                }

                if(hasEps) epsilon=1;
                else{ epsilon=0; break; }
            }
        }

        if(epsilon){
            for(int k=0;follow[row][k]!='\0';k++){
                int col=follow[row][k];
                if(table[row][col][0]!='\0'){
                    printf("\nFirst-Follow conflict at [%c,%c]\n",A,follow[row][k]);
                    conflict=1;
                }
                strcpy(table[row][col], production[i]);
            }
        }
    }

    if(conflict==0)
        printf("\nGrammar is LL(1). Predictive parser can be generated.\n");
    else
        printf("\nGrammar is NOT LL(1).\n");
}

int main(){
    printf("Enter number of productions: ");
    scanf("%d",&count);

    printf("Enter productions (Example: E=TR , use # for epsilon):\n");
    for(int i=0;i<count;i++){
        scanf("%s",production[i]);

        char nt=production[i][0];
        if(getIndex(nt)==-1){
            nonterminals[nt_count++]=nt;
        }
    }

    for(int i=0;i<nt_count;i++){
        first[i][0]='\0';
        follow[i][0]='\0';
    }

    for(int i=0;i<nt_count;i++)
        findFirst(nonterminals[i]);

    for(int i=0;i<nt_count;i++)
        findFollow(nonterminals[i]);

    printf("\nFIRST sets:\n");
    for(int i=0;i<nt_count;i++){
        printf("FIRST(%c) = { %s }\n",nonterminals[i],first[i]);
    }

    printf("\nFOLLOW sets:\n");
    for(int i=0;i<nt_count;i++){
        printf("FOLLOW(%c) = { %s }\n",nonterminals[i],follow[i]);
    }

    constructTable();

    printf("\nPredictive Parsing Table:\n");
    for(int i=0;i<nt_count;i++){
        for(int j=0;j<128;j++){
            if(table[i][j][0]!='\0'){
                printf("M[%c,%c] = %s\n",nonterminals[i],j,table[i][j]);
            }
        }
    }

    return 0;
}
