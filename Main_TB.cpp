#include <iostream>
#include "TopSynthFunction.h"



using namespace std;

int main(){

	dataType buffer[1000] = {1};

	TopFun(buffer);



return 0;
}







/*

template <class T>
class Base
{
public:
	void set(const T& val){data = val;}
private:
	T data;
};

template <class T>
class Derived : public Base<T>
{
public:
	void set(const T& val);
};


Base<int> baza;
	baza.set(5);

*/


/*
int arra[50];
int arrb[50];

for (int i = 0; i < 50; i++)
	{
		arra[i]=1;
		arrb[i]=2;
		cout << arra[i];
	}
cout << endl;

int c[50];

TopFun(arra, arrb, c);

for (int i = 0; i < 50; i++)
{
	cout << c[i] << endl;
}

*/
