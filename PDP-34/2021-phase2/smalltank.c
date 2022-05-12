/*
USER: 34pdppaskp
LANG: C
TASK: smalltank
*/

#include <stdio.h>
#include <stdlib.h>

struct pair {
    int vec1;
    int vec2;
    int weight;
};
typedef struct pair* Pair;

int compare_weights(const void*a ,const void* b);
int find_root(int* city_root, int city);
void unite_trees(int* city_root, int city1, int city2);
void print_array(Pair* road_array, int size)
{
    for (int i = 0; i < size; i++) {
        fprintf(stderr, "%d\n", road_array[i]->weight);
    }
}

int find_root(int* city_root, int city) 
{
    if (city_root[city] != city) {
        city_root[city] = find_root(city_root, city_root[city]);
    }

    return city_root[city];
}

void unite_trees(int* city_root, int city1, int city2)
{
    city_root[find_root(city_root, city1)] = find_root(city_root, city2);
}


int compare_weights(const void* a, const void* b)
{
    return (*(Pair*)a)->weight - (*(Pair*)b)->weight;
}

int main(void)
{
    freopen("smalltank.in", "r", stdin);
    freopen("smalltank.out", "w", stdout);
    int city_num, road_num;
    scanf("%d %d", &city_num, &road_num);

    int* city_root = malloc(sizeof(int) * city_num);
    Pair* road_array = malloc(sizeof(Pair) * road_num);
    //Pair road_array[road_num];

    for (int i = 0; i < city_num; i++) {
        city_root[i] = i;
    }
    for (int i = 0; i < road_num; i++) {
        road_array[i] = malloc(sizeof(struct pair));
        scanf("%d %d %d", &road_array[i]->vec1, &road_array[i]->vec2, &road_array[i]->weight);
        road_array[i]->vec1--;
        road_array[i]->vec2--;
    }

    qsort(road_array, road_num, sizeof(Pair), compare_weights);
    // print_array(road_array, road_num);


    int vectors_left = city_num - 1;
    int i = 0;
    while (vectors_left > 0) {
        Pair curpair = road_array[i];
        if (find_root(city_root, curpair->vec1) != find_root(city_root, curpair->vec2)) {
            unite_trees(city_root, curpair->vec1, curpair->vec2);
            vectors_left--;
        }

        i++;
    }

    printf("%d\n",road_array[--i]->weight);
    return 0;
}

