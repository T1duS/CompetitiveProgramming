/*
Soln:
Use centroid decomposition
At each centroid root the tree at centroid define the following

Let u,u1,u2...,uk,centroid be the path from u to centroid
and let w[x] be the weight of x->parent of x

smtoroot[u] = a[u]-w[u]+a[u1]-w[u1]...a[uk]-w[uk]
smfromroot[u] = a[centroid]-w[uk]+a[uk]-w[uk-1]...a[u1]-w[u]
mntoroot[u] = min prefix of the given expansion of smtoroot[u]
mnfromroot[u] = min prefix of the given expansion of smfromroot[u]

All these values can be calculated using simple dfs

Basically you need the number of vertices u,v (with path u,u1,u2,...,uk,v)such that
minimum prefix sum of the following expansion
a[u]-w[u]+a[u1]-w[u1]...a[uk]-w[uk] 
is >= 0 

u and v lie on different subtrees of centroid
write the expression as
(a[u]-w[u]+.....+a[child of centroid]-w[child of centroid]) -> part I
+(a[centroid]-w[centroid]+.....+a[uk]-w[uk]) -> part II

In other words the condition is min prefix of part I >= 0 and 
sum of part I + min prefix of part II >= 0

This is same as
mntoroot[u] >= 0 ans
smtoroot[u]+mnfromroot[v] >= 0

One more condition to check is u and v lie on different subtrees
This can be done using 2 pointer

Complexity O(nlogn)
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
// typedef tree<int,null_type,less<int>,rb_tree_tag, \
tree_order_statistics_node_update> indexed_set; // use less_equal for multiset
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
#define TRACE
 
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
    // (UNCOMMENT FOR MULTIPLE TEST CASES) \
    cin >> t;
    FOR(testcase,1,t+1){
        // (UNCOMMENT FOR CODEJAM) \
        printf("Case #%lld: ",testcase); 
        solvethetestcase();
    }
}   
 
int n;
int a[MAXN];
vpii adj[MAXN];
int ans = 0;
bitset<MAXN> vis;

int smtoroot[MAXN],smfromroot[MAXN];
int mntoroot[MAXN],mnfromroot[MAXN];
int subtree[MAXN];

int sz[MAXN];

int cnt[MAXN];

vi cc;

void dfs1(int u,int p){
	sz[u] = 1;
	cc.pb(u);
	for(auto v:adj[u]){
		if(v.F != p and vis[v.F] == 0){
			dfs1(v.F,u);
			sz[u] += sz[v.F];
		}
	}
}

int get_centroid(int u,int p,int tot){
	for(auto v:adj[u]){
		if(v.F != p and vis[v.F] == 0){
			if(sz[v.F]*2 > tot){
				return get_centroid(v.F,u,tot);
			}
		}
	}
	return u;
}

void dfs2(int u,int p,int s){
	subtree[u] = s;
	for(auto v:adj[u]){
		if(v.F != p and vis[v.F] == 0){
			smtoroot[v.F] = smtoroot[u]+a[v.F]-v.S;
			smfromroot[v.F] = smfromroot[u]+a[u]-v.S;
			mntoroot[v.F] = min(a[v.F]-v.S,a[v.F]-v.S+mntoroot[u]);
			mnfromroot[v.F] = min(mnfromroot[u],smfromroot[u]+a[u]-v.S);
			dfs2(v.F,u,(u==p)?v.F:s);
		}
	}
}

void centroid_decomposition(int u){
	cc.clear();
	dfs1(u,u);
	int cen = get_centroid(u,u,sz[u]);
	smtoroot[cen] = 0;
	mntoroot[cen] = 0;
	smfromroot[cen] = 0;
	mnfromroot[cen] = 0;
	dfs2(cen,cen,-1);
	vpii v1,v2;
	for(auto x:cc){
		if(x == cen) continue;
		if(mntoroot[x] >= 0){
			ans++;
			v1.pb({smtoroot[x],subtree[x]});
			cnt[subtree[x]]++;
		}
		ans += (mnfromroot[x] >= 0);
		v2.pb({-mnfromroot[x],subtree[x]});
	}
	sort(all(v1));
	sort(all(v2));
	int c1 = 0,c2 = 0;
	while(c1 < v1.size()){
		// no. of values i,j such that
		// v1[i].F >= v2[j].F and
		// v2[i].S != v2[j].S;
		while(c2 == v2.size() or v1[c1].F < v2[c2].F){
			cnt[v1[c1].S]--;
			c1++;
			if(c1 == v1.size()) break;
		}
		if(c2 == v2.size() or c1 == v1.size()) break;
		ans += v1.size()-c1-cnt[v2[c2].S];
		c2++;
	}
	vis[cen] = 1;
	for(auto v:adj[cen]){
		if(!vis[v.F]) centroid_decomposition(v.F);
	}
}
 
void solvethetestcase(){
    cin >> n;
    REP(i,n) cin >> a[i+1];
    REP(i,n-1){
    	int u,v,w; cin >> u >> v >> w;
    	adj[u].pb({v,w});
    	adj[v].pb({u,w});
    }
    centroid_decomposition(1);
    cout << ans << "\n";
}
