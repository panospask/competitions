#include"communication.h"
#include <algorithm>

using namespace std;

const int MAXLOG = 30;

void encode(int N, int X) {
    int bits = MAXLOG;
    while (bits) {
        int b = X % 2;
        X /= 2;
        bits--;

        // b will be our main bit
        while (bits) {
            int cur = X % 2;
            send(cur);
            int v1 = send(b);
            int v2 = send(b);
            if (v1 == v2) {
                break;
            }
            send(cur);

            bits--;
            X /= 2;
        }
    }
}

void clump(int& a, int l, int r) {
    a = min(a, r);
    a = max(a, l);
}

pair<int, int> decode(int N) {
    int found = 0;
    int num = 0;
    int options[2] = {0, 0};
    bool known = true;
    while (found < MAXLOG) {
        // Found is our main bit
        int b = found;
        // Create two numbers, one for found = 0, one for found = 1
        options[0] = num;
        options[1] = num + (1 << b);
        found++;
        known = false;

        while (found < MAXLOG) {
            int a = receive();
            int v1 = receive();
            int v2 = receive();
            if (v1 == v2) {
                // Choose the right option and leave
                num = options[v1];
                known = true;
                break;
            }
            int b = receive();

            // v1 false means a true (and v2 true)
            // v2 false means b true (and v1 true)
            if (v1) {
                swap(v1, v2);
                swap(a, b);
            }
            // v1 == 0, v2 == 1
            options[0] += b * (1 << found);
            options[1] += a * (1 << found);
            found++;
        }
    }

    clump(options[0], 1, N);
    clump(options[1], 1, N);

    if (known) {
        return {num, num};
    }
    return {options[0], options[1]};
}