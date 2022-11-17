/*
ID: panos.p1
LANG: C++11
TASK: twofive
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define L_LENGTH 5
#define N 25

using namespace std;

vector<int> curplace;
vector<int> smpl;
vector<int> ans;
set<int> nums;
bool visited[25];

bool check_good(int a)
{
    // Rowcheck
    if (curplace.size() % L_LENGTH != 0 && curplace[curplace.size() - 1] > a)
        return false;

    // Columncheck
    if (curplace.size() >= L_LENGTH && curplace[curplace.size() - L_LENGTH] > a)    
        return false;

    return true;
}

int find_mth_perm(int m)
{
    if (curplace.size() == N) {
        if (m == 1) {
            ans = curplace;
            return -1;
        }
        else    
            return 1;
    }    

    int curpos = 0;
    int cur_total = 0;

    for (auto num : nums) {
        if (!visited[num] && check_good(num)) {
            curplace.pb(num);
            visited[num] = true;
            cur_total = find_mth_perm(m - curpos);
            if (cur_total == -1) {
                return -1;
            }
            curpos += cur_total;
            visited[num] = false;
            curplace.pop_back();
        }
    }

    return curpos;
}

int find_avail_perms(void)
{
    if (curplace.size() == N)
        return 1;

    int ttl_nums = 0;
    for (auto v : nums) {
        if (!visited[v] && check_good(v)) {
            visited[v] = true;
            curplace.pb(v);
            ttl_nums += find_avail_perms();
            curplace.pop_back();
            visited[v] = false;
        }
    }

    return ttl_nums;
}

int find_total_before(void)
{
    if (curplace.size() == N)
        return 0;

    int ttl_before = 0;
    int pos = curplace.size();
    for (auto v : nums) {
        if (v < smpl[pos]) {
            if (!visited[v] && check_good(v)) {
                visited[v] = true;
                curplace.pb(v);
                ttl_before += find_avail_perms();
                curplace.pop_back();
                visited[v] = false;
            }
        }
        else {
            break;
        }
    }

    visited[smpl[pos]] = true;
    curplace.pb(smpl[pos]);
    ttl_before += find_total_before();
    curplace.pop_back();
    visited[smpl[pos]] = false;

    return ttl_before;
}

int main(void)
{
    freopen("twofive.in", "r", stdin);
    freopen("twofive.out", "w", stdout);

    char type = getchar();
    for (int i = 0; i < N; i++)
        nums.insert(i);

    if (type == 'N') {
        int m;
        scanf("%d", &m);

        curplace.clear();
        find_mth_perm(m);
        for (auto v : ans)
            printf("%c", (char)(v + 'A'));
        printf("\n");
    }
    else {
        char num;
        getchar();
        for (int i = 0; i < N; i++) {
            num = getchar();
            smpl.pb((int)num - 'A');
        }

        printf("%d\n", find_total_before() + 1);
    }

    return 0;
}