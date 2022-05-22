#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>

using std::cin;
using std::getline;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::cerr;
using std::setw;
using std::left;
using std::right;

const int MIN_YEARS = 1800;
const int MAX_YEARS = 9999;
const int month_day[]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct Employee{
	string name, address, noHp, date, poss, gender;
	int id, age, salary;
};

struct Customers{
	string name;
	string pass;
	int id;
};

struct Database{
	string name;
};

struct Clothes{
	string name;
	int price;
	int availability;
	int id;
};

struct Transaksi{
	int long_borrowed;
	int day_check_in;
	int mounth_check_in;
	int year_check_in;
	int day_out;
	int mounth_out;
	int	year_out;
	int day_check_out;
	int mounth_check_out;
	int year_check_out;
	int price;
	int totalPrice;
	int id;
	string clothes_type;
	string name;
};

int mainMenu();
int employeeMenu();
void employee();
void employeeLogin();
int homeEmployeeMenu();
void homeEmployee(int position);
void readDataTransactions(Transaksi *transaksi, int nT);
void showPersonalData(int position);
void sortDataTransactionHome(Transaksi *transaksi, int nT);
void sortTransaction(Transaksi *transaksi, int start, int nT, string output);
int searchDataTransactionMenu();
void searchDataTransactionHome(Transaksi *transaksi, int nT);
void searchDataTransaction(Transaksi *transaksi, int nT, string output);
int customerMenu();
void customers();
void customerRegister(Customers *customer, int n);
void customerLogin(Customers *customer, int n);
int homeCustomerMenu();
void homeCustomer(Customers *customer, int &id);
void readClothes(Clothes **clothes, int n);
int sortClothesMenu();
void sortClothesHome(Clothes **clothes, int n);
void sortClothes(Clothes **clothes, int n, string output);
void outputClothes(Clothes **clothes, int n, string output);
int searchClothesMenu();
void searchClothesHome(Clothes **clothes, int n);
void searchClothes(Clothes **clothes, int n, string output);
bool searchPrice(Clothes **clothes, int n, int &idGender, int &idclothes_type, int price);
bool searchAvailability(Clothes **clothes, int n, int &idGender, int &idclothes_type, int availability);
bool searchId(Clothes **clothes, int n, int &idGender, int &idclothes_type, int id);
bool searchName(Clothes **clothes, int n, int &idGender, int &idclothes_type, string name);
int borrowClothesMenu();
void borrowClothesHome(Customers *customer, Clothes **clothes, int id, int n);
void checkInClothes(Customers *customer, Clothes **clothes, int id, int n, int nT);
void pay(int end, int start);
void checkOutClothes(Customers *customer, Clothes **clothes, int id, int n, int nT);
void count_punishment(Transaksi *transaksi, Clothes **clothes, int n, int nT, int ids);
void syarat_check(int day, int month, int year, bool &syarat_tanggal);
bool is_LeapYear(int year);
void date(int &day, int &month, int &year, int &borrow);
int add_day(int day, int &month, int d_max);
int add_month(int month, int &year, int m_max);
string replaceSpasi(string str);
string replaceUnderScore(string str);
void swap (Clothes &x , Clothes &y);
void swap1 (Transaksi &x , Transaksi &y);

int main(){
	ofstream ofs;
	ofs.open("customers.txt", ios::out | ios::app);
	ofs.close();
	ofs.open("data_transaksi.txt", ios::out | ios::app);
	ofs.close();



	int choice = mainMenu();
	
	while(choice != 3){ 
		switch(choice){
			case 1:
				employee();
				break;
			case 2:
				customers();
				break;	
			default:
				cout << "Please enter the correct input" << endl;
		}
		choice = mainMenu();
	}
	
	cout << "=================" << endl;
	cout << "| THANK YOU !!! |" << endl;
	cout << "=================" << endl;
	
	return 0;
}

int mainMenu(){
	int no;
	
	cout << "+------------------------------------------+" << endl;
	cout << "|   WELCOME TO LOAN CLOTHING PROGRAMMING   |" << endl;
	cout << "+------------------------------------------+" << endl;
	cout << "1. Sign In As Employee" << endl;
	cout << "2. Sign In As Customer" << endl;
	cout << "3. Exit Program" << endl;
	cout << "Enter the menu you want to select\t: "; cin >> no; cin.ignore();
	
	system("pause");
	system("cls");
	return no;
}

int employeeMenu(){
	int no;
	
	cout << "+---------------+" << endl;
	cout << "| Employee Menu |" << endl;
	cout << "+---------------+" << endl;
	cout << "1. Login" << endl;
	cout << "2. Back" << endl;
	cout << "Enter the menu you want to select\t: " ; cin >> no; cin.ignore();
	
	system("pause");
	system("cls");
	return no;
}

void employee(){
	int choice = employeeMenu();
	
	while(choice != 2){
		switch(choice){
			case 1:
				employeeLogin();
				break;
			default:
				cout << "Please enter the correct input" << endl;
		}
		choice = employeeMenu();
	}
}

void employeeLogin(){
	string name, name1, pw, pw1;
	int position;
	ifstream in, inn;
	
	cout << "+-------------------+" << endl;
	cout << "|Sign In As Employee|" << endl;
	cout << "+-------------------+" << endl;
	
	cout << "Enter you'r name\t: ";
	getline(cin,name);
	cout << "Enter you 'r password\t: ";
	getline(cin,pw);
	
	in.open("employee.txt", ios::in);
	if(in.is_open()){
		do{
			in >> position;	
			in.ignore();
			getline(in, name1);
			getline(in, pw1);
		}while(name != name1 && pw != pw1 && !in.eof());
	in.close();
	} else{
		cerr << "Eror Opening File" << endl;
	}

	if(name != name1){
		cout << "You'r not registered as an employee at this hospital, please check your username and password again" << endl;
		system("pause");
		system("cls");
	}else if(name == name1 && pw != pw1){
		cout << "You'r password is wrong" << endl;
		system("pause");
		system("cls");
	}else{
		cout << "You have successfully logged in" << endl;
		system("pause");
		system("cls");
		homeEmployee(position);
	}
	
}

int homeEmployeeMenu(){
	int no;
	
	cout << "+-------------+" << endl;
	cout << "|Home Employee|" << endl;
	cout << "+-------------+" << endl;
	cout << "1. Read Data Transaction Customer" << endl;
	cout << "2. Sort Data Transaction Customer" << endl;
	cout << "3. Search Data Transaction Customer" << endl;
	cout << "4. Show Personal Data" << endl;
	cout << "5. Back" << endl;
	cout << "Enter the menu you want to select\t: " ; cin >> no; cin.ignore();

	system("pause");
	system("cls");
	return no;
}

