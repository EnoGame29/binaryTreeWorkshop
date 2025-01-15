#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

// Define the Student class
class Student {
public:
    string name;
    int enrollmentYear;
    int id;

    Student(string nm, int year, int ident) : name(nm), enrollmentYear(year), id(ident) {}
};

struct TreeNode {
    Student student;
    TreeNode* leftBranch;
    TreeNode* rightBranch;

    TreeNode(Student s) : student(s), leftBranch(NULL), rightBranch(NULL) {}
};

class BST {
public:
    TreeNode* root;

    BST() : root(NULL) {}

    TreeNode* insert(TreeNode* node, Student student) {
        if (node == NULL) {
            return new TreeNode(student);
        }
        if (student.id < node->student.id) {
            node->leftBranch = insert(node->leftBranch, student);
        } else if (student.id > node->student.id) {
            node->rightBranch = insert(node->rightBranch, student);
        }
        return node;
    }

    TreeNode* search(TreeNode* node, int id) {
        if (node == NULL || node->student.id == id) {
            return node;
        }
        if (id < node->student.id) {
            return search(node->leftBranch, id);
        }
        return search(node->rightBranch, id);
    }

    TreeNode* remove(TreeNode* node, int id) {
        if (node == NULL) return node;
        if (id < node->student.id) {
            node->leftBranch = remove(node->leftBranch, id);
        } else if (id > node->student.id) {
            node->rightBranch = remove(node->rightBranch, id);
        } else {
            if (node->leftBranch == NULL || node->rightBranch == NULL) {
                TreeNode* temp = (node->leftBranch != NULL) ? node->leftBranch : node->rightBranch;
                delete node;
                return temp;
            }
            TreeNode* temp = minValueNode(node->rightBranch);
            node->student = temp->student;
            node->rightBranch = remove(node->rightBranch, temp->student.id);
        }
        return node;
    }

    void inorder(TreeNode* node) const {
        if (node != NULL) {
            inorder(node->leftBranch);
            cout << "Name: " << node->student.name << ", Inscription Year: " << node->student.enrollmentYear << ", ID: " << node->student.id << endl;
            inorder(node->rightBranch);
        }
    }

private:
    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->leftBranch != NULL)
            current = current->leftBranch;
        return current;
    }
};

// Function to read an integer from the console and detect invalid input
int readInt(const string& prompt) {
    int value;
    cout << prompt;
    while (!(cin >> value)) {
        cin.clear(); // Delete the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
        cout << "Invalid input. " << prompt;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the input
    return value;
}

// 1st Choice -> Function to add a student to the tree
void addStudent(BST& bst) {
    string name;
    cout << "Write the student's name: ";
    cin >> name;
    int enrollmentYear = readInt("Write his inscription year: ");
    int id = readInt("Write his ID: ");
    bst.root = bst.insert(bst.root, Student(name, enrollmentYear, id));
    cout << "Student added!" << endl;
}

// 2nd Choice -> Function to retrieve a student by ID
void retrieveStudent(BST& bst) {
    int id = readInt("Enter the student's ID you want to find: ");
    TreeNode* node = bst.search(bst.root, id);

    if (node != NULL) {
        cout << "Student FOUND: Name: " << node->student.name << ", Inscription Year: " << node->student.enrollmentYear << ", ID: " << node->student.id << endl;
    } else {
        cout << "Student with ID " << id << " DIDN'T FIND" << endl;
    }
}

// 3rd Choice -> Function to update a student's information
void updateStudent(BST& bst) {
    int id = readInt("Write the student's ID you want to update: ");
    TreeNode* node = bst.search(bst.root, id);

    if (node != NULL) {
        string newName;
        int newYear;
        cout << "Write the new name: ";
        cin >> newName;
        newYear = readInt("Write the new inscription year: ");

        node->student.name = newName;
        node->student.enrollmentYear = newYear;

        cout << "Student updated!" << endl;
    } else {
        cout << "Student with ID " << id << " DIDN'T FIND" << endl;
    }
}

// 4th Choice -> Function to delete a student by ID
void deleteStudent(BST& bst) {
    int id = readInt("Write the student's ID you want to delete: ");
    bst.root = bst.remove(bst.root, id);
    cout << "Student with ID " << id << " DELETED" << endl;
}

// 5th Choice -> Function to print the students in the tree
void printStudentList(const BST& bst) {
    if (bst.root == NULL) {
        cout << "No students found." << endl;
    } else {
        bst.inorder(bst.root);
    }
}

// Function to read the user's choice and detect invalid input
int readChoice() {
    return readInt("Write your choice: ");
}

int main() {
    locale::global(locale("en_US.utf8")); // Avoid problems with accents
    BST bst;

    // Pre-populate the tree with some students
    Student s1("Rachelle", 2019, 1);
    Student s2("Robert", 2021, 2);
    Student s3("Enoal", 2024, 3);

    bst.root = bst.insert(bst.root, s1);
    bst.root = bst.insert(bst.root, s2);
    bst.root = bst.insert(bst.root, s3);

    int choice;

    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Add a student\n";
        cout << "2. Find a student\n";
        cout << "3. Update a student\n";
        cout << "4. Delete a student\n";
        cout << "5. Show the students list\n";
        cout << "0. Quit\n";
        choice = readChoice();

        switch (choice) {
            case 1:
                addStudent(bst);
                break;
            case 2:
                retrieveStudent(bst);
                break;
            case 3:
                updateStudent(bst);
                break;
            case 4:
                deleteStudent(bst);
                break;
            case 5:
                printStudentList(bst);
                break;
            case 0:
                cout << " Bye!" << endl;
                break;
            default:
                cout << "Invalid choice, please try again!" << endl;
        }
    } while (choice != 0);

    return 0;
}
