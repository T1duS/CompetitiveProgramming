/*
Soln:
Consider i < j for now
For a fixed i, the optimal j will be monotonic wrt i so we can use DnC DP
Note: We need to consider a[j]-a[i]+sqrt(j-i) instead of a[j]-a[i]+ceil(sqrt(j-i))
The latter is fine for calculating answer but the monotonic condition won't be valid
Solve the j < i case similarly
*/

// --------------------------------------------------<TEMPLATE>--------------------------------------------------
// --------------------<optimizations>--------------------

#pragma GCC optimize("O3")

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
// #define int ll
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
const int MAXN = 1000005;
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
int a[500005];
int ans[500005];
double sqroot[500005];
int sroot[500005];

void solve1(int l,int r,int optl,int optr){
    if(l > r) return;
    // trace(l,r,optl,optr);
    int mid = (l+r)/2;
    int opt = max(optl,mid);
    double cur = (a[opt]+sqroot[opt-mid]);
    FOR(i,max(optl,mid)+1,optr+1){
        double cur2 = (a[i]+sqroot[i-mid]);
        if(cur2 > cur){
            opt = i;
            cur = cur2;
        }
    }
    remax(ans[mid],(a[opt]-a[mid]+sroot[opt-mid]));
    // trace(mid,opt);
    solve1(l,mid-1,optl,opt);
    solve1(mid+1,r,opt,optr);
}

void solve2(int l,int r,int optl,int optr){
    if(l > r) return;
    // trace(l,r,optl,optr);
    int mid = (l+r)/2;
    int opt = optl;
    double cur = (a[opt]+sqroot[mid-opt]);
    FOR(i,optl+1,min(optr,mid)+1){
        double cur2 = (a[i]+sqroot[mid-i]); 
        if(cur2 > cur){
            cur = cur2;
            opt = i;
        }
    }
    remax(ans[mid],(a[opt]-a[mid]+sroot[mid-opt]));
    // trace(mid,opt);
    solve2(l,mid-1,optl,opt);
    solve2(mid+1,r,opt,optr);
}
 
void solvethetestcase(){
    cin >> n;
    FOR(i,1,n+1){
        cin >> a[i];
        ans[i] = 0;
        sqroot[i] = sqrt(i);
        sroot[i] = (int)ceil(sqroot[i]);
        if(sroot[i]*sroot[i] >= i) sroot[i]--;
        if(sroot[i]*sroot[i] < i) sroot[i]++;
    }
    solve1(1,n,1,n);
    // FOR(i,1,n+1) trace(i,ans[i]);
    solve2(1,n,1,n);
    // FOR(i,1,n+1) trace(i,ans[i]);
    FOR(i,1,n+1){
        cout << ans[i] << "\n";
    }
    // cout << runtime() << endl;
}