void homeEmployee(int position){
	int choice = homeEmployeeMenu();

	int nT = 0;
	ifstream in;
	string line;

	in.open("data_transaksi.txt", ios::in);
	if(in.is_open()){
		while(!in.eof()){
			getline(in, line);
			nT++;
		}
		in.close();
	}else{
		cerr << "Eror Opening File" << endl;
	}
	nT--;

	
		
	while(choice != 5){
		Transaksi *transaksi = new Transaksi[nT];

		in.open("data_transaksi.txt", ios::in);
		if(in.is_open()){
			for(int i=0; i<(nT); i++){
				in >> transaksi[i].clothes_type >> transaksi[i].name >> transaksi[i].totalPrice >> transaksi[i].price >> transaksi[i].long_borrowed 
				>> transaksi[i].day_check_in >> transaksi[i].mounth_check_in >> transaksi[i].year_check_in  
				>> transaksi[i].day_out >> transaksi[i].mounth_out >> transaksi[i].year_out  
				>> transaksi[i].day_check_out >> transaksi[i].mounth_check_out >> transaksi[i].year_check_out  
				>> transaksi[i].id;

				string str = transaksi[i].clothes_type;
				transaksi[i].clothes_type = replaceUnderScore(str);

				str = transaksi[i].name;
				transaksi[i].name = replaceUnderScore(str);
			}
		in.close();
		}else{
			cout << "Eror Opening File" << endl;
		}

		if(choice == 1){
			readDataTransactions(transaksi, nT);
			system("pause");
			system("cls");
		}else if(choice == 2){
			sortDataTransactionHome(transaksi, nT);
		}else if(choice == 3){
			searchDataTransactionHome(transaksi, nT);
		}else if(choice == 4){
			showPersonalData(position);
		}else{
			cout << "Please enter the correct input" << endl;
		}
		delete[] transaksi;
		choice = homeEmployeeMenu();
	}
}

int sortDataTransactionMenu(){
	int no;
	
	cout << "+-------------+" << endl;
	cout << "|Home Employee|" << endl;
	cout << "+-------------+" << endl;
	cout << "1. Sort by Name Customer" << endl;
	cout << "2. Sort by Price" << endl;
	cout << "3. Sort by Id" << endl;
	cout << "4. Back" << endl;
	cout << "Enter the menu you want to select\t: " ; cin >> no; cin.ignore();

	system("pause");
	system("cls");
	return no;
}

void sortDataTransactionHome(Transaksi *transaksi, int nT){
	int choice = sortDataTransactionMenu();

	while(choice != 4){
		switch(choice){
			case 1:
				sortTransaction(transaksi, 0,  nT, "customer");
				readDataTransactions(transaksi, nT);
				break;
			case 2:
				sortTransaction(transaksi, 0, nT, "price");
				readDataTransactions(transaksi, nT);
				break;
			case 3:
				sortTransaction(transaksi, 0, nT, "id");
				readDataTransactions(transaksi, nT);
				break;
			default:
				cout << "Please enter the correct input" << endl;
		}	
		system("pause");
		system("cls");
		choice = sortDataTransactionMenu();
	}
}

void readDataTransactions(Transaksi *transaksi, int nT){
	string line(124, '=');
	cout << "+" << line  << "+" << endl;
	cout << "|" << left << setw(30) << "Clothes Type" << right << setw(25) << "Name Customer" << setw(10) << "T.Price" << setw(10) << "Price" << setw(5) << "Long" << setw(13) << "D.Borrowed" << setw(13) << "D.M.Return" <<  setw(13) << "D.Return" << setw(5) << "ID" << "|" << endl;
	for(int i=0; i<(nT); i++){
		cout << "|" << line << "|" << endl;
		cout << "|" <<  left << setw(30) << transaksi[i].clothes_type << right << setw(25) << transaksi[i].name << setw(10) << transaksi[i].totalPrice << setw(10) << transaksi[i].price << setw(5) << transaksi[i].long_borrowed 
		<< setw(5) << transaksi[i].day_check_in << setw(3) << transaksi[i].mounth_check_in << setw(5) << transaksi[i].year_check_in  
		<< setw(5) << transaksi[i].day_out << setw(3) << transaksi[i].mounth_out << setw(5) << transaksi[i].year_out  
		<< setw(5) << transaksi[i].day_check_out << setw(3) << transaksi[i].mounth_check_out << setw(5) << transaksi[i].year_check_out  
		<< setw(5) << transaksi[i].id << "|" << endl;
	}
	cout << "+" << line  << "+" << endl;
}

void sortTransaction(Transaksi *transaksi, int start, int nT, string output){
	int i, j;
	string temp1;
	for(i=0; i<nT-1; i++) {
		for(j=0; j<nT-1-i; j++) {
			if(output == "price"){
				if(transaksi[j].totalPrice > transaksi[j+1].totalPrice) {
					swap1(transaksi[j], transaksi[j+1]);
				}
			}else if(output == "customer"){
				if(transaksi[j].name > transaksi[j+1].name){
					swap1(transaksi[j], transaksi[j+1]);
				}
			}else if(output == "id"){
				if(transaksi[j].id > transaksi[j+1].id){
					swap1(transaksi[j], transaksi[j+1]);
				}
			}
		}
	}
}

void swap1(Transaksi &x, Transaksi &y){
	Transaksi temp = x ;
    x = y ;
    y = temp ;
}

void showPersonalData(int position){
	Employee employee;
	string lines, line(162,'=');
	ifstream in;
	
	in.open("data_employee.txt", ios::in);
	if(in.is_open()){
		for(int i=0; i<position; i++){
			getline(in, lines);
			in >> employee.id;	
			in >> employee.age;	
			in >> employee.salary;	
			in.ignore();
			getline(in, employee.name);
			getline(in, employee.address);
			getline(in, employee.noHp);
			getline(in, employee.date);
			getline(in, employee.gender);
			getline(in, employee.poss);
		}
		in.close();
	} else{
		cerr << "Eror Opening File" << endl;
	}
	
	cout << line << endl;
	cout << "|" << setw(3) << "ID" << setw(2) << "|" <<  setw(22) << "Employee Name" << setw(10) << "|" << setw(4) << "Age" << setw(3) << "|" << setw(35)<< "Employee Address" << setw(20) << "|" << setw(10) << "No HP" << setw(6) << "|" << setw(13) << "Date" << setw(9) << "|" << setw(7) << "Gender" << setw(2) << "|" << setw(10) << "Salary" << setw(5) << "|" << endl;	

		cout << line << endl;
		cout << "| " << setw(2) << employee.id;
		cout << " | " << setw(29) << employee.name;
		cout << " | " << setw(4) << employee.age;
		cout << " | " << setw(52) << employee.address;		
		cout << " | " <<  setw(13) << employee.noHp;	
		cout << " | " << setw(18) << employee.date;
		cout << " | " << setw(6) << employee.gender;
		cout << " | " << setw(12) << employee.salary;
		cout << " |";
		cout << endl;

	cout << line << endl;
	system("pause");
	system("cls");
}

int searchDataTransactionMenu(){
	int no;
	
	cout << "+-------------+" << endl;
	cout << "|Home Employee|" << endl;
	cout << "+-------------+" << endl;
	cout << "1. Search by Name Customer" << endl;
	cout << "2. Search by Price" << endl;
	cout << "3. Search by Id" << endl;
	cout << "4. Back" << endl;
	cout << "Enter the menu you want to select\t: " ; cin >> no; cin.ignore();

	system("pause");
	system("cls");
	return no;
}

void searchDataTransactionHome(Transaksi *transaksi, int nT){
	int choice = searchDataTransactionMenu();

	while(choice != 4){
		switch(choice){
			case 1:
				searchDataTransaction(transaksi,  nT, "customer");
				break;
			case 2:
				searchDataTransaction(transaksi, nT, "price");
				break;
			case 3:
				searchDataTransaction(transaksi, nT, "id");
				break;
			default:
				cout << "Please enter the correct input" << endl;
		}	
		choice = sortDataTransactionMenu();
	}
}

