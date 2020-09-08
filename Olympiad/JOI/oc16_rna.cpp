/*
Soln:
https://codeforces.com/blog/entry/45502?#comment-301412
*/

#include<bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i = 0; i < n; i++)
#define FOR(i,a,b) for(int i = a; i < b; i++)
#define FORD(i,a,b) for(int i = a; i >= b; i --)
#define vi vector<int>
#define pb push_back
#define all(v) v.begin(),v.end()

int n,q;

string s[200005];

struct node{
    vi pos;
    int to[26];
} trie1[2000005],trie2[2000005];

int SZ1 = 1,SZ2 = 1;

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> q;
    REP(i,n) cin >> s[i];
    sort(s,s+n);
    REP(i,n){
        int cur = 1;
        REP(j,(int)s[i].length()){
            int let = s[i][j]-'A';
            if(!trie1[cur].to[let]) trie1[cur].to[let] = ++SZ1; 
            cur = trie1[cur].to[let];
            trie1[cur].pos.pb(i);
        }
        cur = 1;
        FORD(j,(int)s[i].length()-1,0){
            // cout << i << " " << j << endl;
            int let = s[i][j]-'A';
            if(!trie2[cur].to[let]) trie2[cur].to[let] = ++SZ2; 
            cur = trie2[cur].to[let];
            trie2[cur].pos.pb(i);
        }
    }
    REP(i,SZ2+1) sort(all(trie2[i].pos));
    REP(i,q){
        string s1,s2; cin >> s1 >> s2;
        int cur1 = 1,cur2 = 1;
        bool f = 0;
        REP(j,(int)s1.length()){
            int let = s1[j]-'A';
            if(!trie1[cur1].to[let]){
                f = 1;
                break;
            } 
            cur1 = trie1[cur1].to[let];
        }
        if(f){
            cout << "0\n";
            continue;
        }
        FORD(j,(int)s2.length()-1,0){
            int let = s2[j]-'A';
            if(!trie2[cur2].to[let]){
                f = 1;
                break;
            } 
            cur2 = trie2[cur2].to[let];
        }
        if(f){
            cout << "0\n";
            continue;
        }
        cout << upper_bound(all(trie2[cur2].pos),trie1[cur1].pos.back())-lower_bound(all(trie2[cur2].pos),trie1[cur1].pos[0]) << "\n";
    }
}