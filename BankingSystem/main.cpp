#include <iostream>
#include <fstream>
#include <map>

#define MIN_BALANCE 500

using namespace std;

class Account{
private:
	static long accountCurrentIndex;
	string firstName;
	string lastName;
	float balance;
	long realAccountNumber;
public:	
	//COSTRUTTORI DI ACCOUNT
	Account(string firstName1,string lastName1,float balance1){
		firstName = firstName1;
		lastName = lastName1;
		balance = balance1;
		realAccountNumber = accountCurrentIndex;
		accountCurrentIndex++;
	}
	Account(){
		firstName = "Trial";
		lastName = "Account";
		balance = 500;
	}
	
	//FUNZIONI PROPRIETARIE DI ACCOUNT
	string getFirstName(){
		return firstName;
	}
	string getLastName(){
		return lastName;
	}
	float getBalance(){
		return balance;
	}
	long getrealAccountNumber(){
		return realAccountNumber;
	}
	
	float withdrawBalance(float amount){
		balance -= amount;
		return balance;
	}
	
	float depositBalance(float amount){
		balance += amount;
		return balance; 
	}
	long getCurrentIndex(){
		return accountCurrentIndex;
	}
	//!!! Da usare solo con il reperimento di account da file
	void setAccountNumber(long actNum){
		realAccountNumber = actNum;
		accountCurrentIndex = ++actNum;
	}
	//FUNZIONI AMICHE DI ACCOUNT
	friend ifstream & operator>>(ifstream &ifs, Account &act);
	friend ofstream & operator<<(ofstream &ofs, Account &act);
	friend ostream & operator<<(ostream &ost,Account &act);
};
long Account::accountCurrentIndex = 0;

//CREAZIONE CORPI FUNZIONI AMICHE

//Lettura da file
ifstream & operator>>(ifstream &ifs, Account &act){
	string firstName,lastName;
	float balance;
	long realAccountNumber;
	ifs>>firstName;
	ifs>>lastName;
	ifs>>realAccountNumber;
	ifs>>balance;
	Account trial(firstName,lastName,balance);
	//Questa funzione può essere usata solo qui
	trial.setAccountNumber(realAccountNumber); 
	act = trial;
	
	return ifs;
}
//Scrittura in file
ofstream & operator<<(ofstream &ofs, Account &act){
	//Per fare ciò però, la prima riga del file deve essere presa come vuota e quindi
	//letta in maniera preventiva.
	ofs<<endl<<act.getFirstName()<<endl
	<<act.getLastName()<<endl
	<<act.getrealAccountNumber()<<endl
	<<act.getBalance();
	return ofs;
}
//Scrittura in console
ostream & operator<<(ostream &ost, Account &act){
	ost<<"First Name: "<<act.getFirstName()<<endl
	<<"Last Name: "<<act.getLastName()<<endl
	<<"Account n.: "<<act.getrealAccountNumber()<<endl
	<<"Balance: "<<act.getBalance()<<endl<<endl;
	return ost;
}
class Bank{
private:
	map<long,Account> dataBase;
public:
	void openAccount(Account act){
		dataBase.insert(pair<long,Account>(act.getrealAccountNumber(),act));
	}
	void closeAccount(long number){
		dataBase.erase(number);
	}
	map<long,Account> & getDataBase(){
		return dataBase;
	}
	friend ofstream & operator<<(ofstream &ofs,Bank &bnk);
	friend ifstream & operator>>(ifstream &ifs,Bank &bnk);
	friend ostream & operator<<(ostream &ost,Bank &bnk);
};