void searchDataTransaction(Transaksi *transaksi, int n, string output){
	int i=0, ketemu=0;
	bool found = false;

	if(output == "customer"){
		string name;
		cout << "Enter the name customer you want to find\t: "; getline(cin, name);
		while(i < n){
			if(transaksi[i].name == name) found = true;
			else found = false;

			if(found == true){
				cout << "\nData was found at index array ke-[" << i << "]" << endl;
				cout << "Id Transaction\t\t: " << transaksi[i].id << endl;
				cout << "Name\t\t\t: " << transaksi[i].name << endl;
				cout << "Price Clothes\t\t: " << transaksi[i].price << endl;
				cout << "Long Borrowed\t\t: " << transaksi[i].long_borrowed << endl;
				cout << "Total Price\t\t: " << transaksi[i].totalPrice << endl;
				cout << "Day Check In\t\t: " << transaksi[i].day_check_in << " / " << transaksi[i].mounth_check_in << " / " << transaksi[i].year_check_in << endl;
				cout << "Day Must Check Out\t: " << transaksi[i].day_out << " / " << transaksi[i].mounth_out << " / " << transaksi[i].year_out << endl;
				cout << "Day Check Out\t\t: " << transaksi[i].day_check_out << " / " << transaksi[i].mounth_check_out << " / " << transaksi[i].year_check_out << endl;
				ketemu++;
			}
			i++;
		}
	}else if(output == "price"){
		int price;
		cout << "Enter the total price you want to find\t: "; cin >> price; cin.ignore();
		
		while(i < n){
			if(transaksi[i].totalPrice == price) found = true;
			else found = false;

			if(found == true){
				cout << "Data was found at index array ke-[" << i << "]" << endl;
				cout << "Id Transaction\t\t: " << transaksi[i].id << endl;
				cout << "Name\t\t\t: " << transaksi[i].name << endl;
				cout << "Price Clothes\t\t: " << transaksi[i].price << endl;
				cout << "Long Borrowed\t\t: " << transaksi[i].long_borrowed << endl;
				cout << "Total Price\t\t: " << transaksi[i].totalPrice << endl;
				cout << "Day Check In\t\t: " << transaksi[i].day_check_in << " / " << transaksi[i].mounth_check_in << " / " << transaksi[i].year_check_in << endl;
				cout << "Day Must Check Out\t: " << transaksi[i].day_out << " / " << transaksi[i].mounth_out << " / " << transaksi[i].year_out << endl;
				cout << "Day Check Out\t\t: " << transaksi[i].day_check_out << " / " << transaksi[i].mounth_check_out << " / " << transaksi[i].year_check_out << endl;
				ketemu++;
			}
			i++;
		}
	}else{
		int id;
		cout << "Enter the id you want to find\t: "; cin >> id; cin.ignore();

		while(i < n){
			if(transaksi[i].id == id) found = true;
			else found = false;

			if(found == true){
				cout << "Data was found at index array ke-[" << i << "]" << endl;
				cout << "Id Transaction\t\t: " << transaksi[i].id << endl;
				cout << "Name\t\t\t: " << transaksi[i].name << endl;
				cout << "Price Clothes\t\t: " << transaksi[i].price << endl;
				cout << "Long Borrowed\t\t: " << transaksi[i].long_borrowed << endl;
				cout << "Total Price\t\t: " << transaksi[i].totalPrice << endl;
				cout << "Day Check In\t\t: " << transaksi[i].day_check_in << " / " << transaksi[i].mounth_check_in << " / " << transaksi[i].year_check_in << endl;
				cout << "Day Must Check Out\t: " << transaksi[i].day_out << " / " << transaksi[i].mounth_out << " / " << transaksi[i].year_out << endl;
				cout << "Day Check Out\t\t: " << transaksi[i].day_check_out << " / " << transaksi[i].mounth_check_out << " / " << transaksi[i].year_check_out << endl;
				ketemu++;
			}

			i++;
		}
		
	}

	if(ketemu > 0){
		cout << "There were " << ketemu << " records found in this search" << endl;
	}else{
		cout << "No data found" << endl;
	}

	system("pause");
	system("cls");
}

int customerMenu(){
	int no;
	
	cout << "+---------------+" << endl;
	cout << "| Customer Menu |" << endl;
	cout << "+---------------+" << endl;
	cout << "1. Login" << endl;
	cout << "2. Register" << endl;
	cout << "3. Back" << endl;
	cout << "Enter the menu you want to select\t: " ; cin >> no; cin.ignore();

	system("pause");
	system("cls");	
	return no;
}

void customers(){
	ifstream in;
	string a;
	int n;
	
	int choice = customerMenu();
	
	while(choice != 3){
		n = 0;
		in.open("customers.txt", ios::in);
		if(in.is_open()){
			while(!in.eof()){
				getline(in, a);
				n++;
			}
			n = n/3;
			in.close();
		} else{
			cerr << "Eror Opening File" << endl;
		}

		Customers *customer = new Customers[n];
		in.open("customers.txt", ios::in);
		if(in.is_open()){
			for(int i=0; i<n; i++){
				in >> customer[i].id;
				in.ignore();
				getline(in, customer[i].name);
				getline(in, customer[i].pass);
			}
			in.close();
		} else{
			cerr << "Eror Opening File" << endl;
		}
		
		switch(choice){
			case 1:
				customerLogin(customer, n);
				break;
			case 2:
				customerRegister(customer, n);
				break;
			default:
				cout << "Please enter the correct input" << endl;
		}

		choice = customerMenu();
		delete[]customer;
	}
	
}

void customerRegister(Customers *customer, int n){
	bool syarat_user = true;
	string name, pw, pw1;
	ofstream out;
	
	do{
		cout << "+-----------------+" << endl;
		cout << "|Customer Register|" << endl;
		cout << "+-----------------+" << endl;
		cout << "Enter you'r name\t\t: "; getline(cin, name);
		cout << "Enter you'r password\t\t: "; getline(cin, pw);
		cout << "Enter you'r password again\t: "; getline(cin, pw1);
		
		if(pw != pw1){
			cout << "You'r password and rePassword are different, please enter the same password and rePassword" << endl; 
		}

		for(int i=0; i<n; i++){
			if (customer[i].name == name){
				syarat_user = false;
				cout << "Username have been use, change you'r username" << endl;
				break;
			}else {
				syarat_user = true;
			}
		}
		system("pause");
		system("cls");
	} while(pw != pw1 || syarat_user == false);
	n++;
	out.open("customers.txt", ios::out | ios::app);
	if(out.is_open()){
		out << n << endl;
		out << name << endl;
		out << pw << endl;
		out.close();
	} else{
		cerr << "Eror Opening File" << endl;
	}
	
	system("cls");
}

