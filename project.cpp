#include <iostream>
#include <string>

using namespace std;

class Book {
private:
    int id;
    string title;
    string author;
    bool checkedOut;

public:
    Book(int _id, const string& _title, const string& _author) : id(_id), title(_title), author(_author), checkedOut(false) {}

    
    int getId() 
   const {
        return id;
    }
    string getTitle()
   const { 
        return title; 
    }
    string getAuthor() 
  const {
        return author;
    }
    bool isCheckedOut() 
  const { 
        return checkedOut;
    }

   
    void setId(int _id) { 
        id = _id;
    }
    void setTitle(const string& _title) { 
        title = _title;
    }
    void setAuthor(const string& _author) {
        author = _author; 
    }
    void setCheckedOut(bool value) {
        checkedOut = value; 
    }
};

class TreeNode {
private:
    Book* book;
    TreeNode* left;
    TreeNode* right;

public:
    TreeNode(Book* _book) : book(_book), left(nullptr), right(nullptr) {}

    Book* getBook() const {
        return book;
    }
    TreeNode* getLeft() const { 
        return left;
    }
    TreeNode* getRight() const {
        return right; 
    }

    void setLeft(TreeNode* node) { 
        left = node;
    }
    void setRight(TreeNode* node) { 
        right = node;
    }
};

class LibrarySystem {
private:
    TreeNode* root;

    TreeNode* insertBook(TreeNode* root, Book* book) {
        if (root == nullptr)
            return new TreeNode(book);

        if (book->getId() < root->getBook()->getId())
            root->setLeft(insertBook(root->getLeft(), book));
        else
            root->setRight(insertBook(root->getRight(), book));

        return root;
    }

    Book* searchBook(TreeNode* root, int id) {
        if (root == nullptr || root->getBook()->getId() == id)
            return (root == nullptr) ? nullptr : root->getBook();

        if (id < root->getBook()->getId())
            return searchBook(root->getLeft(), id);
        else
            return searchBook(root->getRight(), id);
    }

    TreeNode* deleteBook(TreeNode* root, int id) {
        if (root == nullptr)
            return root;

        if (id < root->getBook()->getId())

            root->setLeft(deleteBook(root->getLeft(), id));

        else if (id > root->getBook()->getId())

            root->setRight(deleteBook(root->getRight(), id));

        else {
            if (root->getLeft() == nullptr) {
                TreeNode* temp = root->getRight();
                delete root;
                return temp;
            }
            else if (root->getRight() == nullptr) {
                TreeNode* temp = root->getLeft();
                delete root;
                return temp;
            }

            TreeNode* temp = minValueNode(root->getRight());
            root->getBook()->setCheckedOut(temp->getBook()->isCheckedOut());
            root->getBook()->setId(temp->getBook()->getId());
            root->getBook()->setTitle(temp->getBook()->getTitle());
            root->getBook()->setAuthor(temp->getBook()->getAuthor());

            root->setRight(deleteBook(root->getRight(), temp->getBook()->getId()));
        }
        return root;
    }

    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->getLeft() != nullptr)
            current = current->getLeft();
        return current;
    }

public:
    LibrarySystem() : root(nullptr) {}

    bool insertBook(int id, const string& title, const string& author) {
        
        if (searchBook(root, id) != nullptr) {
            cout << "Book with ID " << id << " already exists." << endl;
            return false;
        }

       
        Book* newBook = new Book(id, title, author);
        root = insertBook(root, newBook);
        return true;
    }

    Book* searchBook(int id) {
        return searchBook(root, id);
    }

    bool removeBook(int id) {

        
        if (searchBook(root, id) == nullptr) {
            cout << "Book with ID " << id << " does not exist." << endl;
            return false;
        }

        root = deleteBook(root, id);
        return true;
    }

    void getAllBooks() {
        cout << "                   All Books in the Library:" << endl;
        getAllBooks(root);
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

    }

