#include <bits/stdc++.h>
using namespace std;

/* =================== LCA (Euler Tour + RMQ O(1)) =================== */
struct Edge{ int to; int w; };
int N, M;
vector<vector<Edge>> g;

vector<int> euler, firstOcc, depthv, lg2;
vector<long long> distw;
vector<vector<int>> rmq;

static inline int lca(int u, int v){
    int L = firstOcc[u], R = firstOcc[v];
    if (L > R) swap(L, R);
    int k = lg2[R - L + 1];
    int a = rmq[k][L], b = rmq[k][R - (1<<k) + 1];
    return depthv[a] < depthv[b] ? a : b;
}
static inline long long dists(int u, int v){
    int w = lca(u, v);
    return distw[u] + distw[v] - 2LL * distw[w];
}
static void build_lca(int root=1){
    euler.clear(); euler.reserve(2*N-1);
    firstOcc.assign(N+1, -1);
    depthv.assign(N+1, 0);
    distw.assign(N+1, 0);

    struct F{int v,p,i;};
    vector<F> st; st.reserve(N);
    st.push_back({root,0,0});
    while(!st.empty()){
        auto &cur = st.back();
        int v = cur.v, p = cur.p;
        if (cur.i == 0){
            if (firstOcc[v] == -1) firstOcc[v] = (int)euler.size();
            euler.push_back(v);
        }
        if (cur.i < (int)g[v].size()){
            auto [to,w] = g[v][cur.i++];
            if (to == p) continue;
            depthv[to] = depthv[v] + 1;
            distw[to]  = distw[v] + w;
            st.push_back({to, v, 0});
        }else{
            st.pop_back();
            if (!st.empty()) euler.push_back(st.back().v);
        }
    }
    int E = (int)euler.size();
    lg2.assign(E+1, 0);
    for (int i=2;i<=E;i++) lg2[i] = lg2[i/2]+1;
    int K = lg2[E] + 1;
    rmq.assign(K, vector<int>(E));
    for (int i=0;i<E;i++) rmq[0][i] = euler[i];
    for (int k=1;k<K;k++){
        int len = 1<<k, half = len>>1;
        for (int i=0;i+len<=E;i++){
            int a = rmq[k-1][i], b = rmq[k-1][i+half];
            rmq[k][i] = (depthv[a] < depthv[b] ? a : b);
        }
    }
}

/* =================== Centroid Decomposition =================== */
// Για κάθε v κρατάμε cpath[v]: (centroid id, branch id στο centroid, dist(v, centroid))
struct CInfo { int cid; int branch; long long d; };
vector<int> cdMarked, subSize;
vector<vector<CInfo>> cpath;

static void dfs_size(int v, int p){
    subSize[v]=1;
    for (auto &e: g[v]) if (!cdMarked[e.to] && e.to!=p){
        dfs_size(e.to, v);
        subSize[v]+=subSize[e.to];
    }
}
static int dfs_centroid(int v, int p, int n){
    for (auto &e: g[v]) if (!cdMarked[e.to] && e.to!=p){
        if (subSize[e.to] > n/2) return dfs_centroid(e.to, v, n);
    }
    return v;
}
static void fill_component(int v, int p, int cid, int branch){
    cpath[v].push_back({cid, branch, dists(v, cid)});
    for (auto &e: g[v]) if (!cdMarked[e.to] && e.to!=p){
        fill_component(e.to, v, cid, branch);
    }
}
static void build_cd(int v){
    dfs_size(v,0);
    int c = dfs_centroid(v,0,subSize[v]);
    cdMarked[c]=1;

    // ο ίδιος ο centroid
    cpath[c].push_back({c, -1, 0});

    int branch=0;
    for (auto &e: g[c]) if (!cdMarked[e.to]){
        fill_component(e.to, c, c, branch);
        ++branch;
    }
    for (auto &e: g[c]) if (!cdMarked[e.to]){
        build_cd(e.to);
    }
}

/* =================== Sparse "Segment Tree" per centroid: Treap =================== */
const long long NEG_INF = (long long)-4e18;

struct Agg {
    long long v1; int b1; // best value and its branch
    long long v2; int b2; // second best from DIFFERENT branch
    Agg(long long _v1=NEG_INF,int _b1=-2,long long _v2=NEG_INF,int _b2=-2):v1(_v1),b1(_b1),v2(_v2),b2(_b2){}
};
static inline void addCand(Agg &A, long long v, int b){
    if (v > A.v1){
        if (b != A.b1) { A.v2 = A.v1; A.b2 = A.b1; }
        A.v1 = v; A.b1 = b;
    } else if (b != A.b1 && v > A.v2){
        A.v2 = v; A.b2 = b;
    }
}
static inline Agg mergeAgg(const Agg& L, const Agg& R){
    Agg A = L;
    addCand(A, R.v1, R.b1);
    addCand(A, R.v2, R.b2);
    return A;
}

struct TNode{
    int key;                 // θέση στη λίστα
    long long val;           // dist(y, cid)
    int br;                  // branch(y, cid)
    uint32_t pri;
    TNode *l, *r;
    Agg agg;

    TNode() {}
    TNode(int k,long long v,int b,uint32_t p):key(k),val(v),br(b),pri(p),l(nullptr),r(nullptr),agg(v,b,NEG_INF,-2){}
};

// Pool allocator + freelist (ανακύκλωση σε pop)
struct NodePool{
    vector<TNode*> pool;
    vector<TNode*> freeList;
    NodePool(){ pool.reserve(1<<20); freeList.reserve(1<<20); }
    ~NodePool(){ for(auto p: pool) delete p; }
    TNode* alloc(int k,long long v,int b){
        if (!freeList.empty()){
            TNode* t = freeList.back(); freeList.pop_back();
            new (t) TNode(k,v,b, (uint32_t)rng());
            return t;
        }else{
            TNode* t = new TNode(k,v,b, (uint32_t)rng());
            pool.push_back(t);
            return t;
        }
    }
    void freeNode(TNode* t){ if(!t) return; freeList.push_back(t); }
    static inline uint64_t rng(){
        static uint64_t x=88172645463393265ull;
        x ^= x<<7; x ^= x>>9;
        return x;
    }
} NP;

