
#include<iostream>
using namespace std;
class DLL {

public:
	class record {

	public:
		int issn;
		string title;
		int copiesAvailableAsReferenceBook, copiesAvailableAsIssuableBook;
		record* prv;
		record* next;
		string* listofauthors;
		int noofauthors;

		record(int a, string x, int b, int c, string* list, int e)
		{
			issn = a;
			title = x;
			copiesAvailableAsReferenceBook = b;
			copiesAvailableAsIssuableBook = c;
			noofauthors = e;
			for (int i = 0; i < e; i++)
			{
				listofauthors[i] = list[i];
			}



		}
		record()
		{
			issn = 0;
			title = " ";
			copiesAvailableAsIssuableBook = copiesAvailableAsReferenceBook = 0;
			listofauthors = 0;
			noofauthors = 0;
		}
		void insert(int a, string x, int b, int c, string* list, int e)
		{


			issn = a;
			title = x;
			copiesAvailableAsReferenceBook = b;
			copiesAvailableAsIssuableBook = c;
			noofauthors = e;
			listofauthors = new string[e];
			for (int i = 0; i < e; i++)
			{
				listofauthors[i] = list[i];
			}

		}
		void Display()
		{
			cout << "The ISSN no of book is " << endl;
			cout << issn << endl;
			cout << "The title of book is " << endl;
			cout << title << endl;
			cout << "authors of book are" << endl;

			for (int i = 0; i < noofauthors; i++)
			{
				cout << i + 1 << ")" << listofauthors[i] << endl;
			}
			cout << "No of issueable books are" << endl;
			cout << copiesAvailableAsIssuableBook << endl;
			cout << "No of refernce books are " << endl;
			cout << copiesAvailableAsReferenceBook << endl;
		}
	};
	record* head;
	record* tail;



	DLL()
	{
		head = new record();
		tail = new record();
		head->next = tail;
		head->prv = nullptr;
		tail->next = nullptr;
		tail->prv = head;


	}

	void  insert(int a, string x, int b, int c, string* arr, int j)
	{
		record* temp = new record(a, x, b, c, arr, j);
		temp->prv = head;
		temp->next = head->next;
		head->next->prv = temp;
		head->next = temp;

	}

	void display()
	{
		record* temp = head->next;

		while (temp != tail)
		{
			temp->Display();
			temp = temp->next;
			cout << endl << endl;
		}
	}

	record* gethead()
	{
		return head;
	}


};

class AVL {

	class node {

	public:
		int height;
		int issn;
		node* left;
		node* right;
		DLL::record* ptr = new DLL::record();


		node(DLL::record* head, node* previous, int i, string title, int issuable, int refernce, string* arr, int authorsNO)
		{
			issn = i;

			if (previous == nullptr) //meaning we are inserting first node
			{
				ptr->insert(i, title, issuable, refernce, arr, authorsNO);
				ptr->next = head->next;
				ptr->prv = head;
				head->next->prv = ptr;
				head->next = ptr;






			}
			else if (issn > previous->ptr->issn)
			{
				ptr->insert(i, title, issuable, refernce, arr, authorsNO);
				this->ptr->next = previous->ptr->next;
				this->ptr->prv = previous->ptr;
				previous->ptr->next->prv = this->ptr;
				previous->ptr->next = this->ptr;

			}
			else if (issn < previous->ptr->issn)
			{
				ptr->insert(i, title, issuable, refernce, arr, authorsNO);
				ptr->next = previous->ptr;
				ptr->prv = previous->ptr->prv;
				previous->ptr->prv->next = this->ptr;
				previous->ptr->prv = ptr;
			}

		}
		node()
		{
			issn = 0;
			left = right = nullptr;

		}

		void Display()
		{
			cout << "\t \t The ISSN no of book is : ";
			cout << ptr->issn << endl;
			cout << endl;
			cout << "\t \t The title of book is : ";
			cout << ptr->title << endl;
			cout << endl;
			cout << "\t \t Authors of book are : ";

			for (int i = 0; i < ptr->noofauthors; i++)
			{
				cout << i + 1 << ")" << ptr->listofauthors[i] << " ";
			}
			cout << endl;
			cout << endl;
			cout << "\t \t No of issueable books are : ";
			cout << ptr->copiesAvailableAsIssuableBook << endl;
			cout << endl;
			cout << "\t \t No of refernce books are : ";
			cout << ptr->copiesAvailableAsReferenceBook << endl;
			cout << endl;
			cout << endl;
		}

