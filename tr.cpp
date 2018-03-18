/*
	Name: calculator
	Author: moeis
	Date: 06.11.17 09:08
	Description: support basic arithmetic with minus and floating numbers,
				also support exponential function(exponential must be integer) and logarithm
*/


#include<cstdio>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<stack>
#include<cmath>
using namespace std;
#define maxs 10000
double data[maxs];
char opreator[maxs];
int numlen=0;
int opreatorlen=0;
struct stack1{
	void push(double x){
		numlen++;
		data[numlen]=x;
	}
	void pop(){
		numlen--;
	}
	bool empty(){
		if(numlen==0) return true;
		else return false;
	}
	double top(){
		return data[numlen];
	}
}num;
struct stack2{
	void push(char x){
		opreatorlen++;
		opreator[opreatorlen]=x;
	}
	void pop(){
		opreatorlen--;
	}
	bool empty(){
		if(opreatorlen==0) return true;
		else return false;
	}
	char top(){
		return opreator[opreatorlen];
	}
}ch;
struct i{
	int x;														//x=1��ʾ��������0��ʾ������ 
	char y;														//������ 
	double z;													//������ 
}f[500],g[500];													//fΪ������ʽ��gΪ������ʽ 
//stack<char> ch;													//������ջ 
//stack<double> num;												//������ջ 
int tot=0;														//�������鳤�� 
double l(double x,double y){									//��������log(x,y),��xΪ�� 		
	return log(y)/log(x);
}
double p(double x,int y){										//ָ������pow(x,y),��xΪ�� 
	double base=x;
	double ans=1;
	while(y!=0){
		if(y&1){
			ans*=base;
		}
		base*=base;
		y>>=1;
	}
	return ans;
}
int priority(char c){											//�жϲ��������ȼ� 
	if(c=='*'||c=='/') return 2;
	if(c=='+'||c=='-') return 1;
}
bool isDouble(char c){											//���ʽ�����ֵ��ж� 
	if('0'<=c&&'9'>=c) return true;
	if(c=='.') return true;
	return false; 
}
bool isLeftBracket(char c){										//�������ж� 
	if(c=='(') return true;
	return false;
}
bool isRightBracket(char c){									//�������ж� 
	if(c==')') return true;
	return false;
}
int translate(i *f,int tot){									//��������ʽת��Ϊ������ʽ 
	int sum=0;
	for(int i=1;i<=tot;i++){
		if(f[i].x){
//			cout<<f[i].z;
			sum++;
			g[sum].x=1;
			g[sum].z=f[i].z;
		}
		else{
			if(isLeftBracket(f[i].y)){
				ch.push(f[i].y);
			}
			else if(isRightBracket(f[i].y)){
				while(1){
					if(ch.top()=='('){
						ch.pop();
						break;
					}
					sum++;
					g[sum].x=0;
					g[sum].y=ch.top();
//					cout<<ch.top();
					ch.pop();
				}
			}
			else{
				while(!ch.empty()){
				if(ch.top()=='('||priority(ch.top())<priority(f[i].y)) break;
				sum++;
				g[sum].x=0;
				g[sum].y=ch.top();
//				cout<<ch.top();
				ch.pop();
			}
				ch.push(f[i].y);
			}
		}
	}
	while(!ch.empty()){
		sum++;
		g[sum].x=0;
		g[sum].y=ch.top();
//		cout<<ch.top();
		ch.pop();
	}
	return sum;												//���غ�����ʽ���� 
}
double calc(double x,char c,double y){						
	if(c=='+') return x+y;
	if(c=='-') return x-y;
	if(c=='*') return x*y;
	if(c=='/') return x/y;
}
double calculate(i *g,int len){								//��׺���ʽ���� 
	for(int i=1;i<=len;i++){
		if(g[i].x){
			num.push(g[i].z);
		}
		else{
			double x,y;
			x=num.top();	
			num.pop();
			y=num.top();
			num.pop();
			double m=calc(y,g[i].y,x);
			num.push(m);
		}
	}
	return num.top();
}
int init(char *a){										//�����ʽ�е�����ת��Ϊdouble(��������) 
	char b[500];
	int len=strlen(a);
	int t=0,flag=0,flagp=0,flagl=0;						//flag�жϸ�����1��ʾ��������Ϊ���� 
	memset(f,0,sizeof(f));								//flagp�ж�ָ����flagl�ж϶��� 
	for(int i=0;i<len;i++){
		if(isDouble(a[i])&&!flagp&&!flagl){
			if(flag&&t==0){
				t=1;
			}
			b[t++]=a[i];
			if(!isDouble(a[i+1])||i+1==len){
				double num=strtod(b,NULL);
				tot++;
				f[tot].x=1;
				f[tot].z=num;
				t=0;
				memset(b,0,sizeof(b));
			}
		}
		else if(a[i]=='('&&a[i+1]=='-'&&!flagp&&!flagl){
			flag=1;
			continue;
		}
		else if(a[i]=='-'&&flag==1){
			b[t]='-';
		}
		else if(a[i]==')'&&flag==1){
			flag=0;
			continue;
		}
		else if(a[i]=='p'){							    //ָ���任					
			flagp=1;
			continue;
		}
		else if(a[i]=='('&&flagp==1){
			continue;
		}
		else if((a[i]=='-'||isDouble(a[i]))&&flagp==1){
			while(a[i]!=','){
				b[t++]=a[i];
				i++;
			}
			double num1=strtod(b,NULL);
			memset(b,0,sizeof(b));
			t=0;
			double num2;
			if(a[i]==','){
				while(a[i]!=')'){
					i++;
					b[t++]=a[i];
				}
				num2=strtod(b,NULL);
			}
			memset(b,0,sizeof(b));
			t=0;
			tot++;
			f[tot].x=1;
			f[tot].z=p(num1,num2);
			flagp=0;
		}
		else if(a[i]=='l'){								//�����任 
			flagl=1;
			continue;
		}
		else if(a[i]=='('&&flagl==1){
			continue;
		}
		else if(isDouble(a[i])&&flagl==1){
			while(a[i]!=','){
				b[t++]=a[i];
				i++;
			}
			double num1=strtod(b,NULL);
			memset(b,0,sizeof(b));
			t=0;
			double num2;
			if(a[i]==','){
				while(a[i]!=')'){
					i++;
					b[t++]=a[i];
				}
				num2=strtod(b,NULL);
			}
			memset(b,0,sizeof(b));
			t=0;
			tot++;
			f[tot].x=1;
			f[tot].z=l(num1,num2);
			flagl=0;
		}
		else{
			tot++;
			f[tot].x=0;
			f[tot].y=a[i];
		}
	}
/*	for(int i=1;i<=tot;i++){
		if(f[i].x==1) cout<<f[i].z;
		else cout<<f[i].y;
	}
	cout<<endl;*/
//	cout<<f[tot].z;
}
int main(){
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	char a[500];
	cin>>a;
	init(a);
	memset(g,0,sizeof(g));
	int len2=translate(f,tot);
/*	for(int i=1;i<=len2;i++){
		if(g[i].x==1) cout<<g[i].z;
		else cout<<g[i].y;
	}*/
	printf("%0.8lf",calculate(g,len2));
	return 0;
}
