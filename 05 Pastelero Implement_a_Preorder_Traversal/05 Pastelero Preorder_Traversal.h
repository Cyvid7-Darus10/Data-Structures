#include <iostream>
#include <string>
#include <queue> //For Breath First Traversal and Path Finder

#define max(a,b) ((a)>(b)?(a):(b)) //macro for max function, used in depthChecker

//power function for perfect tree checker
int power(int a, int b) {
    if (b == 0)
        return 1;
    if (b > 1) 
        return a*power(a, b - 1);
    return a;
}


class Node 
{
	public:
	    int key;
	    Node *left, *right;
	    Node(int val): key(val), left(NULL), right(NULL){};
	    Node(): left(NULL), right(NULL) {};
};


class BST
{
    private:
        Node *root;
        int numNodes;
        void Delete(Node*); //recursive deletion of tree nodes
        int depthRecur(Node*, int); //recursion checker for depth

        //can only be access using "void print(int)" funciton.
        void preorder_print(Node*);
        void inorder_print(Node*);
        void postorder_print(Node*);
        void bfTraversal(Node*); //breath first traversal

        //tree printing
        void print2D(Node*, int*, int);

    public:
        BST(): root(NULL), numNodes(0) {};
        ~BST();

        //insertion function
        bool grow(int); //wrap
        Node* insertRecur(Node*, int); 

        //Deletion function
        bool ungrow(int); //wrap
        Node* deleteRecur(Node*, int); 

        //Extra functions
        Node* maxLeaf(Node*); //gets the max leaf
        bool isEmpty();
        bool find(int, int);
        void print(int); //wrapper for printing functions
        int numData(); //number of nodes
        int depthCheck(); //wrap for depth checker

        //Tree Type Checker
        bool isFullTree(Node*);
        bool isPerfectTree();
        void checkType();
};


//destructor
BST::~BST() {
    Delete(root);
}

//Recursive deletion of all nodes
void BST::Delete(Node* rootNode)
{
    if (rootNode) {
        Delete(rootNode->left);
        Delete(rootNode->right);
        delete rootNode;
    }
}

//Preorder (Root, Left, Right)
void BST::preorder_print(Node* rootNode)
{
    if (rootNode != NULL) {
        std::cout << "[" << rootNode->key << "] ";
        preorder_print(rootNode->left);
        preorder_print(rootNode->right);
    }
}

//Inorder (Left, Root, Right)
void BST::inorder_print(Node* rootNode)
{
    if (rootNode != NULL) {
        inorder_print(rootNode->left);
        std::cout << "[" << rootNode->key << "] ";
        inorder_print(rootNode->right);
    }
}

//Postorder (Left, Right, Root)
void BST::postorder_print(Node* rootNode)
{
    if (rootNode != NULL) {
        postorder_print(rootNode->left);
        postorder_print(rootNode->right);
        std::cout << "[" << rootNode->key << "] ";
    }
}

//Breath first traversal
void BST::bfTraversal(Node* rootNode) {
    if(!isEmpty()) {
        std::queue<Node*> holder; //uses queue for printing
        holder.push(rootNode); //stores the main root
        Node* temp; //used for pushing the left and right nodes of the first node in queue
        while(!holder.empty()) {
            temp = holder.front();
            if (temp->left != NULL) { //if left branch is available enque it first
                holder.push(temp->left);
            }
            if (temp->right != NULL) { //the right branch
                holder.push(temp->right);
            }
            std::cout << "[" << temp->key << "] "; //prints the first node in queue
            holder.pop(); //and dequeueing it
        }
    } else {
        std::cout << "[EMPTY]";
    }
}

//uses gotoxy for printing the tree vertically
//uses recursion
void BST::print2D(Node *rootNode, int *x, int y)
{    
    if (rootNode != NULL) {
        print2D(rootNode->left, x, y + 3);
        gotoxy(*x, y);
        std::cout << rootNode->key;
        *x += 3;
        print2D(rootNode->right, x, y + 3);
    }
}

//wrapper for inserRecur function
bool BST::grow(int val)
{
    root = insertRecur(root, val);
    numNodes++; //increase number of nodes
    return true;
}


Node* BST::insertRecur(Node *rootNode, int val)
{
    if(rootNode == NULL) { //only inserts when it is empty
        Node *newNode = new Node(val);
        return newNode;
    }

    if (rootNode->key <= val) { //if val is greater than or equal, it goes to the right branch
        rootNode->right = insertRecur(rootNode->right, val);
    } else if (rootNode->key > val) { //else left
        rootNode->left = insertRecur(rootNode->left, val);
    }

    return rootNode;
}

