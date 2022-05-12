/* Calculates the maximum weight that could enter the elevator at one time */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int find_max(int* array, int size);

int main(void)
{
    freopen("elevator.in", "r", stdin);
    freopen("elevator.out", "w", stdout);

    int dolphincount;
    scanf("%d", &dolphincount);

    int* dolphinweights = malloc(sizeof(int) * dolphincount);
    for (int i = 0; i < dolphincount; i++) {
        scanf("%d", &dolphinweights[i]);
    }

    int maxweight = find_max(dolphinweights, dolphincount);

    int counter[maxweight + 1];
    for (int i = 0; i < maxweight + 1; i++)
        counter[i] = 0;

    for (int i = 0; i < dolphincount; i++) {
        counter[dolphinweights[i]]++;
    }

    int k = 0;
    for (int i = 0; i <= maxweight; i++)
        for (int j = 0; j < counter[i]; j++) 
            dolphinweights[k++] = i;


    int pairweight;
    int turns = 0, i;
    int j = dolphincount - 1;
    bool countmax = false;
    if (dolphincount % 2 == 1) {
        j--;
        countmax = true;
    }

    for (i = 0; i < j; i++, j--) {
        pairweight = dolphinweights[i] + dolphinweights[j];
        if (pairweight > maxweight)
            maxweight = pairweight;

        turns++;
    }

    if (countmax) 
        turns++;

    printf("%d %d", turns, maxweight);

    free(dolphinweights);

    

}

int find_max(int* array, int size)
{
    int max = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] > max)
            max = array[i];
    }

    return max;
}