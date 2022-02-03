#include <iostream>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	// parte dell'esercizio per la somma
	int a,b,c;
	cout<<"Enter two numbers:";
	cin>>a>>b;
	//cin.clear(); usabile in alcuni contesti, in questo basta cin.sync()
	cin.sync();
	c=a+b;
	cout<<"Sum is "<<c<<endl;
	// parte dell'esercizio per le stringhe
	string str;
	cout<<"Posso sapere il tuo nome?"<<endl;
	getline(cin,str);
	cout<<"Hello "<<str<<endl;
	return 0;
}
