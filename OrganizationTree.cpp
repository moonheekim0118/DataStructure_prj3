#include "OrganizationTree.h"
#include <iostream>
using namespace std;

//삭제 시 삭제할 노드의 부모노드 찾아서, 부모->child null로 바꾸어주고 sibling도 움직임 필요.

TreeNode::TreeNode(string name, TreeNode* sibling, int parent_height) {
	this->name = name;
	this->sibling = sibling;
	this->height = parent_height+1;

}

Tree::Tree() {
	root = NULL;
}
Tree::~Tree() {
	clear();
}
void Tree::clear() {
	root = NULL;
}
void Tree::insert(string employer, string employee) {
	//employer와 일치하는 노드를 찾는다.
	//해당 노드의 child의 sibling으로 employee를 삽입한다.
	if (isEmpty()) { //첫 노드라면 
		TreeNode* newRoot = new TreeNode(employer, NULL, 0);
		root = newRoot;
		TreeNode* newEmployee = new TreeNode(employee, root->child, root->height);
		root->child = newEmployee;
	}
	else { //첫 노드가 아니라면
		TreeNode* parent=findEmployer(employer, root);
		if (parent == NULL) { //잘못된 고용주 정보 
			cout << "error" << endl;
			return;
		}
		TreeNode* newEmployee = new TreeNode(employee, NULL, parent->height);
		if (parent->child == NULL) { //첫자식이라면 
			parent->child = newEmployee;
		}
		else  //첫자식이 아니라면 .. sibling들과 엮어준다. 
		{
			insert_sibling(newEmployee, parent->child);
		}
	}
	
}

void Tree::insert_sibling(TreeNode* employee, TreeNode* first) {
	TreeNode* tmp = first;
	while (tmp->sibling != NULL) 
	{
		tmp = tmp->sibling;
	}
	tmp->sibling = employee;
}

TreeNode* Tree:: findEmployer(string name,TreeNode* node)const
{
	TreeNode* tmp = node;
	while (tmp) {
		if (tmp->name == name) return tmp;
		TreeNode* found = findEmployer_child(name, tmp);
		if (found != NULL) return found;
		tmp = tmp->child;
	}
	return NULL;
}

TreeNode* Tree::findEmployer_child(string name, TreeNode* parent)const {
	TreeNode* tmp = parent;
	while (tmp) {
		if (tmp->name == name) return tmp;
		tmp = tmp->sibling;
	}
	return NULL;
}

void Tree::remove(string employee) {
	if (isEmpty()) {
		return;
	}
	TreeNode* employeeNode = findEmployer(employee, root);
	TreeNode* child = employeeNode->child;

	if (child == NULL) {
		employeeNode = NULL;
		delete employeeNode;
		return;
	}
	move_child(employeeNode);
}

void Tree::move_child(TreeNode* parent) {

	if (parent->child == NULL) 
		return;
	TreeNode* child = parent->child;
	parent->name = child->name;
	if (child->child == NULL) 
	{
		if (child->sibling != NULL) parent->child = child->sibling;
		else parent->child = NULL;
	}
	
	else {
		move_child(child);
	}

	
}

void Tree::duplicate_child(TreeNode* parent, TreeNode* dup) 
{
	parent->child = dup->sibling;
	TreeNode* tmp = dup->sibling;
	TreeNode* tmp2 = parent->child;
	while (tmp) 
	{
		tmp2->sibling = tmp->sibling;
		tmp2 = tmp2->sibling;
		tmp = tmp->sibling;
	}
}

bool Tree::isEmpty()const {
	return root == NULL;
}

void Tree::showStrucuture(TreeNode* node)const 
{
	if (node == NULL) node = root;
	TreeNode* tmp = node; //루트부터 

	while (tmp) {
		for (int i = 1; i < tmp->height; i++) cout << "+"; //+ 높이만큼 +출력 
		cout << tmp->name; //이름출력 
		cout << endl;
		TreeNode* tmpChild = tmp->child; //루트 자식 
		while (tmpChild != NULL)  //모든 루트의 자식에 대하여 
		{
			for (int i = 1; i < tmpChild->height; i++) cout << "+"; //+ 높이만큼 +출력 
			cout << tmpChild->name; //이름출력 
			cout << endl;
			if (tmpChild->child != NULL) { //해당 자식이 자식이 있다면 ? 
				showStrucuture(tmpChild->child);
			}
			tmpChild = tmpChild->sibling; //다음 자식 
		}
		tmp = tmp->sibling;
	}
}
