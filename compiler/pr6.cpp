#include <bits/stdc++.h>
using namespace std;

/* ================= DATA STRUCTURES ================= */

struct Item {
    string lhs;
    string rhs;
    int dot;

    bool operator<(const Item &o) const {
        if(lhs!=o.lhs) return lhs<o.lhs;
        if(rhs!=o.rhs) return rhs<o.rhs;
        return dot<o.dot;
    }
    bool operator==(const Item &o) const {
        return lhs==o.lhs && rhs==o.rhs && dot==o.dot;
    }
};

map<string, vector<string>> grammar;
vector<set<Item>> states;
map<pair<int,string>, int> GOTO_TABLE;
map<pair<int,string>, string> ACTION_TABLE;
set<string> terminals, nonTerminals;
string startSymbol;

int shiftReduceConflicts = 0;
int reduceReduceConflicts = 0;

/* ================= CLOSURE ================= */

set<Item> closure(set<Item> I){
    bool changed=true;
    while(changed){
        changed=false;
        for(auto item : vector<Item>(I.begin(), I.end())){
            if(item.dot < item.rhs.size()){
                string B(1,item.rhs[item.dot]);
                if(nonTerminals.count(B)){
                    for(auto prod : grammar[B]){
                        Item newItem={B,prod,0};
                        if(!I.count(newItem)){
                            I.insert(newItem);
                            changed=true;
                        }
                    }
                }
            }
        }
    }
    return I;
}

/* ================= GOTO ================= */

set<Item> gotoSet(set<Item> I, string X){
    set<Item> J;
    for(auto item:I){
        if(item.dot<item.rhs.size()){
            string sym(1,item.rhs[item.dot]);
            if(sym==X){
                item.dot++;
                J.insert(item);
            }
        }
    }
    return closure(J);
}

/* ================= BUILD STATES ================= */

void buildStates(){
    states.clear();
    set<Item> start;
    Item startItem={startSymbol+"'", startSymbol,0};
    grammar[startSymbol+"'"].push_back(startSymbol);
    start.insert(startItem);
    start=closure(start);
    states.push_back(start);

    for(int i=0;i<states.size();i++){
        set<string> symbols;
        for(auto item:states[i])
            if(item.dot<item.rhs.size())
                symbols.insert(string(1,item.rhs[item.dot]));

        for(auto X:symbols){
            set<Item> J=gotoSet(states[i],X);
            if(J.empty()) continue;

            bool exists=false;
            int index=0;
            for(int k=0;k<states.size();k++)
                if(states[k]==J){ exists=true; index=k; break; }

            if(!exists){
                states.push_back(J);
                index=states.size()-1;
            }
            GOTO_TABLE[{i,X}]=index;
        }
    }
}

/* ================= BUILD TABLE ================= */

void buildTable(){
    shiftReduceConflicts=0;
    reduceReduceConflicts=0;

    for(int i=0;i<states.size();i++){
        for(auto item:states[i]){
            if(item.dot<item.rhs.size()){
                string a(1,item.rhs[item.dot]);
                if(terminals.count(a)){
                    int j=GOTO_TABLE[{i,a}];
                    if(ACTION_TABLE.count({i,a}))
                        shiftReduceConflicts++;
                    ACTION_TABLE[{i,a}]="S"+to_string(j);
                }
            }else{
                if(item.lhs==startSymbol+"'"){
                    ACTION_TABLE[{i,"$"}]="ACC";
                }else{
                    for(auto t:terminals){
                        if(ACTION_TABLE.count({i,t}))
                            reduceReduceConflicts++;
                        ACTION_TABLE[{i,t}]="R "+item.lhs+"->"+item.rhs;
                    }
                }
            }
        }
    }
}

/* ================= LOAD GRAMMAR ================= */

void loadGrammar(vector<string> prods){
    grammar.clear();
    terminals.clear();
    nonTerminals.clear();
    states.clear();
    GOTO_TABLE.clear();
    ACTION_TABLE.clear();

    for(auto prod:prods){
        int pos=prod.find("->");
        string lhs=prod.substr(0,pos);
        string rhs=prod.substr(pos+2);

        grammar[lhs].push_back(rhs);
        nonTerminals.insert(lhs);

        for(char c:rhs){
            if(isupper(c))
                nonTerminals.insert(string(1,c));
            else if(c!='#')
                terminals.insert(string(1,c));
        }
    }
    terminals.insert("$");
    startSymbol=prods[0].substr(0,1);
}

/* ================= MAIN ================= */

int main(){

    cout<<"=== Grammar A (Operator Precedence) ===\n";
    loadGrammar({"E->E+T","E->T","T->i"});
    buildStates();
    buildTable();
    cout<<"Shift-Reduce Conflicts: "<<shiftReduceConflicts<<endl;
    cout<<"Reduce-Reduce Conflicts: "<<reduceReduceConflicts<<endl;

    cout<<"\n=== Grammar B (Nullable + Indirect Recursion) ===\n";
    loadGrammar({"S->Aa","A->Sb","A->#"});
    buildStates();
    buildTable();
    cout<<"Shift-Reduce Conflicts: "<<shiftReduceConflicts<<endl;
    cout<<"Reduce-Reduce Conflicts: "<<reduceReduceConflicts<<endl;

    return 0;
}