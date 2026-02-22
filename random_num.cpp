#include <iostream>
#include <ctime>
using namespace std;

int random_number_generator(){
    srand(time(0));
    int num = 0 + (rand() % 100);
    return num;
}
void guess_number(){
    int random_num=random_number_generator();
    int guess=0;
    while(true){
        cout<<"Enter your guess: ";  cin>>guess;
        if(guess==random_num){
            cout<<"You Won!"<<endl;
            return;
        }
        else{
            if(guess>random_num){
                cout<<"The num is smaller"<<endl;
                cout<<"Try Again!!"<<endl;
            }
            else if(guess<random_num){
                cout<<"The number is greater"<<endl;
                cout<<"Try Again!!"<<endl;
            }
            continue;
        }
    }

}
void main_menu(){
    cout<<"-------------------------------------------------"<<endl;
    cout<<"---------Game Of Number Guessing-----------------"<<endl;
    cout<<"You have to guess a number between 1 and 100:"<<endl;
    while(true){
        guess_number();
        bool choice=true; char c; 
        while(choice){
            cout<<"Do you want to play again "<<endl;
            cout<<"(y|n):"<<endl;
            cin>>c;
            if(c=='Y'||c=='y'){
                break;
            }
            else if(c=='N'||c=='n'){
                break;
            }
            else{
                continue;
            }
        }
        if(c=='Y'||c=='y'){
            continue;
        }
        else if(c=='N'||c=='n'){
            return;
        }
    }
}
int main(){
    main_menu();
}