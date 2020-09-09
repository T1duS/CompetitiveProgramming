/*
Soln:
https://codeforces.com/blog/entry/82022
*/

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
const int MAXN = 100005;
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
 
int n,q,root;
vi g[MAXN],adj[MAXN];
int dp[MAXN],dep[MAXN],par[MAXN],sz[MAXN];

int ans = 0,tim = 0;
int st[MAXN],fin[MAXN],nxt[MAXN];
int seg[MAXN*4],lazy[MAXN*4];

vi euler;

void dfs(int u,int p,int d){

    par[u] = p;
    dep[u] = d;
    sz[u] = 1;

    if(SZ(g[u]) == 1) dp[u] = 1;
    else dp[u] = 0;

    for(auto v:g[u]){
        if(v != p){
            dfs(v,u,d+1);
            dp[u] += dp[v];
            sz[u] += sz[v];
            adj[u].pb(v);
        }
    }
    REP(i,SZ(adj[u])){
        if(sz[adj[u][i]] > sz[adj[u][0]]) swap(adj[u][0],adj[u][i]);
    }
}

void dfs_hld(int u){
    euler.pb(u);
    st[u] = tim++;
    REP(i,SZ(adj[u])){
        int v = adj[u][i];
        nxt[v] = (i?v:nxt[u]);
        dfs_hld(v);
    }
    fin[u] = tim;
}

void upd(int l,int r){
    FOR(i,l,r+1){
        if(seg[i]) ans++;
        else ans--;
        seg[i] = 1-seg[i];
    }
}

void build(int ind,int l,int r){
    if(l == r){
        seg[ind] = dp[euler[l]];
        return;
    }
    int mid = (l+r)/2;
    build(2*ind,l,mid);
    build(2*ind+1,mid+1,r);
    seg[ind] = (seg[2*ind]+seg[2*ind+1]);
}

void push(int ind,int l,int r){
    if(!lazy[ind]) return;
    lazy[ind] = 0;
    seg[ind] = (r-l+1-seg[ind]);
    if(l != r){
        lazy[2*ind] = 1-lazy[2*ind];
        lazy[2*ind+1] = 1-lazy[2*ind+1];
    }
}

void upd(int ind,int l,int r,int x,int y){
    push(ind,l,r);
    if(r < x or l > y) return;
    if(l >= x and r <= y){
        ans += 2*seg[ind]-(r-l+1);
        lazy[ind] = 1;
        push(ind,l,r);
        return;
    }
    int mid = (l+r)/2;
    upd(2*ind,l,mid,x,y);
    upd(2*ind+1,mid+1,r,x,y);
    seg[ind] = (seg[2*ind]+seg[2*ind+1]);
}
 
void solvethetestcase(){
    cin >> n >> q;
    REP(i,n-1){
        int u,v; cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    FOR(i,1,n+1){
        if(SZ(g[i]) > 1) root = i;
    }
    dfs(root,-1,0);
    nxt[root] = root;
    dfs_hld(root);

    ans = n-2;
    int leaf = dp[root];

    FOR(i,1,n+1){
        dp[i] %= 2;
        ans += 1-dp[i];
    }
    build(1,0,n-1);
    REP(xyz,q){
        int d; 
        mii freq;
        cin >> d;
        REP(i,d){
            int x; cin >> x;
            freq[x]++;
        }
        vi eff;

        for(auto x:freq){
            if(SZ(g[x.F]) == 1 and x.S%2 == 0) eff.pb(x.F);
            if(SZ(g[x.F]) != 1 and x.S%2 == 1) eff.pb(x.F);
        }
        for(auto x:eff){
            int cur = x;
            while(cur != -1){
                upd(1,0,n-1,st[nxt[cur]],st[cur]);
                cur = par[nxt[cur]];
            }
        }
        ans += d;

        if((leaf+SZ(eff))%2) cout << "-1\n";
        else cout << ans << "\n";

        for(auto x:eff){
            int cur = x;
            while(cur != -1){
                upd(1,0,n-1,st[nxt[cur]],st[cur]);
                cur = par[nxt[cur]];
            }
        }
        ans -= d;
    }
}