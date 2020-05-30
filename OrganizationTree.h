#include <new>
#include <stdexcept>
#include <string>
using namespace std;

class TreeNode 
{
public:
	TreeNode(string name, TreeNode* sibling, int parent_height);
	string name; //이름 저장 
	int height; //트리 높이  + 출력을 위해서 
	TreeNode* sibling; //부모의 자식들을 linkedlist로 연결해주기 
	TreeNode* child; //자식 대표 
};

class Tree
{
public:
	Tree(); //생성자   
	~Tree(); //소멸자 
	void clear(); // 소멸 
	void destroy_child(TreeNode* node); //모든 child 삭제 
	void destroy_sibling(TreeNode* node); //모든 sibling 삭제 
	void insert(string employer, string employee); //삽입 
	void insert_sibling(TreeNode* employee, TreeNode*first); //삽입보조 , sibling에 추가 
	
	void remove(string employee); // fire 
	void removeNode(string employee); //삭제 보조 (삭제할 노드가 child가 없는 경우 ) 
	bool removeNodeSub(string employee, TreeNode* parent); //삭제 보조 2
	
	void move_child(TreeNode* parent); //삭제 보조 (삭제할 노드가 child가 있는 경우, 트리 구조 바꾸는 함수)
	
	bool isEmpty()const; //트리가 비었는지 확인 
	void showStrucuture(TreeNode* root)const; //print 

	TreeNode* getNode(string name, TreeNode* node)const; //name에 해당하는 node반환 
	TreeNode* getNode_sub(string name, TreeNode* parent)const;
private:
	TreeNode* root;

};