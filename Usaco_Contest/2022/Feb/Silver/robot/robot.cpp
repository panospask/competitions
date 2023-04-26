#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define CHECK_BIT(var, pos) (var & (1<<pos))

using namespace std;

typedef pair<long long, long long> pl;
typedef long long ll;

struct InstructionSet {
    ll x;
    ll y;
    int count;
};

bool operator < (const InstructionSet& a, const InstructionSet& b)
{
    if (a.x == b.x) {
        return a.y < b.y;
    }
    return a.x < b.x;
}

bool operator == (const InstructionSet& a, const InstructionSet& b)
{
    return (a < b || b < a ? false : true);
}

pl operator + (pl a, pl b)
{
    return mp(a.first + b.first, a.second + b.second);
}

pl operator - (pl a, pl b)
{
    return mp(a.first - b.first, a.second - b.second);
}

int n;
vector<pl> instructions;
pl inital = mp(0, 0);
pl target;
vector<ll> ans;

vector<InstructionSet> first_orders;
vector<InstructionSet> second_orders;
vector<pl> dp;

int main(void)
{
    // freopen("robot.in", "r", stdin);
    // freopen("robot.out", "w", stdout);

    scanf("%d", &n);
    scanf("%lld %lld", &target.first, &target.second);
    int first_half = n / 2;
    ans.resize(n + 1);
    instructions.resize(first_half);
    for (int i = 0; i < first_half; i++)
        scanf("%lld %lld", &instructions[i].first, &instructions[i].second);

    // Generate the first half subsets
    first_orders.resize(1<<first_half);
    dp.resize(1<<first_half);

    dp[0] = mp(inital.first, inital.second);
    for (int s = 0; s < (1<<first_half); s++) {
        first_orders[s].x = dp[s].first;
        first_orders[s].y = dp[s].second;
        first_orders[s].count = __builtin_popcount(s);

        for (int i = 0; i < first_half; i++) {
            if (!CHECK_BIT(s, i)) {
                dp[s | (1<<i)] = dp[s] + instructions[i];
            }
        }
    }
    sort(first_orders.begin(), first_orders.end());

    int second_half = n - first_half;
    instructions.resize(second_half);
    for (int i = 0; i < second_half; i++)
        scanf("%lld %lld", &instructions[i].first, &instructions[i].second);

    dp.resize(1<<second_half);
    second_orders.resize(1<<second_half);
    dp[0] = mp(0, 0);
    InstructionSet cur;
    for (int s = 0; s < (1<<second_half); s++) {
        // First check how many subsets we can use
        second_orders[s].x = target.first - dp[s].first;
        second_orders[s].y = target.second - dp[s].second;
        second_orders[s].count = __builtin_popcount(s);

        // And calc the next
        for (int i = 0; i < second_half; i++)
            if (!CHECK_BIT(s, i))
                dp[s | (1<<i)] = dp[s] + instructions[i];
    }
    sort(second_orders.begin(), second_orders.end());

    pl prev = mp(LONG_LONG_MAX, LONG_LONG_MAX);
    vector<int> add_ans(second_half + 1);
    int curp = 0;
    for (auto &order : first_orders) {
        if (mp(order.x, order.y) != prev) {
            add_ans.assign(second_half + 1, 0);
            while (curp < second_orders.size() && second_orders[curp] < order)
                curp++;

            while (curp < second_orders.size() && second_orders[curp] == order)
                add_ans[second_orders[curp++].count]++;
            prev = mp(order.x, order.y);
        }
        for (int i = 0; i <= second_half; i++)
            ans[i + order.count] += add_ans[i];
    }

    for (int i = 1; i <= n; i++)
        printf("%lld\n", ans[i]);

    return 0;
}