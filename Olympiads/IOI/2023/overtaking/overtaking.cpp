#include "overtaking.h"
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;

// Represents the segment between 2 consecutive stations
struct Segment {
    ll distance;
    // bunches[d] = a
    // All buses that start after d cannot arrive before a
    map<ll, ll> bunches;
    ll shift = 0;

    ll get_arrival(ll departure, int speed) {
        ll arrival = departure + distance * speed;

        // Find the last bunch before the current departure time
        auto bunch = bunches.lower_bound(departure + shift);
        if (bunch != bunches.begin()) {
            bunch--;

            arrival = max(arrival, bunch->second);
        }

        return arrival;
    }

    // Merge the previous segment into this one
    void backpropagate(Segment prv, int speed) {
        vector<pair<ll, ll>> updated_bunches;
        for (auto [d, a] : prv.bunches) {
            // If you start later than d you finish at a or later (for the segment prv)
            // Start at a on the current segment and see where you end up

            ll ending = get_arrival(a, speed);

            updated_bunches.pb(mp(d - prv.shift, ending));
        }

        distance += prv.distance;
        shift += speed * prv.distance;

        for (auto [d, a] : updated_bunches) {
            // Starting later than means ending at or after a

            // shift d to the right by speed * prv.distance so it matches the constraints
            // imposed by the previous segments

            // Before this, remove all invalid constraints
            auto bunch = bunches.lower_bound(d + shift);
            while (bunch != bunches.end() && bunch->second < a) {
                bunches.erase(bunch);
                bunch = bunches.lower_bound(d + shift);
            }

            bunches[d + shift] = a;
        }
    }
};

struct Bus {
    int travelcost;
    ll arrival;
};

bool operator < (const Bus& a, const Bus& b)
{
    if (a.arrival == b.arrival) {
        return a.travelcost < b.travelcost;
    }

    return a.arrival < b.arrival;
}

vector<Bus> buses;
int special_speed;
vector<Segment> segments;
Segment res;

void advance_segment(int distance)
{
    segments.pb({distance});

    sort(buses.begin(), buses.end());

    ll previous_bunch = 0;
    for (auto& b : buses) {
        ll arrival = b.arrival + (ll)distance * b.travelcost;

        if (arrival > previous_bunch) {
            segments.back().bunches[b.arrival] = max(segments.back().bunches[b.arrival], arrival);
        }

        previous_bunch = max(previous_bunch, arrival);
        b.arrival = previous_bunch;
    }
}

void init(int L, int N, vector<ll> T, vector<int> W, int X, int M, vector<int> S)
{
    special_speed = X;
    for (int i = 0; i < N; i++) {
        if (W[i] > X) {
            buses.pb({W[i], T[i]});
        }
    }

    for (int i = 1; i < M; i++) {
        advance_segment(S[i] - S[i - 1]);
    }
    res = segments.back();
    for (int i = segments.size() - 2; i >= 0; i--) {
        res.backpropagate(segments[i], special_speed);
    }
}

ll arrival_time(ll Y)
{
    return res.get_arrival(Y, special_speed);
}