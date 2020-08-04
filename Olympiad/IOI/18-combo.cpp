#include "combo.h"
#include <bits/stdc++.h>
using namespace std;

#define pb push_back

string ans;
vector<char> lef;

string guess_sequence(int N) {
	int cur = press("AB");
	if(cur == 2) ans += "AB";
	else if(cur == 1){
		cur = press("A");
		if(cur == 1) ans += "A";
		else ans += "B";
	}
	else{
		cur = press("X");
		if(cur == 1) ans += "X";
		else ans += "Y";
	}
	if(ans[0] != 'A') lef.pb('A');
	if(ans[0] != 'B') lef.pb('B');
	if(ans[0] != 'X') lef.pb('X');
	if(ans[0] != 'Y') lef.pb('Y');
	while((int)ans.size() < N){
		int gg = ans.size();
		if((int)ans.size()+1 == N){
			cur = press(ans+lef[0]);
			if(cur-gg) ans += lef[0];
			else{
				cur = press(ans+lef[1]);
				if(cur-gg) ans += lef[1];
				else ans += lef[2];
			}
		}
		else{
			cur = press(ans+lef[0]+ans+lef[1]+lef[0]+ans+lef[1]+lef[1]+ans+lef[1]+lef[2]);
			if(cur-gg == 2) ans += lef[1];
			else if(cur-gg) ans += lef[0];
			else ans += lef[2];
		}
	}
	return ans;
}
