//chockolateman

#include<bits/stdc++.h>

using namespace std;

int N;
pair<int,int> edges[3000005];
vector<int> adj_list[1000001];

bool connected(int node, int t, int par = -1, int d = 1) {
    if (node == t) {
        return true;
    }
    if (d == 0) {
        return false;
    }

    bool ans = false;
    for (auto neigh : adj_list[node]) {
        if (neigh != par)
            ans = ans || connected(neigh, t, node, d - 1);
    }

    return ans;
}

void remove(int x, int y) {
    adj_list[x].erase(find(adj_list[x].begin(), adj_list[x].end(), y));
    adj_list[y].erase(find(adj_list[y].begin(), adj_list[y].end(), x));
}

void add(int x, int y) {
    adj_list[x].push_back(y);
    adj_list[y].push_back(x);
}

int main()
{
    scanf("%d",&N);
    if(N%2==1)
    {
        printf("NO\n");
    }
    else
    {
        edges[1] = {1,2};
        add(1, 2);
        edges[2]  = {2,3};
        add(2, 3);
        edges[3] = {3,4};
        add(3, 4);
        edges[4] = {4,5};
        add(4, 5);
        edges[5] = {5,1};
        add(5, 1);
        edges[6] = {1,6};
        add(1, 6);
        edges[7] = {2,7};
        add(2, 7);
        edges[8] = {3,8};
        add(3, 8);
        edges[9] = {4,9};
        add(4, 9);
        edges[10] = {5,10};
        add(5, 10);
        edges[11] = {6,8};
        add(6, 8);
        edges[12] = {8,10};
        add(8, 10);
        edges[13] = {10,7};
        add(10, 7);
        edges[14] = {7,9};
        add(7, 9);
        edges[15] = {9,6};
        add(9, 6);
        int pos = 15;
        for(int i = 12 ; i <= N ; i += 2)
        {
            ++pos;
            edges[pos] = {i-1,i};
            add(i - 1, i);
            
            int take = 1;
            int x = edges[take].first;
            int y = edges[take].second;

            remove(x, y);
            add(x, i);
            add(y, i);

            edges[take] = {x,i};
            ++pos;
            edges[pos] = {y,i};
            
            take = 2;
            int z, w;
            while (true) {
                z = edges[take].first;
                w = edges[take].second;

                if (connected(x, z) || connected(y, w) || connected(x, w) || connected(y, z)) {
                    take++;
                }
                else {
                    break;
                }
            }

            remove(z, w);
            add(z, i - 1);
            add(w, i - 1);

            edges[take] = {z, i - 1};
            ++pos;
            edges[pos] = {w, i - 1};
        }
        printf("%d\n",(N*3)/2);
        for(int i = 1 ; i <= pos ; i++)
            printf("%d %d\n",edges[i].first,edges[i].second);
    }
    return 0;
}