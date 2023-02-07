#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

map<int, string> num_to_cow;
map<string, int> cow_to_num;
int n;
vector<int> beside[8];
bool used[8];
vector<int> cur_order;

void init_cows(void)
{
    cow_to_num["Bessie"] = 3;
    cow_to_num["Buttercup"] = 6;
    cow_to_num["Belinda"] = 1;
    cow_to_num["Beatrice"] = 0;
    cow_to_num["Bella"] = 2;
    cow_to_num["Blue"] = 5;
    cow_to_num["Betsy"] = 4;
    cow_to_num["Sue"] = 7;

    num_to_cow[3] = "Bessie";
    num_to_cow[6] = "Buttercup";
    num_to_cow[1] = "Belinda";
    num_to_cow[0] = "Beatrice";
    num_to_cow[2] = "Bella";
    num_to_cow[5] = "Blue";
    num_to_cow[4] = "Betsy";
    num_to_cow[7] = "Sue";
}

bool check_pos_to_place(int i)
{
    int waiting = 0;
    for (auto neigh : beside[i]) {
        if (!used[neigh]) 
            waiting++;
        else if (cur_order.back() != neigh)
            return false;

        if (waiting > 1)
            return false;
    }

    return true;
}

bool generate_earliest_perm(void)
{
    if (cur_order.size() == 8) {
        return true;
    }

    bool found = false;
    for (int i = 0; i < 8 && !found; i++) {
        if (!used[i]) {
            if (!check_pos_to_place(i))
                continue;

            cur_order.pb(i);
            used[i] = true;
            found = generate_earliest_perm();
            if (found) break;
            used[i] = false;
            cur_order.pop_back();
        }
    }

    return found;
}

void print_res(void)
{
    for (auto num : cur_order) 
        cout << num_to_cow[num] << '\n';
}

int main(void)
{
    freopen("lineup.in", "r", stdin);
    freopen("lineup.out", "w", stdout);

    scanf("%d", &n);
    init_cows();
    string cow1, temp, cow2;
    int num1, num2;
    for (int i = 0; i < n; i++) {
        cin >> cow1 >> temp >> temp >> temp >> temp >> cow2;
        num1 = cow_to_num[cow1];
        num2 = cow_to_num[cow2];

        beside[num2].pb(num1);
        beside[num1].pb(num2);
    }

    memset(used, false, sizeof(used));
    cur_order.clear();
    generate_earliest_perm();
    print_res();
    return 0;
}