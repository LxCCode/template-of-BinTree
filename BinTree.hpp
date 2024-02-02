//感谢《数据结构（C++语言版）》提供的代码

#include"BinNode.hpp"
#include<algorithm>
#include<memory>

template <typename T> class BinTree {
protected:
	int _size;
	BinNodePosi(T) _root;
	virtual int updateHeight(BinNodePosi(T) x);
	void updateHeightAbove(BinNodePosi(T) x);
public:
	BinTree() : _size(0), _root(NULL) {}
	~BinTree() { if (0 < _size) remove(_root); }
	int size() const { return _size; }
	bool empty() const { return !_root; }
	BinNodePosi(T) root() const { return _root; }
	BinNodePosi(T) insertAsRoot(T const& e);
	BinNodePosi(T) insert(T const& e, BinNodePosi(T) x);
	BinNodePosi(T) insert(BinNodePosi(T) x, T const& e);
	BinNodePosi(T) attach(BinTree<T>* &S, BinNodePosi(T) x);
	BinNodePosi(T) attach(BinNodePosi(T) x, BinTree<T>* &S);
	void travLevel() { if (_root) _root->travLevel(); }
	void travPre() { if (_root) _root->travPre(); }
	void travIn() { if (_root) _root->travIn(); }
	void travPost() { if (_root) _root->travPost(); }
	int remove(BinNodePosi(T) x);
};

template <typename T> int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
	return x->height = 1 + max(stature(x->lc), stature(x->rc));
}

template <typename T> void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
	while (x) { updateHeight(x); x = x->parent; }
}

template <typename T> BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e) {
	_size = 1;
	return _root = new BinNode<T>(e);
}

template <typename T> BinNodePosi(T) BinTree<T>::insert(T const& e, BinNodePosi(T) x) {
	_size++;
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lc;
}

template <typename T> BinNodePosi(T) BinTree<T>::insert(BinNodePosi(T) x, T const& e) {
	_size++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rc;
}

template <typename T> BinNodePosi(T) BinTree<T>::attach(BinTree<T>* &S, BinNodePosi(T) x) {
	if (x->lc = S->_root) x->lc->parent = x;
	_size += S->_size;
	updateHeightAbove(x);
	S->_root = NULL;
	S->_size = 0;
	release(S);
	S = NULL;
	return x;
}

template <typename T> BinNodePosi(T) BinTree<T>::attach(BinNodePosi(T) x, BinTree<T>* &S) {
	if (x->rc = S->_root) x->rc->parent = x;
	_size += S->_size;
	updateHeightAbove(x);
	S->_root = NULL;
	S->_size = 0;
	delete S;
	S = NULL;
	return x;
}

template <typename T> 
static int removeAt(BinNodePosi(T) x) {
	if (!x) return 0;
	int n = 1 + removeAt(x->lc) + removeAt(x->rc);
	delete x;
	return n;
}

template <typename T>
int BinTree<T>::remove(BinNodePosi(T) x) {
	FromParentTo(*x) = NULL;
	updateHeightAbove(x->parent);
	int n = removeAt(x);
	_size -= n;
	return n;
}

