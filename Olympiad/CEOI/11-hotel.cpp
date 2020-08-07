#include<bits/stdc++.h>
using namespace std;

#define int long long

#define vi vector<int>
#define pb push_back
#define REP(i,n) for(int i = 0; i < n; i++)
#define FOR(i,a,b) for(int i = a; i < b; i++)
#define all(v) v.begin(),v.end()
#define remax(a,b) a = max(a,(int)(b))
#define pii pair<int,int>
#define F first
#define S second

const int MX = 300005;

int n,m,o;
priority_queue<int> pq;
vector<pair<pii,int> > v; // {{capacity,type},cost}
vi ans;

signed main(){
	cin >> n >> m >> o;
	REP(i,n){
		int x,y; cin >> x >> y;
		v.pb({{y,1},x});
	}
	REP(i,m){
		int x,y; cin >> x >> y;
		v.pb({{y,0},x});
	}
	sort(all(v));
	REP(i,n+m){
		if(v[i].F.S == 0){
			pq.push(v[i].S);
		}
		else{
			if(pq.empty()) continue;
			ans.pb(-pq.top()+v[i].S);
			pq.pop();
		}
	}
	int res = 0;
	sort(all(ans));
	REP(i,min((int)ans.size(),o)){
		if(ans[i] >= 0) break;
		res -= ans[i];
	}
	cout << res << "\n";
}