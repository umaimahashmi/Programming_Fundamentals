#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <string>
#include <algorithm> 
using namespace std;

string filename="save.txt";
class Node {
public:
    char character;
    Node* before;
    Node* after;
    Node* below;
    Node* above;

    Node(char c) : character(c), before(nullptr), after(nullptr), below(nullptr), above(nullptr) {}
};

class Notepad {
public:
    Notepad() {
        firstLine=nullptr;
        current=nullptr;
        current_character=nullptr;
        cursor=nullptr;
    }
    void InsertCharacter(char c){
        Node* temp=new Node(c);
        if(firstLine==nullptr){
            firstLine=temp;
            current=temp;
            current_character=temp;
            cursor=temp;
            char_no++; line_no=1;
        }
        else if(char_no<=total_characters){
            current_character->after=temp;
            temp->before=current_character;
            current_character=temp;
            cursor=temp;
            char_no++;
        }
        else{
            Insertnewline();
            InsertCharacter(c);
        }
    }
    void Insertnewline() {
        if (line_no == total_lines) {
            cout << "Max line limit reached!" << endl; 
            return;
        }
        Node* newLineNode = new Node('\n');
        current->below=newLineNode;
        newLineNode->above=current;
        newLineNode->before=current_character;
        current_character->after=newLineNode;
        current=newLineNode;
        current_character=newLineNode;
        cursor=newLineNode;
        char_no = 0;
        line_no++;
    }
    void handleKeyboardInput() {
        HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
        DWORD NumEvents = 0;
        INPUT_RECORD InRec;

        while (true) {
            ReadConsoleInput(hInput, &InRec, 1, &NumEvents);

            if (InRec.EventType == KEY_EVENT && InRec.Event.KeyEvent.bKeyDown) {
                char key = InRec.Event.KeyEvent.uChar.AsciiChar;
                cout<<key;
                if(InRec.Event.KeyEvent.wVirtualKeyCode == VK_LEFT) {
                    moveCursorLeft();
                    cout<<endl;
                    cout<<"---------------------------"<<endl;
                    Display_cursor();
                    cout<<"---------------------------"<<endl;
                }else if(InRec.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT) {
                    moveCursorRight();
                    cout<<endl;
                    cout<<"---------------------------"<<endl;
                    Display_cursor();
                    cout<<endl;
                    cout<<"---------------------------"<<endl;
                }else if(InRec.Event.KeyEvent.wVirtualKeyCode == VK_UP) {
                    moveCursorUp();
                    cout<<endl;
                    cout<<"---------------------------"<<endl;
                    Display_cursor();
                    cout<<endl;
                    cout<<"---------------------------"<<endl;
                }else if(InRec.Event.KeyEvent.wVirtualKeyCode == VK_DOWN) {
                    moveCursorbelow();
                    cout<<endl;
                    cout<<"---------------------------"<<endl;
                    Display_cursor();
                    cout<<endl;
                    cout<<"---------------------------"<<endl;
                }
                else if (key == 'q') {
                    break;
                } else if(InRec.Event.KeyEvent.wVirtualKeyCode == VK_RETURN) {
                    Insertnewline();
                } else if (key == 0x08) {
                    delete_before();
                }else if (InRec.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
                    Sleep(100); //handleing the event when esc key pressed
                    break;
                }else if (key == 19||key=='S') {
                        cout<<endl;
                        saving_text_in_file();
                }else if (key==12||key == 'L') {
                        loading_text_from_file();
                }
                else {
                    InsertCharacter(key);
                }
            }
        }
        DisplayText();
    }
    void DisplayText(){
        cout<<endl;
        cout<<"___________________________________________________________________________________________________"<<endl;
        cout<<"------------------------"<<endl;
        cout<<"Text in the notepad is: "<<endl;
        cout<<"------------------------"<<endl;
        cout<<endl;
        Node* temp=firstLine;
        string line;
        while(temp!=nullptr){
            line+=temp->character;
            temp=temp->after;
        }
        cout<<line<<endl;
        cout<<"___________________________________________________________________________________________________"<<endl;
    }
    void current_to_first(){
        Node* temp=current_character;
        while(temp!=NULL){
            cout<<temp->character;
            temp=temp->before;
        }
        cout<<endl;
    }
    void delete_before(){
        if(current_character->before==nullptr){
            firstLine=nullptr;
            current=nullptr;
            cursor=nullptr;
            current_character=nullptr;
            char_no=0; line_no=0;
        }
        else if(cursor==current_character){
            Node* temp=current_character;
            current_character->before->after=nullptr;
            current_character=current_character->before;
            cursor=current_character;
            char_no--;
            delete temp;
        }
        else if(cursor!=current_character){
            Node* temp=cursor;
            cursor->before->after=cursor->after;
            cursor->after->before=cursor->before;
            cursor=cursor->before;
            char_no--;
            delete temp;
        }
    }
    void saving_text_in_file(){
        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cerr << "Error: Unable to open the file for writing." << endl;
            return;
        }

