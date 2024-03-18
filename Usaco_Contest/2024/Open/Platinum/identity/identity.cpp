#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

const string NULLSTR = "";

struct Node {
    Node* kids[2];
    int pos;
    int opt;
    bool full;

    Node(int i) {
        kids[0] = kids[1] = nullptr;
        opt = 0;
        pos = i;
        full = false;
    }
};

int N;
vector<Node> bintree;
vector<string> ids;
int ans = 0;

void add_any(Node* seq, const string& s) {
    // Create children
    for (int k = 0; k < 2; k++) {
        if (seq->kids[k] == nullptr) {
            seq->kids[k] = new Node(seq->pos + 1);
        }
    }

    bool redo = seq->full;
    seq->full = false;

    if (s.length() > seq->pos) {
        // Check if a move is forced
        int kid = s[seq->pos] - '0';
        add_any(seq->kids[kid], s);
    }
    else if (seq->opt == 0) {
        // Check for empty
        seq->full = true;
    }
    else {
        ans++;
        if (seq->opt == seq->kids[0]->opt + 1) {
            add_any(seq->kids[0], s);
        }
        else {
            add_any(seq->kids[1], s);
        }
    }

    seq->opt = min(seq->kids[0]->opt, seq->kids[1]->opt) + 1;
    if (seq->full) {
        // Found bug :)
        seq->opt = 2;
    }

    if (redo) {
        add_any(seq, NULLSTR);
    }
}

bool lensort(const string& a, const string& b)
{
    return a.length() < b.length();
}

int main(void)
{
    ios::sync_with_stdio(false);

    cin >> N;

    ids.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> ids[i];
    }

    Node* root = new Node(0);

    // Sort by reverse length, first take care of big ones
    sort(ids.rbegin(), ids.rend(), lensort);

    for (int i = 0; i < N; i++) {
        add_any(root, ids[i]);
    }

    cout << ans << endl;

    return 0;
}