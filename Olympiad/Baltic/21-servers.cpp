// --------------------------------------------------<TEMPLATE>--------------------------------------------------
// --------------------<optimizations>--------------------
/*
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,fma")
*/ 
// -------------------</optimizations>--------------------
 
// ---------------<Headers and namespaces>----------------
#include <bits/stdc++.h>
using namespace std;
 
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
*/
 
// ---------------</Headers and namespaces>---------------
 
// -----------------<Defines and typedefs>----------------
// typedef tree<int,null_type,less<int>,rb_tree_tag, 
// tree_order_statistics_node_update> indexed_set; // use less_equal for multiset
// order_of_key (val): returns the no. of values less than val
// find_by_order (k): returns the iterator to kth largest element.(0-based)
 
typedef long double LD;
typedef long long ll;
#define int ll
#define pb push_back
#define mp make_pair
#define REP(i,n) for (int i = 0; i < n; i++)
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define REPD(i,n) for (int i = n-1; i >= 0; i--)
#define FORD(i,a,b) for (int i = a; i >= b; i--)
#define remax(a,b) a = max(a,b)
#define remin(a,b) a = min(a,b)
#define all(v) v.begin(),v.end()
typedef map<int,int> mii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;
typedef vector<pii> vpii;
#define F first
#define S second
#define PQ(type) priority_queue<type>
#define PQD(type) priority_queue<type,vector<type>,greater<type> >
#define WL(t) while(t --)
#define SZ(x) ((int)(x).size())
#define runtime() ((double)clock() / CLOCKS_PER_SEC)
#define inrange(i,a,b) ((i>=min(a,b)) && (i<=max(a,b)))
 
/*
// -----<SCANF>-----
#define sfi(x) scanf("%d",&x);
#define sfi2(x,y) scanf("%d%d",&x,&y);
#define sfi3(x,y,z) scanf("%d%d%d",&x,&y,&z);
 
#define sfl(x) scanf("%lld",&x);
#define sfl2(x,y) scanf("%lld%lld",&x,&y);
#define sfl3(x,y,z) scanf("%lld%lld%lld",&x,&y,&z);
#define sfl4(x,y,z,x1) scanf("%lld%lld%lld%lld",&x,&y,&z,&x1);
#define sfl5(x,y,z,x1,y1) scanf("%lld%lld%lld%lld%lld",&x,&y,&z,&x1,&y1);
#define sfl6(x,y,z,x1,y1,z1) scanf("%lld%lld%lld%lld%lld%lld",&x,&y,&z,&x1,&y1,&z1);
 
#define sfs(x) scanf("%s",x);
#define sfs2(x,y) scanf("%s%s",x,y);
#define sfs3(x,y,z) scanf("%s%s%s",x,y,z);
// ----</SCANF>-----
 
// ----<PRINTF>-----
#define pfi(x) printf("%d\n",x);
#define pfi2(x,y) printf("%d %d\n",x,y);
#define pfi3(x,y,z) printf("%d %d %d\n",x,y,z);
 
#define pfl(x) printf("%lld\n",x);
#define pfl2(x,y) printf("%lld %lld\n",x,y);
#define pfl3(x,y,z) printf("%lld %lld %lld\n",x,y,z);
 
#define pfs(x) printf("%s\n",x);
#define pfs2(x,y) printf("%s %s\n",x,y);
#define pfs3(x,y,z) printf("%s %s %s\n",x,y,z);
 
#define pwe(x) printf("%lld ",x); // print without end
// ----</PRINTF>----
*/
#define FLSH fflush(stdout)
#define fileIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#define PRECISION(x) cout << fixed << setprecision(x); 
#define FAST_IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
// ----------------</Defines and typedefs>----------------
 
// -------------------<Debugging stuff>-------------------
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
    cout << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
    const char* comma = strchr(names + 1, ',');cout.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif
 
// ------------------</Debugging stuff>-------------------
 
