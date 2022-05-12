#include <bits/stdc++.h>

using namespace std;

void reverse_string(char* word)
{
    int n = 0;
    while (word[n] != '\0')
        n++;

    for (int i = 0, j = n - 1; i < j; i++, j--) {
        char temp = word[i];
        word[i] = word[j];
        word[j] = temp;
    }
}

int main(void)
{
    freopen("lektira.in", "r", stdin);
    freopen("lektira.out", "w", stdout);

    string word;
    cin >> word;

    char min_word[51];
    min_word[word.copy(min_word, word.size(), 0)] = '\0';
    

    for (int pivot1 = 0; pivot1 < word.size() - 2; pivot1++) 
        for (int pivot2 = pivot1 + 1; pivot2 < word.size() - 1; pivot2++) {
            char one[51];
            one[word.copy(one, pivot1 + 1, 0)] = '\0';
            char two[51];
            two[word.copy(two, pivot2 - pivot1, pivot1 + 1)] = '\0';
            char three[51];
            three[word.copy(three, word.size() - pivot2 - 1, pivot2 + 1)] = '\0';

            reverse_string(one);
            reverse_string(two);
            reverse_string(three);

            strcat(one, two);
            strcat(one, three);

            if (strcmp(min_word, one) > 0)
                strcpy(min_word, one);
        }

    printf("%s\n", min_word);

}