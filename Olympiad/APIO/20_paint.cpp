#include "paint.h"
#include <bits/stdc++.h>
using namespace std;
 
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

int n,m,k;

vi a,c;
vvi b;


int dp[MAXN];

bool valid[MAXN];
vi gg[MAXN];
vi lol[MAXN];
int cnt[MAXN];

void checksegments(){
	REP(i,m){
		for(auto x:b[i]) gg[x].pb(i);
	}
	REP(i,n){
		for(auto x:gg[c[i]]) lol[i].pb({(x-i+n)%m});
	}
	REP(i,n){
		if(i >= m){
			for(auto x:lol[i-m]) cnt[x]--;
		}
		for(auto x:lol[i]){
			cnt[x]++;
			if(cnt[x] == m) valid[i+1-m] = 1;
		}

	}
}

int seg[MAXN*2];

void upd(int pos,int val){
	pos += n+1;
	seg[pos] = val;
	pos /= 2;
	while(pos){
		seg[pos] = min(seg[pos*2],seg[pos*2+1]);
		pos /= 2;
	}
}

int quer(int l,int r){
	l += n+1;
	r += n+1;
	int res = INF;
	while(l < r){
		if(l%2) remin(res,seg[l++]);
		if(r%2) remin(res,seg[--r]);
		l /= 2;
		r /= 2;
	}
	return res;
}

int minimumInstructions(int N, int M, int K, vi C, vi A, vvi B) {
	n = N;
	m = M;
	k = K;
	a = A;
	b = B;
	c = C;
	checksegments();
	dp[0] = 0;
	upd(0,0);
	FOR(i,1,n+1){
		dp[i] = INF;
		if(valid[i-m]) remin(dp[i],quer(i-m,i)+1);
		upd(i,dp[i]);
	}
	if(dp[n] == INF) return -1;
	return dp[n];
}