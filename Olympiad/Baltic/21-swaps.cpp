#include<bits/stdc++.h>
#include "swaps.h"
using namespace std;

int a[1005];

void solve(int N, int V){
	for(int i = 0; i < 2*N; i ++) a[i] = i+1;
	int po2 = 1;
	while(po2 < N) po2 *= 2;
	for(int k = 2; k <= po2; k *= 2){
		for(int j = k/2; j >= 1; j/= 2){
			for(int i = 0; i < po2; i ++){
				int l = (i^j);
				if(l > i){
					if((i&k) == 0){
						if(a[l] > N) continue;
						if(a[i] > N) swap(a[i],a[l]);
						else schedule(a[i],a[l]);
					}
					else{
						if(a[i] > N) continue;
						if(a[l] > N) swap(a[i],a[l]);
						else schedule(a[l],a[i]);
					}
				}
			}
			vector<int> gg = visit();
			int cur = 0;
			for(int i = 0; i < po2; i ++){
				int l = (i^j);
				if(l > i){
					if(a[i] > N or a[l] > N) continue;
					if(gg[cur] != 1) swap(a[i],a[l]);
					cur++;
				}
			}
		}
	}
	vector<int> ans;
	for(int i = 0; i < N; i ++){
		ans.push_back(a[i]);
	}
	answer(ans);
}