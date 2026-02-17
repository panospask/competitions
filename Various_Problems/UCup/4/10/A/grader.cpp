#include <bits/stdc++.h>
#include "grader.hpp"

using namespace Solve;

#define ACTIONS_LIMIT 35000

#define checkRange(val, minn, maks, mes) if(val < minn || val > maks) I.end(0, string(mes) + ". Value " + to_string(val) + " out of range " + to_string(minn) + " to " + to_string(maks));

using namespace std;

int n, res, k, actions;
queue <int> q;
map <int, int> mapa;

int main(int argc, char* argv[]) {
    Interactor& I = Interactor::create(argc, argv);
    InStream& reader = I.reader(0);
    OutStream& writer = I.writer(0);
    std::ifstream& input = I.test_reader();


    input >> n;
    vector<int> V(n + 1);
    vector<int> color(n+1);
    vector<int> num(n+1);
    for(int i = 1; i <= n; i++)
    {
        input >> V[i];
        for(int j = i; j > 0 ;j--){
            if(V[i] == V[j]){
                color[i] = j;
            }
        }
    }
    writer << n << "\n" << flush;

    char c;
    while(true)
    {
        reader >> c;
        string s{c};
        if(c != '+' && c != '-' && c != '!')
            I.end(0, "Wrong character, found '" + s + "', should be +, - or !");
        if(c == '+')
        {
            int a;
            reader >> a;
            checkRange(a, 1, n, "Expected mineral index");
            int col = color[a];
            num[col]++;
            q.push(a);
            if(num[col] == 1)
                res++;
            writer << res << "\n" << flush;
            actions++;
        }
        else if(c == '-')
        {
            if(!q.empty()){
                int col = color[q.front()];
                q.pop();
                num[col]--;
                if(num[col] == 0)
                    res--;
            }
            writer << res << "\n" << flush;
            actions++;
        }
        else if(c == '!')
        {
            int sum = 0;
            int class_num;
            reader >> class_num;
            checkRange(class_num, 1, n, "Expected the number of different kinds");
            vector<int> ans(n + 1);
            for(int i = 1; i <= class_num; i++)
            {
                int card, pos;
                reader >> card;
                checkRange(card, 1, n, "Expected the cardinality of type");
                sum += card;

                for(int j = 0; j < card; j++)
                {
                    reader >> pos;
                    checkRange(pos, 1, n, "Expected mineral index");
                    if(ans[pos]){
                        I.end(0, "Mineral " + to_string(pos) + " appears too many times in the answer.");
                    }
                    ans[pos] = i;
                }
            }
            if(sum != n)
            {
                I.end(0, "Too few elements appear in the output");
            }
            for(int i = 1; i <= n; i++){
                for(int j = 1; j <= n; j++){
                    if(ans[i] == ans[j] && ! (color[i] == color[j]) ){
                        I.end(0, "Minerals " + to_string(i) + " and " + to_string(j) + " reported to have the same kind, which is false");
                    }
                    if(!(ans[i] == ans[j]) && color[i] == color[j]){
                        I.end(0, "Minerals " + to_string(i) + " and " + to_string(j) + " reported to have different kinds, which is false");
                    }
                }
            }

            I.end(100, "OK, moves = " + to_string(actions));
        }
        if(actions > ACTIONS_LIMIT)
            I.end(0, "Limit of " + to_string(ACTIONS_LIMIT) + " actions exceeded");
    }
    return 0;
}
