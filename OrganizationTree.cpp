#include "OrganizationTree.h"
#include <iostream>
using namespace std;


TreeNode::TreeNode(string name, TreeNode* sibling, int parent_height) { //������ 
	this->name = name;
	this->sibling = sibling;
	this->height = parent_height+1; //���� parent_height�� 1�� �߰����ش� .
}

Tree::Tree() { //������ 
	root = NULL;
}

Tree::~Tree() { //�Ҹ���
	clear();
}
void Tree::clear() {
	root = NULL;
	destroy_child(root);
	
}
void Tree::destroy_child(TreeNode* node)  //��� ��� ���� 
{
	if (node == NULL) return;
	destroy_child(node->child); //��������� ��� child�� �����Ѵ�. 
	destroy_sibling(node); //�� child�� sibling�鵵 ��� ���� 
	delete node; 
}
void Tree::destroy_sibling(TreeNode* node)  //Ư�� ����� sibling���� ���� 
{
	TreeNode* tmp = node;
	TreeNode* removed = NULL;
	while (tmp) {
		removed = tmp->sibling;
		delete tmp;
		tmp = removed;
	}
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
		TreeNode* parent=getNode(employer, root);
		if (parent == NULL) { //�߸��� ����� ���� 
			cout << "�̸��� �߸� �Է��Ͽ����ϴ�." << endl;
			return;
		}
		TreeNode* newEmployee = new TreeNode(employee, NULL, parent->height);
		if (parent->child == NULL) { //ù�ڽ��̶��  child�� ���� 
			parent->child = newEmployee;
		}
		else  //ù�ڽ��� �ƴ϶��, sibling ��ũ�帮��Ʈ�� ���� �߰����ش� . 
		{
			insert_sibling(newEmployee, parent->child);
		}
	}
	
}

void Tree::insert_sibling(TreeNode* employee, TreeNode* first) { // sibling ��ũ�帮��Ʈ �ǳ��� �߰����ش�. 
	TreeNode* tmp = first;
	while (tmp->sibling != NULL) 
	{
		tmp = tmp->sibling;
	}
	tmp->sibling = employee;
}

TreeNode* Tree:: getNode(string name,TreeNode* node)const //Ư�� ��� ��ȯ 
{
	TreeNode* tmp = node;
	while (tmp) {
		if (tmp->name == name) return tmp; //�̸��� ���ٸ� �ٷ� ��ȯ 
		TreeNode* found = getNode_sub(name, tmp); // sibling ���Ḯ��Ʈ�� ���캻��. 
		if (found != NULL) return found; //sibling���� ã�Ҵٸ� �ٷ� ��ȯ 
		tmp = tmp->child;
	}
	return NULL;
}

TreeNode* Tree::getNode_sub(string name, TreeNode* parent)const { //sibling���� ���캸�� �Լ� 
	TreeNode* tmp = parent;
	while (tmp) {
		if (tmp->name == name) return tmp;
		tmp = tmp->sibling;
	}
	return NULL;
}

void Tree::remove(string employee) { //fire �ذ��ϴ� �Լ� 
	if (isEmpty()) { 
		return;
	}

	TreeNode* employeeNode = getNode(employee, root);
	if (employeeNode == NULL) {
		cout << "�̸��� �߸� �Է��Ͽ����ϴ�." << endl;
		return;
	}

	TreeNode* child = employeeNode->child; //������ ����� �ڽ� 
	if (child == NULL) { //�ڽ��� ���ٸ� 
		removeNode(employee); // Ʈ�� ������ ���� 
		delete employeeNode; //�Ҵ� ���� 
	}
	else { //�ڽ��� �ִٸ� 
		move_child(employeeNode); //�ڽĵ��� ������ �ٲپ��ش� .
	}
}

void Tree::removeNode(string employee)  //���� �����Լ� 
{
	TreeNode* tmp = root;
	while (tmp->child) { 
		if (tmp->child->name == employee) { //�ٷ� �Ʒ� child �߿� �ִ��� ã�ƺ��� 
			if (tmp->child->sibling != NULL) { //child���� ã�Ұ�, child���� sibling�� �ִٸ�,  
				tmp->child = tmp->child->sibling; //sibling�� ���ο� child�� �ٲپ��ش�. 
				tmp->child->sibling = NULL; 
			}
			else {
				tmp->child = NULL;
			}
			return;
		}
		bool found = removeNodeSub(employee, tmp); //sibling���� ã�ƺ���.  
		if (found) return;
		tmp = tmp->child;
	}
}

bool Tree::removeNodeSub(string employee, TreeNode* parent)
{
	TreeNode* tmp = parent->sibling;
	TreeNode* tmp_pre = parent;
	while (tmp != NULL) {
		if (tmp->name == employee)
		{
			tmp_pre->sibling = tmp->sibling; //sibling���� 
			return true;
		}
		tmp_pre = tmp;
		tmp = tmp->sibling;
	}
	return false;
}



void Tree::move_child(TreeNode* parent) { //Ʈ�� ���� �������ִ� �Լ� 

	if (parent->child == NULL) {
		return;  
	}
	TreeNode* childNode = parent->child; //������ ����� �ڽ� 
	parent->name = childNode->name; //������ ����� �̸��� �ڽ� �̸����� �������ֱ� 
	TreeNode* removed = childNode; //�� ���� ����� ���� �Ҵ��������ش�.
	if (childNode->child == NULL)   //child ���� , ���� child�� ���ٸ�, ���� sibling��带 �ڽ����� �Ű��־���Ѵ�.
	{
		if (childNode->sibling != NULL) parent->child = childNode->sibling;
		else parent->child = NULL;
		delete removed; //�Ҵ� ���� 
	}
	
	else { //child�� �ִٸ� ��������� 
		move_child(childNode);
	}
}


bool Tree::isEmpty()const {
	return root == NULL;
}

void Tree::showStrucuture(TreeNode* node)const 
{
	if (node == NULL) node = root;
	TreeNode* tmp = node; //��Ʈ���� 

	while (tmp!=NULL) {
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