void customerLogin(Customers *customer, int n){
	string name, name1, pw, pw1;
	int id;
	ifstream in, inn;
	bool syarat_user = false, syarat_pw = false;
	
	cout << "+-------------------+" << endl;
	cout << "|Sign In As Customer|" << endl;
	cout << "+-------------------+" << endl;
	
	cout << "Enter you'r name\t: ";
	getline(cin,name);
	cout << "Enter you 'r password\t: ";
	getline(cin,pw);
	

	for(int i=0; i<n; i++){
		if(customer[i].name == name){
			id = i;
			syarat_user = true;
		} else{
			syarat_user = false;
		}
		if(customer[i].pass == pw){
			syarat_pw = true;
		} else{
			syarat_pw = false;
		}
		if(syarat_user == true){
			break;
		}
	}

	if(syarat_user == true && syarat_pw == false){
		cout << "You'r password are wrong, please enter you'r correct password" << endl;
		system("pause");
		system("cls");
	}else if(syarat_user == true && syarat_pw == true){
		cout << "You'r Username and Password are correct !" << endl;
		system("pause");
		system("cls");
		homeCustomer(customer, id);
	}else{
		cout << "You'r username are not registered or wrong" << endl;
		cout << "Choose register menu to register you'r account" << endl;			
		system("pause");
		system("cls");
	}
	
}

int homeCustomerMenu(){
	int no;
	
	cout << "+--------------+" << endl;
	cout << "|Home Customers|" << endl;
	cout << "+--------------+" << endl;
	cout << "1. Read All Clothes" << endl;
	cout << "2. Sort Clothes" << endl;
	cout << "3. Search Clothes" << endl;
	cout << "4. Borrow Clothes" << endl;
	cout << "5. Back" << endl;
	cout << "Enter the menu you want to select\t: " ; cin >> no; cin.ignore();

	system("pause");
	system("cls");
	return no;
}

void homeCustomer(Customers *customer, int &id){
	ifstream in;
	string a;
	
	int n=0;
	in.open("data_baju.txt", ios::in);
	if(in.is_open()){
		while(!in.eof()){
			getline(in, a);
			n++;
		}
		n = n/4;
		in.close();
	} else{
		cerr << "Eror Opening File" << endl;
	}
	n = n/2;

	Clothes **clothes = new Clothes*[2];
	for(int i=0; i<2; i++){
		*(clothes + i) = new Clothes[n];
	}
	
	in.open("data_baju.txt", ios::in);
	if(in.is_open()){
		// in.seekg(ios::beg);
		for(int i=0; i<2; i++){
			for(int j=0; j<n; j++){
				getline(in, (*(clothes + i) + j)->name);
				in >> (*(clothes + i) + j)->price;	
				in >> (*(clothes + i) + j)->availability;	
				in >> (*(clothes + i) + j)->id;	
				in.ignore();
			}
		}
		in.close();
	} else{
		cerr << "Eror Opening File" << endl;
	}

	int choice = homeCustomerMenu();

	while(choice != 5){

		if(choice == 1){
			readClothes(clothes, n);
		}else if(choice == 2){
			sortClothesHome(clothes, n);
		}else if(choice == 3){
			searchClothesHome(clothes, n);
		}else if(choice == 4){
			borrowClothesHome(customer, clothes, id, n);
		}else{
			cout << "Please enter the correct input" << endl;
		}	

		choice = homeCustomerMenu();
	}

	for(int i=0; i<2; i++){
		delete[](*(clothes+i)); // free(arr[i]);
	}

	delete[] clothes;
 	// free(arr);
	clothes = NULL;
}

void readClothes(Clothes **clothes, int n){
	string line(65, '=');
	string line1(65, '-');
	cout << "THIS IS A LIST OF CLOTHES IN OUR SHOP" << endl;
	cout << line << endl;
	cout << "| " << setw(2) << "No" << setw(3) << "| " << setw(21) << "Clothes Type" << setw(11) << "| " << setw(7) << "Price" << setw(5) << "| " << setw(12) << "Availability" << setw(2) <<"|"  << endl;
	for(int i=0; i<2; i++){
		for(int j=0; j<n; j++){
		cout << line1 << endl;
		cout << "| " << setw(2) << left << (*(clothes+i)+j)->id << setw(3) << right << "| " << setw(28) << left << (*(clothes+i)+j)->name << setw(4) << right << "| " << setw(8) << left << (*(clothes+i)+j)->price << setw(4) << right << "| " << setw(12) << left << clothes[i][j].availability << setw(2) << right << "|" << endl;
		}
	}
	cout << line << endl;
	system("pause");
	system("cls");
}

int sortClothesMenu(){
	int no;
	
	cout << "+-------------+" << endl;
	cout << "|Home Employee|" << endl;
	cout << "+-------------+" << endl;
	cout << "1. Sort by Name" << endl;
	cout << "2. Sort by Price" << endl;
	cout << "3. Sort by Availability" << endl;
	cout << "4. Sort by Id" << endl;
	cout << "5. Back" << endl;
	cout << "Enter the menu you want to select\t: " ; cin >> no; cin.ignore();

	system("pause");
	system("cls");
	return no;
}

void sortClothesHome(Clothes **clothes, int n){
	ifstream in;
	int choice = sortClothesMenu();

	while(choice != 5){
		if(choice == 1){
			sortClothes(clothes, n, "name");
			readClothes(clothes, n);
			// outputClothes(clothes, n, "name");
		}else if(choice == 2){
			sortClothes(clothes, n, "price");
			readClothes(clothes, n);
			// outputClothes(clothes, n, "price");
		}else if(choice == 3){
			sortClothes(clothes, n, "availability");
			readClothes(clothes, n);
			// outputClothes(clothes, n, "availability");
		}else if(choice == 4){
			sortClothes(clothes, n, "id");
			readClothes(clothes, n);
			// outputClothes(clothes, n, "id");
		}else{
			cout << "Please enter the correct input" << endl;
		}

		in.open("data_baju.txt", ios::in);
		if(in.is_open()){
			for(int i=0; i<2; i++){
				for(int j=0; j<n; j++){
					getline(in, (*(clothes + i) + j)->name);	
					in >> (*(clothes + i) + j)->price;	
					in >> (*(clothes + i) + j)->availability;	
					in >> (*(clothes + i) + j)->id;	
					in.ignore();
				}
			}
		in.close();
		} else{
			cerr << "Eror Opening File" << endl;
		}
		
		choice = sortClothesMenu();
	}
}

void sortClothes(Clothes **clothes, int n, string output){
	int x = 0;

	for (int k = 0; k < 2; k++)
    {
        for (int m = 0; m < n; m++)
        {
            x = m+1;
            for (int i = k; i < 2 ; i++)
            {
                for (int j = x; j < n; j++)
                {
					if(output == "name"){
						if(clothes[k][m].name > clothes[i][j].name) swap(clothes[k][m] ,clothes[i][j]);
					}else if(output == "price"){
	                    if (clothes[k][m].price > clothes[i][j].price) swap(clothes[k][m] ,clothes[i][j]);
					}else if(output == "availability"){
	                    if (clothes[k][m].availability > clothes[i][j].availability) swap(clothes[k][m] ,clothes[i][j]);
					}else if(output == "id"){
	                    if (clothes[k][m].id > clothes[i][j].id) swap(clothes[k][m] ,clothes[i][j]);
					}
                }
                x=0;
            } 
        }
    }
}

void swap (Clothes &x , Clothes &y)
{
    Clothes temp = x ;
    x = y ;
    y = temp ;
}

