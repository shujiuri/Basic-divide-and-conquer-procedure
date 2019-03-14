# Basic-divide-and-conquer-procedure
Used to store my understanding of algorithmic analysis programs
#include <iostream>  
#include <stdlib.h>  
#include <fstream>  
const int MAX=100;
  
using namespace std;  
   
  
int Random(int p, int r){//随机化  
        //return rand()*(r-p)/32767+p;  
    return rand()%(r-p)+p;  
}  
  
void Swap(int* c, int* d){  
        int temp;   
        temp= *c;  
        *c = *d;  
        *d = temp;  
}  
  
 //小于x放置左边，大于x的放置右边 
int Partition(int* y, int p, int r){  
        int i = p, j = r+1;  
        int x = y[p];  
        while(true){  
                while(y[++i]<x&&i<r);  
                while(y[--j]>x);  
                if(i>=j) break;  
                Swap(&y[i],&y[j]);  
        }  
        y[p] = y[j];  
        y[j] = x;  
        return j;  
}  
  
int RandomizedPartition(int* y, int p, int r){  
        int i = Random(p,r);  
        Swap(&y[i],&y[p]);  
        return Partition(y,p,r);  
}  
 
 
void FindModeIndex(int* y,int i,int* left_index,int* right_index)  
{  
        int mode=y[i];  
        int left=i;  
        int right=i;  
        while(y[--left]==mode);  
        while(y[++right]==mode);  
        left++;  
        right--;
		//最后一次等于mid的下标，因为已经将小于等于x的放在左侧
		//大于等于的放在右侧，所以right-left+1就是x的出现次数；  
        
        *left_index=left;  
        *right_index=right;  
}  
  
void FindMode(int* y, int p, int r, int& mode, int& count){  
        int i = RandomizedPartition(y,p,r);  
        int left_index;  
        int right_index;  
        
        int count_mid,count_left,count_right;  
        FindModeIndex(y,i,&left_index,&right_index);  
        count_mid=right_index-left_index+1;  
        
        count_left=left_index-p;  
        
        count_right=r-right_index;  
        if(count_mid>=count)  
        {  
            mode=y[i];  
            count=count_mid;  
        }  
        
        //如果左边数的和大于等于统计的x的重数，左边递归求解； 
        if(count_left>=count_mid) FindMode(y,p,left_index-1,mode,count);  
        //如果右边数的和大于等于统计的x的重数，左边递归求解；
		if(count_right>=count_mid)  FindMode(y,right_index+1,r,mode,count);  
        return;  
}  
int main()  
{  
    ifstream input("input.txt",ios::in);  
    ofstream output("output.txt",ios::out);  
  
    if (!input)  
    {  
        cerr<<"input file could not be opened"<<endl;  
        exit(1);  
    }  
  
      
    int mode;  
    int count;  
	int n;
	cin>>n;
int*a=(int*)malloc(n*sizeof(int));
	

	 
	for(int i=0;i<n;i++) 
	 	input>>a[i];
		
	mode=MAX;  
    count=0;  
    
    FindMode(a,0,n-1,mode,count);  
    output<<mode<<endl<<count<<endl;  
   
 
    return 0;  
}  
