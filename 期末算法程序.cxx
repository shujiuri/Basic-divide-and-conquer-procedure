#include <stdio.h>
#include <stdlib.h>
#include<string>


typedef struct JDian
{
	double hypothesisZuiYou; //用来存储如果选了一个物品，那么价值是多少
	double realityJiaZhi; 	//用来存储当前价值的
	int *backRongLiang;		//用来表示背包已经装了多少东西

	int XuanShei; //用来记录选了哪个物品

	struct JDian* XYiChu;
} heapJDian;	

heapJDian *head,*tail;//root


 

//定义变量名和初始化
double *realityJiaZhi;
int **attribute;
int nUM;
int nUM_attr;
double check;
int *limitation; 

double bestv; 
int *DangQianRongliang;// 当前背包容量
double c_realityJiaZhi;//当前背包价值
//动态二维数组的存储
void dongTaiFenPei ();
double shiXianGuCe(int t);
double fenZhiXianJieShiXian();
heapJDian* chuDui();
int shiXianBiJiao(int opr, int *l, int *target);
int stact_empty();
void ruDui(double upe, double crealityJiaZhi, int* cons, int XuanShei);
int compare(int* target, int index);
void minus(int* target, int index);

int main(void){
	FILE *f = fopen("数据.txt","r");//从文件读取数据
	fscanf(f,"%d %d %lf",&nUM,&nUM_attr,&check);
	dongTaiFenPei();
	int i,j;
	
	//价值录入
	for(i = 0; i < nUM; i++){
		fscanf(f,"%lf",&realityJiaZhi[i]);
	}

	//属性录入
	for(i = 0 ; i < nUM_attr;i++)
		for(j = 0; j < nUM; j++)
			fscanf(f,"%d", &attribute[i][j]);

	//限制条件录入
	for(i = 0 ; i < nUM_attr;i++)
		fscanf(f,"%d", &limitation[i]);

	double result = fenZhiXianJieShiXian();
	printf("my result is %lf\ntarget is %lf", result,check);

}
//动态分配二维数组空间
void dongTaiFenPei(){
	realityJiaZhi = (double*)malloc(sizeof(double) * nUM);
	attribute = (int**)malloc(sizeof(int*) * nUM_attr);
	int i;
	for(i = 0 ; i < nUM_attr;i++)
		*(attribute + i) = (int*)malloc(sizeof(int) * nUM);

	limitation = (int*)malloc(sizeof(int) * nUM_attr);
	DangQianRongliang = (int*)malloc(sizeof(int) * nUM_attr);
	memset(DangQianRongliang,0,sizeof(int)*nUM_attr);
	head = NULL;
	tail = NULL;
}

//实现最大值的估测用于做最优值的比较，这里会假设物品可分割
double shiXianGuCe(int t){
	double bound = c_realityJiaZhi;//选和不选该物品的思想，如果选，那么后面的I+1个物品的价值是否大于当前背包价值，如果，后面的价值加起来都没有当前的价值大，那么后面就不用计算了。
	int *left = (int*)malloc(sizeof(int) * nUM_attr);
	int i,j;
	for(i = 0; i<nUM_attr; i++)
		*(left + i) = *(limitation + i) - *(DangQianRongliang + i);
	while(t < nUM && compare(left, t)){
		minus(left, t);
		bound += realityJiaZhi[t];
		t++;
	}

	if(t < nUM){
		bound += (realityJiaZhi[t]/attribute[0][t]) * left[0];
	}
	return bound;

}

//实现数组元素的比较，如：A的每个元素是否都比B大
int shiXianBiJiao (int opr, int *l, int *target){
	int i;
	if(opr == 0){
		for(i = 0;i<nUM_attr;i++){
			 if(l[i] < target[i])
			 	return 0;
		}
	}

	else if(opr == 1){
		for(i = 0;i<nUM_attr;i++){
			*(l+i) -=*(target+i);
		}

	}

	else if(opr == 2){
		for(i = 0;i<nUM_attr;i++){
			l[i]+= target[i];
		}
	
	}
	return 1;

}

//分支限界法的选择
double fenZhiXianJieShiXian(){
	int i = 0,j;
	double hypothesisZuiYou = shiXianGuCe(i);
	
	while(1){

		int *c_weight = (int*)malloc(sizeof(int)*nUM_attr);
		memset(c_weight,0,sizeof(int)*nUM_attr);

		for(j = 0;j<nUM_attr;j++){
			c_weight[j] = attribute[j][i] + DangQianRongliang[j];
		}
		
		if(shiXianBiJiao(0, limitation,c_weight)){
			if(c_realityJiaZhi + realityJiaZhi[i] > bestv)
				bestv = c_realityJiaZhi + realityJiaZhi[i];
			ruDui(hypothesisZuiYou,c_realityJiaZhi + realityJiaZhi[i], c_weight, i + 1); //最大值的预测是假设了物品可以分解的，假设背包全部放满，且性价比最高先放。
		}
		hypothesisZuiYou = shiXianGuCe(i + 1);
		if(hypothesisZuiYou >= bestv)
			ruDui(hypothesisZuiYou, c_realityJiaZhi, DangQianRongliang, i + 1);
		if(stact_empty()) 
			return bestv;
		heapJDian *JDian = chuDui(); 
		DangQianRongliang = JDian->backRongLiang;
		c_realityJiaZhi = JDian->realityJiaZhi;
		hypothesisZuiYou = JDian->hypothesisZuiYou;
		i = JDian->XuanShei;
		free(JDian);
		JDian = NULL;
	}
}

//实现队列元素的出队
heapJDian* chuDui(){
	if(head == tail)
		tail == NULL;
	heapJDian* item = head;
	head = item->XYiChu;
	return item;	
}

//实现元素的入队
void ruDui(double upe, double crealityJiaZhi, int* cons, int XuanShei){
	heapJDian *temp = (heapJDian*)malloc(sizeof(heapJDian));
	temp->hypothesisZuiYou = upe;
	temp->realityJiaZhi = crealityJiaZhi;
	temp->backRongLiang = cons;
	temp->XuanShei = XuanShei;
	temp->XYiChu = NULL;
	if(XuanShei <= nUM){
		if(stact_empty()){
			head = temp;
			tail = temp;
		}
		else{
			tail->XYiChu = temp;
			tail= temp;	
		}
		
	}
}

//判断当前队列是否为空
int stact_empty(){
	return (head == NULL);
}
//实现二维数组的位置变化
int compare(int* target, int index){
	int i;
	for(i = 0; i < nUM_attr; i++){
		if(target[i] < attribute[i][index])
			return 0;

	}
	return 1;		//实现的是二维数组的位置变换，因为数组只能横向操作，所以要把限制条件换到每个属性后面
}

void minus(int* target, int index){
	int i;
	for(i = 0; i < nUM_attr; i++){
		target[i] -= attribute[i][index];
	}

}
