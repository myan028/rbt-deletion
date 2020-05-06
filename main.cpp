#include "node.h"
 
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cmath>
 
/*
Code by Michael Yan
3/21/2020
This code creates a Red Black Tree, able to add, search, and print (delete later)
*/

/*
Credit to Ali Fakhry for suggesting the head be declared outside of main and called using double-astericks to (fix?)
issue where the wrong head was being printed during printTree
Note: this issue shouldn't happen, the real cause for this is still not known. This is simply a workaround.
In addition, this 'fix' may have lead to another issue.
*/


Node* addNode(Node**, Node*, int);
void printTree(Node*, int);
Node* fixTree(Node**, Node*);
Node* rotateTree(Node**, Node*, int);


using namespace std;



Node* addNode(Node** head, Node* parent, int input){ //insert pseudo: https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
    if(parent->getData() == NULL){
        parent->setColor(1);
        parent->setData(input);
    }
    else{
        if(input < parent->getData()){ //if the input is less than previous
            if(parent->getLeft() == NULL){ //if no left child
                Node* tempNode = new Node();
                tempNode->setData(input);
                tempNode->setParent(parent);
                parent->setLeft(tempNode);
                return ((fixTree(head, tempNode))); //rotate
            }
            else{
                addNode(head, parent->getLeft(), input); //call recursively to the left until no left child
            }
        }
        else{ //if the input is greater than or equal to the previous
            if(parent->getRight() == NULL){ //if no right child
                Node* tempNode = new Node();
                tempNode->setData(input);
                tempNode->setParent(parent);
                parent->setRight(tempNode);
                return ((fixTree(head, tempNode))); //rotate
            }
            else{
                addNode(head, parent->getRight(), input); //call recursively to the right until no right child
            }
        }
    }
    return (*(head)); //ensure the correct head is returned
}
 
 
 
void printTree(Node* parent, int space){ //sideways tree print algorithm (same as bst)
    
    if(parent == NULL){ //dont print an empty tree
        cout << "(tree is empty)" << endl;
        return;
    }
    
    if(parent->getRight() != NULL){
        printTree(parent->getRight(), space+1);
    }
    
    int n = space; //count variable
    
    
    while(space > 0){ //print spaces
        cout << "    ";
        space--;
    }
    
    
    if(parent->getColor() == 0){ //red
        cout << "\033[1;31m" << parent->getData() << "\033[0m" << endl; //print red
    }
    else if(parent->getColor() == 1){ //black
        cout << "\033[1;34m" << parent->getData() << "\033[0m" << endl; //print black (more like blue)
    }
    
    if(parent->getLeft() != NULL){
        printTree(parent->getLeft(), n+1);
    }
    
}
 
 
 
Node* fixTree(Node** head, Node* current){ //check and fix tree after every insertion
    
    //if current is the root, do nothing
    while(current != *head && current->getParent() != NULL && current->getParent()->getColor() == 0){ //continue fixing tree
        
        Node* parent = current->getParent(); //declare parent
        Node* grandparent = parent->getParent(); //declare grandparent
        
        if(parent == grandparent->getLeft()){ //if parent is left child
		
            Node* uncle = grandparent->getRight(); //right uncle
            
            if(uncle != NULL && uncle->getColor() == 0){ //if uncle is red
                parent->setColor(1);
                uncle->setColor(1);
                grandparent->setColor(0); //grand parent is red
				
                current = grandparent; //set new current to keep fixing tree
            }
            
            else{ //if uncle is black
                if(current == parent->getRight()){ //if current is right child
                    current = parent;
					rotateTree(head, current, 0); //rotate left
					
                }
                //current is left child
                int tempColor = parent->getColor();
                parent->setColor(grandparent->getColor());
                grandparent->setColor(tempColor);
				
				rotateTree(head, grandparent, 1); //rotate right
				
				//return (*(head));
            }
        }
        
        else{ //if parent is right childe
            
            Node* uncle = grandparent->getLeft(); //left uncle
            
            //same as parent left child
            if(uncle != NULL && uncle->getColor() == 0){ //if uncle is red
                
                parent->setColor(1);
                uncle->setColor(1);
                grandparent->setColor(0); //grand parent red
				
                current = grandparent; //set new current to keep fixing tree
            }
			
            else{ //if uncle is black
                if(current == parent->getLeft()){ //if current is left child
                    current = parent; //current is now the PARENT
					rotateTree(head, current, 1); //rotate right
                }
                //current is right child
				
                int tempColor = parent->getColor();
				parent->setColor(1);
                grandparent->setColor(0);
				current->setColor(0);
				
				rotateTree(head, grandparent, 0); //rotate left
				
				//return (*(head)); //needs to break out for some reason (???)
            }
        }
        
    }
    (*head)->setColor(1); //root is always black
    return (*(head)); //ensure correct head
}
 
 
 
 
 
