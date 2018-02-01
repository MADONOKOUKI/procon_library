using namespace std;
using Int = long long;

template <typename T>
struct WeightedUnionFind{
  Int n;
  T d;
  vector<Int> r,p;
  vector<T> ws;
  WeightedUnionFind(){}
  WeightedUnionFind(Int sz,T d_):
    n(sz),d(d_),r(n,1),p(n),ws(n,d){iota(p.begin(),p.end(),0);}
  Int find(Int x){
    if(x==p[x]){
      return x;
    }else{
      Int t=find(p[x]);
      ws[x]+=ws[p[x]];
      return p[x]=t;
    }
  }
  T weight(Int x){
    find(x);
    return ws[x];
  }
  bool same(Int x,Int y){
    return find(x)==find(y);
  }
  void unite(Int x,Int y,T w){
    w+=weight(x);
    w-=weight(y);
    x=find(x);y=find(y);
    if(x==y) return;
    if(r[x]<r[y]) swap(x,y),w=-w;
    r[x]+=r[y];
    p[y]=x;
    ws[y]=w;
  }
  T diff(Int x,Int y){
    return weight(y)-weight(x);
  }
};

signed main(){
  Int n,m;
  cin>>n>>m;
  WeightedUnionFind<Int> wuf(n+1,0);
  for(Int i=0;i<m;i++){
    Int l,r,d;
    cin>>l>>r>>d;
    l--;r--;
    if(wuf.same(l,r)){
      if(wuf.diff(l,r)!=d){
  cout<<"No"<<endl;
  return 0;
      }
    }else{
      wuf.unite(l,r,d);
    }
  }
  cout<<"Yes"<<endl;
  return 0;
}
