#include<iostream>
using namespace std;

int sum(int& num1, int& num2){
	return (num1+num2);
}
int diff(int& num1, int& num2){
	return (num1-num2);
}
int mult(int& num1, int& num2){
	return (num1*num2);
}
float divide(int& num1, int& num2){
	if(num2==0){
		cout<<"division by zero is not possible"<<endl;
		return 0;
	}
	return static_cast<float>(num1) / static_cast<float>(num2);
}
int power(int& num1, int& num2){
	return (num1*num2);
}
void operators(){
	cout<<"------------------------------"<<endl;
	cout<<"1)  +  "<<endl;
	cout<<"2)  -  "<<endl;
	cout<<"3)  *  "<<endl;
	cout<<"4)  /  "<<endl;
	cout<<"5)  ^  "<<endl;
	cout<<"------------------------------"<<endl;
}
void taking_input(){
	char op;
	operators();
	cout<<"Enter operator: "; cin>>op;
	if( (((op=='+'||op=='-')||(op=='*'||op=='/'))||op=='^') ){
		int num1=0; int num2=0; 
		cout<<"enter num1: "; cin>>num1;
		cout<<"enter num2: "; cin>>num2;
		if(op=='+'){
			cout<<"Summation of "<<num1<<" and "<<num2<<" is: "<<sum(num1,num2)<<endl;
		}
		if(op=='-'){
			cout<<"Difference of "<<num1<<" and "<<num2<<" is: "<<diff(num1,num2)<<endl;
		}
		if(op=='*'){
			cout<<"Multiplication of "<<num1<<" and "<<num2<<" is: "<<mult(num1,num2)<<endl;
		}
		if(op=='/'){
			cout<<"Dividing "<<num1<<" with "<<num2<<" you get: "<<divide(num1,num2)<<endl;
		}
		if(op=='^'){
			cout<<num1<<" to the power "<<num2<<" is: "<<power(num1,num2)<<endl;
		}
	}
	else{
		cout<<"Invalid Operator"<<endl;
		taking_input();
	}
}
void main_menu(){
	bool choice=true; 
	char c;
	taking_input();
	while(choice){
		cout<<"Do you want to press again: "<<"(Y|N): "; cin>>c;
		if(c=='Y'||c=='y'){
			main_menu();
        }
        else if(c=='N'||c=='n'){
            break;
        }
        else{
			cout<<"Invalid input!"<<endl;
            continue;
        }
	}
}
int main(){
	main_menu();
}