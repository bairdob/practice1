//pz1 pz2 
#include <iostream>
#include <cstring>
#include "pz1_func.cpp"
using namespace std;

int main(){
	Array<double> arr1(2);
	arr1.setter(0, 3.4);
	arr1.setter(1, 1);
	Array<double> arr2(2);
	arr2.setter(0,1);

	cout << arr1 << endl;
	cout << arr2 << endl;
	cout << arr2.lenght(arr1);
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