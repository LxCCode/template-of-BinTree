#include"RB.hpp"

int main()
{
	RB<int> T;
	T.insert(1);
	T.insert(2);
	T.insert(3);
	T.insert(4);
	T.insert(5);
	T.travPre();
	T.remove(4);
	T.travPre();
}