Node* rotateTree(Node** head, Node* current, int leftright){ //rotate tree to retain rules of the rbt
    
    //0 is left, 1 is right
    if(leftright == 0){ //left rotation
		
        
        Node* rightNode = current->getRight(); //current's right child
        
		current->setRight(rightNode->getLeft());  
        
        if(rightNode->getLeft() != NULL){
            rightNode->getLeft()->setParent(current);
        }

        
        rightNode->setParent(current->getParent());
        
        
        if(current == (*(head))){
            (*(head)) = rightNode;
        }
        else{
            if(current == current->getParent()->getLeft()){
                current->getParent()->setLeft(rightNode);
            }
            else{
                current->getParent()->setRight(rightNode);
            }
        }
        
        rightNode->setLeft(current);
        current->setParent(rightNode);
		
		rightNode->setColor(1);
		
    }
    
    
    
    else if(leftright == 1){ //right rotation
        Node* leftNode = current->getLeft();
        
        cout << current->getLeft()->getData() << endl;
        
        current->setLeft(leftNode->getRight());
        if(leftNode->getRight() != NULL){
            leftNode->getRight()->setParent(current);
        }
        leftNode->setParent(current->getParent());
        if(current == (*(head))){
            (*(head)) = leftNode;
        }
        else{
            if(current == current->getParent()->getLeft()){
                current->getParent()->setLeft(leftNode);
            }
            else{ //must be right
                current->getParent()->setRight(leftNode);
            }
        }
        leftNode->setRight(current);
        current->setParent(leftNode);
		
		//printTree(*head, 0); //test
    }
    
    return *head;
}


Node* search(int number, Node* current){ //search tree for node with certain value
	
	if (number == current -> getData()){
		return current;
	}
	else if (number > current->getData()){
		if (current->getRight() == NULL){
			return NULL;
		}
		else{
			search(number, current->getRight());
		}
	}

	else if (number < current->getData()){
		if (current -> getLeft() == NULL){
			return NULL;
		}
		else{
			search(number, current -> getLeft());
		}
	}
	else {
		return NULL;
	}
}


 
int main(){
    
    Node* head = new Node;
    
    int index = 0;
    int *stor = new int[1000];
    
    
    //Node* head = new Node(); //declare outside
    
    
    while(true){ //give user action command options
        cout << "\nEnter a command. Type 'add', 'read', 'print', 'search', or 'quit': ";
        
        char* command = new char[10];
        cin.getline(command, 10);
        int number = 0;
        
        if(strcmp(command, "add") == 0){ //add numbers in console
            cout << "Enter the number you want to add: " << endl;
            cin >> number;
            cin.get();
            head = ((addNode(&head, head, number)));
            //cout << ":" <<endl;
            //cout << head -> getData() << endl;
        }
        
        else if(strcmp(command, "read") == 0){
            cout << "Type the file name (include the .txt extension): ";
            char* filename = new char[100];
            cin.getline(filename, 100);
            
            ifstream inFile; //get file input
            inFile.open(filename);
			
			while(inFile.eof() != true){
				char* running = new char[3];
				inFile.getline(running, 4, ' '); //numbers separated by spaces
				int input = atoi(running);
				addNode(&head, head, input); //execute insertion
			}
			inFile.close();
        }
        
        else if(strcmp(command, "print") == 0){ //print rbt
            printTree(head, 0);
        }
		
		else if(strcmp(command, "search") == 0){
			if(head->getData() == NULL){ //don't search an empty tree
				cout << "(tree is empty)" << endl;
			}
			else{
				cout << "Enter the number you would like to search: ";
				cin >> number;
				cin.clear();
				cin.ignore(9999, '\n');
				Node* searchResult = search(number, head);
				if(searchResult != NULL){ //if search node is not null, the value exists
					cout << number << " was found!" << endl;
				}
				else{ //else no matching node was found
					cout << number << " was not found in the tree." << endl;
				}
			}
		}
        
        else if(strcmp(command, "quit") == 0){ //if user wants to quit program
            return false; //quit program
        }
    
    }
 
}