void outputClothes(Clothes **clothes, int n, string output){
	if(output == "name"){
		for(int i=0; i<2; i++){
			for(int j=0; j<n; j++){
				cout << clothes[i][j].name << endl;
			}
		}
	}else if(output == "price"){
		for(int i=0; i<2; i++){
			for(int j=0; j<n; j++){
				cout << clothes[i][j].price << endl;
			}
		}
	}else if(output == "availability"){
		for(int i=0; i<2; i++){
			for(int j=0; j<n; j++){
				cout << clothes[i][j].availability << endl;
			}
		}
	}else{
		for(int i=0; i<2; i++){
			for(int j=0; j<n; j++){
				cout << clothes[i][j].availability << endl;
			}
		}
	}
}

int searchClothesMenu(){
	int no;
	
	cout << "+--------------+" << endl;
	cout << "|Home Customers|" << endl;
	cout << "+--------------+" << endl;
	cout << "1. Search by Name" << endl;
	cout << "2. Search by Price" << endl;
	cout << "3. Search by Availability" << endl;
	cout << "4. Search by Id" << endl;
	cout << "5. Back" << endl;
	cout << "Enter the menu you want to select\t: " ; cin >> no; cin.ignore();

	system("pause");
	system("cls");
	return no;
}

void searchClothesHome(Clothes **clothes, int n){
	ifstream in;
	string again;
	
	int choice = searchClothesMenu();
	while(choice != 5){
		if(choice == 1){
			searchClothes(clothes, n, "name");
			// readClothes(clothes, n);
			// outputClothes(clothes, n, "name");
		}else if(choice == 2){
			searchClothes(clothes, n, "price");
			// readClothes(clothes, n);
			// outputClothes(clothes, n, "price");
		}else if(choice == 3){
			searchClothes(clothes, n, "availability");
			// readClothes(clothes, n);
			// outputClothes(clothes, n, "availability");
		}else if(choice == 4){
			searchClothes(clothes, n, "id");
			// readClothes(clothes, n);
			// outputClothes(clothes, n, "id");
		}else{
			cout << "Silahkan Pilih Menu yang Seusai" << endl;
		}

		in.open("data_baju.txt", ios::in);
		if(in.is_open()){
			for(int i=0; i<2; i++){
				for(int j=0; j<n; j++){
					getline(in, (*(clothes + i) + j)->name);	
					in >> (*(clothes + i) + j)->price;	
					in >> (*(clothes + i) + j)->availability;	
					in >> (*(clothes + i) + j)->id;	
					in.ignore();
				}
			}
		in.close();
		} else{
			cerr << "Eror Opening File" << endl;
		}
		
		choice = searchClothesMenu();
	}
}

void searchClothes(Clothes **clothes, int n, string output){
	int idGender=0, idclothes_type=0;
	bool found;

	if(output == "name"){
		string name;
		cout << "Enter the clothes you want to find\t: "; getline(cin, name);
		found = searchName(clothes, n, idGender, idclothes_type, name);
	}else if(output == "price"){
		int price;
		cout << "Enter the clothes you want to find\t: "; cin >> price; cin.ignore();
		found = searchPrice(clothes, n, idGender, idclothes_type, price);
	}else if(output == "availability"){
		int availability;
		cout << "Enter the clothes you want to find\t: "; cin >> availability; cin.ignore();
		found = searchAvailability(clothes, n, idGender, idclothes_type, availability);
	}else{
		int id;
		cout << "Enter the clothes you want to find\t: "; cin >> id; cin.ignore();
		found = searchId(clothes, n, idGender, idclothes_type, id);
	}

	if(found == true){
		cout << "Data was found at index array ke-[" << idGender << "] [" << idclothes_type << "]" << endl;
		cout << "Name\t\t: " << clothes[idGender][idclothes_type].name << endl;
		cout << "Price\t\t: " << clothes[idGender][idclothes_type].price << endl;
		cout << "Availability\t: " << clothes[idGender][idclothes_type].availability << endl;
		cout << "Id\t\t: " << clothes[idGender][idclothes_type].id << endl;
	}else{
		cout << "Data not found" << endl;
	}

	system("pause");
	system("cls");
}

bool searchPrice(Clothes **clothes, int n, int &idGender, int &idclothes_type, int price){
	if(2 > idGender && n > idclothes_type){
		if(price == clothes[idGender][idclothes_type].price){
			return true;
		}else if((n-1) == idclothes_type){
			idclothes_type = 0;
			return searchPrice(clothes, n, ++idGender, idclothes_type, price);
		}else{
			return searchPrice(clothes, n, idGender, ++idclothes_type, price);
		}
	}else{
		return false;
	}
}

bool searchAvailability(Clothes **clothes, int n, int &idGender, int &idclothes_type, int availability){
	if(2 > idGender && n > idclothes_type){
		if(availability == clothes[idGender][idclothes_type].availability){
			return true;
		}else if((n-1) == idclothes_type){
			idclothes_type = 0;
			return searchAvailability(clothes, n, ++idGender, idclothes_type, availability);
		}else{
			return searchAvailability(clothes, n, idGender, ++idclothes_type, availability);
		}
	}else{
		return false;
	}
}

bool searchId(Clothes **clothes, int n, int &idGender, int &idclothes_type, int id){
	if(2 > idGender && n > idclothes_type){
		if(id == clothes[idGender][idclothes_type].id){
			return true;
		}else if((n-1) == idclothes_type){
			idclothes_type = 0;
			return searchId(clothes, n, ++idGender, idclothes_type, id);
		}else{
			return searchId(clothes, n, idGender, ++idclothes_type, id);
		}
	}else{
		return false;
	}
}

bool searchName(Clothes **clothes, int n, int &idGender, int &idclothes_type, string name){
	if(2 > idGender && n > idclothes_type){
		if(name == clothes[idGender][idclothes_type].name){
			return true;
		}else if((n-1) == idclothes_type){
			idclothes_type = 0;
			return searchName(clothes, n, ++idGender, idclothes_type, name);
		}else{
			return searchName(clothes, n, idGender, ++idclothes_type, name);
		}
	}else{
		return false;
	}
}

int borrowClothesMenu(){
	int no;

	cout << "+-----------------+" << endl;
	cout << "|Find You'r Outfit|" << endl;
	cout << "+-----------------+" << endl;
	cout << "1. Choose clothes that you want !" << endl;
	cout << "2. Return the clothes you borrowed !" << endl;
	cout << "3. Back" << endl;
	cout << "Enter the menu you want to select\t: " ; cin >> no; cin.ignore();

	system("pause");
	system("cls");

	return no;
}

void borrowClothesHome(Customers *customer, Clothes **clothes, int id, int n){
	int choice = borrowClothesMenu();
	while(choice != 3){
		ifstream in;
			string a;
			int nT = 0;
			
			in.open("data_transaksi.txt", ios::in);
			if(in.is_open()){
				while(!in.eof()){
					getline(in, a);
					nT++;
				}
				nT -= 1;
				in.close();
			}else{
				cerr << "Eror Opening File" << endl;
			}
			
		switch(choice){
			case 1:
				checkInClothes(customer, clothes, id, n, nT);
				break;
			case 2:
				checkOutClothes(customer, clothes, id, n, nT);
				break;
			default:
				cout << "Enter correct input" << endl;
		}
		choice = borrowClothesMenu();
	}
}