        Node* currentLine = firstLine;
        while (currentLine != nullptr) {
            Node* currentChar = currentLine;
            while (currentChar != nullptr) {
                outFile << currentChar->character;
                currentChar = currentChar->after;
            }
            outFile << endl;
            currentLine = currentLine->below;
        }

        outFile.close();
        cout << "Text saved to " << filename << endl;
    }
    void loading_text_from_file() {
        ifstream file(filename);
        if (file.is_open()) {
            // Clear the existing content in your Notepad
            //ClearNotepadContent();
            string line;
            while (getline(file, line)) {
                // Process each line from the file
                for (char c : line) {
                    InsertCharacter(c);
                }
            }
            file.close();
            cout<<"loaded the content of the file"<<endl;
        } else {
            cout << "Failed to open the file." << endl;
        }
    }
    void moveCursorRight() {
        if (cursor->after) {
            cursor = cursor->after;
        }
    }
    void moveCursorLeft() {
        if (cursor->before) {
            cursor = cursor->before;
        }
    }
    void moveCursorUp() {
        if (cursor->above) {
            cursor = cursor->above;
        }
    }
    void moveCursorbelow() {
        if (cursor->below) {
            cursor = cursor->below;
        }
    }
    void Display_cursor(){
        cout<<endl;
        Node* temp=firstLine;
        string line=""; 
        while(temp!=nullptr){
            line+=temp->character;
            if(temp==cursor){
                line+='|';
            }
            temp=temp->after;
        }
        cout<<line<<endl;
    }
    string covert_to_lower(string word){
        for(int i=0; i!=word.length(); i++){
            if (word[i]>= 'A' && word[i]<= 'Z') {
                word[i]=word[i]+32;
            }
        }
        return word;
    }
    void notepad_dictionary(){
        ifstream file("dictionary.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                line=covert_to_lower(line);
                dictionary.push_back(line);
            }
            file.close();
        } else {
            cout << "Failed to open the file." << endl;
        }
    }    
    bool match_word_in_dict(string word){
        string original=word;
        for(int i=0; i!=word.length(); i++){
            if(word[i]>='A'&&word[i]<='Z'){
                word[i]+=32;
            }
        }
        bool matching=false;
        for(int i=0; i<dictionary.size(); i++){
            if(word==dictionary[i]){
                matching= true;
            }
        }
        if(matching==false){
            wrong_words.push_back(original);
        }
        return matching;
    }
    void check_wrong_words(){
        Node* temp=firstLine;
        vector<string> potential_wrong_words;
        string line;
        while(temp!=nullptr){
            if(temp->character==' '){
                potential_wrong_words.push_back(line);
                line="";
            }
            else if(temp->character!='\n'){
                line+=temp->character;
            }
            temp=temp->after;
        }
        potential_wrong_words.push_back(line);
        for(int i=0; i<potential_wrong_words.size(); i++){
            string str=potential_wrong_words[i];
            match_word_in_dict(str);
        }
    }
    void display_wrong_words(){
        cout<<"_________________________"<<endl;
        cout<<"wrong words are: "<<endl;
        for(int i=0; i<wrong_words.size(); i++){
            cout<<wrong_words[i]<<" ";
        }
        cout<<endl;
        cout<<"_________________________"<<endl;
    }
