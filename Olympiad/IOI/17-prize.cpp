/*
Soln:
90 points soln is obvious. Just randomize everything
*/

#include "prize.h"
#include<bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define pb push_back
#define F first
#define S second
#define pii pair<int,int>
#define all(v) v.begin(),v.end()

mt19937 RNG(2898); 

vector<pii> possible;
int mx;

vi done[200005];

vi asky(int ind){
	// cout << ind << endl;
	if(done[ind].size()) return done[ind];
	return done[ind] = ask(ind);
}

int solve(int l,int r,int lcnt,int rcnt){
	// cout << l << " " << r << " " << lcnt << " " << rcnt << endl;
	if(l > r) return -1;
	if(lcnt+rcnt == mx) return -1;
	int mid = (l+r)/2;
	int m = mid;
	int bizz = 0;
	while(mid >= l){
		vi gg = asky(mid);
		if(gg[0]+gg[1] == mx){
			if(RNG()%2){
				int pos = solve(l,mid-1,lcnt,gg[1]);
				if(pos != -1) return pos;
				return solve(m+1,r,gg[0]+bizz,rcnt);
			}
			else{
				int pos = solve(m+1,r,gg[0]+bizz,rcnt);
				if(pos != -1) return pos;
				return solve(l,mid-1,lcnt,gg[1]);
			}
		}
		if(gg[0]+gg[1] == 0) return mid;
		possible.pb({gg[0]+gg[1],mid});
		bizz++;
		mid--;
	}
	return solve(m+1,r,lcnt+bizz,rcnt);
}

int find_best(int n){
	int ind;
	for(int i = 0; i < 500; i++){
		ind = RNG()%n;
		vi gg = asky(ind);
		mx = max(mx,gg[0]+gg[1]);
		if(mx > 100) break;
	}
	return solve(0,n-1,0,0);
}
