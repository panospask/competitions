#include <bits/stdc++.h>

using namespace std;

const int MAXB = 30;
int a = 0, b = 0;
int v1 = 0, v2 = 0;

int ask(int c, int d)
{
    printf("? %d %d\n", c, d);
    fflush(stdout);

    int res;
    scanf("%d", &res);

    return res;
}

// a and b are equal (using v1/v2) from mbit and down 
void play_equal(int mbit)
{
    for (int bit = mbit; bit >= 0; bit--) {
        if (ask(v1, v2 + (1 << bit)) == 1) {
            a += (1 << bit);
            b += (1 << bit);
        }
    }
}

int main(void)
{
    int prv = ask(v1, v2);

    for (int bit = MAXB - 1; bit >= 0; bit--) {
        int res = ask(v1 + (1 << bit), v2 + (1 << bit));

        if (res == 0) {
            play_equal(bit);
            break;
        }

        if (res != prv) {
            // Answer flipped, therefore bit flipped for BOTH sides
            if (prv == 1) {
                // a had the one in this bit
                a += (1 << bit);
                v1 += (1 << bit);
            }
            else {
                // b had the one in this bit
                b += (1 << bit);
                v2 += (1 << bit);
            }

            prv = ask(v1, v2);
        }
        else {
            // This bit is the same in both a and b, only have to figure out what it is
            // Flip the bit in only one of the values and check if it is higher with bit flipped or not

            if (ask(v1, v2 + (1 << bit)) == 1) {
                // Fliping does not produce higher number
                a += (1 << bit);
                b += (1 << bit);
            }
        }
    }

    printf("! %d %d\n", a, b);
}