void checkInClothes(Customers *customer, Clothes **clothes, int id, int n, int nT){
	string again;
	int choice;
	bool syarat_tanggal = true;
	int day, month, year, borrow, start, end;

	start = nT;
	end = nT;
	
	do{
		Transaksi *transaksi = new Transaksi[1];

		readClothes(clothes, n);
		cout << "Please choose id the clothes you want to borrow\t: ";
		cin >> choice; cin.ignore();
		if ((choice == 1 && clothes[0][0].availability == 0)||(choice == 2 && clothes[0][1].availability == 0)||(choice == 3 && clothes[0][2].availability == 0)||(choice == 4 && clothes[0][3].availability == 0)||(choice == 5 && clothes[0][4].availability == 0)||(choice == 6 && clothes[0][5].availability == 0)||(choice == 7 && clothes[1][0].availability == 0)||(choice == 8 && clothes[1][1].availability == 0)||(choice == 9 && clothes[1][2].availability == 0)||(choice == 10 && clothes[1][3].availability == 0)||(choice == 11 && clothes[1][4].availability == 0)||(choice == 12 && clothes[1][5].availability == 0)){
			cout << "The clothes you selected is not available" << endl;
		}else if(choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 ||  choice == 6 ||  choice == 7 ||  choice == 8 ||  choice == 9 ||  choice == 10 ||  choice == 11 ||  choice == 12){			
			end++;
			nT++;

			do{
				cout << "Enter the date of borrowing clothes(dd/mm/yy)\t\t\t: " << endl;
				cout << "day\t: "; cin >> day;
				cout << "mounth\t: "; cin >> month;
				cout << "year\t: "; cin >> year;
				cout << "How long did you borrow this shirt\t\t\t\t: ";
				cin >> borrow;
				cin.ignore();
				syarat_check(day, month, year, syarat_tanggal);			
			} while (syarat_tanggal == false);

			transaksi[0].long_borrowed = borrow;
			transaksi[0].day_check_in = day;
			transaksi[0].mounth_check_in = month;
			transaksi[0].year_check_in = year;
			transaksi[0].totalPrice = 0;
			transaksi[0].day_check_out = 0;
			transaksi[0].mounth_check_out = 0;
			transaksi[0].year_check_out = 0;
			date(day, month, year, borrow);
			transaksi[0].day_out = day;
			transaksi[0].mounth_out = month;
			transaksi[0].year_out = year;
			cout << "The date you are required to return(dd/mm/yy)\t\t: ";
			cout << transaksi[0].day_out << "/" << transaksi[0].mounth_out << "/" << transaksi[0].year_out << endl;		
			int indexRow, indexColoumn;
			if(choice <= 6){
				indexRow = 0;
				indexColoumn = (choice - 1);
			}else{
				indexRow = 1;
				indexColoumn = (choice - 6 - 1);
			}
			clothes[indexRow][indexColoumn].availability--;
			transaksi[0].clothes_type = clothes[indexRow][indexColoumn].name;
			transaksi[0].price = clothes[indexRow][indexColoumn].price;
			transaksi[0].name = customer[id].name;
			transaksi[0].id = (nT);

			string str = transaksi[0].clothes_type;
			transaksi[0].clothes_type = replaceSpasi(str);

			str = transaksi[0].name;
			transaksi[0].name = replaceSpasi(str);

			ofstream outt;
			outt.open("data_baju.txt", ios::out);
			if(outt.is_open()){
				for(int i=0; i<2; i++){
					for(int j=0; j<n; j++){
						outt << clothes[i][j].name << endl;
						outt << clothes[i][j].price << endl;
						outt << clothes[i][j].availability << endl;
						outt << clothes[i][j].id << endl;
					}
				}
				outt.close();
			}else{
				cerr << "Eror Opening File" << endl;
			}

			ofstream out;
			out.open("data_transaksi.txt", ios::out | ios::app);
			if(out.is_open()){
				out << left << setw(30) << transaksi[0].clothes_type << right << setw(25) << transaksi[0].name << setw(10) << transaksi[0].totalPrice << setw(10) << transaksi[0].price << setw(5) << transaksi[0].long_borrowed 
				<< setw(5) << transaksi[0].day_check_in << setw(3) << transaksi[0].mounth_check_in << setw(5) << transaksi[0].year_check_in  
				<< setw(5) << transaksi[0].day_out << setw(3) << transaksi[0].mounth_out << setw(5) << transaksi[0].year_out  
				<< setw(5) << transaksi[0].day_check_out << setw(3) << transaksi[0].mounth_check_out << setw(5) << transaksi[0].year_check_out  
				<< setw(5) << transaksi[0].id << endl;
				out.close();
			}else{
				cerr << "Eror Opening File" << endl;
			}

		}else {
			cout << "The input you entered is wrong" << endl;
		}

		cout << "Do you want to borrow clothes again (y/n) ? ";
		cin >> again; 
		cin.ignore();

		system("pause");
		system("cls");

		delete[] transaksi;
	}while(again == "y" || again == "Y");

	pay(end, start);
}

