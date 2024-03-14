#include <bits/stdc++.h>

using namespace std;

int category[1005];
set<int> last_of;
vector<int> letters_in[30];
int n;
char s[1005];

void find_category(int i)
{
    int cur_cat = last_of.size();

    cout << "? 2 1 " << i << endl;
    //printf("? 2 1 %d\n", i);
    fflush(stdout);

    int new_cat;
    cin >> new_cat;
    // scanf("%d", &new_cat);

    if (new_cat > cur_cat) {
        category[i] = cur_cat + 1;
        last_of.insert(i);
        letters_in[cur_cat + 1].push_back(i);
    }
    else {
        int expect = cur_cat - 1;
        for (auto j : last_of) {
            if (expect == 0) {
                category[i] = category[j];
                letters_in[category[i]].push_back(i);
                last_of.insert(i);
                last_of.erase(j);
                break;
            }
            //printf("? 2 %d %d\n",j + 1, i);
            cout << "? 2 " <<  j + 1 << " " << i << endl;
            fflush(stdout);

            //int new_cat;
            cin >> new_cat;
            //scanf("%d", &new_cat);
            if (new_cat > expect) {
                category[i] = category[j];
                letters_in[category[i]].push_back(j);
                last_of.insert(i);
                last_of.erase(j);
                break;
            }

            expect--;
        }
    }
}


int main(void)
{
    cin >> n;

    for (int i = 1; i <= n; i++)
        find_category(i);

    for (auto j : last_of) {
        cout << "? 1 " << j << endl;
        //printf("? 1 %d", j);
        fflush(stdout);

        char c;
        cin >> c;
        // char c = getchar();
        for (auto m: letters_in[category[j]]) {
            s[m] = c;
        }
        // getchar();
    }

    cout << "! ";
    // printf("! ");
    for (int i = 1; i <= n; i++) 
        cout << s[i];
        // printf("%c", s[i]);

    //printf("\n");
    cout << endl;
}