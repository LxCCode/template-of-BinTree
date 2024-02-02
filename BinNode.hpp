//感谢《数据结构（C++语言版）》提供的代码

#include"..\..\..\Stack\Stack\template-of-Stack\Stack.hpp"
#include"..\..\..\Queue\Queue\template-of-Queue\Queue.hpp"
#include<iostream>
using namespace std;

#define BinNodePosi(T) BinNode<T>*
#define stature(p) ((p) ? (p)->height : -1)
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (& (x) == (x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (& (x) == (x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))
#define sibling(p) (IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc)
#define uncle(p) (IsLChild(*((x)->parent)) ? (x)->parent->parent->rc : (x)->parent->parent->lc)
#define FromParentTo(x) (IsRoot(x) ? this->_root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))
typedef enum { RED, BLACK } RBColor;

template <typename T> struct BinNode {
	T data;
	BinNodePosi(T) parent;
	BinNodePosi(T) lc;
	BinNodePosi(T) rc;
	int height;
	int npl;
	RBColor color;

	BinNode() :
		parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RED) {}
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
		int h = 0, int l = 1, RBColor c = RED) :
		data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}
	BinNodePosi(T) insertAsLC(T const& e);
	BinNodePosi(T) insertAsRC(T const& e);
	BinNodePosi(T) succ();
	void travLevel();
	void travPre();
	void travIn();
	void travPost();

	bool operator < (BinNode const& bn) { return data < bn.data; }
	bool operator > (BinNode const& bn) { return data > bn.data; }
	bool operator == (BinNode const& bn) { return data == bn.data; }
};

template <typename T> BinNodePosi(T) BinNode<T>::insertAsLC(T const& e)
{
	return this->lc = new BinNode(e, this);
}

template <typename T> BinNodePosi(T) BinNode<T>::insertAsRC(T const& e)
{
	return this->rc = new BinNode(e, this);
}

template<typename T>
static void visitAlongVine(BinNodePosi(T) x, Stack<BinNodePosi(T)>& S) {
	while (x) {
		cout << x->data << ' ' << x->color << endl;
		S.push(x->rc);
		x = x->lc;
	}
}

template<typename T>
void BinNode<T>::travPre() {
	Stack<BinNodePosi(T)> S;
	BinNodePosi(T) x = this;
	while (true)
	{
		visitAlongVine(x, S);
		if (S.empty()) break;
		x = S.pop();
	}
}

template<typename T>
static void goAlongVine(BinNodePosi(T) x, Stack<BinNodePosi(T)>& S) {
	while (x) {
		S.push(x);
		x = x->lc;
	}
}

template<typename T>
void BinNode<T>::travIn() {
	Stack<BinNodePosi(T)> S;
	BinNodePosi(T) x = this;
	while (true)
	{
		goAlongVine(x, S);
		if (S.empty()) break;
		x = S.pop();
		cout << x->data << endl;
		x = x->rc;
	}
}

template <typename T> BinNodePosi(T) BinNode<T>::succ()
{
	BinNodePosi(T) s = this;
	if (rc) {
		s = rc;
		while (HasLChild(*s))
			s = s->lc;
	}
	else {
		while (IsRChild(*s))
			s = s->parent;
	}
	return s;
}

template<typename T>
static void gotoLeft(Stack<BinNodePosi(T)>& S) {
	while (BinNodePosi(T) x = S.top()) {
		if (HasLChild(*x)) {
			if (HasRChild(*x))
				S.push(x->rc);
			S.push(x->lc);
		}
		else
			S.push(x->rc);
	}
	S.pop();
}

template<typename T>
void BinNode<T>::travPost() {
	Stack<BinNodePosi(T)> S;
	BinNodePosi(T) x = this;
	if (x) S.push(x);
	while (!S.empty())
	{
		if (S.top() != x->parent)
			gotoLeft(S);
		x = S.pop();
		cout << x->data << endl;
	}
}

template<typename T>
void BinNode<T>::travLevel() {
	Queue<BinNodePosi(T)> Q;
	Q.enqueue(this);
	while (!Q.empty())
	{
		BinNodePosi(T) x = Q.dequeue();
		cout << x->data << endl;
		if (HasLChild(*x))
			Q.enqueue(x->lc);
		if (HasRChild(*x))
			Q.enqueue(x->rc);
	}
}