void pay(int end, int start){ // INI BELUM KU GANTI KE BAHASA INGGRIS
	ifstream in;

	Transaksi *transaksi = new Transaksi[end];

	in.open("data_transaksi.txt", ios::out | ios::app);
	
	if(in.is_open()){
		for(int i=0; i<(end); i++){
			in >> transaksi[i].clothes_type >> transaksi[i].name >> transaksi[i].totalPrice >> transaksi[i].price >> transaksi[i].long_borrowed 
			>> transaksi[i].day_check_in >> transaksi[i].mounth_check_in >> transaksi[i].year_check_in  
			>> transaksi[i].day_out >> transaksi[i].mounth_out >> transaksi[i].year_out  
			>> transaksi[i].day_check_out >> transaksi[i].mounth_check_out >> transaksi[i].year_check_out  
			>> transaksi[i].id;
		}
		in.close();
	}else{
		cerr << "Eror Opening File" << endl;
	}

	int kelipatan_diskon, pembayaran; 
	float diskon;
	long int total_pembayaran, kembalian, nominal_diskon;
	int harga_sementara =0;
	system("cls");
	cout << "\t\t\t\t+---------------------------------------------------+" << endl;
	cout << "\t\t\t\t||" << setw(34) << "STRUCK PEMBAYARAN" << setw(17) << "||" << endl;
	cout << "\t\t\t\t+---------------------------------------------------+" << endl;
	cout << "\t\t\t\t1. Nama Pembeli\t: " << transaksi[start].name << endl;
	cout << "\t\t\t\t2. Tabel Pembayaran" << endl << endl;
	cout << "\t+========================================================================================================+" << endl;
	cout << "\t|" << setw(27) << "Jenis Baju" << setw(15) << "|" << setw(14) << "Lama Pinjam" << setw(4) << "|" << setw(13) << "Harga/Hari" << setw(5) << "|" << setw(15) << "Total Harga" << setw(5) << "|" << setw(4) << "ID" << setw(3) << "|" << endl;
	cout << "\t+========================================================================================================+" << endl;

	for(int i=start; i<end; i++){
		cout << "\t|" << setw(32) << transaksi[i].clothes_type << setw(10);
		cout << "|" << setw(15) << transaksi[i].long_borrowed << setw(3);
		cout << "|" << setw(15) << transaksi[i].price << setw(3);
		transaksi[i].totalPrice = (transaksi[i].price) * (transaksi[i].long_borrowed);
		cout << "|" << setw(17) << transaksi[i].totalPrice << setw(3);
		cout << "|" << setw(4) << i << setw(3) << "|";
		harga_sementara += transaksi[i].totalPrice;  cout << endl;

		cout << "\t+--------------------------------------------------------------------------------------------------------+" << endl;
	}

	ofstream out;
	out.open("data_transaksi.txt", ios::out);
	if(out.is_open()){
		for(int i=0; i<end; i++){
			out << left << setw(30) << transaksi[i].clothes_type << right << setw(25) << transaksi[i].name << setw(10) << transaksi[i].totalPrice << setw(10) << transaksi[i].price << setw(5) << transaksi[i].long_borrowed 
			<< setw(5) << transaksi[i].day_check_in << setw(3) << transaksi[i].mounth_check_in << setw(5) << transaksi[i].year_check_in  
			<< setw(5) << transaksi[i].day_out << setw(3) << transaksi[i].mounth_out << setw(5) << transaksi[i].year_out  
			<< setw(5) << transaksi[i].day_check_out << setw(3) << transaksi[i].mounth_check_out << setw(5) << transaksi[i].year_check_out  
			<< setw(5) << transaksi[i].id << endl;
		}
		out.close();
	}else{
		cerr << "Eror Opening File" << endl;
	}

	cout << "\t| Harga Sebelum Diskon = " << harga_sementara << setw(74) << "|" << endl;
	cout << "\t+========================================================================================================+" << endl;
	
	kelipatan_diskon = harga_sementara/500000;
	diskon = kelipatan_diskon*2.0/100;
	
	if (diskon >= 0.2){
		diskon = 0.2;
	}
		
	nominal_diskon = diskon*harga_sementara;
	total_pembayaran = harga_sementara-nominal_diskon;
	
	cout << "\n\t\t\t\t----------------------------------------------------\n" << endl;
	cout << "\t\t\t\tTotal Harga\t\t\t: " << total_pembayaran << " Rupiah" << endl;
	cout << "\n\t\t\t\t---------------(Diskon 2,0% per 500k)---------------\n" << endl;	
			
	cout << "\t\t\t\tPresentase Diskon\t\t: " << diskon*100 << "%" << endl; 
	cout << "\t\t\t\tNominal Diskon\t\t\t: " << nominal_diskon << " Rupiah" << endl;
	cout << "\t\t\t\tTotal Pembayaran Setelah Diskon\t: " << total_pembayaran << " Rupiah" << endl;
	cout << "\n\t\t\t\t----------------------------------------------------\n" << endl;
	do{	
		cout << "\t\t\t\tJumlah Uang yang Dibayarkan\t: ";
		cin >> pembayaran;
		cin.ignore ();
		kembalian = pembayaran - total_pembayaran;
	
		if (pembayaran >= total_pembayaran){
			cout << "\t\t\t\tJumlah kembalian\t\t: " << kembalian << " Rupiah" << endl;
			cout << "\n\t\t\t\t----------------------------------------------------\n" << endl;

			system("pause");
			system("cls");		
			} else {
				cout << "\n\t\t\t\tUang yang dibayarkan kurang !" << endl;
				system("pause");
			}
	}while (pembayaran < total_pembayaran);

}

void checkOutClothes(Customers *customer, Clothes **clothes, int id, int n, int nT){
	int ids;
	bool syarat_id = false;
	ifstream in;
	Transaksi *transaksi = new Transaksi[nT];
	
	in.open("data_transaksi.txt", ios::in);
	if(in.is_open()){
		for(int i=0; i<(nT); i++){
			in >> transaksi[i].clothes_type >> transaksi[i].name >> transaksi[i].totalPrice >> transaksi[i].price >> transaksi[i].long_borrowed 
			>> transaksi[i].day_check_in >> transaksi[i].mounth_check_in >> transaksi[i].year_check_in  
			>> transaksi[i].day_out >> transaksi[i].mounth_out >> transaksi[i].year_out  
			>> transaksi[i].day_check_out >> transaksi[i].mounth_check_out >> transaksi[i].year_check_out  
			>> transaksi[i].id;
		}
		in.close();
	}else{
		cerr << "Eror Opening File" << endl;
	}

	do{
		string str;
		cout << "+===========================================================+" << endl;
		cout << "|" << setw(40) << "CHECK OUT BAJU" << setw(20) << "|" << endl;
		cout << "+===========================================================+" << endl;
		cout << "Masukkan id rental mobil anda\t: ";
		cin >> ids;
		cin.ignore();

		if(nT < ids){
			str = " ";
		}else{
			str = transaksi[ids-1].name;
			str = replaceUnderScore(str);
		}

		for(int i=0; i<nT; i++){
			if(i == ids-1 && customer[id].name == str){
				syarat_id = true;
			} else{
				syarat_id = false;
			}
			if(syarat_id == true){
				break;
			}	
		}
		system ("pause");
		system ("cls");
	}while(syarat_id == false);

	count_punishment(transaksi, clothes, n, nT, ids);

	delete[] transaksi;
	 
}

