#ifndef MATRIX_H
#define MATRIX_H
#include<iostream>
#include<fstream>
#include<stdexcept>
#include<string.h>
using namespace std;


class rcMatrix
{

	public:
	class Matrix;
	Matrix *matrix;
	class Cref;
	class Range{};

	rcMatrix(string name);
	rcMatrix(double k, double w);
	rcMatrix();
	rcMatrix(const rcMatrix &_s);
	~rcMatrix();

	rcMatrix & operator = (const rcMatrix &_s);
	rcMatrix & operator += (const rcMatrix &_s);
	rcMatrix & operator -= (const rcMatrix &_s);
	rcMatrix & operator *= (const rcMatrix &_s);
	
	rcMatrix & wprowadzDane();
	
	double index(int n, int m) const;
	int ref();

	void write(int w, int y, const double c);

	friend	rcMatrix  operator + (const rcMatrix &_s, const rcMatrix &_c);
	friend	rcMatrix  operator - (const rcMatrix &_s, const rcMatrix &_c);
	friend	rcMatrix  operator * (const rcMatrix &_s, const rcMatrix &_c);
	
	
	friend ostream & operator<< (ostream &c, const rcMatrix _s);
	bool friend operator ==(const rcMatrix &_s, const rcMatrix &_c);
	
	//double operator[](int w, int k) const;
	Cref operator()(int w, int k);
	



};

class rcMatrix::Matrix
{
	public:

	double *pData;
	int nRef;
	int size, w,k;
	
	
	Matrix(string name);
	Matrix(double k, double w);
	Matrix();
	~Matrix();	
	Matrix* detach();
};

class rcMatrix::Cref
{
	friend class rcMatrix;
	
	rcMatrix &s;
	int x,y;

	Cref(rcMatrix &c, int w, int k):s(c), x(w), y(k) {}
	public:
	
	//Cref(rcMatrix& c, int w, int k);

	operator double() const;
	
	rcMatrix::Cref& operator = (double c);	
};
#endif