// ------------------------<Consts>-----------------------
const int MAXN = 120005;
const int SQRTN = 1003;
const int LOGN = 22;
const double PI=acos(-1);
 
#ifdef int
const int INF=1e16;
#else
const int INF=1e9;
#endif
 
const int MOD = 1000000007;
const int FMOD = 998244353;
const double eps = 1e-9;
// -----------------------</Consts>-----------------------
/*
// -------------------------<RNG>-------------------------
mt19937 RNG(chrono::steady_clock::now().time_since_epoch().count()); 
#define SHUF(v) shuffle(all(v), RNG);
// Use mt19937_64 for 64 bit random numbers.
 
// ------------------------</RNG>-------------------------
 
// ----------------------<MATH>---------------------------
template<typename T> T gcd(T a, T b){return(b?__gcd(a,b):a);}
template<typename T> T lcm(T a, T b){return(a*(b/gcd(a,b)));}
int add(int a, int b, int c = MOD){int res=a+b;return(res>=c?res-c:res);}
int mod_neg(int a, int b, int c = MOD){int res;if(abs(a-b)<c)res=a-b;else res=(a-b)%c;return(res<0?res+c:res);}
int mul(int a, int b, int c = MOD){ll res=(ll)a*b;return(res>=c?res%c:res);}
int muln(int a, int b, int c = MOD){ll res=(ll)a*b;return ((res%c)+c)%c;}
ll mulmod(ll a,ll b, ll m = MOD){ll q = (ll)(((LD)a*(LD)b)/(LD)m);ll r=a*b-q*m;if(r>m)r%=m;if(r<0)r+=m;return r;}
template<typename T>T expo(T e, T n){T x=1,p=e;while(n){if(n&1)x=x*p;p=p*p;n>>=1;}return x;}
template<typename T>T power(T e, T n, T m = MOD){T x=1,p=e;while(n){if(n&1)x=mul(x,p,m);p=mul(p,p,m);n>>=1;}return x;}
template<typename T>T extended_euclid(T a, T b, T &x, T &y){T xx=0,yy=1;y=0;x=1;while(b){T q=a/b,t=b;b=a%b;a=t;\
t=xx;xx=x-q*xx;x=t;t=yy;yy=y-q*yy;y=t;}return a;}
template<typename T>T mod_inverse(T a, T n = MOD){T x,y,z=0;T d=extended_euclid(a,n,x,y);return(d>1?-1:mod_neg(x,z,n));}
 
const int FACSZ = 1; // Make sure to change this
 
int fact[FACSZ],ifact[FACSZ];
 
void precom(int c = MOD){
    fact[0] = 1;
    FOR(i,1,FACSZ) fact[i] = mul(fact[i-1],i,c);
    ifact[FACSZ-1] = mod_inverse(fact[FACSZ-1],c);
    REPD(i,FACSZ-1){
        ifact[i] = mul(i+1,ifact[i+1],c);
    }
}
 
int ncr(int n,int r,int c = MOD){
    return mul(mul(ifact[r],ifact[n-r],c),fact[n],c);
} 
*/
// ----------------------</MATH>--------------------------
// --------------------------------------------------</TEMPLATE>--------------------------------------------------
 
void solvethetestcase();
 
signed main(){
    // comment when using scanf,printf
    FAST_IO
    int t = 1;
    // (UNCOMMENT FOR MULTIPLE TEST CASES)
    // cin >> t;
    FOR(testcase,1,t+1){
        // (UNCOMMENT FOR CODEJAM)
        // printf("Case #%lld: ",testcase); 
        solvethetestcase();
    }
}   
 
int n,q;
vector<pair<int,pii> > queries;
vpii adj[MAXN];
int dep[MAXN],edge_val[MAXN],par[MAXN][21];
int up_inc[MAXN],up_dec[MAXN];
vi gg[MAXN],gg_inc[MAXN],gg_dec[MAXN];
int seg[4*MAXN],ans[2*MAXN];