		void settitle(string a)
		{
			ptr->title = a;
		}

		void setREFBOOKS(int x)
		{
			ptr->copiesAvailableAsReferenceBook = x;
		}
		void setISSUABLEBOOKS(int x)
		{
			ptr->copiesAvailableAsIssuableBook = x;
		}
		void setLISTauthors(string* arr, int a)
		{
			ptr->listofauthors = new string[a];

			for (int i = 0; i < a; i++)
			{
				ptr->listofauthors[i] = arr[i];
			}
		}
	};
	node* root;

public:
	AVL()
	{
		root = nullptr;
	}
	void insert(DLL::record* ptr, int i, string a, int b, int c, string* arr, int e)  // wrapper function
	{
		insert(ptr, root, root, i, a, b, c, arr, e);
	}
	void insert(DLL::record* head, node* previous, node*& r, int i, string a, int b, int c, string* arr, int e)
	{
		if (r == nullptr)
		{
			r = new node(head, previous, i, a, b, c, arr, e);   //previous keeps track of the parent node whose child is to be isnerted (keeps the info of node whose left or right child is to be inserted)

			r->left = nullptr;
			r->right = nullptr;
			r->height = 0;
		}
		if (i > r->issn)
		{
			previous = r;

			insert(head, previous, r->right, i, a, b, c, arr, e);

		}
		if (i < r->issn)
		{
			previous = r;

			insert(head, previous, r->left, i, a, b, c, arr, e);

		}

		balance(r); //it will check the Balance factor of node after isnertio and will perform rotations when BF is disturbed


	}

	void rotateLEFT(node*& r)
	{

		node* newParent = r->right;
		r->right = newParent->left;
		newParent->left = r;

		r->height = 1 + max(getheight(r->right), getheight(r->left));
		newParent->height = 1 + max(getheight(newParent->right), getheight(newParent->left));
		r = newParent;
	}

	void rotateRIGHT(node*& r)
	{
		node* newParent = r->left;
		r->left = newParent->right;
		newParent->right = r;

		r->height = 1 + max(getheight(r->right), getheight(r->left));
		newParent->height = 1 + max(getheight(newParent->right), getheight(newParent->left));
		r = newParent;
	}

	void rotateLEFTRIGHT(node*& r)
	{
		rotateLEFT(r->left);
		rotateRIGHT(r);
	}
	void rotateRIGHTLEFT(node*& r)
	{
		rotateRIGHT(r->right);
		rotateLEFT(r);
	}
	void deletenode()//wrapper function
	{
		cout << "Enter the issn no book record you want to delete " << endl;
		int i;
		cin >> i;
		bool f = true;
		deletenode(root, i, f);
	}

	void deletenode(node*& r, int i, bool f)
	{

		if (r == nullptr)
		{
			cout << "RECORD against ISSN no " << i << " not found " << endl;
			return;
		}

		else if (i > r->issn)
		{
			deletenode(r->right, i, f);

		}

		else if (i < r->issn)
		{
			deletenode(r->left, i, f);

		}
		else if (r->issn = i)
		{

			if (f)
			{

				deletenodeFROMDoubly(r); //deleting node from doubly list of the corresponding avl node
				cout << "RECORD of book  with ISSN " << i << " has been deleted from the records " << endl;

			}



			if (r->right == nullptr && r->left == nullptr)
			{
				delete r;
				r = nullptr;
				return;
			}
			if (r->right == nullptr && r->left != nullptr)
			{
				node* temp = r;
				r = r->left;
				delete temp;
			}
			if (r->right != nullptr && r->left == nullptr)
			{
				node* temp = r;
				r = r->right;
				delete temp;
			}

			if (r->right != nullptr && r->left != nullptr)
			{
				r->issn = findmin(r->right);
				f = false;
				deletenode(r->right, r->issn, f);
			}
		}

		balance(r);


	}