void count_punishment(Transaksi *transaksi, Clothes **clothes, int n, int nT, int ids){
	int day, month, year, kembalian;
	long int denda, dendas;
	bool syarat_tanggal = true;
	long int day_diff=0;
	do{
		cout << "Tanggal Check Out(dd/mm/yy)\t\t\t: " << endl;
		cout << "hari\t: "; cin >> day;
		cout << "bulan\t: "; cin >> month;
		cout << "tahun\t: "; cin >> year;
		cin.ignore();
		syarat_check(day, month, year, syarat_tanggal);
	} while(syarat_tanggal == false);
	transaksi[ids-1].day_check_out = day; 
	transaksi[ids-1].mounth_check_out = month;
	transaksi[ids-1].year_check_out = year;
	
	if(transaksi[ids-1].clothes_type == "Baju_Pengantin_A_(_Male_)"){
		clothes[0][0].availability++;
	}else if(transaksi[ids-1].clothes_type == "Baju_Pengantin_B_(_Male_)"){
		clothes[0][1].availability++;
	}else if(transaksi[ids-1].clothes_type == "Baju_Pengantin_C_(_Male_)"){
		clothes[0][2].availability++;
	}else if(transaksi[ids-1].clothes_type == "Baju_Pesta_A_(_Male_)"){
		clothes[0][3].availability++;
	}else if(transaksi[ids-1].clothes_type == "Baju_Pesta_B_(_Male_)"){
		clothes[0][4].availability++;
	}else if(transaksi[ids-1].clothes_type == "Baju_Pesta_C_(_Male_)"){
		clothes[0][5].availability++;
	}else if(transaksi[ids-1].clothes_type == "Baju_Pengantin_A_(_Female_)"){
		clothes[1][0].availability++;
	}else if(transaksi[ids-1].clothes_type == "Baju_Pengantin_B_(_Female_)"){
		clothes[1][1].availability++;
	}else if(transaksi[ids-1].clothes_type == "Baju_Pengantin_C_(_Female_)"){
		clothes[1][2].availability++;
	}else if(transaksi[ids-1].clothes_type == "Baju_Pesta_A_(_Female_)"){
		clothes[1][3].availability++;
	}else if(transaksi[ids-1].clothes_type == "Baju_Pesta_B_(_Female_)"){
		clothes[1][4].availability++;
	}else if(transaksi[ids-1].clothes_type == "Baju_Pesta_C_(_Female_)"){
		clothes[1][5].availability++;
	}else{
		cout << "KAMU LEMAH" << endl;
	}

	ofstream out;
	out.open("data_transaksi.txt", ios::out);
	if(out.is_open()){
		for(int i=0; i<nT; i++){
			out << left << setw(30) << transaksi[i].clothes_type << right << setw(25) << transaksi[i].name << setw(10) << transaksi[i].totalPrice << setw(10) << transaksi[i].price << setw(5) << transaksi[i].long_borrowed 
			<< setw(5) << transaksi[i].day_check_in << setw(3) << transaksi[i].mounth_check_in << setw(5) << transaksi[i].year_check_in  
			<< setw(5) << transaksi[i].day_out << setw(3) << transaksi[i].mounth_out << setw(5) << transaksi[i].year_out  
			<< setw(5) << transaksi[i].day_check_out << setw(3) << transaksi[i].mounth_check_out << setw(5) << transaksi[i].year_check_out  
			<< setw(5) << transaksi[i].id << endl;
		}
		out.close();
	}else{
		cerr << "Eror Opening File" << endl;
	}

	ofstream outt;
	outt.open("data_baju.txt", ios::out);
	if(outt.is_open()){
		for(int i=0; i<2; i++){
			for(int j=0; j<n; j++){
				outt << clothes[i][j].name << endl;
				outt << clothes[i][j].price << endl;
				outt << clothes[i][j].availability << endl;
				outt << clothes[i][j].id << endl;
			}
		}
		outt.close();
	}else{
		cerr << "Eror Opening File" << endl;
	}

	if(year>transaksi[ids-1].year_out){
		if(transaksi[ids-1].mounth_out == 2){
			if(is_LeapYear(transaksi[ids-1].year_out) == true){
				day_diff += 29- transaksi[ids-1].day_out;
			}else {
				day_diff += 28 - transaksi[ids-1].day_out;
			}
		}else {
			day_diff = month_day[transaksi[ids-1].mounth_out-1] - transaksi[ids-1].day_out;
		}
		transaksi[ids-1].mounth_out++;

		for(int i=transaksi[ids-1].mounth_out;i<=12;i++){
			if(i==2){
				if(is_LeapYear(transaksi[ids-1].year_out) == true){
					day_diff += 29;
				}else {
					day_diff += 28;
				}
			}else {
				day_diff += month_day[i-1];
			}
        }
		transaksi[ids-1].year_out++;

		for(int i=transaksi[ids-1].year_out;i<year;i++){
			if(is_LeapYear(i) == true){
				day_diff += 366;
			}else {
				day_diff += 365;
			}
		}

		for(int i=1;i<month;i++){
			if(i==2){
				if(is_LeapYear(year) == true){
					day_diff += 29;
				}else {
					day_diff += 28;
				}
				}else {
					day_diff += month_day[i-1];
				}
		}

		day_diff += day;

	}else if(transaksi[ids-1].year_out == year){
		if(month>transaksi[ids-1].mounth_out){
			if(transaksi[ids-1].mounth_out==2){
				if(is_LeapYear(transaksi[ids-1].year_out)==true){
					day_diff += 29- transaksi[ids-1].day_out;
				}else {
					day_diff += 28 - transaksi[ids-1].day_out;
				}
			} else {
				day_diff = month_day[transaksi[ids-1].mounth_out-1] - transaksi[ids-1].day_out;
			}
			transaksi[ids-1].mounth_out++;
			for(int i=transaksi[ids-1].mounth_out;i<month;i++){
				if(i==2){
					if(is_LeapYear(transaksi[ids-1].year_out)==true){
						day_diff += 29;
					}else {
						day_diff += 28;
					}
				}else {
					day_diff += month_day[i-1];
				}
			}
			day_diff += month;
		}else if(transaksi[ids-1].mounth_out==month){
			if(day>transaksi[ids-1].day_out){
				day_diff = day - transaksi[ids-1].day_out;
			}else if(transaksi[ids-1].day_out==month){
				day_diff = 0;
			}
		}
	}
	cout << "Keterlambatan\t: " << day_diff << endl;
	
	if(day_diff > 0){
		do{
			cout << "Anda telat mengembalikan, Anda mendapatkan denda!!!" << endl;
			cout << "denda yang diberikan sebesar harga mobil * lama rental * lama keterlambatan" << endl;
			denda =  transaksi[ids-1].totalPrice*day_diff;
			cout << "Anda mendapat denda sebesar Rp" << denda << ",Silahkan dibayar!" << endl;
			cout << "Masukkan nominal\t: ";
			cin >> dendas;
			cin.ignore();
		}while (denda > dendas);
			kembalian = dendas-denda;
			cout << "kembalian anda Rp. " << kembalian  << endl;
	}else{
		cout << "Terima kasih karena mengembalikan tidak telat :)" << endl;
	}

	
	system("pause");
	system("cls");
	
}

string replaceSpasi(string str){
	for(int i=0; str[i]; i++){
		if(str[i] == ' '){
			str.replace(i, 1, 1, '_');
		}
	}
	return str;
}

string replaceUnderScore(string str){
	for(int i=0; str[i]; i++){
		if(str[i] == '_'){
			str.replace(i, 1, 1, ' ');
		}
	}
	return str;
}

void syarat_check(int day, int month, int year, bool &syarat_tanggal){
	bool ly = is_LeapYear(year);
	if(year<MIN_YEARS || year>MAX_YEARS){
		syarat_tanggal = false;
	} else if(month<1 || month > 12){
		syarat_tanggal = false;
	} else if((day > 29) && (month == 2) && (ly == true)){
		syarat_tanggal = false;
	} else if((day > 28) && (month == 2) && (ly == false)){
		 syarat_tanggal = false;
	} else if(month != 2 && (day<1 || day > month_day[month-1])){
		syarat_tanggal = false;
	} else {
		syarat_tanggal = true;
	}
}

bool is_LeapYear(int year){
	if(year%400 == 0){
		return true;
	} else if(year%100 == 0){
		return false;
	} else if(year%4 == 0){
		return true;
	} else {
		return false;
	}
}

void date(int &day, int &month, int &year, int &borrow){
	int d_max; 
	int m_max = 12;
	day += borrow;
	bool ly = is_LeapYear(year);
	if (month != 2){
		d_max = month_day[month-1];
	} else{
		if (ly == false){
			d_max = 28;
		}else{
			d_max = 29;
		}
	}

	int days = add_day(day, month, d_max);
	int months = add_month(month, year, m_max);
	day = days;
	month = months;
	year = year;
}

int add_day(int day, int &month, int d_max){
	if(day <= d_max){
		return day;
	}else {
		return add_day(day-d_max, ++month, d_max);
	}
}

int add_month(int month, int &year, int m_max){
	if(month <= m_max){
		return month;
	}else {
		return add_month(month-m_max, ++year, m_max);
	}
}
