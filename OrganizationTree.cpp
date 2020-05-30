#include "OrganizationTree.h"
#include <iostream>
using namespace std;

//���� �� ������ ����� �θ��� ã�Ƽ�, �θ�->child null�� �ٲپ��ְ� sibling�� ������ �ʿ�.

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
	//employer�� ��ġ�ϴ� ��带 ã�´�.
	//�ش� ����� child�� sibling���� employee�� �����Ѵ�.
	if (isEmpty()) { //ù ����� 
		TreeNode* newRoot = new TreeNode(employer, NULL, 0);
		root = newRoot;
		TreeNode* newEmployee = new TreeNode(employee, root->child, root->height);
		root->child = newEmployee;
	}
	else { //ù ��尡 �ƴ϶��
		TreeNode* parent=findEmployer(employer, root);
		if (parent == NULL) { //�߸��� ����� ���� 
			cout << "error" << endl;
			return;
		}
		TreeNode* newEmployee = new TreeNode(employee, NULL, parent->height);
		if (parent->child == NULL) { //ù�ڽ��̶�� 
			parent->child = newEmployee;
		}
		else  //ù�ڽ��� �ƴ϶�� .. sibling��� �����ش�. 
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
	TreeNode* tmp = node; //��Ʈ���� 

	while (tmp) {
		for (int i = 1; i < tmp->height; i++) cout << "+"; //+ ���̸�ŭ +��� 
		cout << tmp->name; //�̸���� 
		cout << endl;
		TreeNode* tmpChild = tmp->child; //��Ʈ �ڽ� 
		while (tmpChild != NULL)  //��� ��Ʈ�� �ڽĿ� ���Ͽ� 
		{
			for (int i = 1; i < tmpChild->height; i++) cout << "+"; //+ ���̸�ŭ +��� 
			cout << tmpChild->name; //�̸���� 
			cout << endl;
			if (tmpChild->child != NULL) { //�ش� �ڽ��� �ڽ��� �ִٸ� ? 
				showStrucuture(tmpChild->child);
			}
			tmpChild = tmpChild->sibling; //���� �ڽ� 
		}
		tmp = tmp->sibling;
	}
}
