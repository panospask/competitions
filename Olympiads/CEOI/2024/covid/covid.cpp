#include <cassert>
#include <cstdio>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

constexpr double K = 0.54;

/// You may use:

// The number of students
int N;

// The probability any given student is positive
double P;
bool init = false;
int gap;

// This function performs a test on a subset of samples.
// Its argument is a vector of Booleans of length N,
// where the i-th element is true if the i-th sample should be added to the mix.
// It returns true if (and only if) at least one of the samples in the mix is positive.
bool test_students(std::vector<bool> mask) {
    assert(mask.size() == (size_t)N);

    std::string mask_str(N, ' ');
    for (int i = 0; i < N; i++)
        mask_str[i] = mask[i] ? '1' : '0';

    printf("Q %s\n", mask_str.c_str());
    fflush(stdout);

    char answer;
    scanf(" %c", &answer);
    return answer == 'P';
}

bool test_range(int l, int r)
{
    vector<bool> to_test(N, false);
    for (int i = l; i < r; i++) {
        to_test[i] = true;
    }

    return test_students(to_test);
}

int find_first(int l, int r)
{
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (test_range(l, mid)) {
            r = mid;
        }
        else {
            l = mid;
        }
    }

    return l;
}

int initialize_gap(void)
{
    int l = 1;
    int r = N;

    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (pow(1 - P, mid)  < 1 - K) {
            r = mid;
        } 
        else {
            l = mid;
        }
    }

    return l;
}


// This function will be called once for each test instance.
// It should use test_students to determine which samples are positive.
// It must return a vector of Booleans of length N,
// where the i-th element is true if and only if the i-th sample is positive.
std::vector<bool> find_positive() {
    std::vector<bool> answer(N, false);

    if (P == 0) {
        return answer;
    }

    if (!init) {
        gap = initialize_gap();
        init = true;
    }

    int i = 0;
    while (i < N) {
        int len = min(gap, N - i);
        if (test_range(i, i + len)) {
            i = find_first(i, i + len);
            answer[i] = true;
            i++;
        }
        else {
            i += len;
        }
    }

    return answer;
}

int main() {
    int T;
    scanf("%d %lf %d", &N, &P, &T);

    // You may perform any extra initialization here.

    for (int i = 0; i < T; i++) {
        std::vector<bool> answer = find_positive();
        assert(answer.size() == (size_t)N);

        std::string answer_str(N, ' ');
        for (int j = 0; j < N; j++)
            answer_str[j] = answer[j] ? '1' : '0';

        printf("A %s\n", answer_str.c_str());
        fflush(stdout);

        char verdict;
        scanf(" %c", &verdict);
        if (verdict == 'W')
            exit(0);
    }

    return 0;
}
