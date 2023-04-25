#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

struct colour {
    int id;
    int layers;

    colour(int i, int l) {id = i; layers = l;}
};
typedef struct colour Colour;

int n;
vector<int> painting;
vector<bool> seen;
vector<bool> on_stack;
stack<Colour> cur_segments;
int ans = 0;

void clear_stack(void)
{
    while (!cur_segments.empty()) {
        Colour c = cur_segments.top();
        on_stack[c.id] = false;
        ans = max(ans, c.layers);
        cur_segments.pop();
    }
}

int main(void)
{
    freopen("art2.in", "r", stdin);
    freopen("art2.out", "w", stdout);

    scanf("%d", &n);
    painting.resize(n + 2);
    seen.resize(n + 2);
    on_stack.resize(n + 2);

    for (int i = 0; i < n; i++)
        scanf("%d", &painting[i]);

    int prevc = 0;
    for (int i = 0; i < n; i++) {
        if (painting[i] == prevc)
            continue;

        if (painting[i] == 0) {
            clear_stack();
        }
        else {
            if (seen[painting[i]]) {
                if (!on_stack[painting[i]]) {
                    printf("-1\n");
                    return 0;
                }

                int above_layer = 0;
                while (cur_segments.top().id != painting[i]) {
                    above_layer = max(above_layer, cur_segments.top().layers);
                    on_stack[cur_segments.top().id] = false;
                    cur_segments.pop();
                }

                Colour prv = cur_segments.top();
                cur_segments.pop();
                cur_segments.push(Colour(painting[i], max(above_layer + 1, prv.layers)));
            }
            else {
                seen[painting[i]] = true;
                on_stack[painting[i]] = true;
                cur_segments.push(Colour(painting[i], 1));
            }
        }
        prevc = painting[i];
    }
    // Important to also clear after finishing
    clear_stack();

    printf("%d\n", ans);
    return 0;
}