#include <iostream>
#include "array.h"

template < class L, class H, class OP >
struct DBinaryExpression {
  L m_l;
  H m_h;
  DBinaryExpression (L l, H h) : m_l (l), m_h (h) {}
  Array<T>& operator () () { return OP::apply (l_ (), h_()); }
};

template <typename T>
class Add {
		T apply(T t1, T t2) { 
			return t1 + t2;
		} 
};

template < class E >
struct DExpression {
  E expr_;
  DExpression (E e) : expr_ (e) {}
  double operator() () { return expr_();  }
};

template < class Itr, class Func >
void evaluate (Itr begin, Itr end, Func func) 
{
  for (Itr i = begin; i != end; ++i)
    std::cout << func () << std::endl;
}

template< class A, class B >
DExpression<DBinaryExpression<DExpression<A>, DExpression<B>, Add> > operator + (DExpression<A> a, DExpression<B> b)
{
  typedef DBinaryExpression <DExpression<A>, DExpression<B>, Add> ExprT;
  return DExpression<ExprT>(ExprT(a,b));
}

int main (void)
{
	typedef DExpression <Array<int>> MyArray;

	int* a = new int(5);
	for (int i = 0; i < 5; i++)
		a[i] = i;
	MyArray ar1 (Array(a,5));
	MyArray ar2 (Array(a,5));
	MyArray ar3 (Array(a,5));



	evaluate (ar1 + ar2 + ar3); 

	return 0;
}