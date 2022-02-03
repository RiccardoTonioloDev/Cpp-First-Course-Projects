#include <iostream>
using namespace std;
class Rational{
private:
	int p;
	int q;
public:
	Rational(){
		p=0;
		q=1;
	};
	Rational(int pp, int qq){
		p=pp;
		q=qq;
	};
	void setP(int pp){
		p=pp;
	};
	void setQ(int qq){
		q=qq;
	};
	int getP(){
		return p;
	};
	int getQ(){
		return q;
	};
	friend Rational operator+(Rational r1, Rational r2);
	friend ostream & operator<<(ostream &out, Rational r1);
};

Rational operator+(Rational r1, Rational r2){
	Rational temp;
	temp.setP(r1.getP()*r2.getQ()+r2.getP()*r1.getQ());
	temp.setQ(r1.getQ()*r2.getQ());
	return temp;
};

ostream & operator<<(ostream &out, Rational r1){
	out<<r1.getP()<<"/"<<r1.getQ()<<endl;
}

int main(int argc, char** argv) {
	Rational r1(12,7);
	Rational r2(3,8);
	Rational r3 = r1+r2;
	cout<<r3;
	return 0;
}
