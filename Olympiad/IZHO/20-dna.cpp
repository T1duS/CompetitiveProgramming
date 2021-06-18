#include "grader.h"
#include<bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i = 0; i < n; i ++)
#define FOR(i,a,b) for(int i = a; i < b; i ++)
#define F first
#define S second

string find_next(string str) {
	int n = str.length();
	int last = -1;
	REP(i,n){
		string cur;
		REP(j,i) cur += str[j];
		cur += '?';
		REP(j,n-i-1) cur += '_';
		pair<string,string> gg = get_min_max(cur);
		if(gg.S.length() == 0 or gg.S[i] < str[i]) break;
		if(gg.S[i] > str[i]) last = i;
		else if(i == n-1) return str;
	}
	if(last == -1) return "";
	for(auto c:{'A','C','G','T'}){
		if(c <= str[last]) continue;
		string cur = str;
		cur[last] = c;
		FOR(i,last+1,n) cur[i] = '_';
		if(get_min_max(cur).F.length()){
			FOR(i,last+1,n) cur[i] = '?';
			return get_min_max(cur).F;
		}
	}
	return "";
}