/*
Author: Miguel Martinez
Program: Binary Search Tree
Description: Implements a binary search tree

*/

#include<iostream>
using namespace std;

//struct for our tree nodes (has left and right nodes)
struct bNode
{
	int num;
	bNode* left;
	bNode* right;
};

//prototype for search function so it can be used in insert function (not actually used in the insert function after all)
bool search(bNode* root, int num);

//adds new node to tree
bNode* NewNode(int num)
{
	bNode* newNode = new bNode();
	newNode->num = num;
	newNode->left = newNode->right = NULL; 
	return newNode;
}

//insert function adds new node to tree
bNode* Insert(bNode* root, int num)
{
	//if there is no node in the tree, it makes this original node the root
	if (root == NULL)
	{
		root = NewNode(num);
	}
	else if (num <= root->num)
	{
		//comparing the new number to the root to see if it should be the new node or make a subtree
		root->left = Insert(root->left, num);
	}
	else
	{
		//inserts into right node if the new number is greater than root
		root->right = Insert(root->right, num);
	}
	return root; //returns root adress to the main so we can keep track of list
	
}

//search function
bool search(bNode* root, int num)
{
	if (root == NULL)
	{
		//number isn't there so it will always be false
		return false;
	}
	else if (root->num == num)
	{
		//if the root is the number we are searching for
		return true;
	}
	else if (num <= root->num)
	{
		//goes to the left side of bst and recursive calls search function for numbers in right side of bst
		return search(root->left, num);
	}
	else
	{
		//goes to right side of bst and recursively calls the search function for the numbers in right side of bst
		return search(root->right, num);
	}
}

//finds min value in right side of tree if node needing to be deleted has more than 1 child, this preserves the bst rules
bNode* Min(bNode* root)
{
	//delete function passes the right pointer of whatever needs to be delete, this function finds the minimum (lesser value) of the right subtree
	while (root->left != NULL)
	{
		root = root->left;
		return root;
	}
}

bNode* Delete(bNode* root, int num)
{
	if (root == NULL)
	{
		//base case if bst is empty
		return root;
	}
	else if (num < root->num)
	{
		//if number needing to be deleted is less than root, go to left and recall delete function while making this left value act as the new 'root' node in the new function call
		root->left = Delete(root->left, num);
	}
	else if (num > root->num)
	{
		//same as previous but it compares if number is bigger than the root
		root->right = Delete(root->right, num);
	}
	else
	{
		//checks if the root is what is being deleted (through recursive calls, the program will always end up here to be deleted since with each new recursive call it essentially assigns a new root value
		if (root->left == NULL && root->right == NULL)
		{
			//if the current value is a leaf then all you have to do is delete the node and return NULL as the value and recursion will fix the pointer
			delete root;
			root = NULL;
			return root;
		}
		else if (root->left == NULL)
		{
			//if the current root has only one child 
			struct bNode *temp = root;
			root = root->right;
			delete temp;
			return root;
		}
		else if (root->right == NULL)
		{
			//if the current "root" has only one child; if the "root" has 2 children, it will go to next else statement and that else statement will eventually make its way back to this one
			struct bNode *temp = root;
			root = root->right;
			delete temp;
			return root;
		}
		else
		{
			//this is if the current "root" has 2 children; it will find the minumum value in the right subtree and switch the value that needs to be deleted with it
			//that way it preserves the rules of the bst
			struct bNode *temp = Min(root->right);
			root->num = temp->num;
			root->right = Delete(root->right, temp->num);
			return root;
		}
	}
}

void printPre(bNode* root)
{
	if (root == NULL)
	{
		return;
	}

	//recursive calls for printing
	cout << root->num << ',';
	printPre(root->left);
	printPre(root->right);

}

void printIn(bNode* root)
{
	if (root == NULL)
	{
		return;
	}

	printIn(root->left);
	cout << root->num << ',';
	printIn(root->right);
}

void printPost(bNode* root)
{
	if (root == NULL)
	{
		return;
	}

	printPost(root->left);
	printPost(root->right);
	cout << root->num << ',';
}

int main()
{
	//originally sets root node to NULL
	bNode* root = NULL;
	int choice = 0; // used for user in
	int num = 0; // used for user in

	do
	{
		//prompt will show until program is quit
		cout << "BINARY SEARCH TREE" << endl;
		cout << "1. Add\n2. Search\n3. Remove\n4. Print\n5. Quit\n";
		cin >> choice;
		switch (choice)
		{
			case 1 :
				cout << "What is the number you would like to add? ";
				cin >> num;
				if (search(root, num) == true)
				{
					//this checks to see if the number is already in the tree
					cout << "ERROR: Value already in tree: " << num << endl;
				}
				else
				{
					//make root equal the function in case the root value changes
					root = Insert(root, num);
				}
				break;
			case 2 :
				cout << "What number would you like to search for? ";
				cin >> num;
				if (search(root, num) == true)
				{
					cout << "TRUE:" << num << endl;
				}
				else
				{
					cout << "FALSE:" << num << endl;
				}
				break;
			case 3 :
				cout << "What number would you like to delete? ";
				cin >> num;
				if (search(root, num) == true)
				{
					root = Delete(root, num);
					cout << "Removal successful: " << num << endl;
				}
				else
				{
					cout << "ERROR: Not found in tree: " << num << endl;
				}
				break;
			case 4 :
				cout << "Preorder:" << endl;
				printPre(root);
				cout << endl;
				cout << "Inorder:" << endl;
				printIn(root);
				cout << endl;
				cout << "Postorder:" << endl;
				printPost(root);
				cout << endl;
				break;
			case 5 :
				break;
			default : 
				cout << "This is not a valid entry" << endl;
				break;
		}
	} while (choice != 5);
	
}
