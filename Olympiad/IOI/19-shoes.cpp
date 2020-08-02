#include "shoes.h"
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vi vector<int>
#define pb push_back
#define REP(i,n) for(int i = 0; i < n; i++)
#define FOR(i,a,b) for(int i = a; i < b; i++)

int n;
vi a;

ll ans = 0;

bool paired(int ind){
	if(ind >= 2*n-1 or ind < 0) return 0;
	return (a[ind]+a[ind+1] == 0 and a[ind] < a[ind+1]);
}

int last[200005];
bool exis[200005];

vi gg1[200005],gg2[200005];
int seg[400005];

void upd(int ind,int val){
	ind += 2*n;
	while(ind){
		seg[ind] += val;
		ind /= 2;
	}
}

int quer(int l,int r){
	l += 2*n;
	r += 2*n+1;
	int res = 0;
	while(l < r){
		if(l%2) res += seg[l++];
		if(r%2) res += seg[--r];
		l /= 2;
		r /= 2;
	}
	return res;
}

ll count_swaps(vector<int> s) {
	n = s.size()/2;
	a = s;
	REP(i,2*n){
		if(a[i] < 0) gg1[-a[i]].pb(i);
		else gg2[a[i]].pb(i);
	}
	int cur = 1;
	FOR(i,1,n+1){
		REP(j,(int)gg1[i].size()){
			a[gg1[i][j]] = -cur;
			a[gg2[i][j]] = cur;
			cur++;
		}
	}
	REP(i,2*n){
		if(exis[n-a[i]]){
			ans += i-last[n-a[i]]-1;
			if(a[i] < 0) ans++;
			ans -= quer(0,last[n-a[i]]);
			upd(last[n-a[i]],1);
			upd(i,-1);
			exis[n+a[i]] = 0;
			exis[n-a[i]] = 0; 
		}
		else{
			exis[n+a[i]] = 1;
			last[n+a[i]] = i;
		}
		// cout << i << " " << ans << endl;
	}
	return ans;
}
