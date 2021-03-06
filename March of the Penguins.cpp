/*
•题意：
有N个冰块,每个冰块上有ni个企鹅每个冰块最多能跳着离开mi次.企鹅每次最多能跳D单位远,每两个冰块之间有坐标距离..要你求出哪些点可以聚集所有的企鹅
   解法：网络流
◦每个冰块拆成两个点，第 i 个冰块用 i 和 i+n 表示，其中 i 到 i+n 的容量为第 i 个冰块最多能跳着离开的次数，通过拆分点，可以确保每个冰块的进入的总流量小于等于该冰块能跳着离开的次数。
◦添加源点0，源点到每个冰块 i 的容量为冰块 i 在初始状态上的企鹅数。
◦冰块 i 到冰块 j 之间的容量，即 i+n 到 j 的容量为 i 最多能跳着离开的次数。
◦添加汇点2*n+1，依次将1 -- i连到汇点，判断最大流是否与企鹅总数相同。
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include <queue>
#include <vector>
#include <algorithm>
#include<math.h>
#include<iostream>
#define N (100*2+2)
#define M (N*N+4*N)
#define Inf 0x3f3f3f3f
typedef long long LL;

using namespace std;

struct edge {
  int v, cap, next;
};
edge e[M];

int head[N], level[N], cur[N];
int num_of_edges;

struct node{
	int x;
	int y;
	int maxx;
	int num;
}g[N];
/*
 * When there are multiple test sets, you need to re-initialize before each
 */
void dinic_init(void) {
  num_of_edges = 0;
  memset(head, -1, sizeof(head));
  return;
}

int add_edge(int u, int v, int c1, int c2) {
  int& i=num_of_edges;

  assert(c1>=0 && c2>=0 && c1+c2>=0); // check for possibility of overflow
  e[i].v = v;
  e[i].cap = c1;
  e[i].next = head[u];
  head[u] = i++;

  e[i].v = u;
  e[i].cap = c2;
  e[i].next = head[v];
  head[v] = i++;
  return i;
}

void print_graph(int n) {
  for (int u=0; u<n; u++) {
    printf("%d: ", u);
    for (int i=head[u]; i>=0; i=e[i].next) {
      printf("%d(%d)", e[i].v, e[i].cap);
    }
    printf("\n");
  }
  return;
}

/*
 * Find all augmentation paths in the current level graph
 * This is the recursive version
 */
int dfs(int u, int t, int bn) {
  if (u == t) return bn;
  int left = bn;
  for (int &i=cur[u]; i>=0; i=e[i].next) {
    int v = e[i].v;
    int c = e[i].cap;
    if (c > 0 && level[u]+1 == level[v]) {
      int flow = dfs(v, t, min(left, c));
      if (flow > 0) {
        e[i].cap -= flow;
        e[i^1].cap += flow;
        cur[u] = i;
        left -= flow;
        if (!left) break;
      }
    }
  }
  if (left > 0) level[u] = 0;
  return bn - left;
}

bool bfs(int s, int t) {
  memset(level, 0, sizeof(level));
  level[s] = 1;
  queue<int> q;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    if (u == t) return true;
    for (int i=head[u]; i>=0; i=e[i].next) {
      int v = e[i].v;
      if (!level[v] && e[i].cap > 0) {
        level[v] = level[u]+1;
        q.push(v);
      }
    }
  }
  return false;
}

LL dinic(int s, int t) {
  LL max_flow = 0;

  while (bfs(s, t)) {
    memcpy(cur, head, sizeof(head));
    max_flow += dfs(s, t, INT_MAX);
  }
  return max_flow;
}

int upstream(int s, int n) {
  int cnt = 0;
  vector<bool> visited(n);
  queue<int> q;
  visited[s] = true;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i=head[u]; i>=0; i=e[i].next) {
      int v = e[i].v;
      if (e[i].cap > 0 && !visited[v]) {
        visited[v] = true;
        q.push(v);
        cnt++;
      }
    }
  }
  return cnt; // excluding s
}
double calDis(int index1,int index2){
	return sqrt( pow(g[index1].x-g[index2].x,2) + pow(g[index1].y-g[index2].y,2) );
}
int main() {
   int t;
   cin>>t;
   while(t--){
   	int n;
   	double d;
   	bool flag = true;
   	cin>>n>>d;
   	int s,e;
   	s = 0;
   	e = 2*n+1;
   	int total = 0;
   	for(int i=1;i<=n;i++){
   		cin>>g[i].x>>g[i].y>>g[i].num>>g[i].maxx;
   		total += g[i].num;
	   }

  for(int i=1;i<=n;i++){
	 	dinic_init();
	for(int j=1;j<=n;j++){
	 	add_edge(s,j,g[j].num,0);
	 	add_edge(j,j+n,g[j].maxx,0);
	 	 for(int k=1;k<=n;k++){
	 		if(calDis(j,k)<=d&&(j!=k)){
				add_edge(j+n,k,g[j].maxx,0);
			 }
		   }
	   }
	  	add_edge(i,e,Inf,0);
	  	//print_graph(2*n+2);
	  	int res = dinic(s,e);
		if(total==res){
			flag = false;
			cout<<(i-1)<<" ";
		}
    }
	 if(flag){
	 	cout<<"-1";
	 }
	 cout<<endl;
	   
   }

  return 0;
}




















