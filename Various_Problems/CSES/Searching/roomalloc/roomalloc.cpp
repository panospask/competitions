#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> ii;

int n;
vector<ii> arrivals;
vector<ii> departures;
set<int> empty_rooms;
int cur_rooms;
map<int, int> guestroom;

int main(void)
{
    scanf("%d", &n);
    int s, e;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &s, &e);
        arrivals.pb(mp(s, i));
        departures.pb(mp(e, i));
    }

    sort(arrivals.begin(), arrivals.end());
    sort(departures.begin(), departures.end());
    int arnum = 0, depnum = 0;
    ii guest;
    while (arnum < arrivals.size()) {
        if (arrivals[arnum].first <= departures[depnum].first) {
            guest = arrivals[arnum];
            arnum++;
            if (!empty_rooms.empty()) {
                guestroom[guest.second] = *(empty_rooms.begin());
                empty_rooms.erase(empty_rooms.begin());
            }
            else {
                guestroom[guest.second] = cur_rooms++;
            }
        }
        else {
            guest = departures[depnum];
            depnum++;
            empty_rooms.insert(guestroom[guest.second]);
        }
    }

    printf("%d\n", cur_rooms);
    for (int i = 0; i < n; i++)
        printf("%d ", guestroom[i] + 1);
    return 0;
}