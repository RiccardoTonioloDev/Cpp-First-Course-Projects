#include <iostream>
#include <cstring>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
int main(int argc, char** argv) {
	char s1[20]="x=20;y=30;z=40";
	char *token = strtok(s1,"=;");
	while(token!=NULL){
		cout<<token<<endl;
		token=strtok(NULL,"=;");
	}
	
	return 0;
}
