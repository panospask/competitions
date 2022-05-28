#include <bits/stdc++.h>

using namespace std;

char word[200005];
bool used[200005];
int ab_rem, ba_rem, a_rem, b_rem, n;

void checking(int i)
{
    if (used[i-1] == true)
        return;
    
    if (word[i] != word[i-1]) {
        if (word[i-1] == 'A') {
            if (ab_rem) {
                ab_rem--;
                used[i] = true;
                used[i-1] = true;
            }
        }
        else
            if (ba_rem) {
                ba_rem--;
                used[i] = true;
                used[i-1] = true;
            }
    }
}

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        scanf("%d %d %d %d", &a_rem, &b_rem, &ab_rem, &ba_rem);
        getchar();
        n = a_rem + b_rem + 2 * ab_rem + 2 * ba_rem;
        memset(used, false, n);

        for (int i = 0; i < n; i++)
            word[i] = getchar();
        for (int i = 1; i < n; i++)
            checking(i);

        bool exists = true;
        if (ab_rem != 0 || ba_rem != 0)
            exists = false;

        for (int i = 0; i < n && exists; i++)
            if (!used[i]) {
                if (word[i] == 'A') {
                    if (a_rem) {
                        used[i] = true;
                        a_rem--;
                    }
                    else {
                        exists = false;
                    }
                }
                else {
                    if (b_rem) {
                        used[i] = true;
                        b_rem--;
                    }
                    else {
                        exists = false;
                    }
                }
            }
        

        if (exists)
            printf("YES\n");
        else 
            printf("NO\n");
    }
}