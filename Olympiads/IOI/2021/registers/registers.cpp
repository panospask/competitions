#include "registers.h"

const int REGSIZE = 2000;

const int INIT = 0;
const int KEEP = 2;
const int TEMP = 1;
const int VAL = 3;
const int ANS = 4;

void isolate_last(int reg, int pos)
{
    append_left(reg, reg, REGSIZE - 1);
    append_right(reg, reg, REGSIZE - pos - 1);
}

void construct_instructions(int s, int n, int k, int q)
{
    // Solve s = 0;

    std::vector<bool> v(REGSIZE);
    v.assign(REGSIZE, false);
    v[0] = true;

    for (int b = k - 1; b >= 0; b--) {
        // Start from the highest bit
        append_or(INIT, INIT, KEEP);
        append_store(VAL, v);

        for (int i = 0; i < n; i++) {
            // We are interested in the bit in position k * i + b
            int pos = k * i + b;

            append_right(TEMP, INIT, pos);

            append_and(VAL, TEMP, VAL);
        }

        append_add(ANS, VAL, ANS);

        if (b > 0) {
            append_left(ANS, ANS, 1);
            append_not(VAL, VAL);
            append_left(VAL, VAL, REGSIZE - b - 1);
            append_left(VAL, VAL, b);

            append_print(VAL);
            for (int i = 0; i < n; i++) {
                int pos = k * i + b;

                append_and(TEMP, INIT, VAL);

                append_or(KEEP, KEEP, TEMP);

                if (i != n - 1)
                    append_left(VAL, VAL, k);
            }
        }

        // The bit in val is good

        append_right(KEEP, KEEP, 1);
    }

    append_move(INIT, ANS);

    return;
}
