#include <bits/stdc++.h>

using namespace std;

struct TrieNode {
    int WordCount;
    int next[10] = {0};
};

int node_count;
TrieNode trie[10000000];


void init(void)
{
    node_count = 1;
}

void add(int* num, int length)
{
    int i, next_node, cur_node = 0;
    trie[0].WordCount++;

    for (i = length - 1; i >= 0; i--) {
        next_node = trie[cur_node].next[num[i]];

        if (next_node == 0) {
            next_node = node_count;
            trie[cur_node].next[num[i]] = next_node;
            cur_node = next_node;
            node_count++;
        }
        else 
            cur_node = next_node;

        trie[cur_node].WordCount++;
    }

    trie[cur_node].WordCount++;
}

pair<long long int,int> check(int* num, int length)
{
    int i, next_node, cur_node = 0;
    pair<long long int, int> sum;
    sum.first = 0;
    sum.second = 0;
    long long int mult = 1;

    for (int i = length - 1; i >= -1; i--) {

        if (i == -1) {
            sum.first = (((trie[cur_node].WordCount * mult) % 1000000007) + sum.first - 1) % 1000000007;
            sum.second += trie[cur_node].WordCount; 
            return sum;
        }

        next_node = trie[cur_node].next[num[i]];
        if (cur_node == 0 && i != length - 1)
            return sum;
        
        else {
            int count;
            if (next_node != 0) {
                count = trie[cur_node].WordCount - trie[next_node].WordCount;
            }
            else {
                count = trie[cur_node].WordCount;
            }
            

            if (count != 0 && cur_node != 0) {
                sum.second += count;
                sum.first = (((count * mult) % 1000000007) + sum.first - 1) % 1000000007;
            }

            cur_node = next_node;
        }

        mult *= 2;
        mult %= 1000000007; 
    }

    return sum;
}

int main(void)
{
    freopen("lottery.in", "r", stdin);
    freopen("lottery.out", "w", stdout);

    int n, q, k;

    scanf("%d %d %d", &k, &n, &q);

    init();

    int word[101];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            scanf ("%1d", &word[j]);
        }
        add(word, k);
    }
    pair<long long int, int > wins;
    for (int i = 0; i < q; i++) {
        for (int j = 0; j < k; j++) {
            scanf("%1d", &word[j]);
        }
        wins = check(word, k);
        printf("%d %lld\n", wins.second, wins.first);
    }
}