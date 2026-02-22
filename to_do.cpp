//---------------------------------------------------------------------------
//------------------------***TO DO List***-----------------------------------
#include <iostream>
using namespace std;

class node{
    public:
    int data;
    string task;
    node* next;
    node(string task,int data=0){
        this->task=task;
        this->data=data;
        next=nullptr;
    }
};
class To_Do{
    public:
    node* head; node* tail;
    To_Do(){
        head=nullptr; tail=nullptr;
    }
    int total_size(){
        node* temp=head; int count=1;
        while(temp!=nullptr){
            temp=temp->next; count++;
        }
        return count;
    }
    void insert_at_end(string task,int data){
        node* temp=new node(task,data);
        if(head==nullptr){
            head=temp; tail=temp;
        }
        else{
            tail->next=temp;
            tail=temp;
        }
    }
    void delete_at_start(){
        if(head==nullptr){
            cout<<"To-Do List is empty!"<<endl;
        }
        else{
            node* temp=head;
            head=head->next;
            delete temp;
        }
    }
    void delete_at_end(){
        if(head==nullptr){
            cout<<"To-Do List is empty!"<<endl;
        }
        else{
            node* temp=tail;
            node* p=head;
            while(p->next!=tail){
                p=p->next;
            }
            tail=p;
            p->next=nullptr;
            delete temp;
        }
    }
    void delete_at_position(int position){
        if(position>=1&&position<=total_size()){
            if(position==1){
                delete_at_start();
            }
            else if(position==total_size()){
                delete_at_end();
            }
            else{
                node* c=head;
                for(int i=1; i<position-1; i++){
                    c=c->next;
                }
                c->next=c->next->next;
            }
        }
        else{
            cout<<"The Index is not present"<<endl;
            return;
        }
    }
    void print(){
        node* temp=head;
        if(head==nullptr){
            cout<<"To do List is empty!"<<endl;
            return;
        }
        cout<<"-----------------------------------------"<<endl;
        cout<<"---------Printing The To-Do List---------"<<endl;
        while(temp!=nullptr){
            cout<<temp->task<<endl;
            temp=temp->next;
        }
        cout<<"-----------------------------------------"<<endl;
    }

};
void main_menu(){
    To_Do L; string Task=""; int index=0;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"----CONSOLE BASED TO-DO APP-----------------------"<<endl;
    cout<<"1) Insert New Task"<<endl;
    cout<<"2) Delete A Task"<<endl;
    cout<<"3) Mark As Completed"<<endl;
    cout<<"4) Print To Do List"<<endl;
    cout<<"--------------------------------------------------"<<endl;
    while(true){
        cout<<"Enter your choice"<<endl;
        int choice;     cin>>choice;
        if(choice>=1&&choice<=4){
            if(choice==1){
                cout<<"Enter the Task: "<<endl; cin>>Task;
                L.insert_at_end(Task,index++);
            }
            else if(choice==2){
                L.print();
                cout<<"Enter the Index of Task: "<<endl;  int n; cin>>n;
                L.delete_at_position(n);
                cout<<"Deleted Index "<<n<<endl;
            }
            else if(choice==3){
                L.print();
                cout<<"Enter the Index of Task: "<<endl;  int n; cin>>n;
                L.delete_at_position(n);
                cout<<"Index "<<n<<" Marked as Completed"<<endl;
            }
            else{
                L.print();
            }
        }
        else{
            cout<<"Invalid Number!"<<endl;
            continue;
        }
    }
}
int main(){
    main_menu();
}