static inline void pull(TNode* t){
    t->agg = Agg(t->val, t->br, NEG_INF, -2);
    if (t->l) t->agg = mergeAgg(t->l->agg, t->agg);
    if (t->r) t->agg = mergeAgg(t->agg, t->r->agg);
}
static void split(TNode* t, int key, TNode* &L, TNode* &R){
    if (!t){ L=R=nullptr; return; }
    if (key < t->key){
        split(t->l, key, L, t->l);
        pull(t);
        R = t;
    }else{
        split(t->r, key, t->r, R);
        pull(t);
        L = t;
    }
}
static TNode* merge(TNode* L, TNode* R){
    if (!L) return R;
    if (!R) return L;
    if (L->pri < R->pri){
        L->r = merge(L->r, R);
        pull(L);
        return L;
    }else{
        R->l = merge(L, R->l);
        pull(R);
        return R;
    }
}
// insert unique key
static void insertNode(TNode* &root, int key, long long val, int br){
    TNode *A, *B;
    split(root, key, A, B);
    // remove any existing at key (shouldn't exist, αλλά ασφαλές)
    TNode *C, *D;
    split(B, key, C, D); // C has keys <= key
    // delete C (single node at key) if present
    if (C){
        // extract left and right of C to free C
        TNode *CL = C->l, *CR = C->r;
        NP.freeNode(C);
        C = merge(CL, CR); // shouldn't happen (unique keys) but keep robust
    }
    TNode* mid = NP.alloc(key, val, br);
    root = merge(merge(A, mid), D);
}
static void eraseKey(TNode* &root, int key){
    TNode *A,*B; split(root, key-1, A, B);
    TNode *C,*D; split(B, key, C, D); // C contains key
    // free all nodes in C (should be one)
    // Rather than recursive free, we just discard one node; C might be multi if corrupt;
    // We'll in-order free nodes in C to freelist
    if (C){
        // iterative stack
        vector<TNode*> st; st.push_back(C);
        while(!st.empty()){
            TNode* t = st.back(); st.pop_back();
            if (!t) continue;
            st.push_back(t->l);
            st.push_back(t->r);
            NP.freeNode(t);
        }
        C = nullptr;
    }
    root = merge(A, D);
}
static Agg rangeQuery(TNode* &root, int L, int R){
    if (!root) return Agg();
    TNode *A,*B,*C;
    split(root, L-1, A, B);
    split(B, R, B, C);
    Agg res = (B? B->agg : Agg());
    root = merge(A, merge(B, C));
    return res;
}

/* ============== per-centroid treap roots ============== */
vector<TNode*> roots; // roots[cid]

/* =================== Main =================== */
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    g.assign(N+1, {});
    for (int i=0;i<N-1;i++){
        int u,v,w; cin>>u>>v>>w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }
    build_lca(1);

    // centroid decomposition
    cdMarked.assign(N+1, 0);
    subSize.assign(N+1, 0);
    cpath.assign(N+1, {});
    build_cd(1);

    roots.assign(N+1, nullptr);

    cin >> M;
    vector<int> A; A.reserve(M+5); // store nodes by position (1-based externally)
    long long last_ans = 0;
    int sz = 0;

    for (int qi=0; qi<M; ++qi){
        int tp; cin >> tp;
        if (tp == 1){
            unsigned long long x; cin >> x;
            int xx = int( ((x ^ abs(last_ans)) % (unsigned long long)N) ) + 1;
            A.push_back(xx);
            ++sz;
            // update all centroid ancestors for this node
            for (const auto &ci : cpath[xx]){
                insertNode(roots[ci.cid], sz, ci.d, ci.branch);
            }
        }else if (tp == 2){
            if (sz > 0){
                int y = A.back(); A.pop_back();
                // erase from all centroid ancestors
                for (const auto &ci : cpath[y]){
                    eraseKey(roots[ci.cid], sz); // erase position sz
                }
                --sz;
            }
        }else{ // tp == 3
            unsigned long long l, r, x; cin >> l >> r >> x;
            if (sz == 0){
                cout << 0 << '\n';
                last_ans = 0;
                continue;
            }
            
            int ll = int( ((l ^ abs(last_ans)) % (unsigned long long)sz) ) + 1;
            int rr = int( ((r ^ abs(last_ans)) % (unsigned long long)sz) ) + 1;
            if (ll > rr) swap(ll, rr);
            int xx = int( ((x ^ abs(last_ans)) % (unsigned long long)N) ) + 1;

            long long ans = NEG_INF;
            // For each centroid on x's path, query treap range [ll, rr]
            for (const auto &ci : cpath[xx]){
                TNode* &root = roots[ci.cid];
                if (!root) continue;
                Agg got = rangeQuery(root, ll, rr);
                long long cand = NEG_INF;
                if (got.v1 != NEG_INF){
                    if (got.b1 != ci.branch) cand = got.v1;
                    else if (got.v2 != NEG_INF) cand = got.v2;
                }
                if (cand != NEG_INF){
                    ans = max(ans, ci.d + cand); // dist(x,cid) + best_excluding_branch
                }
            }
            // Άν για κάποιο λόγο δεν βρέθηκε (δεν πρέπει), βάλτο 0
            if (ans == NEG_INF) ans = 0;
            cout << ans << '\n';
            last_ans = ans;
        }
    }
    return 0;
}
