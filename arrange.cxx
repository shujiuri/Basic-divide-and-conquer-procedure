#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct point
{
    int t;
    bool f;
};

bool cmp(point x,point y)
{
    return x.t<y.t;
}

int greedy(vector<point> x)
{
    int max=0,cur=0,n=x.size();
    sort(x.begin(),x.end(),cmp);
    for(int i=0;i<n;i++)
    {
        if(x[i].f) 
            cur++;
        else
            cur--;
        if((i==n-1 || x[i].t<x[i+1].t) && cur>max)//处理x[i]==x[i+1]的情况
            max=cur;                              //当cur>max且x[i]==x[i+1]时，i时间肯定是开始时间，i+1时间可能是开始时间，也可能是结束时间
    }                                              //如果是结束时间，说明某活动开始时间和结束时间相同，不需要会场，故不对max更新;如果是开始时间，那在i+1次更新max效果一样
    return max;                                   //因此i次不进行更新
}

int main()
{
    vector<point> x;
    int n,i;
    point temp;
    while(cin>>n,n)
    {
        for(i=0;i<n;i++)
        {
            temp.f=true;
            cin>>temp.t;
            x.push_back(temp);
            temp.f=false;
            cin>>temp.t;
            x.push_back(temp);
        }
        cout<<greedy(x)<<endl;
        x.clear();
    }
    return 0;
}