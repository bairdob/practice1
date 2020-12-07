//pooh.cpp Реализация аэродинамического принципа полета
/*
theory
https://oat.mai.ru/index.htm
http://smekhnovsergey.ru/LIB/PILOT/Динамика%20полёта%20вертолёта%20Онушкин%20Кочиш%20часть%202.pdf
https://ru.wikipedia.org/wiki/ПИД-регулятор
https://www.youtube.com/watch?v=FbrZS_4LZdM
http://we.easyelectronics.ru/Theory/prostoy-metod-nastroyki-pid-regulyatora.html  метод Зиглера–Никольса для коэффициентов
https://ru.m.wikipedia.org/wiki/Файл:PID_Compensation_Animated.gif
*/
#include <iostream>
using namespace std;
const float G = 9.81;
enum aero_quality {subsonic = 15, postsonic = 8, helicopter = 4};


class Engine{
private:
	float power;
	int time; //duration of the power
public:
	Engine(float p = 0,int t = 0) : power(p),time(t){};
	float getPower(){
		return power;
	};
	void setPower(float p){
		power = p;
	};
	int getTime(){
		return time;
	};
};

class Pooh : public Engine{
private:
	float height;
	float mass;
public:
	Pooh(float m = 0, float h = 0) : mass(m), height(h){};
	void eat(float m) {
		mass += m;
	};
	void move(int t, Engine &e){
		int flytime = 0;
		if (flight(e)) {
				cout << "Полетели!" << endl;
				while (flytime < 500 && setH(flytime,e) >= 0){
					cout << "\t" << setH(flytime,e);
					flytime+=t;
				}
				cout << endl;
			}
			else cout << "Не хватает подъемной силы" << endl;
	}
	float getM(){
		return mass;
	}
	float getH(){
		return height;
	}
	float setH(float t,Engine &e){
		return velocity(e) * t - (G * t * t / 2);
	}
	void show()const{
		cout << "m = "<< mass << " h = " << height << endl;
	}
	float requared_force(){
		return mass * G / helicopter;
	}
	bool flight(Engine &e){
		if (e.getPower() > requared_force()) return true;
			else return false;
	}
	float velocity(Engine &e){
		if (flight(e)) return e.getPower() * e.getTime() / mass;
			else return 0;
	}
};

float kp = 0, ki = 0, kd = 0, ku = 0.8, tu = 1;
class Fsystem{ //flight system 
private: //power
	float input;
	float last_input;
	//float error;
	//float dinput;
	float output;
public:
	Fsystem(float i = 0, float s = 0) : input(i), last_input(s), output(s){
		setKoef();
	};
	void setFsystem(){
		//dinput = last_input - input;
		output = kp * input;
		last_input = input;
		input = output;
		if (zero()) output = 0; 
	}
	bool zero(){ //can eat an apple
		if (output < 1) return true;
			else return false;
	}
	void setKoef(){
		kp = 0.6 * ku;
		ki = 2 * kp / tu;
		kd = kp * tu / 8;
	}
	void show()const{
		cout << input << " " << last_input << " " << output << endl;
	}
};

class Apple{
private:
	float mass;
	float height;
public:
	Apple(float h = 1.5, float m = 0.1) : height(h), mass(m){};	
	void show()const{
		cout << mass << "-" << height << "\t";
	}
	float getH(){
		return height;
	}
	float getM(){
		return mass;
	}
};

void init_tree(Apple arr[], int size){
	for (int i = 0; i < size; i++) arr[i] = Apple(1.5 + static_cast<float>(i) / 10);
}

void show_tree(const Apple arr[], int size){
	for (int i = 0; i < size; i++) arr[i].show();
	cout << endl;
}

int main(){
	const int SIZE = 3;
	Apple tree[SIZE];
	init_tree(tree, SIZE);
	show_tree(tree, SIZE);
	cout << endl;

	Pooh p1(50, 5); 
	Engine e1(150, 30);
	Fsystem f1(e1.getPower());
	//cout << p1.flight(e1);
	p1.move(1,e1);
	cout << "Velocity: " << p1.velocity(e1) << endl;
	f1.show();
	f1.setFsystem(); f1.show();

	return 0;
}