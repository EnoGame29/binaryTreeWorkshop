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
            if (node->leftBranch == NULL) {
                TreeNode* temp = node->rightBranch;
                delete node;
                return temp;
            } else if (node->rightBranch == NULL) {
                TreeNode* temp = node->leftBranch;
                delete node;
                return temp;
            }
            TreeNode* temp = minValueNode(node->rightBranch);
            node->student = temp->student;
            node->rightBranch = remove(node->rightBranch, temp->student.id);
        }
        return node;
    }

private:
    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->leftBranch != NULL)
            current = current->leftBranch;
        return current;
    }
};

int main() {
    BST bst;

    Student s1("Alice", 2020, 1);
    Student s2("Bob", 2021, 2);
    Student s3("Charlie", 2022, 3);

    bst.root = bst.insert(bst.root, s1);
    bst.root = bst.insert(bst.root, s2);
    bst.root = bst.insert(bst.root, s3);

    TreeNode* result = bst.search(bst.root, 2);
    if (result != nullptr) {
        cout << "Student found: " << result->student.name << endl;
    } else {
        cout << "Student not found!" << endl;
    }

    bst.root = bst.remove(bst.root, 2);

    result = bst.search(bst.root, 2);
    if (result != nullptr) {
        cout << "Student found: " << result->student.name << endl;
    } else {
        cout << "Student not found!" << endl;
    }

    return 0;
}
