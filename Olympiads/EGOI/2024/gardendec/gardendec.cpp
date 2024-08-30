#include <bits/stdc++.h>

using namespace std;

const int PASSES = 3;

int N, w;

// receipient[i]: The person that will live at house i
vector<int> receipient;

// target[i]: The house at which person i will live
vector<int> target;


void case1(void)
{
    vector<int> b(N);
    for (int i = 0; i < N; i++) {
        int cur = i;

        scanf("%d", &b[cur]);

        if (receipient[cur] < cur) {
            printf("%d", b[cur] ^ b[receipient[cur]]);
        }
        else {
            printf("%d", b[cur]);
        }
        printf("\n");
        fflush(stdout);
    }
}

int main(void)
{
    scanf("%d %d", &w, &N);
    receipient.resize(N);
    target.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &receipient[i]);
        target[receipient[i]] = i;
    }


    if (w == 0) {
        printf("%d\n", PASSES);
        fflush(stdout);
        return 0;
    }

    bool check = true;
    for (int i = 0; i < N; i++) {
        check = check && receipient[i] == target[i];
    }

    // if (check) {
    //     case1();
    //     return 0;
    // }

    vector<int> b(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &b[i]);

        if (i) {
            if (w < 3) {
                printf("%d", b[i] ^ b[i - 1]);
                if (w == 2) {
                    b[i] = b[i] ^ b[i - 1];
                }
            }
            else {
                printf("%d", b[i] ^ b[0]);
            }
        }
        else {
            printf("%d", b[i]);
        }
        printf("\n");
        fflush(stdout);
    }

    return 0;
}