//Scrittura del db intero
ofstream & operator<<(ofstream &ofs,Bank &bnk){
	map<long,Account>::iterator itr;
	for(itr=bnk.getDataBase().begin();itr!=bnk.getDataBase().end();itr++){
		ofs<<itr->second;
	}
}
//Lettura del db intero e caricato in memoria
ifstream & operator>>(ifstream &ifs,Bank &bnk){
	Account trial;
	Bank trialBnk;
	while(!ifs.eof()){
		ifs>>trial;
		trialBnk.openAccount(trial);
	}
	bnk = trialBnk;
}
//Scrittura in console, di tutti gli account
ostream & operator<<(ostream &ost,Bank &bnk){
	map<long,Account>::iterator itr;
	//ost<<endl<<bnk.getDataBase().begin()<<endl<<bnk.getDataBase().end()<<endl;
	for(itr=bnk.getDataBase().begin();itr!=bnk.getDataBase().end();itr++){
		ost<<itr->second<<endl;
	}
}

int main(int argc, char** argv) {
	cout<<"****** BANKING SYSTEM ******"<<endl<<endl;
	char response;
	int verifyFile = 1;
	Bank bnk;
	do{
		ifstream infile("bankDB.txt");
		if(infile.is_open()){
			verifyFile = 0;
		}
		infile.close();
		cout<<"Select an option:"<<endl;
		cout<<"1. Open an Account"<<endl
		<<"2. Balance Enquiry"<<endl
		<<"3. Deposit"<<endl
		<<"4. Withdrawal"<<endl
		<<"5. Close an Account"<<endl
		<<"6. Show All Accounts"<<endl
		<<"7. Quit"<<endl
		<<"Enter your choice: "<<endl<<endl;
		cin>>response;
		cin.ignore();
		cin.sync();
		cout<<endl;
		switch(response){
			case '1':{
				//FUNZIONA PERFETTAMENTE, CON ANCHE CONTROLLO DEL BILANCIO MINIMO
				string firstName;
				string lastName;
				float balance;
				cout<<"Scrivere il primo nome: ";
				getline(cin,firstName); 
				cout<<"Scrivere il cognome: ";
				getline(cin,lastName);
				cout<<"Scrivere il saldo: ";
				cin>>balance;
				cin.ignore();
				cin.sync();
				if(balance<MIN_BALANCE){
					cout<<endl<<"************************************************";
					cout<<endl<<"Per creare un account ci vuole un minimo di 500$"<<endl;
					cout<<"L'ACCOUNT NON E' STATO CREATO";
					cout<<endl<<"************************************************"<<endl<<endl;
					break;
				}
				cout<<endl;
				if(!verifyFile){
					ifstream ifs("bankDB.txt");
					ifs>>bnk;
					ifs.close();
				}
				Account act (firstName,lastName,balance);
				bnk.openAccount(act);
				ofstream ofs("bankDB.txt");
				ofs<<bnk;
				ofs.close();
				cout<<endl<<"############################################";
				cout<<endl<<"Congratulazioni, account creato con successo";
				cout<<endl<<act;
				cout<<endl<<"############################################"<<endl<<endl;
			}break;
			case '2':{
				//FUNZIONA PERFETTAMENTE MA NON HA IL CONTROLLO DEGLI ACCOUNT NON ESISTENTI
				long accountNumber;
				if(verifyFile){
					cout<<endl<<"Nessun account è stato ancora registrato"<<endl
					<<"Operazione non riuscita: si prega di creare almeno un account"<<endl<<endl;
					break;
				}
				cout<<endl<<"Di che account si desidera sapere il bilancio? (Indicare n.): ";
				cin>>accountNumber;
				cin.ignore();
				cin.sync();
				ifstream ifs("bankDB.txt");
				ifs>>bnk;
				ifs.close();
				map<long,Account>::iterator itr;
				itr = bnk.getDataBase().find(accountNumber);
				cout<<itr->second;
				
				
			}break;	
			case '3':{
				//FUNZIONA PERFETTAMENTE, NON SONO PRESENTI CONTROLLI SUGLI INPUT
				if(verifyFile){
					cout<<endl<<"Nessun account è stato ancora registrato"<<endl
					<<"Operazione non riuscita: si prega di creare almeno un account"<<endl<<endl;
					break;
				}
				long accountNumber;
				float amount;
				ifstream ifs("bankDB.txt");
				ifs>>bnk;
				ifs.close();
				cout<<endl<<"In quale account vuoi depositare?: ";
				cin>>accountNumber;
				cin.ignore();
				cin.sync();
				cout<<endl;
				cout<<endl<<"Quanto vuoi depositare?: ";
				cin>>amount;
				cin.ignore();
				cin.sync();
				cout<<endl;
				bnk.getDataBase().find(accountNumber)->second.depositBalance(amount);
				ofstream ofs("bankDB.txt");
				ofs<<bnk;
				ofs.close();
				cout<<endl<<endl<<"############################################"<<endl;
				cout<<"Deposito avvenuto con successo: "<<endl;
				cout<<bnk.getDataBase().find(accountNumber)->second<<endl;
				cout<<"############################################"<<endl<<endl;
				
			}break;	
			case '4':{
				//FUNZIONA PERFETTAMENTE, NON SONO PRESENTI CONTROLLI SUGLI INPUT
				if(verifyFile){
					cout<<endl<<"Nessun account è stato ancora registrato"<<endl
					<<"Operazione non riuscita: si prega di creare almeno un account"<<endl<<endl;
					break;
				}
				long accountNumber;
				float amount;
				ifstream ifs("bankDB.txt");
				ifs>>bnk;
				ifs.close();
				cout<<endl<<"In quale account vuoi prelevare?: ";
				cin>>accountNumber;
				cin.ignore();
				cin.sync();
				cout<<endl;
				cout<<endl<<"Quanto vuoi prelevare?: ";
				cin>>amount;
				cin.ignore();
				cin.sync();
				cout<<endl;
				bnk.getDataBase().find(accountNumber)->second.withdrawBalance(amount);
				ofstream ofs("bankDB.txt");
				ofs<<bnk;
				ofs.close();
				cout<<endl<<endl<<"############################################"<<endl;
				cout<<"Prelievo avvenuto con successo: "<<endl;
				cout<<bnk.getDataBase().find(accountNumber)->second<<endl;
				cout<<"############################################"<<endl<<endl;
			}break;	
			case '5':{
				//FUNZIONA PERFETTAMENTE, NON SERVE TECNICAMENTE ALCUN CONTROLLO PER GLI INPUT
				if(verifyFile){
					cout<<endl<<"Nessun account è stato ancora registrato"<<endl
					<<"Operazione non riuscita: si prega di creare almeno un account"<<endl<<endl;
					break;
				}
				long accountNumber;
				ifstream ifs("bankDB.txt");
				ifs>>bnk;
				ifs.close();
				cout<<endl<<"Quale account si desidera cancellare?: ";
				cin>>accountNumber;
				cin.ignore();
				cin.sync();
				cout<<endl;
				bnk.getDataBase().erase(accountNumber);
				ofstream ofs("bankDB.txt");
				ofs<<bnk;
				ofs.close();
				cout<<endl<<endl<<"############################################"<<endl;
				cout<<"ELIMINAZIONE ACCOUNT N."<<accountNumber<<" AVVENUTA CON SUCCESSO"<<endl;
				cout<<"############################################"<<endl<<endl;
			}break;	
			case '6':{
				//FUNZIONA PERFETTAMENTE ED è COMPLETO
				if(verifyFile){
					cout<<endl<<"Nessun account è stato ancora registrato"<<endl
					<<"Operazione non riuscita: si prega di creare almeno un account"<<endl<<endl;
					break;
				}
				ifstream ifs("bankDB.txt");
				ifs>>bnk;
				ifs.close();
				cout<<bnk;
				
			}break;	
			case '7':{
				//FUNZIONA PERFETTAMENTE ED è COMPLETO
				//NULLA DA FARE IN QUESTA OPERAZIONE
				
			}break;
			default:{
				//FUNZIONA PERFETTAMENTE ED è COMPLETO
				cout<<endl<<"--------------------------------------------"
				<<endl<<"Ha inserito un valore non valido."<<endl
				<<"Per piacere, inserisca uno dei valori validi sopra riportati."<<endl
				<<"--------------------------------------------"<<endl;
				
			}break;
		}
	}while(response!='7');
	cout<<endl<<"Arrivederci!"<<endl;
	return 0;
}
