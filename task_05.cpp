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
    string isbn;
    bool available;

    Book(int id, string title, string author, string isbn, bool available)
        : id(id), title(title), author(author), isbn(isbn), available(available) {}
};

class Borrower {
public:
    int id;
    string name;
    string contactInfo;

    Borrower(int id, string name, string contactInfo)
        : id(id), name(name), contactInfo(contactInfo) {}
};

class Transaction {
public:
    int id;
    int bookId;
    int borrowerId;
    string checkoutDate;
    string returnDate;
    double fineAmount;

    Transaction(int id, int bookId, int borrowerId, string checkoutDate, string returnDate, double fineAmount)
        : id(id), bookId(bookId), borrowerId(borrowerId), checkoutDate(checkoutDate), returnDate(returnDate), fineAmount(fineAmount) {}
};

class LibraryManagementSystem {
private:
    vector<Book> books;
    vector<Borrower> borrowers;
    vector<Transaction> transactions;
    int bookIdCounter;
    int borrowerIdCounter;
    int transactionIdCounter;

    string getCurrentDate() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        return to_string(1900 + ltm->tm_year) + "-" +
               to_string(1 + ltm->tm_mon) + "-" +
               to_string(ltm->tm_mday);
    }

public:
    LibraryManagementSystem()
        : bookIdCounter(1), borrowerIdCounter(1), transactionIdCounter(1) {}

    void addBook(string title, string author, string isbn) {
        books.push_back(Book(bookIdCounter++, title, author, isbn, true));
        cout << "Book added successfully!\n";
    }

    void searchBook(string query) {
        for (const auto &book : books) {
            if (book.title.find(query) != string::npos ||
                book.author.find(query) != string::npos ||
                book.isbn.find(query) != string::npos) {
                cout << "ID: " << book.id << ", Title: " << book.title
                          << ", Author: " << book.author << ", ISBN: " << book.isbn
                          << ", Available: " << (book.available ? "Yes" : "No") << "\n";
            }
        }
    }

    void addBorrower(string name, string contactInfo) {
        borrowers.push_back(Borrower(borrowerIdCounter++, name, contactInfo));
        cout << "Borrower added successfully!\n";
    }

    void checkoutBook(int bookId, int borrowerId) {
        for (auto &book : books) {
            if (book.id == bookId && book.available) {
                book.available = false;
                transactions.push_back(Transaction(transactionIdCounter++, bookId, borrowerId, getCurrentDate(), "", 0.0));
                cout << "Book checked out successfully!\n";
                return;
            }
        }
        cout << "Book not available or not found!\n";
    }

    void returnBook(int bookId) {
        for (auto &book : books) {
            if (book.id == bookId && !book.available) {
                book.available = true;
                for (auto &transaction : transactions) {
                    if (transaction.bookId == bookId && transaction.returnDate.empty()) {
                        transaction.returnDate = getCurrentDate();
                        // For simplicity, let's assume the fine is a fixed amount if overdue.
                        // Here, we can add more complex fine calculation logic.
                        transaction.fineAmount = 10.0; // Placeholder fine amount
                        cout << "Book returned successfully with a fine of $" << transaction.fineAmount << "!\n";
                        return;
                    }
                }
            }
        }
        cout << "Book not found or not checked out!\n";
    }
};

int main() {
    LibraryManagementSystem lms;

    lms.addBook("The Kite Runner", "Khaled Hosseini", "9780743273565");
    lms.addBook("Three Daughters of Eve", "Elif Shafak", "9780060935467");

    lms.addBorrower("John Doe", "john.doe@example.com");

    cout << "Searching for 'Kite Runner':\n";
    lms.searchBook("Kite Runner");

    lms.checkoutBook(1, 1); // Checkout "The Kite Runner" by John Doe

    lms.returnBook(1); // Return "The Kite Runner"

    return 0;
}
