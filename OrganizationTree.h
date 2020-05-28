#include <new>
#include <stdexcept>
#include <string>
using namespace std;

class TreeNode 
{
public:
	TreeNode(string name, TreeNode* sibling, int parent_height);
	string name;
	int height; //Ʈ�� ���� 
	TreeNode* sibling; //linkedlist 
	TreeNode* child;
};

class Tree
{
public:
	Tree();
	~Tree();
	void clear();
	void insert(string employer, string employee);
	void insert_sibling(TreeNode* employee, TreeNode*first);
	void remove(string employee);
	void remove_node(TreeNode* parent);
	bool isEmpty()const;
	void showStrucuture(TreeNode* root)const;
	void showSub()const;
	TreeNode* findEmployer(string name, TreeNode* node)const;
	TreeNode* findEmployer_child(string name, TreeNode* parent)const;
private:
	TreeNode* root;

};