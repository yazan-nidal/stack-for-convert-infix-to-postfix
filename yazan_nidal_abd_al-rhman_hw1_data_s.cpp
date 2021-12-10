#include<iostream>
#include<math.h>
using namespace std;
#define size 100
typedef char item;
typedef float item1;
struct stack{//stack for convert infix to postfix
	item exp[size];
	int top;
	bool emptY(){return top==-1;}
	void cleaR(){top=-1;}
	item poP(){if(!emptY())return exp[top--];}
	void pusH(item x){exp[++top]=x;}
	item toP(){if(!emptY())return exp[top];}
};//end stack
struct stackF{//stackF for evaluation
	item1 exp[size];
	int top;
	bool emptY(){return top==-1;}
	void cleaR(){top=-1;}
	item1 poP(){if(!emptY())return exp[top--];}
	void pusH(item1 x){exp[++top]=x;}
	item1 toP(){if(!emptY())return exp[top];}
};//end stackF

//comon

bool in_an_Operand(char x){// fun operand cheek
	if(((x-48)>=0)&&((x-48)<=9)){return true;} else{return false;}
}//end fun operand cheek
bool in_an_Operation(char x){// fun Operation cheek
	if((x=='^')||(x=='*')||(x=='/')||(x=='%')||(x=='+')||(x=='-')){return true;}else{return false;} 
}//end fun Operation cheek

// for convert infix to postfix

int PrioritY(char c){ //priortY
if(c=='^') 
return 3; 
else 
if((c=='*')||(c=='/')||(c=='%')) 
return 2; 
else 
if((c=='+')||(c=='-'))
return 1; 
else
return -1; 
}// end prioritY

char* postfix_convert(stack &s,char exp[]){// convert
char postfix_exp[100]="";
s.cleaR();
int length=strlen(exp);
int j=0;
for(int i=0;i<length;i++){// for 
if(exp[i]==' ')continue;
while(in_an_Operand(exp[i])==1){postfix_exp[j++]=exp[i++];}
if(in_an_Operand(exp[i-1])==1){postfix_exp[j++]=' ';}
if(exp[i]=='('){s.pusH('(');}
else{if(exp[i]==')'){
while(s.toP()!='('){postfix_exp[j++]=s.poP();
if(in_an_Operation(postfix_exp[j-1])==1){postfix_exp[j++]=' ';}}s.poP();}
else{while(!s.emptY() && PrioritY(exp[i])<=PrioritY(s.toP())){
	postfix_exp[j++]=s.poP();
	if(in_an_Operation(postfix_exp[j-1])==1){postfix_exp[j++]=' ';}
	}s.pusH(exp[i]);}}

}// end for
while(!s.emptY()){postfix_exp[j++]=s.poP();}
if(in_an_Operation(postfix_exp[j-1])==1){postfix_exp[j++]=' ';}
postfix_exp[j]=NULL;
return postfix_exp;
}//end convert

// for evaluation 

float math_Operation(float op1,float op2,char oper){//math
	switch(oper){
	case '+':
		return op1+op2;
	case '-':
		return op1-op2;
	case '*':
		return op1*op2;
	case '/':
		return op1/op2;
	case '%':
		return (int)op1%(int)op2;
	case '^':
		return pow(op1,op2);
	default :
		return 0;
	
	}
}//end math

float evaluation(stackF d,char postfix[]){//evl
d.cleaR();
float num=0;
int length=strlen(postfix);
for(int i=0;i<length;i++){if(in_an_Operand(postfix[i])==1){while(in_an_Operand(postfix[i])==1){
	num *=10;
	num +=(postfix[i]-48);
i++;}
	d.pusH(num);
	num=0;
}
else{
if(postfix[i]==' '){continue;}
if(in_an_Operation(postfix[i])==1){float op2=d.poP();
float op1=d.poP();
d.pusH(math_Operation(op1,op2,postfix[i]));
}
}
}
return d.poP();
}//end evl

// main list

void List_and_Processing(stack &s,char exp[],stackF &d){
int select=0;
cout<<"	List : \n";
cout<<"	1 -	Input Expression in Infix \n";
cout<<"	2 -	Convert Expression an Infix to Postfix \n";
cout<<"	3 -	Evaluating Expression \n";
cout<<"	4 -	Clean the Screen \n";
cout<<"	5 -	Exit the Program \n";
while(select !=5){
cout<<"	Select from the List -> ";
cin>>select;
cout<<endl;
switch(select){
case 1:{cout<<"	Enter Expression -> ";
	   cin>>exp;
	   cout<<"\n";
	   break ;}
case 2:{  if(strcmp(exp," ")==0){cout<<" Error Must Input Expression \n";break;}else{
	char output[100];
	strcpy(output,postfix_convert(s,exp));
	cout<<"	The Postfix Expression : "<<output<<"\n";
	break;}}
case 3:{ if(strcmp(exp," ")==0){cout<<" Error Must Input Expression \n";break;}else{
	char output[100];
	strcpy(output,postfix_convert(s,exp));
	   float result=evaluation(d,output);
	cout<<"	Expression Value = "<<result<<"\n";
	break;}
	   }
case 4:{system("cls");
cout<<"	List : \n";
cout<<"	1 -	Input Expression in Infix \n";
cout<<"	2 -	Convert Expression an Infix to Postfix \n";
cout<<"	3 -	Evaluating Expression \n";
cout<<"	4 -	Clean the Screen \n";
cout<<"	5 -	Exit the Program \n";
	   break;}

default :{if(select!=5)cout<<" Error Select \n";
		 }}
}
cout<<" End OF ProGraM \n";
}


void main(){//main
stack s;
s.cleaR();
stackF d;
d.cleaR();
char exp[100]=" ";
List_and_Processing(s,exp,d);
}//main