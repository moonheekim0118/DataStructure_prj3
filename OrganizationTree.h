#include <new>
#include <stdexcept>
#include <string>
using namespace std;

class TreeNode 
{
public:
	TreeNode(string name, TreeNode* sibling, int parent_height);
	string name;
	int height; //트리 높이 
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
	void find_parent(string employee);
	bool find_parentSub(string employee, TreeNode* parent);
	void remove(string employee);
	void move_child(TreeNode* parent);
	void duplicate_child(TreeNode* parent, TreeNode* dup);
	bool isEmpty()const;
	void showStrucuture(TreeNode* root)const;
	TreeNode* findEmployer(string name, TreeNode* node)const;
	TreeNode* findEmployer_child(string name, TreeNode* parent)const;
private:
	TreeNode* root;

};