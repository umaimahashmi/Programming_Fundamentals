#include <iostream>
#include <time.h>
#include <string>
using namespace std;

bool substr_present(string& s,string& sub) {
    int n = s.length();
    int m = sub.length();

    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (s[i + j] != sub[j]) { break;}
        }
        if (j == m) {
            return true;  // Substring found
        }
    }
    return false;  // Substring not found
}
void swap(string& a, string& b){
    string temp;
    temp=a;
    a=b;
    b=temp;
}
void swap(int& a, int& b){
    int temp;
    temp=a;
    a=b;
    b=temp;
}
class Post
{
    public:
    Post* next; //pointer part
    string timestamp; //string timestamp;
    static int total_posts;
    int ID;
    string text;

    public:
    Post(string txt="empty"){
        ID=total_posts+1;
        total_posts++;
        this->text=txt;
        time_t now=time(0);
        timestamp=ctime(&now);
        //pointer initialization
        next=nullptr;
    }
    void display() const{
        cout<<"ID is:"<<ID<<" "<<"text is:"<<text<<" "<<"timestamp is:"<<timestamp<<endl;
    }
    string get_text(){return text;}
    int get_ID(){return ID;}
    void set_text(string text){this->text=text;}
    void set_timestamp(){  time_t now=time(0);  timestamp=ctime(&now);}

};
int Post:: total_posts=1000;  //initializing the static variable
class Feed
{
    Post* head;
    public:
    Feed(){
        head=nullptr;
    }
    //complexity O(1)
    void insert_at_start(string txt=""){
        if(head==NULL){
            Post* new_post=new Post;
            head=new_post;
            new_post->set_text(txt);
        }
        else{
            //insertion in the linked list
            Post* new_post=new Post;
            new_post->next=head;
            head=new_post;
            //now putting the value
            new_post->set_text(txt);
        }
    }
    //complexity O(n)
    void display_latest(){
        Post* temp=head;
        while(temp!=NULL){
            temp->display();
            temp=temp->next;
        }
    }
    //computational complexity
    //time xomplexity is O(n)
    //space complexity here is also O(n) we are creating and extra space(array) to store the addresss
    /*logic to implement the backward display is to make the temp pointer 
    and transverse it to whole linked list store the addresses in the pointer array then display
    that array in reverse*/
    void display_oldest(){
        Post* temp=head;
        Post* array[100]; int i=0;
        while(temp!=NULL){
            array[i]=temp;
            i++;
            temp=temp->next;
        }
        for(int j=i-1; j>=0; j--){
            temp=array[j];
            temp->display();
        }
    }
    //delete a post
    void delete_post(int num) {
    Post* j = head;
    Post* i = nullptr;
    bool deleted = false;

    // Check if the head node should be deleted
    if (head != nullptr && head->get_ID() == num) {
        head = head->next;
        delete j; 
        deleted = true;
    }
    else{
        while (j != nullptr){
            if (j->get_ID() == num){
                i->next = j->next;
                delete j;
                deleted = true;
                break;
            }
            i = j;
            j = j->next;
        }
    }
        if (deleted) {
            cout << "Post deleted successfully" << endl;
        } else {
            cout << "ID not found!" << endl;
        }
    }
    //O(n)
    //search for a post by the text
    //it will search all the posts and where ever a given substring is present
    //that post will be printed
    void search_post(string txt){
        cout<<"displaying the texts where the substring is found"<<endl;
        Post* temp=head;
        bool found=false;
        while(temp!=NULL)
        {
            if(substr_present(temp->text,txt)){
                temp->display();
                found=true;
            }
            temp=temp->next;
        }
        if(!found){
            cout<<"no substrings found!"<<endl;
        }
    }
    /*void edit_post(int num, string new_text){
        //search the id 
        //replace the text
        //update the time
        Post* temp=head;
        while(temp!=NULL){
            if(temp->get_ID()==num){
                temp->set_text(new_text);
                temp->set_timestamp();
            }
            temp=temp->next;
        }
        temp=head;
        //now place the post in the right time order
        //bubble sort
        int size=(temp->total_posts)-1000;
        for(int i=0; i<size; i++){
            for(int j=0; j<size-i; j++){
                if(temp->timestamp>temp->next->timestamp){
                    swap(temp->timestamp,temp->next->timestamp);
                }
                temp=temp->next;
            }
        }

    }*/
    //complexity O(n)
    //the basic logic is that i find the id fisrt in the linked list
    //when i am able to find the id then i edit the txt present at that id and update tht time
    //simply after that to put the linked list in correct order i do bubble sort
    //which does sorting based on the timestamps 
    void edit_post(int num, string new_text) {
    Post* temp = head; bool post_found=false;
    // Search for the post to edit
    while (temp != NULL) {
        if (temp->get_ID() == num) {
            temp->set_text(new_text);
            temp->set_timestamp();
            post_found=true;
            break;
        }
        temp = temp->next;
    }
    if(!post_found){
        cout<<"the entered id is incorrect"<<endl;
        return;
    }
    // Bubble sort to order posts by timestamp
    int swapped;
    Post* end = NULL;
    if (head == NULL) {
        return;
    }
    do {
        swapped = 0;
        temp = head;
        while (temp->next != end) {
            if (temp->timestamp < temp->next->timestamp) {
                swap(temp->timestamp, temp->next->timestamp);
                swap(temp->ID, temp->next->ID);
                swap(temp->text, temp->next->text);
                swapped = 1;
            }
            temp = temp->next;
        }
        end = temp;
    } while (swapped);
    }
};
int main(){

    Feed f1;
    string s; 
    f1.insert_at_start("Hello World!");
    f1.insert_at_start("How is everyone doing today");
    //1 random string
    cout<<"enter the string: "<<endl; getline(cin,s);
    f1.insert_at_start(s);
    //2 random string
    cout<<"enter the string: "<<endl; getline(cin,s);
    f1.insert_at_start(s);
    //3 random string
    cout<<"enter the string: "<<endl; getline(cin,s);
    f1.insert_at_start(s);
    //4 random string
    cout<<"enter the string: "<<endl; getline(cin,s);
    f1.insert_at_start(s);
    //5 random string
    cout<<"enter the string: "<<endl; getline(cin,s);
    f1.insert_at_start(s);
    //6 random string
    cout<<"enter the string: "<<endl; getline(cin,s);
    f1.insert_at_start(s);
    f1.insert_at_start("I should be going, see you guys later.");
    f1.insert_at_start("Bye");

    //oldest first display
    cout<<"display in the oldest order.."<<endl;
    cout<<"____________________________________________________________"<<endl;
    f1.display_oldest();
    cout<<"____________________________________________________________"<<endl;

    //search a substring in a post
    cout<<"finding the substring World in the texts.."<<endl;
    f1.search_post("World");

    //edit post
    cout<<"enter the id that you want to edit"<<endl; int n; cin>>n;
    f1.edit_post(n,"Hello guys!");

    //display oldest first
    cout<<"display in the oldest order.."<<endl;
    cout<<"____________________________________________________________"<<endl;
    f1.display_oldest();
    cout<<"____________________________________________________________"<<endl;

    //search a substring in a post
    cout<<"searching the posts with substring guys..."<<endl;
    f1.search_post("guys");

    //delete the post
    int num=0; char c;
    while(true){
    cout<<"enter the ID of the post that you want to delete"<<endl;
    cin>>num;
    f1.delete_post(num);
    cout<<"do you want to delete again"<<endl;
    cout<<"press (y/n) or (Y/N)"<<endl; cin>>c;
        if((c=='y')||(c=='Y')){
            continue;
        }
        else{break;}
    }

    //display latest first
    cout<<"display in the latest order.."<<endl;
    cout<<"____________________________________________________________"<<endl;
    f1.display_latest();
    cout<<"____________________________________________________________"<<endl;

}