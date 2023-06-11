#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pl;

int n;
map<ll, pl> able;
vector<ll> cookies;
ll combos = 0;
ll latest = 1;
ll nxt_start;

void DIE(pl a, pl b)
{
    cout << "! 2 2" << endl;

    assert(a.first > 0 && a.second > 0 && b.first > 0 && b.second > 0);
    assert(a != b);

    cout << a.first << ' ' << a.second << endl;
    cout << b.first << ' ' << b.second << endl;
}

ll get_next_cookies(void)
{
    priority_queue<int, vector<int>, greater<int>> q;
    cout << "?";
    int given = 0;

    while (given < n) {
        if (!q.empty() && q.top() == latest) {
            while (!q.empty() && q.top() == latest)
                q.pop();
        }
        else if (able.find(latest) == able.end()) {
            cout << ' ' << latest;
            given++;
            for (int i = 0; i < cookies.size() && (ll)(n) * cookies.size() + combos >= cookies[i]; i++)
                q.push(cookies[i] + latest);
        }

        latest++;
    }
    assert(given == n);
    cout << endl;

    ll num;
    cin >> num;

    return num;
}

int main(void)
{
    cin >> n;

    int cnt = 0;
    while (combos < n && cnt < 100) {
        assert(cnt < 100);
        cnt++;
        ll new_cookie = get_next_cookies();

        for (auto& c : cookies) {
            ll sum = c + new_cookie;

            if (able.find(sum) != able.end()) {
                DIE(able[sum], mp(new_cookie, c));
                return 0;
            }

            able[sum] = mp(c, new_cookie);
        }

        combos += cookies.size();
        cookies.push_back(new_cookie);
    }

    assert(cnt <= 100);

    if (combos < n) {
        // Generate some triples with (0, n)
        ll fsum = cookies[0] + cookies.back();

        for (int i = 2; i < cookies.size() && combos < n; i++) {
            if (able.find(fsum + cookies[i]) != able.end()) {
                pl a = able[fsum + cookies[i]];

                cout << "! 2 3" << endl;
                cout << a.first << ' ' << a.second << endl;
                cout << cookies[0] << ' ' << cookies.back() << ' ' << cookies[i] << endl;

                return 0;
            }

            able[fsum + cookies[i]] = mp(-1, cookies[i]);
            combos++;
        }
    }

    // Now combos are greater than n;

    assert(able.size() >= n);
    cnt = 0;
    cout << "?";
    for (auto& comb : able) {
        cout << " " << comb.first;
        cnt++;
        if (cnt == n)
            break;
    }
    cout << endl;
    assert(cnt == n);

    ll res;
    cin >> res;
    assert(able.find(res) != able.end());

    pl sec = able[res];

    if (sec.first == -1) {

        cout << "! 3 1" << endl;
        cout << cookies[0] << " " << cookies.back() << ' ' << sec.second << endl;
        cout << res << endl;

        return 0;
    }

    cout << "! 2 1" << endl;
    cout << sec.first << " " << sec.second << endl;
    cout << res << endl;

    return 0;
}