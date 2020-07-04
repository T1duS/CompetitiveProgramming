/*
Soln:
https://www.youtube.com/watch?v=g2-kTX0GIOg
*/

// --------------------------------------------------<TEMPLATE>--------------------------------------------------
// --------------------<optimizations>--------------------
#pragma GCC optimize("Ofast,unroll-loops")
/* I don't understand these pragmas at all. 
   Earlier I added all the optimizations I could find but 
   upon my short amount of testing, these 2 are enough and adding more makes it slower. */
 
// -------------------</optimizations>--------------------
 
// ---------------<Headers and namespaces>----------------
#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <ratio>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
 
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace __gnu_cxx;
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
#define ITR :: iterator it
#define WL(t) while(t --)
#define SZ(x) ((int)(x).size())
#define runtime() ((double)clock() / CLOCKS_PER_SEC)
#define TR(container,it) for(typeof(container.begin()) it=container.begin();it!=container.end();it++)
#define sqr(x) ((x)*(x))
#define inrange(i,a,b) ((i>=min(a,b)) && (i<=max(a,b)))
 
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
    cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
    const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
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
 
// -----------------------</Consts>-----------------------
 
// -------------------------<RNG>-------------------------
mt19937 RNG(chrono::steady_clock::now().time_since_epoch().count()); 
#define SHUF(v) shuffle(all(v), RNG);
// Use mt19937_64 for 64 bit random numbers.
 
// ------------------------</RNG>-------------------------

// --------------------------------------------------</TEMPLATE>--------------------------------------------------
 
void solvethetestcase();
 
signed main(){
    // (UNCOMMENT FOR CIN/COUT) \
    FAST_IO
    PRECISION(10)
 
    int t = 1;
    // (UNCOMMENT FOR MULTIPLE TEST CASES) \
    sfl(t);
    FOR(testcase,1,t+1){
        // (UNCOMMENT FOR CODEJAM) \
        printf("Case #%lld: ",testcase); 
        solvethetestcase();
    }
}   
 
int n,k;
int a[100005],pref[100005];
int dp[100005][2];
signed opt[100005][201];

int ptr;

vector<pair<pii,int> > lines;

void reset(){
    lines.clear();
    ptr = 0;
}

bool bad(pii l1,pii l2,pii l3){
    // check if intersection of l1,l3 is <= intersection of l1,l2
    // x*l1.F+l1.S = x*l3.F+l3.S
    // x*(l3.F-l1.F) = l1.S-l3.S
    // x = (l1.S-l3.S)/(l3.F-l1.F)
    // (l1.S-l3.S)/(l3.F-l1.F) <= (l1.S-l2.S)/(l2.F-l1.F)
    return (l1.S-l3.S)*(l2.F-l1.F) <= (l1.S-l2.S)*(l3.F-l1.F);
}

void add(int m,int c,int ind){ // y = mx+c
    pair<pii,int> u = {{m,c},ind};
    while(lines.size() >= 2 and bad(lines[lines.size()-2].F,lines[lines.size()-1].F,u.F)) lines.pop_back();
    lines.pb(u);
}

pii quer(int x){
    if(!lines.size()) return {-INF,-1};
    if(ptr >= lines.size()) ptr = lines.size()-1;
    while(ptr < lines.size()-1 and lines[ptr].F.F*x+lines[ptr].F.S < lines[ptr+1].F.F*x+lines[ptr+1].F.S) ptr++;
    return {lines[ptr].F.F*x+lines[ptr].F.S,lines[ptr].S};
}
 
void solvethetestcase(){
    sfl2(n,k)
    FOR(i,1,n+1){
        sfl(a[i])
        pref[i] = pref[i-1]+a[i];
    }
    if(k == 0){
        printf("0\n");
        return;
    }
    FOR(j,1,k+1){
        int cur = j%2;
        int prev = 1-cur;
        reset();
        FOR(i,1,n+1){
            pii u = quer(pref[i]);
            dp[i][cur] = u.F;
            opt[i][j] = u.S;
            if(dp[i][prev] != -INF) add(pref[i],dp[i][prev]-pref[i]*pref[i],i);
        }
    }
    pfl(dp[n][k%2]);
    int cur = opt[n][k];
    REP(i,k){
        pwe(cur)
        if(i+1 != k) cur = opt[cur][k-1-i];
    }
    printf("\n");
}
