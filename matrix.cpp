#include<iostream>
#include<fstream>
#include<stdexcept>
#include<string.h>
#include<stdbool.h>
#include"matrix.h"
using namespace std;

rcMatrix::Matrix::Matrix(double _w, double _k)
{	
	nRef = 1;
	k = _k;
	w = _w;
	size = k * w;
	pData = new double[size];
	for(int i=0;i<size;i++)
		*(pData+i) = 0;
}

rcMatrix::Matrix::Matrix(string name)
{
	fstream plik;
	plik.open(name.c_str());
	nRef = 1;
	if(plik.good())
	{	
		cout << "Dostep do pliku uzyskany!" << endl;

		
		plik >> w;
		plik >> k;
		size = k*w;
		pData = new double[size];
		int i = 0, x = size;
		
		while(x)
		{
			plik >> *(pData + i);
			i++;
			x--;
		}
			
		plik.close();
	}
	else
		throw runtime_error("Nie mozna otworzyc pliku");
	
	
}

rcMatrix::Matrix::Matrix()
{
	this->nRef = 1;
	this->k = 1;
	this->w = 1;
	this->size = 1;
	this->pData = new double[size];
	*(this->pData) = 0;
}


rcMatrix::Matrix::~Matrix()
{
	k = 0;
	w = 0;
	size = 0;
	delete [] pData;
}

ostream & operator<< (ostream &c, const rcMatrix _s)
{
	c << "[";
	for(int i = 0; i<_s.matrix->size; i++)
		{
			if(i > 1 && i %_s.matrix->k == 0) c << endl;
			c <<  *(_s.matrix->pData + i) << "\t";
		}
	c << "]";
	
	return c;
}

rcMatrix & rcMatrix::operator += (const rcMatrix &_s)
{
	if(this->matrix->k == _s.matrix->k && this->matrix->w == _s.matrix->w)
	{
		Matrix *newData = new Matrix(matrix->w,matrix->k);
		for(int i =0; i<_s.matrix->size; i++)
			*(newData->pData + i) = *(this->matrix->pData + i) + *(_s.matrix->pData + i);
	
		if(--matrix->nRef == 0)
			delete matrix;
		matrix = newData;

	}
	else 
		throw out_of_range("Zly wymiar");
	
		
	return *this; 
}

rcMatrix & rcMatrix::operator -= (const rcMatrix &_s)
{
	if(this->matrix->k == _s.matrix->k && this->matrix->w == _s.matrix->w)
	{
		Matrix *newData = new Matrix(matrix->w,matrix->k);
		for(int i =0; i<_s.matrix->size; i++)
			*(newData->pData + i) = *(this->matrix->pData + i) - *(_s.matrix->pData + i);

		if(--matrix->nRef == 0)
			delete matrix;
		matrix = newData;
	}
	else 
		throw out_of_range("Zly wymiar");
		
	return *this;
}

rcMatrix & rcMatrix::operator *= (const rcMatrix &_s)
{
	if(this->matrix->k != _s.matrix->w)
	{	throw out_of_range("Zly wymiar");

	}
	
			Matrix* newData = new Matrix(this->matrix->w,_s.matrix->k);

			int l = 0;
			double temp = 0;

			for(int i = 1; i<=this->matrix->w;i++)
				{
					for(int j = 1; j<=_s.matrix->k;j++)
						{	
							temp = 0;
							for(int k = 1; k<=this->matrix->k;k++)
								temp+=(this->index(i,k)) * (_s.index(k,j));
							*(newData->pData + l) = temp;
							l++;
						}
				
				}
			
		if(--matrix->nRef == 0)
			delete matrix;
		matrix = newData;
		
	return *this;
 } 
 
rcMatrix  operator + (const rcMatrix &_s, const rcMatrix &_c)
{
	if(_c.matrix->k == _s.matrix->k && _c.matrix->w == _s.matrix->w)
	{
		rcMatrix temp(_c.matrix->w,_s.matrix->k);
		for(int i =0; i<_s.matrix->size; i++)
			*(temp.matrix->pData + i) = *(_s.matrix->pData + i) + *(_c.matrix->pData + i);	
		return temp;
	}
	else 
		throw out_of_range("Zly wymiar");

}

rcMatrix  operator - (const rcMatrix &_s, const rcMatrix &_c)
{

	if(_c.matrix->k != _s.matrix->k && _c.matrix->w != _s.matrix->w)
	{
		throw out_of_range("Zly wymiar");
	}
	else 
	{	
		rcMatrix temp(_c.matrix->w,_s.matrix->k);
		for(int i =0; i<_s.matrix->size; i++)
			*(temp.matrix->pData + i) = *(_s.matrix->pData + i) - *(_c.matrix->pData + i);	
		return temp;
		
	}

}

rcMatrix  operator * (const rcMatrix &_s, const rcMatrix &_c)
{
	if(_s.matrix->w != _c.matrix->k)
	{
		throw out_of_range("Zly wymiar");
	}
		
	rcMatrix C(_s.matrix->w,_c.matrix->k);
	int l = 0;
	double temp = 0;
	for(int i = 1; i<=_s.matrix->w;i++)
			{
				for(int j = 1; j<=_c.matrix->k;j++)
						{	
						temp = 0;

						for(int k = 1; k<=_s.matrix->k;k++)
							temp+=(_s.index(i,k)) * (_c.index(k,j));
						*(C.matrix->pData + l) = temp;
						l++;
					}
			
			}
	return C;
}

rcMatrix & rcMatrix::wprowadzDane()
{
	for(int i = 0; i < this->matrix->size; i++)
		{
			cout <<"Podaj liczbe ktora chcesz wprowadzic na " << i + 1 << " miejsce macierzy." << endl;
			cin >> *(this->matrix->pData + i);
		}
	
	return *this;
}

bool operator == (const rcMatrix &_s, const rcMatrix &_c)
{
	if(_s.matrix->size == _c.matrix->size)
	{
		for(int i = 0; i<_s.matrix->size; i++)
			if(*(_s.matrix->pData + i) != *(_c.matrix->pData + i))
				return false;		
		
		return true;
	}
	else return false;
}
rcMatrix::~rcMatrix()
{
	if(--matrix->nRef == 0)
   		 delete matrix;
}
rcMatrix::rcMatrix(string name)
{
	matrix = new Matrix(name);
}

rcMatrix::rcMatrix(double w, double k)
{	
	matrix = new Matrix(w,k);
}

rcMatrix::rcMatrix()
{
	matrix = new Matrix();
}

rcMatrix::rcMatrix(const rcMatrix &_s)
{	

	_s.matrix->nRef++;
	matrix = _s.matrix;
}

rcMatrix & rcMatrix::operator = (const rcMatrix &_s)
{

	  _s.matrix->nRef++;

 	 if(--matrix->nRef == 0)
   		 delete matrix;
 	
	matrix = _s.matrix;
	
  	return *this;
}

rcMatrix::Matrix *rcMatrix::Matrix::detach()
{
	if(nRef == 1)
		return this;
	Matrix* newData = new Matrix(k,w);
	nRef--;
	return newData;
}

double rcMatrix::index(int n, int m) const
{

	return this->matrix->pData[(n-1)*this->matrix->k+m-1];
}

int rcMatrix::ref()
{
	cout << "REF: " << matrix->nRef << endl;
}

void rcMatrix::write(int w, int k, const double c)
{
	matrix = matrix -> detach();
	matrix -> pData[(w-1)*matrix->k+k-1] = c;
}

rcMatrix::Cref rcMatrix::operator()(int w, int k)
{
	return Cref(*this,w,k);
}	