private:
    void getAllBooks(TreeNode* root) {
        if (root == nullptr)
            return;

        getAllBooks(root->getLeft());
        cout << "ID: " << root->getBook()->getId() << ", Title: " << root->getBook()->getTitle() << ", Author: " << root->getBook()->getAuthor() << endl;
        getAllBooks(root->getRight());
    }
};

class StudentDashboard; 

class LibrarianDashboard {
public:
    static void showDashboard(LibrarySystem& library);
private:
    static void addNewBook(LibrarySystem& library);
    static void removeBook(LibrarySystem& library);
};

class StudentDashboard {
public:
    static void showDashboard(LibrarySystem& library);
private:
    static void searchBook(LibrarySystem& library);
    static void showAllBooks(LibrarySystem& library);
};

void LibrarianDashboard::showDashboard(LibrarySystem& library) {
    string password;
    cout << "Enter Librarian Password: ";
    cin >> password;

    if (password != "1234") {
        cout << "Incorrect Password. Access Denied." << endl;
        return;
    }

    int choice;
    do {
        cout << "Successfully Access" << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

        cout << "                         Librarian Dashboard" << endl;
        cout << "1. Add New Book" << endl;
        cout << "2. Remove Book" << endl;
        cout << "3. Go to Student Dashboard" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

        switch (choice) {
        case 1:
            addNewBook(library);
            break;
        case 2:
            removeBook(library);
            break;
        case 3:
            StudentDashboard::showDashboard(library);
            break;
        case 4:
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);
}

void LibrarianDashboard::addNewBook(LibrarySystem& library) {
    int id;
    string title, author;

    cout << "Enter Book ID: ";
    cin >> id;
    cout << "Enter Book Title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter Author: ";
    getline(cin, author);

    if (library.insertBook(id, title, author)) {
        cout << "Book added successfully!" << endl;
    }
}

void LibrarianDashboard::removeBook(LibrarySystem& library) {
    int id;
    cout << "Enter Book ID to remove: ";
    cin >> id;

    if (library.removeBook(id)) {
        cout << "Book removed successfully!" << endl;
    }
}

void StudentDashboard::showDashboard(LibrarySystem& library) {
    int choice;
    do {
        cout << "                         Student Dashboard" << endl;
        cout << "1. Search Book" << endl;
        cout << "2. Show All Books" << endl;
        cout << "3. Go to Librarian Dashboard" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
        switch (choice) {
        case 1:
            searchBook(library);
            break;
        case 2:
            library.getAllBooks();
            break;
        case 3:
            LibrarianDashboard::showDashboard(library);
            break;
        case 4:
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);
}

void StudentDashboard::searchBook(LibrarySystem& library) {
    int id;
    cout << "Enter Book ID to search: ";
    cin >> id;
    Book* book = library.searchBook(id);
    if (book != nullptr) {
        cout << "--------------Book found---------------------------" << endl;
        cout << "Title: " << book->getTitle() << endl;
        cout << "Author: " << book->getAuthor() << endl;
    }
    else {
        cout << "Book with ID " << id << " not found." << endl;
    }
}

int main() {
    LibrarySystem library;
    library.insertBook(101, "To Kill a Mockingbird", "Harper Lee");
    library.insertBook(102, "1984", "George Orwell");
    library.insertBook(103, "The Great Gatsby", "F. Scott Fitzgerald");
    int role;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "                              Welcome to the Library Management System" << endl;
    cout << "Select your role:" << endl;
    cout << "1. Librarian (Password: 1234)" << endl;
    cout << "2. Student" << endl;
    cout << "Enter your choice: ";
    cin >> role;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;

    switch (role) {
    case 1:
        LibrarianDashboard::showDashboard(library);
        break;
    case 2:
        StudentDashboard::showDashboard(library);
        break;
    default:
        cout << "Invalid choice. Exiting..." << endl;
        break;
    }

    return 0;
}
