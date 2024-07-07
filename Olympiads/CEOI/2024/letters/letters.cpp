#include <cassert>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

/// You may use:

// The number of houses
int N;

// This function checks the letter delivired to a house.
// Its argument is a house number between 1 and N.
// It returns the number on the bill delivered to that house.
int ask_house(int house_id) {
    assert(1 <= house_id);
    assert(house_id <= N);

    printf("Q %d\n", house_id);
    fflush(stdout);

    int answer;
    scanf(" %d", &answer);
    return answer;
}

/// You should implement:

// This function will be called once for each problem.
// It should return an integer between 1 and N,
// the number of any house that received a letter addressed to it.
// It should use ask_house to find such a house.
int find_correctly_delivered_letter() {
    std::vector<bool> possible(N, true);
    std::vector<int> order(N);
    for (int i = 0; i < N; i++) {
        order[i] = i;
    }

    std::random_shuffle(order.begin(), order.end());

    int rem = N;

    for (int i = 0; rem >= 2; i++) {
        int j = order[i];
        if (possible[j]) {
            int res = ask_house(j + 1) - 1;
            if (res == j) {
                return j + 1;
            }

            possible[j] = false;
            rem--;

            if (possible[res]) {
                possible[res] = false;
                rem--;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        if (possible[i]) {
            return i + 1;
        }
    }

    return 0;
}

int main(int argc, char **argv) {
    int T;
    scanf("%d %d", &N, &T);

    // You may perform any extra initialization here.
    srand(1);

    for (int i = 0; i < T; i++) {
        int answer = find_correctly_delivered_letter();
        assert(1 <= answer);
        assert(answer <= N);

        printf("A %d\n", answer);
        fflush(stdout);

        char verdict;
        scanf(" %c", &verdict);
        if (verdict == 'W')
            exit(0);
    }
    return 0;
}
