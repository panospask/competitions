#include "longesttrip.h"
#include <bits/stdc++.h>
#define pb push_back

using namespace std;

void extend(vector<int>& a, vector<int>& b, int first, int last)
{
    for (int i = first; i <= last; i++) {
        a.pb(b[i]);
    }
}

bool connected(vector<int> v1, vector<int> v2)
{
    v1.resize(unique(v1.begin(), v1.end()) - v1.begin());
    v2.resize(unique(v2.begin(), v2.end()) - v2.begin());

    return are_connected(v1, v2);
}

vector<int> longest_trip(int N, int D)
{
    vector<int> v1, v2;

    v1.pb(0);
    v2.pb(1);

    // Randomize the order of elements
    vector<int> order;
    for (int i = 2; i < N; i++) {
        order.pb(i);
    }
    srand(15);
    random_shuffle(order.begin(), order.end());

    // True if we are sure that the last elements of v1 and v2 are disconnected
    bool last_disconnect = false;

    for (int j = 0; j < N - 2; j++) {
        int i = order[j];
        if (connected({v1.back()}, {i})) {
            v1.pb(i);
            last_disconnect = false;
        }
        else {
            if (last_disconnect || connected({v2.back()}, {i})) {
                v2.pb(i);

                // i and v1.back() are not connected(asserted above)
                last_disconnect = true;
            }
            else {
                // The density constraint means that the last elements of v1 and v2 are connected
                reverse(v2.begin(), v2.end());
                extend(v1, v2, 0, v2.size() - 1);
                
                if (v2.size() > 1) {
                    last_disconnect = false;
                }
                else {
                    // The last element of the new v1 is, once again, v2.back() and it is definetely not connected to i
                    last_disconnect = true;
                }

                v2.clear();
                v2.pb(i);
            }
        } 

        if (v1.size() < v2.size()) {
            swap(v1, v2);
        }
    }

    vector<int> res;

    if (connected(v1, v2)) {
        if (connected({v1.front(), v1.back()}, {v2.front(), v2.back()})) {
            // Some endpoints are connected
            if (connected({v1.front()}, {v2.front(), v2.back()})) {
                reverse(v1.begin(), v1.end());
            }
            if (connected({v1.back()}, {v2.back()})) {
                reverse(v2.begin(), v2.end());
            }

            extend(res, v1, 0, v1.size() - 1);
            extend(res, v2, 0, v2.size() - 1);
        }
        else {
            // No endpoints are connected => v1 and v2 are 2 cycles
            int l = 0;
            int r = v1.size();

            while (l + 1 < r) {
                int mid = (l + r) / 2;
                if (connected(vector<int>(v1.begin(), v1.begin() + mid), v2)) {
                    r = mid;
                }
                else {
                    l = mid;
                }
            }

            int p1 = l;
            l = 0;
            r = v2.size();
            while (l + 1 < r) {
                int mid = (l + r) / 2;
                if (connected(vector<int>(v2.begin(), v2.begin() + mid), {v1[p1]})) {
                    r = mid;
                }
                else {
                    l = mid;
                }
            }

            int p2 = l;

            extend(res, v1, p1 + 1, v1.size() - 1);
            extend(res, v1, 0, p1);
            extend(res, v2, p2, v2.size() - 1);
            extend(res, v2, 0, p2 - 1);
        }
    }
    else {
        res = v1;
    }

    return res;
}
