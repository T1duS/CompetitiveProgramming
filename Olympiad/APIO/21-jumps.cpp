#include "jumps.h"

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

const int MAXN = 200005;

int a[MAXN],ng[MAXN],pg[MAXN];
int dist[MAXN];

int lft[MAXN][22],rgt[MAXN][22];
int lftmax[MAXN][22],rgtmax[MAXN][22];

int n;

int segpg[2*MAXN];
vi segng[2*MAXN];

int querypg(int l,int r){
	l += n;
	r += n+1;
	int res = l;
	while(l < r){
		if(l%2) remin(res,segpg[l++]);
		if(r%2) remin(res,segpg[--r]);
		l /= 2;
		r /= 2;
	}
	return res;
}

int queryng(int l,int r,int x){
	// trace(l,r,x);
	int res = r;
	l += n;
	r += n+1;
	while(l < r){
		if(l%2){
			if(segng[l][0] <= x){
				auto it = lower_bound(all(segng[l]),x+1);
				it--;
				remax(res,(*it));
			}
			l++;
		}
		if(r%2){
			--r;
			if(segng[r][0] <= x){
				auto it = lower_bound(all(segng[r]),x+1);
				it--;
				remax(res,(*it));
			}
		}
		l /= 2;
		r /= 2;
	}
	// trace(res);
	return res;
}

void init(int N, vi H) {
	n = N;
	REP(i,n){
		a[i] = H[i];
	}
	stack<int> st;
	REP(i,n){
		while(SZ(st) and H[st.top()] < H[i]){
			ng[st.top()] = i;
			st.pop();
		}
		st.push(i);
	}
	while(!st.empty()){
		ng[st.top()] = st.top();
		st.pop();
	}
	FORD(i,n-1,0){
		while(SZ(st) and H[st.top()] < H[i]){
			pg[st.top()] = i;
			st.pop();
		}
		st.push(i);
	}
	while(!st.empty()){
		pg[st.top()] = st.top();
		st.pop();
	}
	REP(i,n){
		lft[i][0] = pg[i];
		lftmax[i][0] = pg[i];
		rgt[i][0] = ng[i];
		rgtmax[i][0] = ng[i];
		segpg[i+n] = pg[i];
		segng[i+n].pb(ng[i]);
	}
	FORD(i,n-1,1){
		segpg[i] = min(segpg[2*i],segpg[2*i+1]);
		for(auto x:segng[2*i]) segng[i].pb(x);
		for(auto x:segng[2*i+1]) segng[i].pb(x);
		sort(all(segng[i]));
	}
	// REP(i,2*n){
	// 	trace(i,SZ(segng[i]));
	// 	for(auto x:segng[i]) trace(x);
	// }
	FOR(j,1,20){
		REP(i,n){
			lft[i][j] = lft[lft[i][j-1]][j-1];
			rgt[i][j] = rgt[rgt[i][j-1]][j-1];
			lftmax[i][j] = min(lftmax[lftmax[i][j-1]][j-1],lftmax[rgtmax[i][j-1]][j-1]);
			rgtmax[i][j] = max(rgtmax[lftmax[i][j-1]][j-1],rgtmax[rgtmax[i][j-1]][j-1]);
		}
	}
}

int minimum_jumps(int A, int B, int C, int D) {
	int l = A,r = B;
	int cnt = 1;
	l = querypg(A,B);
	r = queryng(A,B,D);
	if(r >= C) return cnt;
	FORD(j,19,0){
		if(max(rgtmax[l][j],rgtmax[r][j]) < C){
			cnt += (1<<j);
			int newl = min(lftmax[l][j],lftmax[r][j]);
			int newr = max(rgtmax[l][j],rgtmax[r][j]);
			l = newl;
			r = newr;
		}
	}
	if(ng[l] >= C and ng[l] <= D) return cnt+1;
	FORD(j,19,0){
		if(rgt[r][j] < C){
			cnt += (1<<j);
			r = rgt[r][j];
		}
	}
	if(ng[r] >= C and ng[r] <= D) return cnt+1;
	return -1;
}
