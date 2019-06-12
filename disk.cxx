#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
int n;
struct node{
    int a,b;
}p[1005];
bool cmp(node a,node b){
    return a.a*a.b<b.a*b.b;
}
int main()
{
    cin>>n;
    int sum=0;
    for(int i = 0;i < n; i++){
        cin>>p[i].a>>p[i].b;
        sum+=p[i].b;
    }
    sort(p,p+n,cmp);
    double t=0,tmp=0;
    for( i=0;i<n;i++){
        tmp=0;
        for(int j=0;j<=i;j++){
            tmp+=p[j].a*(p[j].b*1.0/sum);
        }
        t+=tmp;
    }
    printf("%.4lf\n",t);
    return 0;
}
 
/*
5
71 872
46 452
9 265
73 120
35 85
*/