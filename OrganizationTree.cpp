#include "OrganizationTree.h"
#include <iostream>
using namespace std;


TreeNode::TreeNode(string name, TreeNode* sibling, int parent_height) { //생성자 
	this->name = name;
	this->sibling = sibling;
	this->height = parent_height+1; //받은 parent_height에 1을 추가해준다 .
}

Tree::Tree() { //생성자 
	root = NULL;
}

Tree::~Tree() { //소멸자
	clear();
}
void Tree::clear() {
	root = NULL;
	destroy_child(root);
	
}
void Tree::destroy_child(TreeNode* node)  //모든 노드 삭제 
{
	if (node == NULL) return;
	destroy_child(node->child); //재귀적으로 모든 child를 삭제한다. 
	destroy_sibling(node); //각 child의 sibling들도 모두 삭제 
	delete node; 
}
void Tree::destroy_sibling(TreeNode* node)  //특정 노드의 sibling노드들 삭제 
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
	//employer와 일치하는 노드를 찾는다.
	//해당 노드의 child의 sibling으로 employee를 삽입한다.
	if (isEmpty()) { //첫 노드라면 
		TreeNode* newRoot = new TreeNode(employer, NULL, 0);
		root = newRoot;
		TreeNode* newEmployee = new TreeNode(employee, root->child, root->height);
		root->child = newEmployee;
	}
	else { //첫 노드가 아니라면
		TreeNode* parent=getNode(employer, root);
		if (parent == NULL) { //잘못된 고용주 정보 
			cout << "이름을 잘못 입력하였습니다." << endl;
			return;
		}
		TreeNode* newEmployee = new TreeNode(employee, NULL, parent->height);
		if (parent->child == NULL) { //첫자식이라면  child로 지정 
			parent->child = newEmployee;
		}
		else  //첫자식이 아니라면, sibling 링크드리스트에 따로 추가해준다 . 
		{
			insert_sibling(newEmployee, parent->child);
		}
	}
	
}

void Tree::insert_sibling(TreeNode* employee, TreeNode* first) { // sibling 링크드리스트 맨끝에 추가해준다. 
	TreeNode* tmp = first;
	while (tmp->sibling != NULL) 
	{
		tmp = tmp->sibling;
	}
	tmp->sibling = employee;
}

TreeNode* Tree:: getNode(string name,TreeNode* node)const //특정 노드 반환 
{
	TreeNode* tmp = node;
	while (tmp) {
		if (tmp->name == name) return tmp; //이름이 같다면 바로 반환 
		TreeNode* found = getNode_sub(name, tmp); // sibling 연결리스트도 살펴본다. 
		if (found != NULL) return found; //sibling에서 찾았다면 바로 반환 
		tmp = tmp->child;
	}
	return NULL;
}

TreeNode* Tree::getNode_sub(string name, TreeNode* parent)const { //sibling노드들 살펴보는 함수 
	TreeNode* tmp = parent;
	while (tmp) {
		if (tmp->name == name) return tmp;
		tmp = tmp->sibling;
	}
	return NULL;
}

void Tree::remove(string employee) { //fire 해고하는 함수 
	if (isEmpty()) { 
		return;
	}

	TreeNode* employeeNode = getNode(employee, root);
	if (employeeNode == NULL) {
		cout << "이름을 잘못 입력하였습니다." << endl;
		return;
	}

	TreeNode* child = employeeNode->child; //삭제할 노드의 자식 
	if (child == NULL) { //자식이 없다면 
		removeNode(employee); // 트리 내에서 삭제 
		delete employeeNode; //할당 해제 
	}
	else { //자식이 있다면 
		move_child(employeeNode); //자식들의 구조를 바꾸어준다 .
	}
}

void Tree::removeNode(string employee)  //삭제 보조함수 
{
	TreeNode* tmp = root;
	while (tmp->child) { 
		if (tmp->child->name == employee) { //바로 아래 child 중에 있는지 찾아보기 
			if (tmp->child->sibling != NULL) { //child에서 찾았고, child옆에 sibling이 있다면,  
				tmp->child = tmp->child->sibling; //sibling을 새로운 child로 바꾸어준다. 
				tmp->child->sibling = NULL; 
			}
			else {
				tmp->child = NULL;
			}
			return;
		}
		bool found = removeNodeSub(employee, tmp); //sibling에서 찾아본다.  
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
			tmp_pre->sibling = tmp->sibling; //sibling조정 
			return true;
		}
		tmp_pre = tmp;
		tmp = tmp->sibling;
	}
	return false;
}



void Tree::move_child(TreeNode* parent) { //트리 구조 변경해주는 함수 

	if (parent->child == NULL) {
		return;  
	}
	TreeNode* childNode = parent->child; //삭제할 노드의 자식 
	parent->name = childNode->name; //삭제할 노드의 이름을 자식 이름으로 변경해주기 
	TreeNode* removed = childNode; //위 노드로 복사된 노드는 할당해제해준다.
	if (childNode->child == NULL)   //child 변경 , 만약 child가 없다면, 기존 sibling노드를 자식으로 옮겨주어야한다.
	{
		if (childNode->sibling != NULL) parent->child = childNode->sibling;
		else parent->child = NULL;
		delete removed; //할당 해제 
	}
	
	else { //child가 있다면 재귀적으로 
		move_child(childNode);
	}
}


bool Tree::isEmpty()const {
	return root == NULL;
}

void Tree::showStrucuture(TreeNode* node)const 
{
	if (node == NULL) node = root;
	TreeNode* tmp = node; //루트부터 

	while (tmp!=NULL) {
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
