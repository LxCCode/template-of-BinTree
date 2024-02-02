//感谢《数据结构（C++语言版）》提供的代码

#include"BST.hpp"

template <typename T> class RB :public BST<T> {
protected:
	void solveDoubleRed(BinNodePosi(T) x);
	void solveDoubleBlack(BinNodePosi(T) x);
	int updateHeight(BinNodePosi(T) x);
public:
	BinNodePosi(T) insert(const T& e);
	bool remove(const T& e);
};

#define IsBlack(p) (!(p) || (BLACK == (p)->color))
#define IsRed(p) (!(IsBlack(p)))
#define BlackHeightUpdated(x) ( (stature((x).lc) == stature((x).rc)) && ((x).height == (IsRed(&x) ? stature((x).lc) : stature((x).lc) + 1)))

template <typename T> int RB<T>::updateHeight(BinNodePosi(T) x) {
	x->height = max(stature(x->lc), stature(x->rc));
	return IsBlack(x) ? x->height++ : x->height;
}

template <typename T> BinNodePosi(T) RB<T>::insert(const T& e) {
	BinNodePosi(T)& x = this->search(e);
	if (x) return x;
	x = new BinNode<T>(e, this->_hot, NULL, NULL, -1);
	this->_size++;
	solveDoubleRed(x);
	return x ? x : this->_hot->parent;
}

template <typename T> void RB<T>::solveDoubleRed(BinNodePosi(T) x)
{
	if (IsRoot(*x)) {
		this->_root->color = BLACK;
		this->_root->height++;
		return;
	}
	BinNodePosi(T) p = x->parent;
	if (IsBlack(p))
		return;
	BinNodePosi(T) g = p->parent;
	BinNodePosi(T) u = uncle(x);
	if (IsBlack(u)) {
		if (IsLChild(*x) == IsLChild(*p))
			p->color = BLACK;
		else
			x->color = BLACK;
		g->color = RED;
		BinNodePosi(T) gg = g->parent;
		BinNodePosi(T) r = FromParentTo(*g) = this->rotateAt(x);
		r->parent = gg;
	}
	else {
		p->color = BLACK;
		p->height++;
		u->color = BLACK;
		u->height++;
		if (!IsRoot(*g)) g->color = RED;
		solveDoubleRed(g);
	}
}

template <typename T> bool RB<T>::remove(const T& e) {
	BinNodePosi(T)& x = this->search(e);
	if (!x)
		return false;
	BinNodePosi(T) r = removeAt(x, this->_hot);
	if (!(--this->_size)) return true;
	if (!this->_hot)
	{
		this->_root->color = BLACK;
		updateHeight(this->_root);
		return true;
	}
	if (BlackHeightUpdated(*this->_hot))
		return true;
	if (IsRed(r))
	{
		r->color = BLACK;
		r->height++;
		return true;
	}
	solveDoubleBlack(r);
	return true;
}

template <typename T> void RB<T>::solveDoubleBlack(BinNodePosi(T) r) {
	BinNodePosi(T) p = r ? r->parent : this->_hot;
	if (!p) return;
	BinNodePosi(T) s = (r == p->lc) ? p->rc : p->lc;
	if (IsBlack(s)) {
		BinNodePosi(T) t = NULL;
		if (IsRed(s->rc))
		{
			t = s->rc;
		}
		if (IsRed(s->lc))
		{
			t = s->lc;
		}
		if (t) {
			RBColor oldColor = p->color;
			BinNodePosi(T) b = FromParentTo(*p) = this->rotateAt(t);
			if (HasLChild(*b)) {
				b->lc->color = BLACK;
				updateHeight(b->lc);
			}
			if (HasRChild(*b)) {
				b->rc->color = BLACK;
				updateHeight(b->rc);
			}
			b->color = oldColor;
			updateHeight(b);
		}
		else {
			s->color = RED;
			s->height--;
			if (IsRed(p)) {
				p->color = BLACK;
			}
			else {
				p->height--;
				solveDoubleBlack(p);
			}
		}
	}
	else {
		s->color = BLACK;
		p->color = RED;
		BinNodePosi(T) t = IsLChild(*s) ? s->lc : s->rc;
		this->_hot = p;
		FromParentTo(*p) = this->rotateAt(t);
		solveDoubleBlack(r);
	}
}