#include <bits/stdc++.h>
#define MAXN (int)(10e5)
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> ii;

int n;
queue<int> q;
stack<int> s;
deque<int> d;

vector<ii> numsorted;
vector<int> numorder;

bool in_top_3(ii i)
{
    if (numsorted.size() > 0)
        if (numsorted[0] == i)
            return true;
    if (numsorted.size() > 1)
        if (numsorted[1] == i)
            return true;
    if (numsorted.size() > 2)
        if (numsorted[2] == i)
            return true;

    return false;
}

void print_top_3(void)
{
    int commandnum = 0;
    string commands = "";
    if (!s.empty()) {
        commands += " popStack";
        commandnum++;
    }
    if (!q.empty()) {
        commands += " popQueue";
        commandnum++;
    }
    if (!d.empty()) {
        commands += " popFront";
        commandnum++;
    }

    cout << commandnum << commands << endl;
}

void solve(void)
{
    for (int i = 0; i < numorder.size(); i++)
        numsorted.pb(mp(numorder[i], i));
    sort(numsorted.rbegin(), numsorted.rend());
    // reverse(numsorted.begin(), numsorted.end());
    string command;
    int i = 0;

    for (auto num : numorder) {
        command = "push";
        if (in_top_3(mp(num, i))) {
            if (s.empty()) {
                s.push(num);
                command += "Stack";
            }
            else if (q.empty()) {
                q.push(num);
                command += "Queue";
            }
            else {
                d.push_front(num);
                command += "Front";
            }
        }
        else {
            d.push_back(num);
            command += "Back";
        }

        cout << command << '\n';
        i++;
    }

    print_top_3();
    while (!q.empty())
        q.pop();
    while (!s.empty())
        s.pop();
    while (!d.empty())
        d.pop_back();
}

int main(void)
{
    scanf("%d", &n);
    int curnum;
    for (int i = 0; i < n; i++) {
        scanf("%d", &curnum);
        if (curnum != 0)
            numorder.pb(curnum);
        else {
            solve();
            numorder.clear();
            numsorted.clear();
        }
    }
    for (auto left : numorder)
        printf("pushStack\n");

    return 0;
}