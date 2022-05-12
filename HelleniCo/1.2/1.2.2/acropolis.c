/* Calculates the transportation of stone to the acropolis*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_WEIGHT 10000

int main(void)
{
    freopen("acropolis.in", "r", stdin);
    freopen("acropolis.out", "w", stdout);

    int size;
    scanf("%d", &size);

    int *pieces = malloc(sizeof(int*) * size);

    for (int i = 0; i < size; i++)
        scanf("%d", &pieces[i]);

    int counter[MAX_WEIGHT] = {0};

    for (int i = 0; i < size; i++) 
    if (pieces[i] != 1) {
        counter[pieces[i]]++;
    }

    int k = 0;

    for (int i = 0; i < MAX_WEIGHT; i++)
        for (int j = 0; j < counter[i]; j++) {
            if (pieces[k] == 1) {
                j--;
            }
            else {
                pieces[k] = i;
            }
            
            k++;
        }


    for (int i = 0; i < size; i++) {
        printf("%d\n", pieces[i]);
    }  

    free (pieces);
}