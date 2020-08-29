/*
Soln:
https://apio2020.id/assets/problem_discussion.pdf
*/
#include "fun.h"
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


int n;

int sz0[MAXN];
int dep[MAXN];
int dist0[MAXN],dist1[MAXN];
int sub[MAXN];
vi subtreeroots;

vi sub0,sub1,sub2;

bool cmp(int x,int y){
	return dep[x] < dep[y];
}

vi createFunTour(int N, int Q){
	n = N;
	if(n == 2) return {0,1};
	sz0[0] = n;
	int cen = 0;
	FOR(i,1,n){
		sz0[i] = attractionsBehind(0,i);
		if(sz0[i]*2 >= n and sz0[i] < sz0[cen]) cen = i;
	}
	REP(i,n){
		if(i == cen) dep[i] = 0;
		else dep[i] = hoursRequired(cen,i);
		if(dep[i] == 1) subtreeroots.pb(i);
	}
	vi ans,ans1;

	REP(i,n){
		dist0[i] = hoursRequired(i,subtreeroots[0]);
		dist1[i] = hoursRequired(i,subtreeroots[1]);
		if(i != cen){
			if(dep[i] == 1+dist0[i]){
				sub0.pb(i);
				sub[i] = 0;
			}
			else if(dep[i] == 1+dist1[i]){
				sub1.pb(i);
				sub[i] = 1;
			}
			else{
				sub2.pb(i);
				sub[i] = 2;
			}
		}
		else sub[i] = -1;
	}
	sort(all(sub0),cmp);
	sort(all(sub1),cmp);
	sort(all(sub2),cmp);
	int last = -1;

	vi part1,part2;

	FORD(i,n-1,1){
		if(SZ(sub0)*2 >= i){
			for(auto x:sub0){
				part1.pb(x);
			}
			for(auto x:sub1){
				part2.pb(x);
			}
			for(auto x:sub2){
				part2.pb(x);
			}
			sort(all(part1),cmp);
			sort(all(part2),cmp);
			break;
		}
		if(SZ(sub1)*2 >= i){
			for(auto x:sub0){
				part2.pb(x);
			}
			for(auto x:sub1){
				part1.pb(x);
			}
			for(auto x:sub2){
				part2.pb(x);
			}
			sort(all(part1),cmp);
			sort(all(part2),cmp);
			break;
		}
		if(SZ(sub2)*2 >= i){
			for(auto x:sub0){
				part2.pb(x);
			}
			for(auto x:sub1){
				part2.pb(x);
			}
			for(auto x:sub2){
				part1.pb(x);
			}
			sort(all(part1),cmp);
			sort(all(part2),cmp);
			break;
		}
		int cur = cen,sb = -1;
		if(SZ(sub0) and last != 0 and dep[sub0.back()] > dep[cur]){
			cur = sub0.back();
			sb = 0;
		}
		if(SZ(sub1) and last != 1 and dep[sub1.back()] > dep[cur]){
			cur = sub1.back();
			sb = 1;
		}
		if(SZ(sub2) and last != 2 and dep[sub2.back()] > dep[cur]){
			cur = sub2.back();
			sb = 2;
		}

		last = sb;
		ans.pb(cur);
		// trace(cur);
		if(sb == 0) sub0.pop_back();
		if(sb == 1) sub1.pop_back();
		if(sb == 2) sub2.pop_back();
	}
	ans1 = ans;
	if(SZ(part1) > SZ(part2)){
		while(SZ(part1)){
			ans.pb(part1.back());
			part1.pop_back();
			if(SZ(part2)){
				ans.pb(part2.back());
				part2.pop_back();
			}
		}
		ans.pb(cen);
		return ans;
	}

	while(SZ(part1)){
		ans.pb(part1.back());
		ans.pb(part2.back());

		ans1.pb(part2.back());
		ans1.pb(part1.back());

		part1.pop_back();
		part2.pop_back();
	}
	ans.pb(cen);
	ans1.pb(cen);

	vi v,vs;

	REP(i,n){
		if(i){
			if(sub[ans[i]] == sub[ans[i-1]]) return ans1;
			v.pb(dep[ans[i]]+dep[ans[i-1]]);
			vs.pb(dep[ans[i]]+dep[ans[i-1]]);
			// trace(ans[i],sub[i],dep[ans[i]]+dep[ans[i-1]]);
		}
	}
	sort(all(vs));
	reverse(all(v));
	if(v == vs){
		return ans;
	}
	else return ans1;
}