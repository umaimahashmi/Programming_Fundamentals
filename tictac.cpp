//Tic Tac Toe
#include <iostream>
using namespace std;

void display_matrix(char** matrix){
    int count=1;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(matrix[i][j]=='-'){
                cout<<count<<" ";
            }
            else{
            cout<<matrix[i][j]<<" ";
            }
            count++;
        }
        cout<<endl;
    }
}
bool results(char** matrix){
    int p1=0; int p2=0;
    //Horizontally Searching
    for(int i=0; i<3; i++){
        p1=0; p2=0;
        for(int j=0; j<3; j++){
            if(matrix[i][j]=='O'){
                p1++;
            }
            if(matrix[i][j]=='X'){
                p2++;
            }
            if(p1==3){
                cout<<"Player One won"<<endl; return true;
            }
            if(p2==3){
                cout<<"Player Two won"<<endl; return true;
            }
        }
    }
    //Vertically Searching
    for(int j=0; j<3; j++){
        p1=0; p2=0;
        for(int i=0; i<3; i++){
            if(matrix[i][j]=='O'){
                p1++;
            }
            if(matrix[i][j]=='X'){
                p2++;
            }
            if(p1==3){
                cout<<"Player One won"<<endl; return true;
            }
            if(p2==3){
                cout<<"Player Two won"<<endl; return true;
            }
        }
    }
    //Diagonally Searching 
    for(int i=0; i<3; i++){    //for left diagonal
    p1=0; p2=0;
        if(matrix[i][i]=='O'){
            p1++;
        }
        if(matrix[i][i]=='X'){
            p2++;
        }
    }
    if(p1==3){
        cout<<"Player One won"<<endl; return true;
    }
    if(p2==3){
        cout<<"Player Two won"<<endl; return true;
    }
    p1=0; p2=0;
    for(int j=2; j>=0; j--){   //for right diagonal
        for(int i=0; i<3; i++){
            if(matrix[i][j]=='O'){
                p1++;
            }
            if(matrix[i][j]=='X'){
                p2++;
            }
        }
    }
    if(p1==3){
        cout<<"Player One won"<<endl; return true;
    }
    if(p2==3){
        cout<<"Player Two won"<<endl; return true;
    }
    return false;
}

bool valid(char** matrix,int choice){
    int count=1;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(count==choice){
                if(matrix[i][j]=='-'){
                    return true;
                }
                else{
                    return false;
                }
            }
            count++;
        }
    }
}
void place_char(char** matrix, int choice, char ch){
    int count=1;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(count==choice){
                matrix[i][j]=ch;
            }
            count++;
        }
    }
}
void Turn(char** matrix){
    char player1='O'; char player2='X';
    cout<<"------------Player one turn----------------"<<endl;
    int choice=-1; bool break_from_loop=true;
    while(break_from_loop){
        cout<<"Enter a number between 1 and 9: "<<endl; cin>>choice;
        if(choice>=1&&choice<=9){
            if(valid(matrix,choice)){
                place_char(matrix,choice,player1);
                break;
            }
            else{
                cout<<"Index is already filled"<<endl;
                continue;
            }
        }
        else{
            cout<<"Invalid"<<endl; continue;
        }
    }
    if(results(matrix)){
        return;
    }
    cout<<"------------Player Two turn----------------"<<endl;
    choice=-1; break_from_loop=true;
    while(break_from_loop){
        cout<<"Enter a number between 1 and 9: "<<endl; cin>>choice;
        if(choice>=1&&choice<=9){
            if(valid(matrix,choice)){
                place_char(matrix,choice,player2);
                break;
            }
            else{
                cout<<"Index is already filled"<<endl;
                continue;
            }
        }
        else{
            cout<<"Invalid"<<endl; continue;
        }
    }
}
void main_menu(){
    //creation of 3*3 game board
    char** matrix=new char*[3];
    for(int i=0; i<3; i++){
        matrix[i]=new char[3];
    }
    //initialization
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            matrix[i][j]='-';
        }
    }
    display_matrix(matrix);
    while(true){
        Turn(matrix);
        display_matrix(matrix);
        if(results(matrix)){
            return;
        }
    }
}
int main(){
    main_menu();
}