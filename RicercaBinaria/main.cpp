#include <iostream>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
int A[10] = {0,1,2,3,4,5,6,7,9};
	int searched = 8;
	// Diamo noi quanto valgono visto che abbiamo creato noi l'array
	int high=9;
	int low=0;
	
	do{
		if(A[(low+high)/2]==searched){
			cout<<"Position: "<<(low+high)/2;
			return 0;
		}else if(A[(low+high)/2]>searched){
			high = (low+high)/2;
		}else{
			low = (low+high)/2;
		}
		cout<<"high: "<<high<<endl;
		cout<<"low: "<<low<<endl;
		cout<<"----------------------"<<endl;
	}while(high!=low+1);
	cout<<"Nothing found";
	return 0;
}
