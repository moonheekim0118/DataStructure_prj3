#include "OrganizationTree.h"
#include <iostream>
using namespace std;

//���� �ʿ� : ���� 2�� �ڽĵ��� �ڽ� 1���ۿ� �߰��� �ȵȴ�.
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
		cout << tmp->name << endl;
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
		//parentã�Ƽ�..nulló���������..
		delete employeeNode;
		return;
	}
	employeeNode->name = child->name;
	employeeNode->child = child->sibling;
}


bool Tree::isEmpty()const {
	return root == NULL;
}

void Tree::showStrucuture(TreeNode* root)const 
{
	TreeNode* tmp = root; //��Ʈ���� 
	for (int i = 1; i < tmp->height; i++) cout << "+"; //+ ���̸�ŭ +��� 
	cout << tmp->name; //�̸���� 
	cout << endl;
	tmp = root->child; //��Ʈ �ڽ� 
	while (tmp != NULL)  //��� ��Ʈ�� �ڽĿ� ���Ͽ� 
	{
		for (int i = 1; i < tmp->height; i++) cout << "+"; //+ ���̸�ŭ +��� 
		cout << tmp->name; //�̸���� 
		cout << endl;
		if (tmp->child != NULL) { //�ش� �ڽ��� �ڽ��� �ִٸ� ? 
			showStrucuture(tmp->child);
		}
		tmp = tmp->sibling; //���� �ڽ� 
	}
}
//�� �� �Լ� �ϳ��� ��ġ�� 
void Tree::showSub()const 
{
	TreeNode* tmp = root; //��Ʈ���� 
	cout << tmp->name; //�̸���� 
	cout << endl;
	tmp = root->child; //��Ʈ �ڽ� 
	while (tmp != NULL)  //��� ��Ʈ�� �ڽĿ� ���Ͽ� 
	{
		for (int i = 1; i < tmp->height; i++) cout << "+"; //+ ���̸�ŭ +��� 
		cout << tmp->name; //�̸���� 
		cout << endl;
		if (tmp->child != NULL) { //�ش� �ڽ��� �ڽ��� �ִٸ� ? 
			showStrucuture(tmp->child);
		}
		tmp = tmp->sibling; //���� �ڽ� 
	}
}