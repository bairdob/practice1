//pz1.h
#include <iostream>

template<class Type>
class Array;
template<class Type>
std::ostream& operator <<(std::ostream& os, const Array<Type>& arr); //?????


template <class Type>
class Array{
private:
	int size;
	Type *array;
public:
	Array(int n = 0);
	Array(Array &arr);
	void show()const;
	void setter(int index, Type value = 0)const;
	int getter(int position);
	Array &operator=(const Array &arr2);
	Array &operator+(const Array &arr2);
	Array &operator-(const Array &arr2);
	friend std::ostream &operator<<<Type>(std::ostream &os,const Array &arr);//<Type> откуда
	void add(const Array &arr);
	void minus(const Array &arr);
	void push_back(Type value);
	double lenght(const Array &arr);
	~Array();
};

