#include <bits/stdc++.h>
#include "books.h"
using namespace std;

long long a[100005];

void solve(int N, int K, long long A, int S) {
    for(int i = 1; i <= K; i ++) a[i] = skim(i);
    long long sm = 0;
	for(int i = 1; i <= K; i ++){
		sm += a[i];
		if(sm > 2*A){
			impossible();
			return;
		}
	}
    int low = K,high = N,mid,ans;
	while(low <= high){
		mid = (low+high)/2;
		if(skim(mid)+sm-a[K] <= 2*A){
			ans = mid;
			low = mid+1;
		}
		else high = mid-1;
	}
	int cur = K;
	for(int i = ans; i > ans-K; i --){
		sm -= a[cur];
		sm += skim(i);
		cur--;
		if(sm >= A){
			vector<int> bruh;
			for(int j = i; j <= ans; j++) bruh.push_back(j);
			for(int j = 1; j <= cur; j ++) bruh.push_back(j);
			answer(bruh);
			return;
		}
	}
	impossible();
}