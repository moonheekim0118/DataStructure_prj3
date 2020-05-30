#include <new>
#include <stdexcept>
#include <string>
using namespace std;

class TreeNode 
{
public:
	TreeNode(string name, TreeNode* sibling, int parent_height);
	string name; //�̸� ���� 
	int height; //Ʈ�� ����  + ����� ���ؼ� 
	TreeNode* sibling; //�θ��� �ڽĵ��� linkedlist�� �������ֱ� 
	TreeNode* child; //�ڽ� ��ǥ 
};

class Tree
{
public:
	Tree(); //������   
	~Tree(); //�Ҹ��� 
	void clear(); // �Ҹ� 
	void destroy_child(TreeNode* node); //��� child ���� 
	void destroy_sibling(TreeNode* node); //��� sibling ���� 
	void insert(string employer, string employee); //���� 
	void insert_sibling(TreeNode* employee, TreeNode*first); //���Ժ��� , sibling�� �߰� 
	
	void remove(string employee); // fire 
	void removeNode(string employee); //���� ���� (������ ��尡 child�� ���� ��� ) 
	bool removeNodeSub(string employee, TreeNode* parent); //���� ���� 2
	
	void move_child(TreeNode* parent); //���� ���� (������ ��尡 child�� �ִ� ���, Ʈ�� ���� �ٲٴ� �Լ�)
	
	bool isEmpty()const; //Ʈ���� ������� Ȯ�� 
	void showStrucuture(TreeNode* root)const; //print 

	TreeNode* getNode(string name, TreeNode* node)const; //name�� �ش��ϴ� node��ȯ 
	TreeNode* getNode_sub(string name, TreeNode* parent)const;
private:
	TreeNode* root;

};