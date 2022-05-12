/* Sorts an array by swapping it's contents */

#include <stdio.h>

#define MAX_NUM 3

int find_smaller(int a, int b);


int main(void)
{
    freopen("sort3.in", "r", stdin);
    freopen("sort3.out", "w", stdout);

    int length;
    scanf("%d", &length);

    int remaining_length = length;

    int sortarray[length];

    int ones = 0, twos = 0, threes = 0;

    for (int i = 0; i < length; i++) {
        scanf("%d", &sortarray[i]);
        if (sortarray[i] == 1)
            ones++;
        else if (sortarray[i] == 2)
            twos++;
        else 
            threes++;
    }

    int one_end = ones - 1;
    int three_start = length - threes;
    int swaps = 0;
    int ones_in_twos = 0,ones_in_threes = 0, twos_in_ones = 0, twos_in_threes = 0, threes_in_ones = 0, threes_in_twos = 0;

    for (int i = 0; i < length; i++) {
        if (sortarray[i] == 1) {
            if (i > one_end && i < three_start) {
                ones_in_twos++;
            }
            else if (i >= three_start) {
                ones_in_threes++;
            }
            else {
                remaining_length--;
            }
        }
        
        else if (sortarray[i] == 2) {
            if (i <= one_end) {
               twos_in_ones++;
            }
            else if (i >= three_start) {
                twos_in_threes++;
            }
            else {
                remaining_length--;
            }
        }

        else {
            if (i <= one_end) {
               threes_in_ones++;
            }
            else if (i < three_start) {
                threes_in_twos++;
            }
            else {
                remaining_length--;
            }
        }

    }

    int count = find_smaller(ones_in_twos, twos_in_ones) + find_smaller(ones_in_threes, threes_in_ones) + find_smaller(twos_in_threes, threes_in_twos);
    remaining_length -= count * 2;
    swaps += count;


    swaps += remaining_length * 2 / 3;


    printf("%d", swaps);
    
}

int find_smaller(int a, int b)
{
    return (a < b ? a : b);
}