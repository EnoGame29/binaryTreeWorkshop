#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

// Define the Student class
class Student 
{
    public:
        string name;
        int enrollmentYear;
        int id;

        Student(string nm, int year, int ident) : name(nm), enrollmentYear(year), id(ident) {}
};

// TreeNode class representing a node in the binary search tree
struct TreeNode
{
    Student student;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Student s) : student(s), left(NULL), right(NULL) {}
};

//Define the BST class, creating the tree and its operations
class BST 
{
    public:
        TreeNode* root;

        BST() : root(NULL) {}

        // Insert a student into the BST
        void insert(Student student)
        {
            root = insertNode(root, student);
        }

        // Search for a student by ID
        TreeNode* search(int id)
        {
            return searchNode(root, id);
        }

        // Remove a student by ID
        void remove(int id)
        {
            root = removeNode(root, id);
        }

        // Print the BST in-order
        void printInOrder() const
        {
            inorderTraversal(root);
        }

    private:
        // Helper function to insert a node
        TreeNode* insertNode(TreeNode* node, Student student)
        {
            if (node == NULL)
            {
                return new TreeNode(student);
            }
            
            if (student.id < node->student.id)
            {
                node->left = insertNode(node->left, student);
            }
            
            else if (student.id > node->student.id)
            {
                node->right = insertNode(node->right, student);
            }
            
            return node;
        }

        // Helper function to search for a node
        TreeNode* searchNode(TreeNode* node, int id)
        {
            if (node == NULL || node->student.id == id)
            {
                return node;
            }
            
            if (id < node->student.id)
            {
                return searchNode(node->left, id);
            }
            
            return searchNode(node->right, id);
        }

        // Helper function to remove a node
        TreeNode* removeNode(TreeNode* node, int id)
        {
            if (node == NULL) return node;

            if (id < node->student.id)
            {
                node->left = removeNode(node->left, id);
            }
            
            else if (id > node->student.id)
            {
                node->right = removeNode(node->right, id);
            }
            
            else
            {
                if (node->left == NULL)
                {
                    TreeNode* temp = node->right;
                    delete node;
                    return temp;
                }
                
                else if (node->right == NULL)
                {
                    TreeNode* temp = node->left;
                    delete node;
                    return temp;
                }

                TreeNode* temp = findMinNode(node->right);
                node->student = temp->student;
                node->right = removeNode(node->right, temp->student.id);
            }
            
            return node;
        }

        // Helper function to find the minimum node
        TreeNode* findMinNode(TreeNode* node)
        {
            while (node && node->left != NULL)
            {
                node = node->left;
            }
            
            return node;
        }

        // Helper function for in-order traversal
        void inorderTraversal(TreeNode* node) const
        {
            if (node != NULL)
            {
                inorderTraversal(node->left);
                cout << "Name: " << node->student.name << ", Inscription Year: " << node->student.enrollmentYear << ", ID: " << node->student.id << endl;
                inorderTraversal(node->right);
            }
        }
};

// Function to read an integer from the console and detect invalid input
int readInt(const string& prompt)
{
    int value;
    cout << prompt;
    while (!(cin >> value))
    {
        cin.clear(); // Delete the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
        cout << "Invalid input. " << prompt;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the input
    return value;
}

// 1st Choice -> Function to add a student to the tree
void addStudent(BST& bst)
{
    string name;
    cout << "Write the student's name: ";
    cin >> name;
    int enrollmentYear = readInt("Write his inscription year: ");
    int id = readInt("Write his ID: ");
    bst.insert(Student(name, enrollmentYear, id));
    cout << "Student added!" << endl;
}

// 2nd Choice -> Function to retrieve a student by ID
void retrieveStudent(BST& bst)
{
    int id = readInt("Enter the student's ID you want to find: ");
    TreeNode* node = bst.search(id);

    if (node != NULL)
    {
        cout << "Student FOUND: Name: " << node->student.name << ", Inscription Year: " << node->student.enrollmentYear << ", ID: " << node->student.id << endl;
    }
    
    else {
        cout << "Student with ID " << id << " DIDN'T FIND" << endl;
    }
}

// 3rd Choice -> Function to update a student's information
void updateStudent(BST& bst) {
    int id = readInt("Write the student's ID you want to update: ");
    TreeNode* node = bst.search(id);

    if (node != NULL)
    {
        string newName;
        int newYear;
        cout << "Write the new name: ";
        cin >> newName;
        newYear = readInt("Write the new inscription year: ");

        node->student.name = newName;
        node->student.enrollmentYear = newYear;

        cout << "Student updated!" << endl;
    }
    
    else
    {
        cout << "Student with ID " << id << " DIDN'T FIND" << endl;
    }
}

// 4th Choice -> Function to delete a student by ID
void deleteStudent(BST& bst) {
    int id = readInt("Write the student's ID you want to delete: ");
    bst.remove(id);
    cout << "Student with ID " << id << " DELETED" << endl;
}

// 5th Choice -> Function to print the students in the tree
void printStudentList(const BST& bst) {
    if (bst.root == NULL)
    {
        cout << "No students found." << endl;
    }
    
    else
    {
        bst.printInOrder();
    }
}

// Function to read the user's choice and detect invalid input
int readChoice()
{
    return readInt("Write your choice: ");
}

int main()
{
    locale::global(locale("en_US.utf8")); // Avoid problems with accents
    BST bst;

    // Pre-populate the tree with some students
    Student s1("Rachelle", 2019, 1);
    Student s2("Robert", 2022, 2);
    Student s3("Enoal", 2024, 3);

    bst.insert(s1);
    bst.insert(s2);
    bst.insert(s3);

    int choice;

    do
    {
        cout << "\n--- Menu ---\n";
        cout << "1. Add a student\n";
        cout << "2. Find a student\n";
        cout << "3. Update a student\n";
        cout << "4. Delete a student\n";
        cout << "5. Show the students list\n";
        cout << "0. Quit\n";
        choice = readChoice();

        switch (choice)
        {
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
