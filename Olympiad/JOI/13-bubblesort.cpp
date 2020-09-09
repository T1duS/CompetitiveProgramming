/*
Soln:
https://github.com/dolphingarlic/CompetitiveProgramming/blob/master/JOI/JOI%2013-bubblesort.cpp
*/

// --------------------------------------------------<TEMPLATE>--------------------------------------------------
#pragma GCC optimize("Ofast,unroll-loops")

#include <bits/stdc++.h>
using namespace std;
 
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
 
#define FLSH fflush(stdout)
#define fileIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#define PRECISION(x) cout << fixed << setprecision(x); 
#define FAST_IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
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
 
// --------------------------------------------------</TEMPLATE>--------------------------------------------------
 
void solvethetestcase();
 
signed main(){
    FAST_IO

    int t = 1;
    FOR(testcase,1,t+1){
        solvethetestcase();
    }
}   
 
int n;
int a[100005];
int seg[200005];

vi cand;

int inv = 0;

void upd(int pos,int val){
    pos += n;
    while(pos){
        seg[pos] += val;
        pos /= 2;
    }
}

int quer(int l,int r){
    int res = 0;
    l += n;
    r += n+1;
    while(l < r){
        if(l%2) res += seg[l++];
        if(r%2) res += seg[--r];
        l /= 2;
        r /= 2;
    }
    return res;
}

int calc(int i,int j){
    int res = quer(a[j],a[i])+quer(a[j]+1,a[i]-1)+1;
    return res;
}
int solve(int l,int r,int optmn,int optmx){
    int m = (l+r)/2;
    int res = -1,ind = max(cand[m]+1,optmn);
    // everything from cand[m]+1 to optmn-1 should already be updated
    // FOR(i,cand[m]+1,optmn) upd(a[i],1);
    FOR(i,max(cand[m]+1,optmn),optmx+1){
        int gg = calc(cand[m],i);
        if(gg > res){
            res = gg;
            ind = i;
        }
        upd(a[i],1);
    }

    int resl = -1,resr = -1;
    if(l != m){
        FOR(i,cand[(l+m-1)/2]+1,min(cand[m],optmn-1)+1) upd(a[i],1);
        FOR(i,max(cand[m],optmn-1)+1,optmx+1) upd(a[i],-1);
        resl = solve(l,m-1,optmn,ind);
        FOR(i,cand[(l+m-1)/2]+1,min(cand[m],optmn-1)+1) upd(a[i],-1);
        FOR(i,max(cand[m],optmn-1)+1,optmx+1) upd(a[i],1);
    }
    if(m != r){
        FOR(i,cand[m]+1,cand[(r+m+1)/2]+1) upd(a[i],-1);
        FOR(i,max(ind,cand[(r+m+1)/2]+1),optmx+1) upd(a[i],-1);
        resr = solve(m+1,r,ind,optmx);
        FOR(i,cand[m]+1,cand[(r+m+1)/2]+1) upd(a[i],1);
        FOR(i,max(ind,cand[(r+m+1)/2]+1),optmx+1) upd(a[i],1);
    }

    FOR(i,max(cand[m]+1,optmn),optmx+1) upd(a[i],-1);

    return max({res,resl,resr});
}
 
void solvethetestcase(){
    cin >> n;
    bool flag1 = 1,flag2 = 1;
    set<int> s;
    mii m;
    REP(i,n){
        cin >> a[i];
        if(i and a[i] < a[i-1]) flag1 = 0;
        if(a[i] == a[i-1]) flag2 = 0;
        s.insert(a[i]);
    }
    if(flag1 and flag2){
        printf("1\n");
        return;
    }
    if(flag1){
        printf("0\n");
        return;
    }
    int bzz = 0;
    for(auto x:s) m[x] = bzz++;
    REP(i,n){
        a[i] = m[a[i]];
    }
    cand.pb(0);
    FOR(i,1,n){
        if(a[i] > a[cand.back()]) cand.pb(i);
    }
    FORD(i,n-1,0){
        upd(a[i],1);
        inv += quer(0,a[i]-1);
    }
    FORD(i,n-1,0){
        upd(a[i],-1);
    }  
    cout << (inv-solve(0,cand.size()-1,0,n-1)) << endl;
}
    
