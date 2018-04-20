#include<iostream>
#include<fstream>
#include<stdexcept>
#include<string.h>
#include<stdbool.h>
#include"matrix.h"
using namespace std;

/*rcMatrix::Cref::Cref(rcMatrix &c, int w, int k)
{
	s = c;
	x = w;
	y = k;
}*/

rcMatrix::Cref::operator double() const
{
	cout <<"operator double() const" << endl;
	return s.index(x,y);
}

rcMatrix::Cref 	&rcMatrix::Cref::operator = (double c)
{
	cout <<"Operator =" << endl;
	s.write(x,y,c);
	return *this;
}

/*double rcMatrix::operator[](int w, int k) const
{
	cout<<"double rcMatrix" << endl;
	return this->index(w,k);
}*/


