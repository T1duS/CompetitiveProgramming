#include "mushrooms.h"
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)
#define vi vector<int>
#define pb push_back
 
int count_mushrooms(int n){
	int cnt = 1;
	vi a,b;
	a.pb(0);
	int LIM = 150; 
	int i;
	for (i = 1; i < LIM; i += 2){
		vi v;
		if(i == n) return cnt;
		if(i == n-1){
			v.pb(0);
			v.pb(i);
			if(use_machine(v) == 0) cnt++;
			return cnt;
		}
		else if(a.size() < 2 and b.size() < 2){
			v.pb(0);
			v.pb(i);
			v.pb(i+1);
			int val = use_machine(v);
			if(val == 0){
				a.pb(i);
				a.pb(i+1);
				cnt += 2;
			}
			else if(val == 2){
				cnt += 1;
				a.pb(i+1);
				b.pb(i);
			}
			else{
				v.clear();
				v.pb(0);
				v.pb(i);
				val = use_machine(v);
				if(val == 1){
					b.pb(i);
					b.pb(i+1);
				}
				else{
					a.pb(i);
					b.pb(i+1);
					cnt ++;
				}
			}
		}
		else{
			if(a.size() >= 2){
				v.pb(0);
				v.pb(i);
				v.pb(a[1]);
				v.pb(i+1);
				int val = use_machine(v);
				if(val == 1 or val == 3){
					b.pb(i+1);
				}
				else{
					a.pb(i+1);
					cnt++;
				}
 
				if(val == 2 or val == 3){
					b.pb(i);
				}
				else{
					a.pb(i);
					cnt++;
				}
			}
			else{
				v.pb(b[0]);
				v.pb(i);
				v.pb(b[1]);
				v.pb(i+1);
				int val = use_machine(v);
				if(val == 1 or val == 3){
					a.pb(i+1);
					cnt++;
				}
				else{
					b.pb(i+1);
				}
 
				if(val == 2 or val == 3){
					a.pb(i);
					cnt++;
				}
				else{
					b.pb(i);
				}
			}
		}
	}
	while(i < n){
		vi v;
		if(a.size() > b.size()){
			int j = i;
			int cur = 0;
			while(j < n and cur < (int)a.size()){
				v.pb(a[cur]);
				v.pb(j);
				cur++;
				j++;
			}
			int bruh = use_machine(v);
			int val = ((bruh+1)/2);
			cnt += cur-val;
			if(val == 0){
				FOR(ii,i,j) a.pb(ii);
			}
			else if(val == cur){
				FOR(ii,i,j) b.pb(ii);
			}
			else if(bruh%2){
				b.pb(j-1);
			}
			else{
				a.pb(j-1);
			}
			i = j;
		}
		else{
			int j = i;
			int cur = 0;
			while(j < n and cur < (int)b.size()){
				v.pb(b[cur]);
				v.pb(j);
				cur++;
				j++;
			}
			int bruh = use_machine(v);
			int val = ((bruh+1)/2); 
			cnt += val;
			if(val == 0){
				FOR(ii,i,j) b.pb(ii);
			}
			else if(val == cur){
				FOR(ii,i,j) a.pb(ii);
			}
			else if(bruh%2){
				a.pb(j-1);
			}
			else{
				b.pb(j-1);
			}
			i = j;
		}
	}
	return cnt;
}