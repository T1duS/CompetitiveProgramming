#include "interactive.h"
#include<bits/stdc++.h>
#define F first
#define S second
using namespace std;

vector<int> guess(int n) {
	vector <int> ans(n);
	map<int,int> gg;
	int a1 = ask(1);
	gg[a1] = 1;
	for(int j = 0; j < 7; j++){
		vector<int> v1,v2,r1,r2;
		v2.push_back(1);
		for(int i = 2; i <= n; i ++){
			if(i&(1<<j)){
				v1.push_back(i);
				v2.push_back(i);
			}
		}
		if(v1.empty()) continue;
		r1 = get_pairwise_xor(v1);
		r2 = get_pairwise_xor(v2);
		map<int,int> lol;
		for(auto x:r1) lol[x]++;
		for(auto x:r2) lol[x]--;
		lol[0]++;
		for(auto x:lol){
			if(x.S){
				// cout << (x.F^a1) << " " << j << endl;
				gg[x.F^a1] |= (1<<j);
			}
		}
	}
	for(auto x:gg) ans[x.S-1] = x.F;
	// for(auto x:ans) cout << x << " "; cout << "\n";
	return ans;
}
