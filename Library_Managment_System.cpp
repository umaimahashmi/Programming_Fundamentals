//------------------------------------------------------------------
//------------Libraray Management System----------------------------
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Book {
public:
    string title;
    string author;

    Book(string t, string a) : title(t), author(a) {}
};

class Library {
private:
    vector<Book> books;

public:
    void addBook(const Book& book) {
        books.push_back(book);
        cout << "Book '" << book.title << "' added successfully." << endl;
    }

    void removeBook(const string& title) {
        auto it = find_if(books.begin(), books.end(), [&](const Book& b) { return b.title == title; });
        if (it != books.end()) {
            books.erase(it);
            cout << "Book '" << title << "' removed successfully." << endl;
        } else {
            cout << "Book '" << title << "' not found in the library." << endl;
        }
    }

    void displayBooks() {
        if (books.empty()) {
            cout << "No books in the library." << endl;
        } else {
            cout << "List of books in the library:" << endl;
            for (const auto& book : books) {
                cout << "Title: " << book.title << ", Author: " << book.author << endl;
            }
        }
    }

    void searchBook(const string& query) {
        vector<Book> foundBooks;
        for (const auto& book : books) {
            if (book.title.find(query) != string::npos || book.author.find(query) != string::npos) {
                foundBooks.push_back(book);
            }
        }

        if (foundBooks.empty()) {
            cout << "No books found matching your search." << endl;
        } else {
            cout << "Found " << foundBooks.size() << " book(s) matching your search:" << endl;
            for (const auto& book : foundBooks) {
                cout << "Title: " << book.title << ", Author: " << book.author << endl;
            }
        }
    }
};
int main() {
    Library library;

    while (true) {
        cout << "\n==============================" << endl;
        cout << "   Library Management System  " << endl;
        cout << "==============================" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Remove Book" << endl;
        cout << "3. Display Books" << endl;
        cout << "4. Search Book" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string title, author;
                cout << "\nEnter the title of the book: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter the author of the book: ";
                getline(cin, author);
                Book book(title, author);
                library.addBook(book);
                break;
            }
            case 2: {
                string title;
                cout << "\nEnter the title of the book to remove: ";
                cin.ignore();
                getline(cin, title);
                library.removeBook(title);
                break;
            }
            case 3:
                library.displayBooks();
                break;
            case 4: {
                string query;
                cout << "\nEnter search query (title or author): ";
                cin.ignore();
                getline(cin, query);
                library.searchBook(query);
                break;
            }
            case 5:
                cout << "\nExiting program. Goodbye!" << endl;
                return 0;
            default:
                cout << "\nInvalid choice. Please choose a valid option." << endl;
        }
    }

    return 0;
}
