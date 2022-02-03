#include <iostream>
#include <fstream>

// Questa libreria mi permette di utilizzare il simbolo NULL, come effettivo simbolo
// esistente in C++
#include <cstddef>

using namespace std;
class Item{
	private:
		string name;
		int price;
		int quantity;
	public:
		Item(){
			name ="none";
			price = 0;
			quantity = 0;
		}
		Item(string name,int price,int quantity) throw (int){
			Item::name = name;
			if(price<0){
				throw 1;
			}else{
				Item::price = price;
			}
			Item::quantity = quantity;
		}
		string getName(){
			return name;
		}
		int getPrice(){
			return price;
		}
		int getQuantity(){
			return quantity;
		}
		void setName(string name){
			Item::name=name;
		}
		void setPrice(int price){
			Item::price=price;
		}
		void setQuantity(int quantity){
			Item::quantity=quantity;
		}
		//Metto in overloading sia gli operatori di inserimento per dialogo con file
		//sia per dialogo con console.
		//In più faccio overloading anche per l'estrazione di oggetti da un file.
		friend ofstream & operator<<(ofstream &ofs,Item &itm);
		friend ifstream & operator>>(ifstream &ifs,Item &itm);
		friend ostream & operator<<(ostream &ost, Item &itm);
	
};

//Effettivo overloading degli operandi
ofstream & operator<<(ofstream &ofs,Item &itm){
	ofs<<itm.getName()<<endl;
	ofs<<itm.getPrice()<<endl;
	ofs<<itm.getQuantity()<<endl;
	return ofs;
}
ifstream & operator>>(ifstream &ifs,Item &itm){
	string name;
	int price;
	int quantity;
	ifs>>name;
		itm.setName(name);
		ifs>>price;
		itm.setPrice(price);
		ifs>>quantity;
		itm.setQuantity(quantity);
	return ifs;
}
ostream & operator<<(ostream &ost,Item &itm){
	if(itm.getName()[0]==NULL){
		return ost;
	}
	ost<<"Name: "<<itm.getName()<<endl;
	ost<<"Price: "<<itm.getPrice()<<endl;
	ost<<"Quantity "<<itm.getQuantity()<<endl;
	return ost;
}

int main(int argc, char** argv) {
	try{
		char risposta;
		cout<<"Vuole inserire altri oggetti?(s/altro) [altri caratteri al di fuori di 's', verranno interpretati come no]"<<endl;
		cin>>risposta;
		ifstream infile;
		int numOggetti;
		infile.open("myStorageDB.txt");
		//Verifico l'esistenza del file e se l'utente vuole scrivere ulteriormente.
		//In caso non voglia più scrivere, allora il programma metterà in display i
		//vari oggetti salvati.
		if(infile && risposta!='s'){
			while(!infile.eof()){
				Item displayItem;
				infile>>displayItem;
				cout<<displayItem;
			}
			infile.close();	
		}else{
			cout<<"Quanti oggetti desidera inserire?"<<endl;
			cin>>numOggetti;
			ofstream outfile("myStorageDB.txt",ios::app);
	
			for(int c=0;c<numOggetti;c++){
				string name;
				int price;
				int quantity;
				cout<<"Nome oggetto: ";
				cin>>name;
				cout<<endl;
				cout<<"Prezzo oggetto: ";
				cin>>price;
				cout<<endl;
				cout<<"Quantità oggetto: ";
				cin>>quantity;
				cout<<endl;
				Item numberC(name,price,quantity);
				outfile<<numberC;
			}
			outfile.close();
		}
	}catch(int e){
		//Gestione di una eventuale eccezione.
		if(e==1){
			cout<<"Non puoi inserire un prezzo negativo";
		}
	}
	
	return 0;
}