	void balance(node*& r)
	{
		if (r == nullptr)
			return;

		if (getheight(r->left) - getheight(r->right) >= 2) //rotate right case  (left side heavy)
		{     //now we check if we require one rotation or two

			if (getheight(r->left->left) >= getheight(r->left->right)) //insertion happened on left side of left subtree
			{                      // we will rotate once
				rotateRIGHT(r);
			}
			else                 //insertion happened on right side of left subtree
			{
				rotateLEFTRIGHT(r);                 // we will rotate twice
			}

		}
		if (getheight(r->left) - getheight(r->right) <= -2) //rotate left case   (right side heavy)
		{     //now we check if we require one rotation or two

			if (getheight(r->right->right) >= getheight(r->right->left)) //insertion happened on right side of right subtree
			{                      // we will rotate once
				rotateLEFT(r);
			}
			else                 //insertion happened on left side of right subtree
			{
				rotateRIGHTLEFT(r);                 // we will rotate twice
			}

		}
		r->height = 1 + max(getheight(r->left), getheight(r->right));
	}


	bool deletenodeFROMDoubly(node*& r)
	{
		DLL::record* temp = r->ptr;
		temp->prv->next = temp->next;
		temp->next->prv = temp->prv;
		delete temp;

		return true;


	}


	int findmin(node* r)
	{
		while (r->left != nullptr)
		{
			r = r->left;
		}
		return r->issn;
	}
	void setINFO(DLL::record* ptr)
	{
		int a;
		string title;
		int b;
		int c;
		int d;
		cout << "Enter the ISSN no of book you want to add " << endl;
		cin >> a;

		cout << "Enter the title of book " << endl;
		cin >> title;
		cout << "Enter the no of copies available as refernce books" << endl;

		cin >> b;
		cout << "Enter the no of copies available as ISSUABLE book" << endl;

		cin >> c;
		cout << "Enter the no of authors of book " << endl;

		cin >> d;
		string* arr = new string[d];

		for (int i = 0; i < d; i++)
		{
			cout << "Enter the name of author no " << i + 1 << endl;
			cin >> arr[i];
		}
		insert(ptr, a, title, b, c, arr, d);

	}

	void display()//wrapper function
	{
		cout << "Enter the ISSN no you want to search the record of book against " << endl;
		int i;
		cin >> i;
		display(i, root);
	}
	void modify()//wrapper function
	{
		int i;
		cout << "ENTER the ISSN no of book record you want to modifiy" << endl;
		cin >> i;

		modify(i, root);
	}


	void modify(int i, node* r)
	{
		if (r == nullptr)
		{
			cout << "BOOK record with ISSN " << i << " not found in LIBRARY records" << endl;
			return;
		}
		if (i > r->issn)
		{
			modify(i, r->right);

		}
		if (i < r->issn)
		{
			modify(i, r->left);
		}
		if (i == r->issn)
		{
			cout << "RECORD OF BOOK Before modification IS " << endl;
			r->Display();
			change(r);
			cout << "RECORD OF BOOK AFTER modification IS " << endl;
			r->Display();
		}
	}

	void change(node* r)
	{
		int chose;

		do {
			cout << "Press 1 if you want to change the name of book " << endl;
			cout << "PRESS 2 if you want to change the no of issuable books" << endl;
			cout << "PRESS 3 if you want to change the no of refernce books" << endl;
			cout << "PRESS 4 if you want to change the name of author " << endl;
			cin >> chose;

			if (chose == 1)
			{
				string a;
				cout << "Enter the new name of book " << endl;
				cin >> a;
				r->settitle(a);
			}
			if (chose == 2)
			{
				int a;
				cout << "Enter the new no of issuable books " << endl;
				cin >> a;
				r->setISSUABLEBOOKS(a);

			}

			if (chose == 3)
			{
				int a;
				cout << "Enter the new no of refernce books " << endl;
				cin >> a;
				r->setREFBOOKS(a);
			}

			if (chose == 4)
			{
				cout << "Enter the new no of authors for the book " << endl;
				int x;
				cin >> x;
				string* arr = new string[x];

				for (int i = 0; i < x; i++)
				{
					cout << "Enter the name of author number " << i + 1 << endl;
					cin >> arr[i];
				}

				r->setLISTauthors(arr, x);
			}

		} while (chose < 1 || chose>4);


	}
	void display(int i, node* r)
	{
		if (r == nullptr)
		{
			cout << "BOOK record with ISSN " << i << " not found in LIBRARY records" << endl;
			return;
		}
		if (i > r->issn)
		{
			display(i, r->right);

		}
		if (i < r->issn)
		{
			display(i, r->left);
		}
		if (i == r->issn)
		{
			r->Display();
		}




	}

