#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e18;

int N, K, T, D;
vector<int> a;
int l_car, p_car, l_mot, p_mot;

ll ans = INF;

priority_queue<int, vector<int>, greater<int>> cardrivers;
priority_queue<int> remaining;

// How much life are we able to give
ll available = 0;

// To how many people have we given more life than allowed? (Needs to be 0 for the cost to be valid)
int impossible = 0;

// How much life we want to receive
ll wanted = 0;

int cars = 0;
int motorcycles = 0;

// Raise age a to age b(or keep it the same if a > b)
void connect(int a, int b)
{
    if (a + D < b) {
        impossible++;
    }

    // How much age does this person want?
    wanted += max(0, b - a);

    // This person is unable to give further age
    available -= max(D, a - 1);

    // However this person can give some age if a > b
    available += max(0, a - b);
}

// Return age b to a (or do nothing if a > b)
void disconnect(int a, int b)
{
    if (a + D < b) {
        impossible--;
    }

    // This person no longer requires age
    wanted -= max(0, b - a);

    // This person is now able to give age
    available += max(D, a - 1);

    // Remove the bonus added by raise(a, b)
    available -= max(0, a - b);
}

// Checks if current configuration is valid and updates answer accordingly
void check(void)
{
    if (wanted <= available && !impossible) {
        ans = min(ans, (ll)wanted * T + (ll)cars * p_car + (ll)motorcycles * p_mot);
    }
}

int main(void)
{
    scanf("%d %d", &N, &K);
    scanf("%d %d %d %d", &l_car, &p_car, &l_mot, &p_mot);
    scanf("%d %d", &T, &D);

    a.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        available += max(D, a[i] - 1);
    }
    sort(a.rbegin(), a.rend());

    // Initialize by filling with cars only
    while (cars * K < N) {
        cardrivers.push(a[cars]);
        connect(a[cars], l_car);
        cars++;
    }

    for (int i = cars; i < N; i++) {
        remaining.push(a[i]);
    }

    check();
    while (cars) {
        // Remove the last car and put motorcycles in its place
        int u = cardrivers.top();
        cardrivers.pop();

        disconnect(u, l_car);
        cars--;

        connect(u, l_mot);
        motorcycles++;

        while (K * cars + motorcycles < N) {
            int v = remaining.top();
            remaining.pop();

            connect(v, l_mot);
            motorcycles++;
        }

        check();
    }

    if (ans == INF) {
        printf("-1\n");
    }
    else {
        printf("%lld\n", ans);
    }

    return 0;
}