//wrappe for deleteRecur function
bool BST::ungrow(int val)
{
    if (isEmpty()) //checks if empty first
        return false;
    if (!find(val, 0)) //secondly, checks if it is available before deletion
        return false;
    root = deleteRecur(root, val); //updates the root with the new deleted root
    numNodes--; //decrease number of nodes
    return true; //success
}

//deletion of a particular node function, uses recursion
Node* BST::deleteRecur(Node* rootNode, int val)
{
  if (rootNode->key == val) { 
      if (rootNode->left == NULL && rootNode->right == NULL) { //easiest deletion since it is a leaf
          delete rootNode;
          rootNode = NULL;
      } else if (rootNode->left != NULL && rootNode->right != NULL) { //node has left and right childs
            Node* lMax = maxLeaf(rootNode->left);  //finds the maximum value of the left branch
            rootNode->key = lMax->key; //change the value to be delete with the max val
            rootNode->left = deleteRecur(rootNode->left, lMax->key); //delete the max leaf using the same function
      } else {
          if (rootNode->left != NULL) { //if left branch is not NULL, make it the parent
              Node* temp = rootNode;
              rootNode = rootNode->left;
              delete temp;
          } else { //else the right
              Node* temp = rootNode;
              rootNode = rootNode->right;
              delete temp;
          }
      }
  } else if (rootNode->key < val) {
    rootNode->right = deleteRecur(rootNode->right, val); //if val is greater than, recursion goes to the right branch
  } else {
    rootNode->left = deleteRecur(rootNode->left, val); //else left
  }

  return rootNode;
}


//used for deletion of a particular node
//the right most leaf is the max value
Node* BST::maxLeaf(Node* rootNode)
{
    if (rootNode->right != NULL)
        rootNode = maxLeaf(rootNode->right);
    return rootNode;
}


//if root is empty, then false
bool BST::isEmpty() 
{
    if (root == NULL) {
        return true;
    } 
    return false;
}

//find function for checking and printing
bool BST::find(int val, int type)
{
    std::queue<std::string> path;
    int depth = 0;
    if (!isEmpty()) {
        Node* copy = root;
        while (copy != NULL) {
            if (val < copy->key) {
                path.push("[LEFT]->");
                depth++;
                copy = copy->left;
            }
            else if (val > copy->key) {
                path.push("[RIGHT]->");
                depth++;
                copy = copy->right;
            } else {
                if (type) {
                    int size = path.size();
                    std::cout << "[DEPTH: " << depth << "] ";
                    std::cout << "PATH: [ROOT]->";
                    for (int i = 0; i < size; i++) {
                        std::cout << path.front();
                        path.pop();
                    }
                    std::cout << "[KEY]";
                }
                return true;
            }
        }
    }

    return false;
}

//wrapper for different printing functions
void BST::print(int type)
{
     int x = 65;
    switch (type) {
        case 1:
            print2D(root, &x, 7);
            break;
        case 2:
            preorder_print(root);
            break;
        case 3:
            inorder_print(root);
            break;
        case 4:
            postorder_print(root);
            break;
        case 5:
            bfTraversal(root);
            break;
    }
}

//get the number of data
int BST::numData()
{
    return numNodes;
}

//wrapper for height checker
int BST::depthCheck()
{
    return depthRecur(root, 0) - 1;
}

//Finds the deepest root, and it is its height
int BST::depthRecur(Node* rootNode, int depth)
{
    if (rootNode != NULL)   {
        depth = max(max(depth, depthRecur(rootNode->left, depth + 1)) ,
                    max(depth, depthRecur(rootNode->right, depth + 1)));
    }
    return depth;
}

//Full tree's each node is either a leaf or possesses exactly two child nodes
bool BST::isFullTree(Node* rootNode) {
    if (!rootNode || (rootNode->left == NULL && rootNode->right == NULL)) {
        return true;
    } else if (rootNode->left != NULL && rootNode->right != NULL) {
        return (isFullTree(rootNode->left) && isFullTree(rootNode->right));
    }

    return false;
}


bool BST::isPerfectTree() {
    int height = depthCheck() + 1;
    int numToCheck = 0; //the number of nodes in a perfect tree

    //Gets the total number of nodes a perfect tree must have
    while (height--) {
        numToCheck += power(2, height);
    }

    //compares it with the current number of nodes
    if (numToCheck == numNodes) {
        return true;
    }
    return false;
}


void BST::checkType() {
    if(!isEmpty()) {
        if (isPerfectTree()) {
            std::cout << "[PERFECT TREE]";
        } else if (isFullTree(root)) {
            std::cout << "[FULL TREE]";
        } else {
            std::cout << "[NOT A FULL TREE AND A PERFECT TREE]";
        }
    } else {
        std::cout << "[CAN'T CHECK, IT'S EMPTY]";
    }
}
