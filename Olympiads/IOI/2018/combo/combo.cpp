#include "combo.h"
#include <vector>
#define pb push_back

using namespace std;

int N;
string res;

string letters;
char impossible;

void push_res(string& q)
{
    for (auto c : res)
        q.pb(c);
}

string guess_sequence(int n) {
    N = n;

    letters = "ABXY";
    // Find the first one via b.s and erase it from letters
    int pos = 0;
    if (press(string(letters.begin(), letters.begin() + 2)) == 0)
        pos = 2;
    if (press(string(letters.begin() + pos, letters.begin() + pos + 1)) == 0)
        pos++;

    impossible = letters[pos];
    res.pb(letters[pos]);
    letters.erase(letters.begin() + pos);

    if (N == 1)
        return res;

    for (int i = 1; i < N - 1; i++) {
        string q;
        push_res(q);
        q.pb(letters[0]);
        q.pb(impossible);

        for (int i = 0; i < 3; i++) {
            push_res(q);
            q.pb(letters[1]);
            q.pb(letters[i]);
        }

        int moved = press(q) - i;
        if (moved == 0) {
            res.pb(letters[2]);
        }
        else if (moved == 1) {
            res.pb(letters[0]);
        }
        else {
            res.pb(letters[1]);
        }
    }

    // Find the last in 2 moves
    bool found = false;
    for (int i = 0; i < 2; i++) {
        res.pb(letters[i]);
        if (press(res) == N) {
            found = true;
            break;
        }
        res.pop_back();
    }

    if (!found)
        res.pb(letters[2]);

    return res;
}
