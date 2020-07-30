/*
Soln:
http://blog.brucemerry.org.za/2014/07/
*/

#include "gondola.h"
#include<bits/stdc++.h>
using namespace std;

#define ll long long

int valid(int n, int inputSeq[]){
	set<int> s;
	for(int i = 0; i < n; i ++){
		s.insert(inputSeq[i]);
	}
	if(s.size() != n) return 0;
	for(int i = 0; i < n; i ++){
		if(inputSeq[i] <= n){
			for(int j = (i+1)%n; j != i; j = (j+1)%n){
				if(inputSeq[j] > n) continue;
				if(inputSeq[j] != ((inputSeq[i]+(j-i)+n-1)%n)+1) return 0;
			}
			return 1;
		}
	}
	return 1;
}

//----------------------
int a[100005];

int replacement(int n, int gondolaSeq[], int replacementSeq[]){
	bool flag = 0;
	for(int i = 0; i < n; i ++){
		a[i] = gondolaSeq[i];
		flag |= (a[i] <= n);
	}
	// for(int i = 0; i < n; i ++){
	// 	cout << i << " - " << a[i] << endl;
	// }
	if(!flag) a[0] = 1;
	// for(int i = 0; i < n; i ++){
	// 	cout << i << " - " << a[i] << endl;
	// }

	for(int i = 0; i < n; i ++){
		if(a[i] <= n){
			// cout << i << endl;
			for(int j = (i+1)%n; j != i; j = (j+1)%n){
				a[j] = (a[i]+(j-i)+n-1)%n + 1;
			}
			break;
		}
	}
	// for(int i = 0; i < n; i ++){
	// 	cout << i << " - " << a[i] << endl;
	// }
	vector<pair<int,int> > v;
	for(int i = 0; i < n; i ++){
		if(gondolaSeq[i] <= n) continue;
		v.push_back({gondolaSeq[i],a[i]});
	}
	sort(v.begin(),v.end());
	int cur = n+1,ind = 0;
	for(int i = 0; i < v.size(); i ++){
		replacementSeq[ind++] = v[i].second;
		while(cur < v[i].first){
			replacementSeq[ind++] = cur++;
		}
		cur++;
	}
	return ind;
}

//----------------------

const ll MOD = 1000000009;

ll power(int x,int y){
	if(y == 0) return 1;
	if(y == 1) return x;
	ll cur = power(x,y/2);
	cur = (cur*cur)%MOD;
	if(y%2) cur = (cur*x)%MOD;
	return cur;
}

int countReplacement(int n, int inputSeq[]){
	if(!valid(n,inputSeq)) return 0;
	ll ans = 1;
	int cur = 0;
	vector<int> v;
	for(int i = 0; i < n; i ++){
		if(inputSeq[i] <= n) continue;
		v.push_back(inputSeq[i]);
	}
	if(v.empty()) return 1;
	sort(v.begin(),v.end());
	if(v.size() == n) ans = n;
	ans = (ans*power(v.size(),v[0]-n-1))%MOD;
	for(int i = 1; i < v.size(); i ++){
		ans = (ans*power(v.size()-i,v[i]-v[i-1]-1))%MOD;
	}
	return ans;
}
