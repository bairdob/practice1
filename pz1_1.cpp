//pz1 pz2 
#include <iostream>
#include <exception>
#include <new>
#include <cmath>
using namespace std;

template <class Type>
class Array{
private:
	int size;
	Type *array;
public:
	Array(int n = 0) : size(n){
		array = new Type[size];
		//for (int i = 0; i < size; i++) array[i] = i;
	};

	~Array(){
		delete []array;
	};

	void show()const{
		for (int i = 0; i < size; i++) std::cout << array[i] << " ";
		std::cout << std::endl;
	}

	void setter(int index, Type value = 0)const{
		if (index > size) throw std::range_error("range_error");
		if (value >= -100 && value <=100) array[index] = value;
			else throw std::out_of_range("out_of_range");

	}

	int getter(int position){
		if (position >= 0 && position <= size) return array[position];
			else throw std::range_error("range_error");

	}

	Array &operator=(const Array &arr2){
		if (this == &arr2) return *this;
		for (int i = 0; i < size; i++){
			array[i] = arr2.array[i];
		}
		return *this;
	}

	Array &operator+(const Array &arr2){
		if (this == &arr2) return *this;
		for (int i = 0; i < size; i++){
			array[i] += arr2.array[i];
		}
		return *this;
	}

	Array &operator-(const Array &arr2){
		if (this == &arr2) return *this;
		for (int i = 0; i < size; i++){
			array[i] -= arr2.array[i];
		}
		return *this;
	}
	friend std::ostream &operator<<(std::ostream &os,const Array &arr){
		for (int i = 0; i < arr.size; i++) os << arr.array[i] << " ";
		return os;

	}
	Array(Array &arr){
			size = arr.size;
			array = new int[size];
			for (int i = 0; i < size; i++){
			array[i] = arr.array[i];
		}
	}

	void add(const Array &arr){
		for (int i = 0; i < size; i++){
			array[i] += arr.array[i];
		}
	}

	void minus(const Array &arr){
		for (int i = 0; i < size; i++){
			array[i] -= arr.array[i];
		}
	}

	void push_back(Type value){//переписать bad alloc
		if (value < -100 || value > 100) throw std::out_of_range("out_of_range");
		size++;
		Type *new_array = new Type[size];
		if (new_array == nullptr) throw std::bad_alloc();
		for (int i = 0; i < size-1; i++) new_array[i] = array[i];
		new_array[size-1] = value;
		delete []array;
		array = new_array;
		

	}
	double lenght(const Array &arr){
		if (size != arr.size) {cout << "error_lenght"; return -1;}
		long long summ = 0;
		for (int i = 0; i < size; i++) 
			summ += pow (arr.array[i]- array[i],2);
		return sqrt(summ);
	}
	
};

int main(){
	Array<double> arr1(2);
	arr1.setter(0, 3.4);
	arr1.setter(1, 1);
	Array<double> arr2(2);
	arr2.setter(0,1);
	cout << arr1 << endl;
	cout << arr2 << endl;
	cout << arr2.lenght(arr1)<< endl;
	arr1.push_back(5); 
	// try{
 //    	arr1.setter(1, -100000);

 //   	} 
 //   	catch (std::range_error i) {
 //   		cerr<< i.what()<<endl;
 //    }
 //    catch (std::out_of_range i) {
 //   		cerr<< i.what()<<endl;
 //    }
	return 0;
}