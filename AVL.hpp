//感谢《数据结构（C++语言版）》提供的代码

#include"BST.hpp"

template <typename T> class AVL :public BST<T> {
public:
	BinNodePosi(T) insert(const T& e);
	bool remove(const T& e);
};

#define Balanced(x) (stature((x)->lc) == stature((x)->rc))
#define BalFac(x) (stature((x)->lc) - stature((x)->rc))
#define AVLBalanced(x) ( (-2 < BalFac(x)) && (BalFac(x) > -2))

#define tallerChild(x) (stature((x)->lc) > stature((x)->rc) ? (x)->lc : (stature((x)->lc) < stature((x)->rc) ? (x)->rc : (IsLChild(*(x)) ? (x)->lc : (x)->rc)))

template <typename T> BinNodePosi(T) AVL<T>::insert(const T& e)
{
	BinNodePosi(T)& x = this->search(e);
	if (x) return x;
	BinNodePosi(T) xx = x = new BinNode<T>(e, this->_hot);
	this->_size++;
	for (BinNodePosi(T) g = this->_hot; g; g = g->parent)
	{
		if (!AVLBalanced(g)) {
			FromParentTo(*g) = this->rotateAt(tallerChild(tallerChild(g)));
			break;
		}
		else
			this->updateHeight(g);
	}
	return xx;
}

template <typename T> bool AVL<T>::remove(const T& e) {
	BinNodePosi(T)& x = this->search(e);
	if (!x) return false;
	removeAt(x, this->_hot);
	this->_size--;
	for (BinNodePosi(T) g = this->_hot; g; g = g->parent)
	{
		if (!AVLBalanced(g)) {
			g = FromParentTo(*g) = this->rotateAt(tallerChild(tallerChild(g)));
			this->updateHeight(g);
		}
	}
	return true;
}