void letterOmissionSuggestions() {
    vector<string> suggestions;
    for (size_t i = 0; i < wrong_words.size(); i++) {
        string misspelled_words = wrong_words[i];
        for (size_t j = 0; j <misspelled_words.length(); j++) {
            string suggestion =misspelled_words;
            suggestion.erase(j, 1); // Erase the character at position 'j'
            if (match_word_in_dict(suggestion)) {
                if (find(suggestions.begin(), suggestions.end(), suggestion) == suggestions.end()) { //this fun adds unique elemnts in suggestios
                    suggestions.push_back(suggestion);
                }
            }
        }
    }
    // Display suggestions
    cout << "----Suggestions for letter omission----: ";
    for (const string& suggestion : suggestions) {
        cout << suggestion << " ";
    }
    cout << endl;
}
void letterReversalSuggestions() {
    cout << "-----Suggestions for letter reversal-----: ";
    
    for (size_t i = 0; i < wrong_words.size(); i++) {
        string misspelledWord = wrong_words[i];
        for (size_t charIndex = 0; charIndex < misspelledWord.length() - i; charIndex++) {
            string wordSuggestion = misspelledWord;
            swap(wordSuggestion[charIndex], wordSuggestion[charIndex + 1]);
            if (match_word_in_dict(wordSuggestion)) {
                cout << wordSuggestion << " ";
            }
        }
    }
    cout << endl;
}
/*
void letterInsertionSuggestions() {
    cout << "-----Suggestions for letter insertion-----: ";
    // Define a string of all possible characters to insert
    const string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for (size_t i = 0; i < wrong_words.size(); i++) {
        string misspelledWord = wrong_words[i];
        // Generate suggestions for each word in the list
        for (size_t pos = 0; pos <= misspelledWord.length(); pos++) {
            for (char c : alphabet) {
                string wordSuggestion = misspelledWord;
                // Insert character 'c' at position 'pos'
                wordSuggestion.insert(pos, 1, c);

                if (match_word_in_dict(wordSuggestion)) {
                    cout << wordSuggestion << " ";
                }
            }
        }
    }
    cout << endl;
}*/
void letterInsertionSuggestions() {
    cout << "-----Suggestions for letter insertion-----: ";
    const string alphabet = "abcdefghijklmnopqrstuvwxyz";

    for (size_t i = 0; i < wrong_words.size(); i++) {
        string misspelledWord = wrong_words[i];

        for (size_t pos = 0; pos <= misspelledWord.length(); pos++) {
            for (char c : alphabet) {
                string wordSuggestion = misspelledWord;
                wordSuggestion.insert(pos, 1, c);

                if (match_word_in_dict(wordSuggestion)) {
                    cout << wordSuggestion << " ";
                }
            }
        }
    }
    cout << endl;
}

private:
    Node* firstLine;
    Node* current;
    Node* current_character;
    Node* cursor;//pointer for cursor
    vector<string> dictionary;
    vector<string> wrong_words;

    static int const total_lines=10; //total number of lines in my notepad
    static int const total_characters=50; //total no of characters allowed in my notepad
    static int line_no; //current line no
    static int char_no; //current character no
};
int Notepad:: line_no=0;   //initialization of my static variables
int Notepad::char_no=0;
int main() {
    Notepad notepad;
    cout<<"____________________________________________________________"<<endl;
    cout<<"-------------------Text Editor------------------------------"<<endl;
    cout<<"____________________________________________________________"<<endl;
    cout<<"Text Editor - Enter 'q' or Esc key to quit" << endl;
    cout<<"press: ctr+s or S -----> to save file"<<endl;
    cout<<"press: ctr+l or L -----> to load file"<<endl;
    cout<<"------------------------------------------------------------"<<endl;
    notepad.notepad_dictionary();
    notepad.handleKeyboardInput();
    notepad.check_wrong_words();
    notepad.display_wrong_words();


    notepad.letterOmissionSuggestions();
    //notepad.letterInsertionSuggestions();
    notepad.letterReversalSuggestions();
    return 0;
}
