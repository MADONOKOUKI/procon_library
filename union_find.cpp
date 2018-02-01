#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <bitset>
#include <fstream>
using namespace std;

#define repl(i,a,b) for(int i=(int)(a);i<(int)(b);i++)
#define rep(i,n) repl(i,0,n)
#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)
#define all(x) (x).begin(),(x).end()
#define dbg(x) cout<<#x"="<<x<<endl
typedef long long ll;

#define INF 1000000000

class UnionFind {
public:
  vector<int> par, rank, sizes; // parent, depth, size(only for root)
  UnionFind(int sz) : par(sz), rank(sz, 0), sizes(sz, 1){
    rep(i,sz) par[i]=i; // initial tree is independent each other
  }
  int find(int x){
    if(par[x]==x) return x;
    else return par[x] = find(par[x]);
  }
  void unite(int x, int y){
    x=find(x);
    y=find(y);
    if(x==y) return;  // already belong to same tree
    if(rank[x] < rank[y]){  // y becomes parent node
      par[x] = y;
      sizes[y] += sizes[x];
    } else {  // x becomes parent node
      par[y]=x;
      if(rank[x]==rank[y]) rank[x]++;
      sizes[x] += sizes[y];
    }
  }
  bool same(int x, int y){
    return find(x) == find(y);
  }
  int size(int x){
    return sizes[find(x)];
  }
}; // END class UnionFind

struct bridge{
  int a,b,year;
  bool operator<(const bridge& r) const{
    return year < r.year;
  }
};

struct query{
  int n,v,w;
  bool operator<(const query& r) const{
    return w < r.w;
  }
};

int main(){
  int n,m,q;

  cin>>n>>m;
  priority_queue<bridge> bq; // bridges queue
  rep(i,m){
    bridge t;
    scanf("%d %d %d", &(t.a), &(t.b), &(t.year));
    bq.push(t);
  }

  cin>>q;
  priority_queue<query> qq; // query queue
  rep(i,q){
    query t;
    t.n=i;
    scanf("%d %d", &(t.v), &(t.w));
    qq.push(t);
  }

  UnionFind uf(n+1);
  vector<int> res(q);

  while(!qq.empty()){
    if(!bq.empty() && bq.top().year > qq.top().w){
      bridge b = bq.top(); bq.pop();
      uf.unite(b.a, b.b);
    } else {
      query qu = qq.top(); qq.pop();
      res[qu.n] = uf.size(qu.v);
    }
  }

  rep(i,q) printf("%d\n", res[i]);
  return 0;
}

int par[MAX_N]; // 親
int rank[MAX_N]; // 木の深さ

void init(int n){
  rep(i,n){
    par[i] = i;
    rank[i] = 0;
  }
}

int find(int x){
  if(par[x] == x){
    return x;
  } else {
    return par[x] = find(par[x]);
  }
}

void unite(int x,int y){
  x  = find(x);
  y  = find(y);
  if(x == y) return;

  if( rank [x] < rank[y]){
    par[x] = y;
  } else {
    par[y] = x;
    if(rank[x] == rank[y]) rank[x]++;
  }
}

bool same(int x,int y){
  return find(x) == find(y);
}
