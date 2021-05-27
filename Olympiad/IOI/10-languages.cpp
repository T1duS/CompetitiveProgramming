/*
got 93 :'(
*/
#include <bits/stdc++.h>
using namespace std;
 
#include "grader.h"
#include "lang.h"
 
typedef long double LD;
typedef long long ll;
#define int ll
#define pb push_back
#define mp make_pair
#define REP(i,n) for (int i = 0; i < n; i++)
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define REPD(i,n) for (int i = n-1; i >= 0; i--)
#define FORD(i,a,b) for (int i = a; i >= b; i--)
#define remax(a,b) a = max(a,b)
#define remin(a,b) a = min(a,b)
#define all(v) v.begin(),v.end()
typedef unordered_map<int,signed> mii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;
typedef vector<pii> vpii;
#define F first
#define S second
#define PQ(type) priority_queue<type>
#define PQD(type) priority_queue<type,vector<type>,greater<type> >
#define WL(t) while(t --)
#define SZ(x) ((int)(x).size())
#define runtime() ((double)clock() / CLOCKS_PER_SEC)
#define inrange(i,a,b) ((i>=min(a,b)) && (i<=max(a,b)))
 
const int LA = 56;
const int CH = 65536;
const int SZ = 100;
 
int cnt1[LA][CH];
mii cnt2[LA];
mii cnt3[LA];
mii cnt4[LA];
int tot[LA];
 
int CH2 = 294967268;
int CH3 = 974740338;
 
int get4(int a,int b,int c,int d){
	return a*CH3+b*CH2+c*CH+d;
}
 
void excerpt(signed *E){
	int l = 0;
	pii f = {0,1};
	REP(i,LA){
		int num = 0;
		int den = tot[i]+1;
		REP(j,SZ){
			num += cnt1[i][E[j]];
		}
		REP(j,SZ-3){
			int val = get4(E[j],E[j+1],E[j+2],E[j+3]);
			if(cnt4[i].find(val) != cnt4[i].end()) num += cnt4[i][val]*SZ*SZ*SZ;
		}
		if(f.F*den < num*f.S){
			f = {num,den};
			l = i;
		}
	}
	int lang = language(l);
	tot[lang] += SZ;
	REP(i,100) cnt1[lang][E[i]]++;
	REP(i,99) cnt2[lang][E[i]*CH+E[i+1]]++;
	REP(i,98) cnt3[lang][E[i]*CH*CH+E[i+1]*CH+E[i+2]]++;
	REP(i,97){
		cnt4[lang][get4(E[i],E[i+1],E[i+2],E[i+3])]++;
	}
}