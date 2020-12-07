//pz1_func
#include <cmath>
#include <exception>
#include <new>
#include "pz1.h"


template <class Type>
Array<Type>::Array(int n) : size(n){
	array = new Type[size];
}
	
template <class Type>
Array<Type>::~Array(){
	delete []array;
}

template <class Type>
void Array<Type>::show()const{
	for (int i = 0; i < size; i++) std::cout << array[i] << " ";
	std::cout << std::endl;
}

template <class Type>
void Array<Type>::setter(int index, Type value)const{
	if (index > size) throw std::range_error("range_error");
	if (value >= -100 && value <=100) array[index] = value;
		else throw std::out_of_range("out_of_range");
}

template <class Type>
int Array<Type>::getter(int position){
	if (position >= 0 && position <= size) return array[position];
		else throw std::range_error("range_error");
}

template <class Type>
Array<Type> &Array<Type>::operator=(const Array<Type> &arr2){
	if (this == &arr2) return *this;
	for (int i = 0; i < size; i++){
		array[i] = arr2.array[i];
	}
	return *this;
}

template <class Type>
Array<Type> &Array<Type>::operator+(const Array<Type> &arr2){
	if (this == &arr2) return *this;
	for (int i = 0; i < size; i++){
		array[i] += arr2.array[i];
	}
	return *this;
}

template <class Type>
Array<Type> &Array<Type>::operator-(const Array<Type> &arr2){
	if (this == &arr2) return *this;
	for (int i = 0; i < size; i++){
		array[i] -= arr2.array[i];
	}
	return *this;
}

template <class Type>
std::ostream &operator<<(std::ostream &os,const Array<Type> &arr){
	for (int i = 0; i < arr.size; i++) os << arr.array[i] << " ";
	return os;
}

template <class Type>
Array<Type>::Array(Array<Type> &arr){
	size = arr.size;
	array = new int[size];
	for (int i = 0; i < size; i++){
		array[i] = arr.array[i];
	}
}

template <class Type>
void Array<Type>::add(const Array &arr){
	for (int i = 0; i < size; i++){
		array[i] += arr.array[i];
	}
}

template <class Type>
void Array<Type>::minus(const Array &arr){
	for (int i = 0; i < size; i++){
		array[i] -= arr.array[i];
	}
}

template <class Type>
void Array<Type>::push_back(Type value){//переписать bad alloc
	if (value < -100 || value > 100) throw std::out_of_range("out_of_range");
	size++;
	Type *new_array = new Type[size];
	if (new_array == nullptr) throw std::bad_alloc();
	for (int i = 0; i < size-1; i++) new_array[i] = array[i];
	new_array[size-1] = value;
	delete []array;// очистить старый массив
	array = new_array;//перекинуть указатель старого на новый
}

template <class Type>
double Array<Type>::lenght(const Array &arr){
	if (size != arr.size) {std::cout << "error_lenght"; return -1;}
	long long summ = 0;//ll
	for (int i = 0; i < size; i++) 
		summ += pow (arr.array[i]- array[i],2);
	return sqrt(summ);
}


