#include <bits/stdc++.h>
#define MAXQ 1000
#define MAXK (int)(10e18)
#define MAXD 17

using namespace std;

long long int k;
int q;

long long int sizeofn[MAXD  + 2];
long long int tenpow[MAXD + 2];

long long int size_of_n_and_under_digs(int n)
{
    int curdigs_per_num = 1;
    long long int curnums = 9;
    int i = 1;
    long long int size = 0;

    while (i <= n) {
        size += curnums * curdigs_per_num;
        curnums *= 10;
        curdigs_per_num++;
        i++;
    }

    return size;
}

int main(void)
{
    scanf("%d", &q);

    long long int tpow = 1;
    for (int i = 0; i <= MAXD; i++) {
        sizeofn[i] = size_of_n_and_under_digs(i);
        tenpow[i] = tpow;
        tpow *= 10;
    }


    for (int i = 0; i < q; i++) {
        scanf("%lld", &k);

        int low = 0;
        int high = MAXD;
        while (low != high) {
            int mid = (low + high) / 2;
            if (mid == low) 
                break;

            if (sizeofn[mid] >= k)
                high = mid;
            else 
                low = mid;
        }
        if (sizeofn[high] < k)
            low = high;
        
        // We know that our num has [low + 1] digits
        long long int digs_to_remove = sizeofn[low];
        k -= digs_to_remove;
        
        // Only have the same digit numbers to remove => each number left has [low + 1] digits
        long long int numspot = (k - 1) / (low + 1); // The spot of the number
        int numdig = k % (low + 1); // The digit we are looking for

        long long int number = tenpow[low] + numspot;

        if (numdig != 0) {
            for (int i = 0; i < low + 1 - numdig; i++)
                number /= 10;
        }

        int digit = number % 10;
        printf("%d\n", digit);
    }

    return 0;
}