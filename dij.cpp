#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N=5e5;

int n,m,a,b,c,temp;
vector<pair<int,int>> graph[N];
vector<int> dist(N),parent(N),path;
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;

void setMemory() {
    for(int i=0;i<N;i++) dist[i]=INT_MAX;
    for(int i=0;i<N;i++) parent[i]=-1;
    for(auto i : graph) i.clear();
}

void TracePath(int idx) {
    if (parent[idx] == -1) return;
    TracePath(parent[idx]);
    path.push_back(idx);
}

void Dijkstra() {
    dist[0]=0;
    pq.push({0,0});
    while(!pq.empty()) {
        pair<int,int> p=pq.top();
        pq.pop();
        if(dist[p.second]<p.first) continue;
        int u=p.second;
        for(auto i : graph[u]) {
            int v=i.first;
            int w=i.second;
            if(dist[v]>dist[u]+w)
            {
                dist[v]=dist[u]+w;
                parent[v]=u;
                temp=v;
                pq.push({dist[v],v});
            }
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    setMemory();
    freopen("inp300k.txt","r",stdin);
    freopen("gv.dot","w",stdout);
    clock_t start=clock();
    cin>>n>>m;
    for(int i=0;i<m;i++)
    {
        cin>>a>>b>>c;
        graph[a].push_back(make_pair(b,c));
        graph[b].push_back(make_pair(a,c));
    }
    Dijkstra();
    TracePath(temp);
    cout<<"digraph a {\n";
    int sz=path.size();
    for (int i=0;i<sz-1;i++) {
        cout<<path[i]<<" -> "<<path[i+1]<<"\n";
    }
    cout<<"}\n";
    clock_t stop=clock();
    // cout<<"\nRun time of the Dijkstra's algorithm\n\ntime: "<<(stop-start)/(double)CLOCKS_PER_SEC<<" sec\n";
}
