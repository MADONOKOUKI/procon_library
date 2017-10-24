#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define repl(i,a,b) for(int i=(int)(a);i<(int)(b);i++)
#define rep(i,n) repl(i,0,n)
#define each(itr,v) for(auto itr:v)
#define pb(s) push_back(s)
#define mmax(x,y) (x>y?x:y)
#define mmin(x,y) (x<y?x:y)
#define maxch(x,y) x=mmax(x,y)
#define minch(x,y) x=mmin(x,y)
#define mp(a,b) make_pair(a,b)
#define all(x) (x).begin(),(x).end()
#define dbg(x) cout<<#x"="<<x<<endl

#define uni(x) x.erase(unique(all(x)),x.end())
template<class T,class U>inline void chmin(T &t,U f){if(t>f)t=f;}
template<class T,class U>inline void chmax(T &t,U f){if(t<f)t=f;}
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

typedef long long ll;
typedef unsigned long long ull;
// typedef pair<int, int> P;
// typedef pair<P, int> PPI;

#define INF INT_MAX/3
#define MAX_N 1000
#define MAX_V 105
#define M_INF 1000000000

//辺を表す構造体｛行き先、要領、逆辺｝
struct edge {ll to,cap,rev;};
ll N,X,Y,P,A,B;
// std::vector<edge> G[MAX_V];//グラフの隣接リスト
// int level[MAX_V]; //sからの距離
// int iter[MAX_V]; // どこまで調べ終わったか
vector<edge> G[101];
bool used[101];

// fromからtoへ向かうcapの辺をグラフに追加する
void add_edge(ll from, ll to, ll cap) {
  G[from].push_back((edge) { to, cap, (ll) G[to].size() });
  G[to].push_back((edge) { from, cap, (ll) G[from].size() - 1 });
}

//sからの最短距離をdfsで計算する
ll dfs(ll v,ll t,ll f){
  if(v==t) return f;
  used[v] = true;

  rep(i,G[v].size()){
    edge &e = G[v][i];
    if(!used[e.to] && e.cap > 0){
      ll d = dfs(e.to, t ,min(f,e.cap));
      if(d > 0){
        e.cap -= d;
        G[e.to][e.rev].cap += d;
        return d;
      }
    }
  }
  return 0;
}

ll max_flow(ll s,ll t){
  ll flow = 0;
  while(1){
    memset(used,0,sizeof(used));
    ll f = dfs(s,t,INF);
    if(f==0) break;
    flow +=f;
  }

  return flow;
}
int main(){
  cin>>N>>X>>Y;
  rep(i,X){
    cin>>P;
    add_edge(P,N,1);
  }
  rep(i,Y){
    cin>>A>>B;
    add_edge(A,B,1);
  }

  cout<<max_flow(0,N)<<endl;
}