	void BF()//wrapper function
	{
		BF(root);
	}

	void BF(node* r)
	{
		if (r != nullptr)
		{
			BF(r->left);

			cout << "BALANCE Factor of node with issn  " << r->issn << " : ";
			if (r->left == nullptr && r->right == nullptr)
				cout << 0 << endl;
			else
				cout << getheight(r->left) - getheight(r->right) << endl;
			BF(r->right);
		}
	}
	void printroot()//wrapper function
	{
		printroot(root);
	}

	void printroot(node* r)
	{
		cout << "Root of AVL TREE at the moment is " << r->issn << endl;
		cout << "Height of root is " << r->height << endl;
	}
	void displayHEIGHT()//wrapper function
	{
		displayHEIGHT(root);

	}

	void displayHEIGHT(node* r)
	{
		if (r != nullptr)
		{
			displayHEIGHT(r->left);
			cout << "HEIGHT OF NODE WITH ISSN " << r->issn << " is " << r->height << endl;
			displayHEIGHT(r->right);
		}
	}
	void displayall() //wrapper function
	{
		displayall(root);
	}

	void displayall(node* r)
	{
		if (r != nullptr)
		{
			displayall(r->left);
			r->Display();
			displayall(r->right);
		}

	}
	int getheight(node* r)
	{
		if (r == nullptr)
			return -1;
		else
			return r->height;
	}

	void inorderPRINT()//wrapper function
	{
		inorderPRINT(root);
	}

	void inorderPRINT(node* r)
	{
		cout << "INORDER ISSN OF BOOKS IN AVL TREE ARE " << endl;
		if (r != nullptr)
		{
			inorderPRINT(r->left);
			cout << r->issn << " ";
			inorderPRINT(r->right);
		}
		cout << endl;
	}
};

int main()
{
	AVL ptr; // we will perform all our avl funs with this object

	DLL obj; // when performing the first insertion we need head of DLL to do so . so we create an object whose DLL will fill up  when we perfrom insertion ion DLL to keep records of book

	int choice;
	cout << "\t \t \t LUMBER 1 LIBRARY ALL YOUR BOOK RECORDS ARE SAFE WITH US " << endl;
	cout << endl;
	do
	{
		cout << "IF you want to ADD a new book record PRESS 1 " << endl;
		cout << endl << endl;
		cout << "IF you want to REVIEW book record PRESS 2 " << endl;
		cout << endl << endl;
		cout << "IF you want to UPDATE book record PRESS 3 " << endl;
		cout << endl << endl;
		cout << "IF you want to DELETE a book record PRESS 4 " << endl;
		cout << endl << endl;
		cout << "IF you want to see records of all the books stored in DOUBLY LINKED LIST PRESS 5 " << endl;
		cout << endl << endl;
		cout << "IF you want to see INORDER records of ISSN of all the books PRESS 6 " << endl;
		cout << endl << endl;
		cout << "IF you want to see INFORMATION of ROOT of AVL TREE  PRESS 7 " << endl;
		cout << endl << endl;
		cout << "IF you want to see Balance Factor of all the NODES PRESS 8 " << endl;
		cout << endl << endl;
		cout << "IF you want to see HEIGHT OF all the NODES PRESS 9 " << endl;
		cout << endl;
		cout << "IF you want to TERMINATE PRESS -1 " << endl;
		cin >> choice;


		if (choice == 1)
		{
			ptr.setINFO(obj.gethead());
		}
		if (choice == 2)
		{

			ptr.display();
		}
		if (choice == 3)
		{
			ptr.modify();
		}
		if (choice == 4)
		{
			ptr.deletenode();
		}

		if (choice == 5)
		{
			ptr.displayall();
		}
		if (choice == 6)
		{
			ptr.inorderPRINT();
		}
		if (choice == 7)
		{
			ptr.printroot();
		}

		if (choice == 8)
		{
			ptr.BF();
		}
		if (choice == 9)
		{
			ptr.displayHEIGHT();
		}

	} while (choice != -1);

}
