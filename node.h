#ifndef NODE_H
#define NODE_H

class Node{
	public:
		Node();
		Node* getRight();
		Node* getLeft();
		Node* getParent();
		int getData();
		int getColor();
		void setData(int);
		void setLeft(Node*);
		void setRight(Node*);
		void setParent(Node*);
		void setColor(int);
		~Node();
	private:
		Node* left;
		Node* right;
		Node* parent;
		int data;
		int color;
};
#endif
