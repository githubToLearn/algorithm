#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include <queue>
#include <vector>
#include<list>
#include <algorithm>
#include<iostream>
#include<math.h>
using namespace std;
#define N 1005
#define Inf 0x3f3f3f3f
struct node{
	double s,e;
}g[N];
bool cmp(node a, node b){
		return a.e<b.e;

}
int main() {
  double d;
  int n;
  int time = 0;
  while(cin>>n>>d){
  	if(n==0&&d==0){
  		break;
	  }
	  time++;
	  bool flag = false;
  	for(int i=0;i<n;i++){
  		double x,y;
  		cin>>x>>y;
  		if(y>d){
  			flag = true;
  			continue;
		  }
		g[i].s = x - sqrt(d*d-y*y);
		g[i].e= x + sqrt(d*d-y*y);
	  }
	 sort(g,g+n,cmp);
	 if(flag){
	 	cout<<"Case "<<time<<": -1"<<endl;
	 }else{
	 	double maxx = g[0].e;
	 	int total = 1;
	 	for(int i=1;i<n;i++){
	 		if(g[i].s>maxx){
				total++;
				maxx = g[i].e;
			 }
		 }
	 	cout<<"Case "<<time<<": "<<total<<endl;
	 }
  }
  

  return 0;
}