void dfs(int u,int p,int d){
    par[u][0] = p;
    dep[u] = d;
    for(auto v:adj[u]){
        if(v.F == p) continue;
        edge_val[v.F] = v.S;
        if(v.S < edge_val[u]){
            up_inc[v.F] = up_inc[u];
            up_dec[v.F] = u;
        }
        else{
            up_dec[v.F] = up_dec[u];
            up_inc[v.F] = u;
        }
        dfs(v.F,u,d+1);
    }
}

int incpath(int u,int v){
    int d = max(dep[up_inc[u]],dep[up_dec[v]]);
    int vp = edge_val[v];
    if(dep[u] < dep[v]){
        FORD(j,20,0){
            if(dep[v]-(1<<j) > dep[u]) v = par[v][j];
        }
        if(par[v][0] == u){
            if(d > dep[u]) return INF;
            return vp;
        }
        v = par[v][0];
    }
    else if(dep[v] < dep[u]){
        FORD(j,20,0){
            if(dep[u]-(1<<j) > dep[v]) u = par[u][j];
        }
        if(par[u][0] == v){
            if(d > dep[v]) return INF;
            return edge_val[u];
        }
        u = par[u][0];
    }
    FORD(j,20,0){
        if(par[u][j] != par[v][j]){
            u = par[u][j];
            v = par[v][j];
        }
    }
    if(d <= dep[u]-1 and edge_val[u] < edge_val[v]) return vp;  
    return INF;
}

void update(int t,int val){
    t += 2*MAXN;
    while(t){
        seg[t] += val;
        t /= 2;
    }
}

int query(int t){
    int l = 0,r = t+1;
    l += 2*MAXN;
    r += 2*MAXN;
    int res = 0;
    while(l < r){
        if(l&1) res += seg[l++];
        if(r&1) res += seg[--r];
        l >>= 1;
        r >>= 1;
    }
    return res;
}

void dfs_solve(int u){
    if(u != 1) update(edge_val[u],1);
    for(auto t:gg_inc[u]) ans[t] -= query(t);
    for(auto v:adj[u]){
        if(par[v.F][0] == u) dfs_solve(v.F);
    }
    for(auto t:gg[u]) ans[t] += query(t);
    for(auto t:gg_dec[u]) update(t,-1);
}
 
void solvethetestcase(){
    cin >> n >> q;
    REP(i,q+n-1){
        char type; cin >> type;
        if(type == 'S'){
            int u,v; cin >> u >> v;
            adj[u].pb({v,i});
            adj[v].pb({u,i});
            queries.pb({1,{u,v}});
        }
        else if(type == 'Q'){
            int u,v; cin >> u >> v;
            queries.pb({2,{v,u}});
            // tell whether there is an increasing path from v->u 
            // st. value of last edge <= i
        }
        else{
            int u; cin >> u;
            queries.pb({3,{u,0}});
            // number of increasing paths starting from u
            // st. value of last edge <= i
        }
    }
    FOR(i,1,n+1){
        reverse(all(adj[i]));
    }
    dfs(1,1,0);
    FOR(j,1,20){
        FOR(i,1,n+1){
            par[i][j] = par[par[i][j-1]][j-1];
        }
    }
    REP(i,q+n-1){
        if(queries[i].F == 1){
            int u = queries[i].S.F;
            int v = queries[i].S.S;
            if(par[u][0] == v) swap(u,v);
            gg_dec[up_dec[v]].pb(i);
        }
        else if(queries[i].F == 3){
            int u = queries[i].S.F;
            gg[u].pb(i);
            gg_inc[up_inc[u]].pb(i);
        }
    }
    dfs_solve(1);
    REP(i,q+n-1){
        if(queries[i].F == 2){
            int u = queries[i].S.F;
            int v = queries[i].S.S;
            if(u == v or incpath(u,v) < i) cout << "yes\n";
            else cout << "no\n";
        }
        else if(queries[i].F == 3){
            cout << ans[i]+1 << "\n";
        }
    }
}