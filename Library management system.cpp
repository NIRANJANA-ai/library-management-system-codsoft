#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool checked_out;
    time_t due_date;

    Book(int id, string title, string author) {
        this->id = id;
        this->title = title;
        this->author = author;
        checked_out = false;
        due_date = 0;
    }
};

vector<Book> books;

void addBook() {
    int id;
    string title, author;
    cout << "Enter book ID: ";
    cin >> id;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    books.push_back(Book(id, title, author));
    cout << "Book added successfully!" << endl;
}

void searchBook() {
    string title;
    cout << "Enter book title to search: ";
    cin.ignore();
    getline(cin, title);
    for (const auto& book : books) {
        if (book.title.find(title) != string::npos) {
            cout << "ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author << ", Checked out: " << (book.checked_out ? "Yes" : "No") << endl;
        }
    }
}

void checkOutBook() {
    int id;
    cout << "Enter book ID to check out: ";
    cin >> id;
    for (auto& book : books) {
        if (book.id == id && !book.checked_out) {
            book.checked_out = true;
            time(&book.due_date);
            book.due_date += 14 * 24 * 3600; // Due in 2 weeks
            cout << "Book checked out successfully!" << endl;
            return;
        }
    }
    cout << "Book not found or already checked out!" << endl;
}

void returnBook() {
    int id;
    cout << "Enter book ID to return: ";
    cin >> id;
    for (auto& book : books) {
        if (book.id == id && book.checked_out) {
            book.checked_out = false;
            time_t now;
            time(&now);
            if (now > book.due_date) {
                double fine = difftime(now, book.due_date) / (24 * 3600) * 0.5; // $0.5 per day late
                cout << "Book returned late! Fine: $" << fine << endl;
            } else {
                cout << "Book returned successfully!" << endl;
            }
            return;
        }
    }
    cout << "Book not found or not checked out!" << endl;
}

void displayBooks() {
    cout << "\nLibrary Books:\n";
    for (const auto& book : books) {
        cout << "ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author << ", Checked out: " << (book.checked_out ? "Yes" : "No") << endl;
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add a book\n";
        cout << "2. Search for a book\n";
        cout << "3. Check out a book\n";
        cout << "4. Return a book\n";
        cout << "5. Display all books\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addBook();
            break;
        case 2:
            searchBook();
            break;
        case 3:
            checkOutBook();
            break;
        case 4:
            returnBook();
            break;
        case 5:
            displayBooks();
            break;
        case 6:
            return 0;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    }
}
