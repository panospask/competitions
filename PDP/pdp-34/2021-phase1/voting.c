/*
USER: 34pdppaskp
LANG: C
TAST: voting
*/

#include <stdio.h>
#include <stdlib.h>

int winning_number(int *candidate_votes, int candidates, int left_to_vote);

int main(void)
{
    freopen("voting.in", "r", stdin);
    freopen("voting.out", "w", stdout);

    int candidates, voters, currently_voted, left_to_vote, current_vote;

    scanf("%d %d %d", &voters, &candidates, &currently_voted);
    left_to_vote = voters - currently_voted;

    int* candidate_list = malloc(sizeof(int) * candidates);

    for (int i = 0; i < currently_voted; i++) {
        scanf("%d", &current_vote);
        candidate_list[current_vote - 1]++;
    }

    int win_number = winning_number(candidate_list, candidates, left_to_vote);
    printf("%d", win_number);

    return 0;
}

int winning_number(int *candidate_votes, int candidates, int left_to_vote)
{
    int max1 = 0, max2 = 0;

    for (int i = 0; i < candidates; i++) {
        if (candidate_votes[i] > max1) {
            max2 = max1;
            max1 = candidate_votes[i];
        }
        else if (candidate_votes[i] > max2) {
            max2= candidate_votes[i];
        }
    }

    if (left_to_vote == 0)
        return (max1 > max2 ? 1 : 0);
    
    int winners = 0;
    for (int i = 0; i < candidates; i++) {
        if (candidate_votes[i] + left_to_vote > max1)
            winners++;
    }
    
    return winners;
}