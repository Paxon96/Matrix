#include<iostream>
#include<fstream>
#include<string.h>
#include<stdexcept>
#include"matrix.cpp"
#include"mref.cpp"
using namespace std;

int main()
{
	rcMatrix c("macierz.txt"), b("macierz2.txt"), d(2,3);

try{
	//c.wprowadzDane();
	//b.wprowadzDane();
	cout << "flaga" << endl;
	cout << c << endl;
	cout << "flaga2" << endl;
	cout << b << endl;


	 b -= d;
	cout << "flaga3" << endl;
	cout << "C: " << b << endl;
	c.ref();
	d.ref();
	c(1,2) = 1000;
	c(2,3) = 9999;
	cout << c << endl;

}
catch(exception &ex)
	{
		cout << ex.what() << endl << "Koncze program!" << endl;
	}


	return 0;
}
