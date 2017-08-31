#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <list>	 //διπλά linked list
#include <iostream>
#include <string> // atoi 
#include <sstream> // για το stringstream (χρησιμοποιείται για μετατροπή int σε string)
#include <iomanip> // for organizing output into columns
#include <vector>

using namespace std;

// forward declaration
class Person; 
class Flight;
class Queue;

/* ----ΚΛΑΣΕΙΣ---- */

class Menu //κλάση για τη διαχείριση του κεντρικού μενού
{
	public:
		static void displayMenu(); //προβάλλει το κεντρικό μενού επιλογής
		static void select(int selection); //δέχεται την είσοδο του χρήστη και εκτελεί την κατάλληλη λειτουργία
		static void exit_prog(); //όταν κληθεί, τερματίζει το πρόγραμμα (επιλογή μενού Νο 8)
};

struct Time //δομή για τη διαχείριση της ώρα αναχώρησης και άφιξης των πτήσεων
{
	int min; 
	int hour;
};

class Flight //κλάση για τη διαχείριση λειτουργιών σχετικά με τις πτήσεις
{				
	private:
	
		int flightNo, cost, seats, booked_seats;
		string from, to, plane_type;	
		Time t_leave, t_arrive;
		
	public:
		/* --ΠΡΟΣΘΑΦΑΙΡΕΣΗ ΠΤΗΣΕΩΝ--*/
		void addFlight(); //διαχειρίζεται την προσθήκη πτήσεων (επιλογή μενού Νο 1)
		static void deleteFlight(int num); //διαχειρίζεται την αφαίρεση πτήσεων (επιλογή μενού Νο 2)
		
		/* --ΠΡΟΒΟΛΗ ΠΤΗΣΕΩΝ--*/
		static void displayFlightInfo(int num); //προβάλλει τις πληροφορίες μιας πτήσης (επιλογή μενού Νο 3)
		static void displaySchedule(); //προβάλλει τις πτήσεις που υπάρχουν καταχωρημένες στο σύστημα (επιλογή μενού Νο 4)
		
		/* --ΚΡΑΤΗΣΗ-ΜΕΙΩΣΗ ΘΕΣΕΩΝ--*/
		static void resSeat(int num, int val); //αυξομειώνει τις κατοχυρωμένες θέσεις μιας πτήσεις
		
		/* --ΕΛΕΓΧΟΣ ΣΤΟΙΧΕΙΩΝ ΠΤΗΣΕΩΝ--*/
		static bool flightExists(int num); //ελέγχει αν υπάρχουν κενές θέσεις σε μία πτήση	
		static bool checkForSeats(int num); //ελέγχει αν μια πτήση υπάρχει ήδη στο σύστημα
		
		/* --GETTERS--*/
		int getFlightNo() { return this -> flightNo; }
		Time getLeavingTime() { return this -> t_leave; }
		Time getArrivingTime() { return this -> t_arrive; }
		string getDeparture() { return this -> from; }
		string getDestination() { return this -> to; }
};			
	
class Person //κλάση για τη διαχείριση των λειτουργιών αναφορικά με τους επιβάτες				
{
	private:
	
		int passportNo, tel;
		list<int> flights;
		string name, surname, nationallity, address;		
	
	public:
		/* --ΚΡΑΤΗΣΗ-ΑΚΥΡΩΣΗ ΘΕΣΕΩΝ-- */
		void book(); //κράτηση θέσεων του εκάστοτε πελάτη (επιλογή μενού Νο 6)
		void bookFromQueue(int num); //κράτηση θέσεων του αρχαιότερου (καλείται ΜΟΝΟ στην περίπτωση ακύρωσης κράτησης)
		void cancel(); //ακύρωση κράτησης (επιλογή μενού Νο 7)
		
		/* --ΠΡΟΒΟΛΗ ΣΤΟΙΧΕΙΩΝ ΕΠΙΒΑΤΗ-- */
		static bool displayPersonInfo(int passport);
		
		/* --ΕΛΕΓΧΟΣ ΣΤΟΙΧΕΙΩΝ-- */
		static bool uniquePass(int passport);
		
		/* --GETTERS-- */
		int getPassport() { return this -> passportNo; }
		string getName() { return this -> name; }
		string getSurname() { return this -> surname; }
		
};	

struct Node //δομή για τη διαχείριση των αντικειμένων της εκάστοτε ουράς
{
    Person person;
    Node* next;
};

class Queue //ουρά αναμονής για την αποθήκευση των πελατών
{

    private:

		int queueNo;
        Node* rear;
        Node* front;	
	
	public:
		/* --ΟΡΙΣΜΟΣ ΝΕΑΣ ΟΥΡΑΣ ΑΝΑΜΟΝΗΣ-- */
        Queue(int queueId); //ορίζει μια νέα ουρά για την εκάστοτε πτήση, με ID τον αντίστοιχο αιρθμό πτήσης
		
		/* --ΠΡΟΣΘΑΦΑΙΡΕΣΗ ΑΝΤΙΚΕΙΜΕΝΩΝ ΣΤΗΝ ΟΥΡΑ-- */
        void enqueue(Person p); //προσθέτει στην ουρά της εκάστοτε πτήσης ένα νέο αντικείμενο πελάτη-Person
        void dequeue(); //αφαιρεί στην ουρά της εκάστοτε πτήσης ένα αντικείμενο πελάτη-Person
		
		/* --ΠΡΟΒΟΛΗ ΣΤΟΙΧΕΙΩΝ ΟΥΡΑΣ-- */
		static void display(int num); //εμφανίζει τους πελάτες, που βρίσκονται κατοχυρωμένοι 
									 //στην ουρά αναμονής της εκάστοτε πτήσης

		/* --ΕΠΙΣΤΡΟΦΗ ΑΡΧΑΙΟΤΕΡΟΥ ΧΡΗΣΤΗ-- */
		Person oldest(); //επιστρέφει το αντικέιμενο του αρχαιότερου πελάτη, μέσω της κλάσης Person
		
		/* --ΕΛΕΓΧΟΣ ΓΙΑ ΚΕΝΗ ΟΥΡΑ-- */
		bool isEmpty(); //επιστρέφει true αν η ουρά είναι κενή
		
		/* --GETTERS-- */
		int getNo() { return this -> queueNo; }	
		Node* getFront() { return this -> front; }
		Node* getRear() { return this -> rear; }
		
		/* --SETTERS-- */
		void setFront(Node* f) { 
			if (f == 0){
				this -> front = NULL;
			}else{
				this -> front = f; 
			}
		}
		void setRear(Node* r) {
			this -> rear = r; 
		}
};

/* ----ΣΥΝΑΡΤΗΣΕΙΣ ΕΛΕΓΧΟΥ ΕΙΣΟΔΟΥ---- */

/* --ΕΛΕΓΧΟΣ ΓΕΝΙΚΗΣ ΠΕΡΙΠΤΩΣΗΣ-- */
bool checkTime(string time) { //έλεγχος για την εγκυρότητα της μορφής ώρας (αποδεκτή μορφή xx:xx, όπου x = φυσικός αριθμός
	
	//είσοδος ΜΟΝΟ αν το string δεν είναι κενό
	if(!time.empty()){
		for (int i=0; i < time.length(); i++) {		
			if (i==2){
				if (time.at(i) != ':') {
				return false;
				}
				
			}else if ( !(time.at(i) >= '0' && time.at(i) <= '9') ) {
				return false;
			}				
		}
		return true;
	}else{//return false αν το string είναι άδειο
		return false;
	}
	
}

bool checkNumber(string s){ //έλεγχει αν το δοθέν string αποτελείται μόνο από αριθμούς
	
	//είσοδος μόνο αν το string ΔΕΝ είναι κενό
	if(!s.empty()){
		for (int i = 0; i < s.length(); i++){
			if ( ((s.at(i) >= 'a' && s.at(i) <= 'z') || (s.at(i) >= 'A' && s.at(i) <= 'Z') || (s.at(i) == ' ')) ){
				return false;
			}
		}
	
		//ελεγχος αν το δοθεν string, όταν μετατραπεί σε αριθμό είναι θετικός
		if ( atoi(s.c_str()) > 0 ){
			return true;
		}else{
			return false;
		}
	}else{ //είσοδος εδώ όταν το string είναι κενό
		return false;
	}
	
	
}

bool checkString(string s){ //έλεγχει αν το δοθέν string αποτελείται μόνο από γράμματα
	
	//είσοδος μόνο εάν το string ΔΕΝ είναι κενό
	if(!s.empty()){
		for (int i = 0; i < s.length(); i++){
			if ( !((s.at(i) >= 'a' && s.at(i) <= 'z') || (s.at(i) >= 'A' && s.at(i) <= 'Z')) ){
				return false;
			}
		}
		return true;
	}
	else{ //return false αν το string είναι άδειο
		return false;
	}
	
	
}

/* --ΕΛΕΓΧΟΣ ΜΟΝΟ ΣΤΗΝ ΠΕΡΙΠΤΩΣΗ ΕΝΑΛΛΑΚΤΙΚΩΝ ΠΤΗΣΕΩΝ-- */
bool checkTime2(Time tLeaving, Time tArriving){	//ελεγχος των ωρών αφίξεων και αναχωρήσεων
	if(tLeaving.hour > tArriving.hour){
		return true;
	}else if(tLeaving.hour == tArriving.hour){
		if(tLeaving.min > tArriving.min){
			return true;
		}
	}
	return false;	
}


/* 
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ 
																IMPLEMENTATION	 
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/


/* ----GLOBAL ΜΕΤΑΒΛΗΤΕΣ---- */

list<Flight> flist; //αποθηκεύονται οι πτήσεις του συστήματος
list<Person> plist; //αποθηκευόνται οι πελάτες 
list<Queue> qlist; //αποθηκεύονται οι πελάτες που βρίσκονται σε ουρά αναμονής

/* ----ΣΥΝΑΡΤΗΣΕΙΣ ΤΗΣ ΟΥΡΑΣ---- */

Queue::Queue(int queueId){
	
	this -> queueNo = queueId;
    this -> rear = NULL;
    this -> front = NULL;
}

void Queue::enqueue(Person p){
	
    Node* temp = new Node;

    temp -> person = p;
    temp -> next = NULL;

    if(this -> front == NULL){
       this -> front = temp;
   }else{
        this -> rear -> next = temp;
    }
    this -> rear = temp;
}

void Queue::dequeue(){

    Node* temp = new Node;

	temp = this -> front;

	this -> front = this -> front -> next;

	delete temp;
}

void Queue::display(int num){
	

	for (std::list<Queue>::iterator i = qlist.begin(); i != qlist.end(); ++i) {
		if(num == i -> queueNo){
			Node* p = new Node;
			p = i -> front;

			if(i -> front == NULL){
				cout<<"\nEmpty queue.\n";
			}else{
				cout << "\nPassengers waiting on queue:" << endl;
				cout << left << setw(15) << "Passport" << left << setw(15) << "Name" << left << setw(15) << "Surame" << endl;
				while(p!=NULL){
					cout << left << setw(15) << p -> person.getPassport() << left << setw(15) << p -> person.getName() << left << setw(15) << p -> person.getSurname() << endl;
					p = p -> next;
				}
			}
		}
	}

    

}

Person Queue::oldest(){
	
	return this -> front -> person;
}

bool Queue::isEmpty(){
 if(this -> front == NULL && this -> rear == NULL){
  return true;
 }
 
 return false;
} 


/* ----ΣΥΝΑΡΤΗΣΕΙΣ ΤΗΣ ΚΛΑΣΗΣ Menu---- */

void Menu::displayMenu(){
	
	int selection;	//η είσοδος του χρήστη
	string temp; //string για την προσωρινή αποθήκευση της εισόδου του χρήστη
	
	do{
			cout << "-----------------------------------------------";
			
			cout << "\n\t AIRLINE RESERVATION SYSTEM \n\n";
			cout << "Please pick an option from the menu below. \n";
			cout << "1. Add new flights \n";
			cout << "2. Delete flights \n";
			cout << "3. Display flight schedule \n";
			cout << "4. Display flight details \n";
			cout << "5. Display passenger personal info \n";
			cout << "6. Book reservation \n";
			cout << "7. Cancel reservation \n";
			cout << "8. Exit \n\n";
			
			cout << "-----------------------------------------------" << endl;
			
			cout << "Enter the number of a menu option: ";
			cin >> temp;
			
			//έλεγχος εγκυρότητας εισόδου
			while (!checkNumber(temp)) {
				cout << "Please enter a number!" << endl;
				cin.clear();
				cin.ignore(256,'\n');
				cin >> temp;
			}
			cout << endl;
			
			selection = atoi(temp.c_str()); //μετατροπή της έγκυρης εισόδου σε int
			select(selection);
	
	}while(true);
}

void  Menu::select(int selection){
	
	Flight f; //αντικέιμενο της κλάσης Flight
	Person p; //αντικέιμενο της κλάσης Person
	string temp; //αποθηκεύεται προσωρινά ο αριθμός πτήσης ή διαβατηρίου που εισήγαγε ο χρήστης
	
	switch(selection){
		case 1:
			f.addFlight();
			break;
		case 2:
			if (!flist.empty()) {
				cout << "Enter the Flight Number you want to delete: "; cin >> temp;
				cout << endl;
				while (!checkNumber(temp)){
					cout << "Flight Number must be a number!" << endl; 
					cin.clear();
					cin.ignore(256,'\n');
					cin >> temp;
					cout << endl;
				}
				
				Flight::deleteFlight( atoi(temp.c_str()) );
			}else {
				cout << "There are no flights to delete" << endl;
			}
						
			break;
		case 3:
			if (!flist.empty()) {
				Flight::displaySchedule();
			}else {
				cout << "There are no scheduled flights!" << endl;
			}
			break;
		case 4:
			if (!flist.empty()) {
				cout << "Please insert flight's number: ";
				cin >> temp; cout << endl;
				while (!checkNumber(temp)){
					cout << "Flight number must be a number!" << endl; 
					cin.clear();
					cin.ignore(256,'\n');
					cin >> temp;
					cout << endl;
				}
				Flight::displayFlightInfo( atoi(temp.c_str()) );
			}else {
				cout << "There are no scheduled flights!" << endl;
			}			
			break;
		case 5:
			if (!plist.empty()){
				cout << "Please insert passport number: ";
				cin >> temp;
				while (!Person::displayPersonInfo( atoi(temp.c_str()) )) {
					cout << "Wrong passport number!" << endl;
					cin.clear();
					cin.ignore(256,'\n');
					cin >> temp;
					cout << endl;
				}
			}else{
				cout << "There are no registered clients at the moment!" << endl;
			}
			break;
		case 6:
			p.book();
			break;
		case 7:
			p.cancel();
			break;
		case 8:
			Menu::exit_prog();
			break;
		default:
			cout << "Invalid selection \n"; 
	}
	
}

void Menu::exit_prog(){
	
	cout << "Thank you for using our system! \n";
	exit(1); //έξοδος από το πρόγραμμα
}

/* ----ΣΥΝΑΡΤΗΣΕΙΣ ΤΗΣ ΚΛΑΣΗΣ Flight---- */

void Flight::addFlight(){ 
	
	/* ----ΔΗΛΩΣΗ-ΑΡΧΙΚΟΠΟΙΗΣΗ ΜΕΤΑΒΛΗΤΩΝ----*/
	bool flag = false; //χρησιμοποιείται για έξοδο από Loops
	
	/* --ΔΙΑΧΕΙΡΙΣΗ ΚΑΙ ΕΛΕΓΧΟΣ ΕΓΚΥΡΟΤΗΤΑΣ ΤΙΜΩΝ ΩΡΑΣ (ΜΟΝΟ ΣΕ BOARDING ΚΑΙ ARRIVING TIME)-- */
	vector<string> fields; //αποθηκεύεται, διαχωρισμένη,  η είσοδος του χρήστης που πρόκεται να ελεγχθεί
	string temp; //αποθηκεύεται, προσωρινά, η είσοδος του χρήστη
	char* pch; //αποθήκευση του αποτελέσματος της συνάρτησης strtok() 
	int hour; //αποθήκευση προσωρινά της ώρας
	int min; //αποθήκευση προσωρινά των λεπτών

	cout << "Add new flights by giving the following attributes: \n";
	
	//"καθάρισμα' του stream
	cin.clear();
	cin.ignore(256,'\n');
	
	/* --ΑΡΙΘΜΟΣ ΠΤΗΣΗΣ-- */
	cout << "Flight Number: "; 
	//λήψη εισόδου χρήστη
	getline(cin, temp);
	
	do{
		flag = true;
		
		//έλεγχος εισόδου
		if (!checkNumber(temp)){
			cout << "Please insert a valid Flight Number! " << endl;
			flag = false;
			getline(cin, temp);
		}else if (Flight::flightExists( atoi(temp.c_str()) )) {
			cout << "This Flight already exists!" << endl;
			cout << "Please insert a valid Flight Number!" << endl;
			flag = false;
			getline(cin, temp);
		}else {
			flag = true;
			this -> flightNo = atoi(temp.c_str());
		}
	}while(!flag);
	
	/* --ΠΟΛΗ ΑΝΑΧΩΡΗΣΗΣ-- */
	cout << "Departure: ";
	flag = false;
	
	//έλεγχος εισόδου
	LOOP:do{
		getline(cin, temp);
		if ( (temp.length() <= 10) && (checkString(temp)) ){
			this -> from = temp;
			flag = true;
		}else {
			cout << "Please insert a valid Departure city! ";
			goto LOOP;
		}
	}while(!flag);
	
	/* --ΠΟΛΗ ΑΦΙΞΗΣ-- */
	cout << "Destination: "; 
	flag = false;
	
	//έλεγχος εισόδου
	LOOP2:do{
		getline(cin, temp);
		if ( (temp.length() <= 10) && (checkString(temp)) && (temp.compare(this -> from)) ){
			this -> to = temp;
			flag = true;
		}else{
			cout << "Please insert a valid Destination city! ";
			goto LOOP2;
		}
	}while(!flag);
	
	/* --ΩΡΑ ΑΝΑΧΩΡΗΣΗΣ-- */
	cout << "Boarding time (e.g. 19:40): "; //ask from admin for the boarding time
	flag = false;
	
	//έλεγχος εισόδου
	LOOP3:do{
		getline(cin, temp);
		
		if( temp.length() != 5 || !checkTime(temp) ){
			cout << "Please insert a valid boarding time (e.g. 19:40)! ";
			goto LOOP3;			 
		}
		
		char t_temp[temp.length()];
		
		strcpy(t_temp, temp.c_str());
		
		//split string
		pch = strtok(t_temp, ":");
		
		while(pch != NULL){
			fields.push_back(pch); //εισαγωγή των δύο διαχωρισμένων string (hours και minutes) σε έναν char array
			pch = strtok(NULL, ":");
		}
		
		hour = atoi(fields[0].c_str()); //αναθεση της ώρας στη μεταβλητή hour
		min = atoi(fields[1].c_str()); //ανάθεση των λεπτών στη μεταβλητή min
		
		//έλεγχος διαστήματος ώρας και λεπτών
		if ((hour >=0 && hour<=23) && (min>=0 && min <=59)){ 
			this -> t_leave.hour = hour; //"πέρασμα" της ώρας στο αντίστοιχο αντικείμενο 
			this -> t_leave.min = min; //"πέρασμα" των λεπτών στο αντίστοιχο αντικείμενοs
			flag = true;
		}else{
			cout << "Please insert a valid boarding time (e.g. 19:40)! ";
			fields.clear();		
		}	
		
	}while(!flag); //έξοδος αν η δοθείσα ώρα είναι ορθή
	
	/* --ΩΡΑ ΑΦΙΞΗΣ-- */
	cout << "Arriving time (e.g. 21:40): ";
	flag = false;
	fields.clear();	//άδειασμα της λίστας fields (λόγω του προηγούμενου πεδίου, "ΩΡΑ ΑΝΑΧΩΡΗΣΗΣ")
	
	//έλεγχος εισόδου
	LOOP4:do{
		getline(cin, temp);
		
		if( temp.length() > 5 || !checkTime(temp) ){
			cout << "Please insert a valid boarding time (e.g. 19:40)! ";
			goto LOOP4;			 
		}
		
		char t_temp[temp.length()];
		
		strcpy(t_temp, temp.c_str());
		
		//split string
		pch = strtok(t_temp, ":");
		
		while(pch != NULL){
			fields.push_back(pch); //εισαγωγή των δύο διαχωρισμένων string (hours και minutes) σε έναν char array
			pch = strtok(NULL, ":");
		}
		
		hour = atoi(fields[0].c_str()); //αναθεση της ώρας στη μεταβλητή hour
		min = atoi(fields[1].c_str()); //ανάθεση των λεπτών στη μεταβλητή min
		
		//έλεγχος διαστήματος ώρας και λεπτών
		if ((hour >=0 && hour<=23) && (min>=0 && min <=59)){ // check for valid hours and minutes
			this -> t_arrive.hour = hour; //αποθήκευση της ώρας στο αντίστοιχο αντικείμενο
			this -> t_arrive.min = min; //αποθήκευση των λεπτών στο αντίστοιχο αντικείμενο
			flag = true;
		}else{
			cout << "Please insert a valid arriving time (e.g. 19:40)! ";
			fields.clear();		
		}	
		
	}while(!flag); //έξοδος αν η δοθείσα ώρα είναι ορθή
	
	/* --ΚΟΣΤΟΣ ΕΙΣΙΤΗΡΙΟΥ-- */
	cout << "Ticket price: ";
	LOOP5:do{
		
		getline(cin, temp);
		flag = true;
		
		//έλεγχος εισόδου
		if (!checkNumber(temp)){
			cout << "Please insert a valid ticket price!" << endl;
			flag = false;
			goto LOOP5;
		}else{
			flag = true;
			this -> cost = atoi(temp.c_str());
		}
	}while(!flag);
	
	/* --ΤΥΠΟΣ ΑΕΡΟΠΛΑΝΟΥ-- */
	cout << "Aeroplane type: ";
	getline(cin, this -> plane_type);
	while(this -> plane_type.empty()){
		cout << "Please insert a valid Aeroplane type!" << endl;
		getline(cin, this -> plane_type);
	}
	
	/* --ΑΡΙΘΜΟΣ ΘΕΣΕΩΝ-- */
	cout << "Number of seats: ";
	LOOP6:do{
		
		getline(cin, temp);
		flag = true;
		
		//έλεγχος εισόδου
		if (!checkNumber(temp)){
			cout << "Please insert a valid number of seats!" << endl;
			flag = false;
			goto LOOP6;
		}else{
			flag = true;
			this -> seats = atoi(temp.c_str());
		}
	}while(!flag);
	
	/* --ΑΡΙΘΜΟΣ ΚΛΕΙΣΜΕΝΩΝ ΘΕΣΕΩΝ-- */
	cout << "Number of booked seats: ";
	LOOP7:do{
		
		getline(cin, temp);
		flag = true;
		
		//έλεγχος εισόδου
		if (!checkNumber(temp)){
			cout << "Please insert a valid number of booked seats!" << endl;
			flag = false;
			goto LOOP7;
		}else if ( atoi(temp.c_str()) > this -> seats ) {
			cout << "Booked seats must be less than plane's seats!" << endl;
			flag = false;
			goto LOOP7;
		}else {
			flag = true;
			this -> booked_seats = atoi(temp.c_str());
		}
	}while(!flag);
	cout << endl;
	
	
	flist.push_back(*this); //εκχώρηση αντικειμένου στη λίστα flist
	
	Queue q(this -> flightNo); //δημιουργία νέας ουράς για την εκάστοτε πτήση
	qlist.push_back(q); //εισαγωγή αντικειμένου λίστα qlist
	
	cout << "Flight No: "<< this -> flightNo << " was successfully added!" << endl;
	
}

void Flight::deleteFlight(int num){
		
		for (std::list<Queue>::iterator i = qlist.begin(); i != qlist.end(); ++i){
			if( num == i -> getNo() ){
				
				//είσοδος μονο αν η ουρά αναμονής της εκάστοτε πτήσης ΔΕΝ είναι κενή
				if (!i -> isEmpty()) {
					//διαγραφή του αντικειμένου-πτήση από τη λίστα flist
					for (std::list<Flight>::iterator i2 = flist.begin(); i2 != flist.end(); ++i2){
						if( num == (i2 -> flightNo) ){
							i2 = flist.erase(i2);
							i = qlist.erase(i);
							cout << "Flight with number: " << num << " was successfully deleted" << endl;
							return;
						}
					}
				}else{
					cout << "There are passengers in the queue of the flight with No: " << num << endl;
					cout << "Remove ALL of them from the queue first!" << endl;
					return;
				}
			}
		}
		//αν δε βρεθεί ο αριθμός πτήσης, τερματίζει
		cout << "This flight number doesn't exist!" << endl;
		return;					
}

void Flight::displayFlightInfo(int num){

	string l_time, a_time; //ώρες αναχώρησης και άφιξης πτήσης αντίστοιχα
	stringstream convert; 
	stringstream convert2; 
	
	for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i) {
		if (num == i -> flightNo) {
				
			convert.str(std::string());		//"άδεισμα" των στοιχείων του stringstream "convert"
			convert2.str(std::string());	//"άδεισμα" των στοιχείων του stringstream "convert2"
			
			convert << i -> t_leave.hour;
			convert2 << i -> t_leave.min;		 
			l_time = convert.str() + ":" + convert2.str();
				
			convert.str(std::string());		//"άδεισμα" των στοιχείων του stringstream "convert"
			convert2.str(std::string());	//"άδεισμα" των στοιχείων του stringstream "convert2"
			
			convert << i -> t_arrive.hour;
			convert2 << i -> t_arrive.min;		 
			a_time = convert.str() + ":" + convert2.str();
			
			cout << left << setw(10) << "FLIGHT" << left << setw(10) << "FROM" << left << setw(10) << "TO" << left << setw(10) << "LEAVE" << left << setw(10) << "ARRIVE" << left << setw(10) << "COST" << left << setw(10) << "TYPE" << left << setw(10) << "SEATS" << left << setw(10) << "BOOKED" << endl;
			cout << left << setw(10) << i -> flightNo << left << setw(10) << i -> from << left << setw(10) << i -> to << left << setw(10) << l_time << left << setw(10) << a_time << left << setw(10) << i -> cost << left << setw(10) << i -> plane_type << left << setw(10) << i -> seats << left << setw(10) << i -> booked_seats << endl;
			
			Queue::display(num);
			return;
		}
	}	
	
	cout << "Invalid number of flight was given." << endl;
}

void Flight::displaySchedule(){
	
	string l_time, a_time; //ώρες αναχώρησης και άφιξης πτήσης αντίστοιχα
	stringstream convert; 
	stringstream convert2; 
	 
		cout << "\n\t\t\t\t FLIGHT SCHEDULE" << endl << endl;
		cout << left << setw(10) << "FLIGHT" << left << setw(10) << "FROM" << left << setw(10) << "TO" << left << setw(10) << "LEAVE" << left << setw(10) << "ARRIVE" << left << setw(10) << "COST" << left << setw(10) << "TYPE" << left << setw(10) << "SEATS" << left << setw(10) << "BOOKED" << endl;
		
		for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i) {
				convert.str(std::string());		//"άδεισμα" των στοιχείων του stringstream "convert"
				convert2.str(std::string());	//"άδεισμα" των στοιχείων του stringstream "convert2"
				
				convert << i -> t_leave.hour;
				convert2 << i -> t_leave.min;		 
				l_time = convert.str() + ":" + convert2.str();
				
				convert.str(std::string());		//"άδεισμα" των στοιχείων του stringstream "convert"
				convert2.str(std::string());	//"άδεισμα" των στοιχείων του stringstream "convert2"
				
				convert << i -> t_arrive.hour;
				convert2 << i -> t_arrive.min;		 
				a_time = convert.str() + ":" + convert2.str();
				
				cout << left << setw(10) << i -> flightNo << left << setw(10) << i -> from << left << setw(10) << i -> to << left << setw(10) << l_time << left << setw(10) << a_time << left << setw(10) << i -> cost << left << setw(10) << i -> plane_type << left << setw(10) << i -> seats << left << setw(10) << i -> booked_seats << endl;
		}
		
		cout << endl;
}

void Flight::resSeat(int num, int val){
	for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i){	
		if( num == (i -> flightNo) ){			
			i -> booked_seats += val ;
			break;
		}
	}	
}

bool Flight::flightExists(int num){
	for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i){
		if (num == i -> flightNo){
			return true;
		}
	}
	return false;
}

bool Flight::checkForSeats(int num){
	for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i){		
		if( num == (i -> flightNo) ){
				if( i -> seats == i -> booked_seats )
					return false;
				else
					return true;
		}
	}
}

/* ----ΣΥΝΑΡΤΗΣΕΙΣ ΤΗΣ ΚΛΑΣΗΣ Person---- */	

void Person::book(){
	
	/* ----ΔΗΛΩΣΗ-ΑΡΧΙΚΟΠΟΙΗΣΗ ΜΕΤΑΒΛΗΤΩΝ----*/
	/* --ΠΤΗΣΕΙΣ-- */
	string temp; //αποθηκεύoνται, προσωρινά, εισαγόμενα δεδομένα από το χρήστη για να ελεγχθούν
	int num; //αποθηκεύεται ο αριθμός της εκάστοτε πτήσης, αφού έχει περάσει επιτυχή έλεγχο
	
	/* --ΜΕΤΑΒΛΗΤΕΣ ΓΙΑ ΤΗΝ ΠΕΡΙΠΤΩΣΗ ΤΩΝ ΕΝΑΛΛΑΚΤΙΚΩΝ ΠΤΗΣΕΩΝ-- */
	int	counter = 1; //αποθηκεύει το πλήθος(>=2) των εναλλακτικών 
					//πτήσεων που εισήγαγε ο πελάτης
	string choice; //αποθηκεύεται η επιλογή του χρήστη για 
					//προσθήκη ή όχι επιπλέον εναλλακτικών πτήσεων
	Time tArriving; //αποθήκευση ώρας άφιξης της κάθε πτήσης
	Time tLeaving; //αποθήκευση ώρας αναχώρησης της κάθε πτήσης
	string Departure; //αποθήκευση πόλης αναχώρηση της κάθε πτήσης
	string Destination; //αποθήκευση πόλης άφιξης της κάθε πτήσης
	list<int> nums; //προσωρινή λίστα για την αποθήκευση των αριθμών 
					//των εναλλακτικών πτήσεων του πελάτη
	list<int>::iterator i1 = nums.begin(); //iterator για την πρόσβαση
					//στα στοιχεία της nums, για τον έλεγχο των στοιχείων των
					//εναλλακτικών πτήσεων (ώρα άφιξης/αναχώρησης, πόλη άφιξης/αναχώρησης)
	
	/* --ΜΕΤΑΒΛΗΤΗ ΓΙΑ ΕΞΟΔΟ ΑΠΟ LOOPS-- */
	bool flag = true;
	
	//"καθάρισμα' του stream
	cin.clear();
	cin.ignore(256,'\n');
	
	//έλεγχος αν η λίστα πτήσεων είναι κενή
	if (!flist.empty()) {
		cout << "Insert y (yes) for a new client or n (no) for an existing client. ";
		getline(cin, choice);
	
		if (choice == "y" || choice == "Y") {
			
			cout << "Please give us your personal info. " << endl;
		
			/* --ΟΝΟΜΑ-- */
			cout << "Name: ";
			flag = false;
			
			//έλεγχος εισόδου
			LOOP8:do{
				getline(cin, this -> name);
				if ( (this -> name.length() <= 10) && (checkString(this -> name)) ){
					flag = true;
				}else {
					cout << "Please insert a valid Name! ";
					goto LOOP8;
				}
			}while(!flag);
			
			/* --ΕΠΩΝΥΜΟ-- */
			cout << "Surname: ";
			flag = false;
			
			//έλεγχος εισόδου
			LOOP9:do{
				getline(cin, this -> surname);
				if ( (this -> surname.length() <= 10) && (checkString(this -> surname)) ){
					flag = true;
				}else {
					cout << "Please insert a valid Surname! ";
					goto LOOP9;
				}
			}while(!flag);
			
			/* --ΑΡΙΘΜΟΣ ΔΙΑΒΑΤΗΡΙΟΥ-- */
			cout << "Passport number: ";
			
			//έλεγχος εισόδου
			LOOP10:do{
				
				getline(cin, temp);
				flag = true;
				
				if (!checkNumber(temp)){
					cout << "Please insert a valid passport number" << endl;
					flag = false;
					goto LOOP10;
				}else if (!Person::uniquePass( atoi(temp.c_str()) )) {
					cout << "Please check the validity of your passport number" << endl;
					flag = false;
					goto LOOP10;
				}else{
					flag = true;
					this -> passportNo = atoi(temp.c_str());
				}	
			}while(!flag);
			
			/* --ΕΘΝΙΚΟΤΗΤΑ-- */
			cout << "Nationallity: ";
			flag = false;
			
			//έλεγχος εισόδου
			LOOP11:do{
				
				getline(cin, this -> nationallity);
				
				if ( (this -> nationallity.length() <= 10) && (checkString(this -> nationallity)) ){
					flag = true;
				}else {
					cout << "Please insert a valid Nationallity! ";
					goto LOOP11;
				}
			}while(!flag);
			
			/* --ΔΙΕΥΘΥΝΣΗ-- */
			cout << "Address: ";
			getline(cin, this -> address);
			
			/* --ΤΗΛΕΦΩΝΟ-- */
			cout << "Telephone: "; 
			getline(cin, temp);
			
			//έλεγχος εισόδου
			while (!checkNumber(temp)) {
				cout << "Please insert a valid telephone number!" << endl;
				getline(cin, temp);
			}
			this -> tel = atoi(temp.c_str());
		}else {
			cout << "Pleas give us your passport No: ";
			getline(cin, temp);
			
			//έλεγχος εισόδου
			while(!checkNumber(temp)){
				cout << "Please insert a valid passport number!" << endl;
				flag = false;
				getline(cin, temp);
			}
				
			//έλεγχος αν ο αριθμός διαβατηρίου υπάρχει στο σύστημα
			if ( !(Person::uniquePass( atoi(temp.c_str()) ))) {
					for (std::list<Person>::iterator i = plist.begin(); i != plist.end(); ++i){
						if (atoi(temp.c_str()) == i -> passportNo) {
							this -> name = i -> name;
							this -> surname = i -> surname;
							this -> passportNo = i -> passportNo;
							this -> nationallity = i -> nationallity;
							this -> address = i -> address;
							this -> tel = i -> tel;
							
							for (std::list<int>::iterator i2 = i->flights.begin(); i2 != i->flights.end(); ++i2) {
								this -> flights.push_back(*i2);
							}
							
							//αφού περάσουμε όλα τα στοιχεία του υπάρχοντος πελάτη,
							//διαγράφουμε το παλιό αντικείμενο που δείχνει σε αυτόν
							i = plist.erase(i);
							break;
						}
					}
			}else {
				cout << "Wrong passport number!" << endl;
				return;
			}
		}
		
		
		//εμφάνιση των πτήσεων στον πελάτη, ώστε να επιλέξει
		Flight::displaySchedule(); 
		
		/* --ΑΡΙΘΜΟΣ ΠΤΗΣΗΣ-- */
		cout << "\n\nEnter the number of the flight you 're intrested in: ";
		getline(cin, temp);
		flag = true;
		
		//έλεγχος εισόδου
		while ( !checkNumber(temp) && !Flight::flightExists(atoi(temp.c_str())) ) {
			cout << "Please insert a valid Flight No!" << endl;
			getline(cin, temp);
		}
		num = atoi(temp.c_str());
		
		/*
		------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ 
							ΚΡΑΤΗΣΗ ΑΠΕΥΘΕΙΑΣ ΠΤΗΣΗΣ ΠΕΛΑΤΗ Ή ΕΚΧΩΡΗΣΗ ΕΝΑΛΛΑΚΤΙΚΩΝ	 
		------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		*/
		
		//ΑΠΕΥΘΕΙΑΣ ΠΤΗΣΗ
		if(Flight::checkForSeats(num)){ //έλεγχος για διαθέσιμη θέση στην απευθείας πτήση		
			this -> flights.push_back(num);
			Flight::resSeat(num,1);
			cout << "Your flight with No: " << num << " was successfully booked." << endl;
		
		//ΕΝΑΛΛΑΚΤΙΚΕΣ ΠΤΗΣΕΙΣ	
		}else{
			choice = "y";
			
			cout << "There are no available direct flights for this destination." << endl;
			cout << "Please enter the special numbers for the alternative flights.";
			
			while(choice == "y" || choice == "Y"){ //έξοδος όταν ο χρήστης δε θέλει να εισάγει επιπλέον πτήσεις
				
		  LOOP12:cout << "\nNumber #" << counter << " : ";
				getline(cin, temp);
				
				//έλεγχος εισόδου
				while ( !checkNumber(temp) && !Flight::flightExists(atoi(temp.c_str())) ) {
					cout << "Please insert a valid Flight No!" << endl;
					cin >> temp;
				}
				
				num = atoi(temp.c_str());	
								
				if (counter > 1){ //είσοδος μόνο εάν ο χρήστης έχει εισάγει τουλάχιστον 2 αριθμούς πτήσεων			
				
					//αποθήκευση των ωρών αναχώρησης-άφιξης κααι των πόλεων αναχώρησης-άφιξης των πτήσεων
					for (std::list<Flight>::iterator i2 = flist.begin(); i2 != flist.end(); ++i2) {
						if (*i1 == i2 -> getFlightNo()) {					
							tArriving = i2 -> getArrivingTime();
							Destination = i2 -> getDestination();
						}else if (num == i2 -> getFlightNo()) {
							tLeaving = i2 -> getLeavingTime();
							Departure = i2 -> getDeparture();
						}
					}
					
					//έλεγχος εγκυρότητας των πτήσεων ως προς την ώρα και τις πόλεις αναχώρησης-άφιξης
					if ( !(checkTime2(tLeaving,tArriving) && !Departure.compare(Destination)) ) {
						cout << "Please enter a flight to a valid Destination!" << endl;
						goto LOOP12;	
					}
				}
				
				nums.push_back(num); //αποθήκευση του αριθμού πτήσης στην προσωρινή λίστα nums			
				i1++;
				
				if(counter >= 2){ //είσοδος μόνο αν ο χρήστης έχει εισάγει τουλάχιστον 2 αριθμούς πτήσεων
					cout << "Do you want to add more flight numbers?(y/n) "; 
					getline(cin, choice);
				}
				
				counter++; 
			}//έξοδος απο το while όταν ο χρήστης ΔΕΝ επιθυμεί να δώσει άλλες ενδιάμεσες πτήσεις
			
			
			//έλεγχος διαθέσιμων θέσεων στις πτήσεις που εισήγαγε ο πελάτης
			//και εκχώρηση των κωδικών αυτών στο εκάστοτε κόμβο της λίστα flights 
			for (std::list<int>::iterator i = nums.begin(); i != nums.end(); ++i){
				flag = Flight::checkForSeats(*i) and flag;
				this -> flights.push_back(*i);
			}
			
			//είσοδος ΜΟΝΟ αν υπάρχουν διαθέσιμες θέσεις στις πτήσεις που εισήγαγε ο πελάτης
			//και κράτηση θέσεων σε κάθε μία από αυτές
			if(flag){
				for (std::list<int>::iterator i = nums.begin(); i != nums.end(); ++i){				
					Flight::resSeat(*i,1);
				}
				cout << "Your flights were successfully booked." << endl;
			
			//στην περίπτωση που δεν υπάρχει διαθέσιμη θέση σε τουλάχιστον μία από τις πτήσεις
			//που εισήγαγε ο πελάτης, γίνεται προσθήκη στις ουρές αναμονής αυτών
			}else{
				cout << endl;
				cout << "Some of the flights you inserted were over booked." << endl;
				
				for (std::list<int>::iterator i = nums.begin(); i != nums.end(); ++i){
					for (std::list<Queue>::iterator i2 = qlist.begin(); i2 != qlist.end(); ++i2){
						if( *i == i2 -> getNo()){
							i2 -> enqueue(*this);
						}
					}
				}
				cout << "We have added you in queues for each of these flights." << endl;
			}
		}
		plist.push_back(*this); //καταχώρηση του αντικειμένου-πελάτη στη λίστα plist
	}else{
		cout << "There are no available flights at the moment." << endl;
		return;
	}	
}

void Person::bookFromQueue(int num){  //καλείται ΜΟΝΟ μέσω της cancel()
	
	bool flag = true; //για έξοδο από LOOPS
	Person queueFront; //το αντικείμενο του αρχαιότερου πελάτη στην ουρά αναμονής της εκάστοτε πτήσης

	//εύρεση του αρχαιότερου χρήστης στην ουρά αναμονής της εκάστοτε πτήσης
	for (std::list<Queue>::iterator it = qlist.begin(); it != qlist.end(); ++it){
		if (num == it -> getNo() ){
			if( !(it -> isEmpty()) ){
				queueFront = it -> oldest();
				break;
			}else{
				return;
			}	
		}
	}
	
	//έλεγχος αν όλες οι πτήσεις του αρχαιότερου πελάτη έχουν διαθέσιμες θέσεις
	for (std::list<int>::iterator i = queueFront.flights.begin(); i != queueFront.flights.end(); ++i){
		flag = Flight::checkForSeats(*i) and flag;
	}
	
	//είσοδος μόνο εάν υπάρχουν διαθέσιμες θέσεις σε όλες τις πτήσεις του αρχαιότερου πελάτη
	// και κράτηση θέσεων σε κάθε μια από αυτές
	if(flag){			
		Node* p = new Node; 
		
		//προσπέλαση σε όλες τις πτήσεις του αρχαιότερου χρήστη
		for (std::list<int>::iterator i = queueFront.flights.begin(); i != queueFront.flights.end(); ++i){
			
			//αναζήτηση στις ουρές αναμονής που βρίσκεται ο αρχαιότερος χρήστης, βάσει των πτήσεών του
			for (std::list<Queue>::iterator i2 = qlist.begin(); i2 != qlist.end(); ++i2) {				
				if(*i == i2 -> getNo()){
					p = i2 -> getFront();		
					while(p != NULL){					
						if(queueFront.passportNo == p -> person.passportNo){
							i2 -> dequeue();
							Flight::resSeat(*i,1);	
						}							
						p = p -> next;
					}
				}
			}
					
		}	
	}	
}

void Person::cancel(){
		
	string passport, num; //αποθηκεύεται ο αριθμός διαβατηρίου και πτήσης που εισάγει ο χρήστης αντίστοιχα
	int counter = 1; //counter που αποθηκεύεται το πλήθος των λανθασμένων εισαγωγών του πελάτη
	bool flightFound = false; //είναι false αν η ο αριθμός πτήσης που εισήγαγε ο χρήστης υπάρχει στις πτήσεις του
	bool isInQueue = false; //είναι false όταν ο προς διαγραφή πελάτης ΔΕΝ ανήκει στην ουρά αναμονής της εκάστοτε πτήσης
	
	if (!plist.empty()) {
		//"καθάρισμα' του stream
		cin.clear();
		cin.ignore(256,'\n');
		
		cout << "Please give us your passport number: ";
		getline(cin, passport); cout << endl;
		
		//έλεγχος αν ο αριθμός διαβατηρίου είναι αριθμός
		while(!checkNumber(passport)){
			cout << "Please insert a valid passport number!" << endl;
			getline(cin, passport); cout << endl; 
		}
		
		//έλεγχος για την εγκυρότητα του αριθμού διαβατηρίου
		while(!Person::displayPersonInfo( atoi(passport.c_str()) )) {
					
			//έξοδος από το πρόγραμμα αν δοθεί λανθασμένος αριθμός διαβατηρίου 5 φορές
			if (counter == 5) {
				cout << "Wrong passport number was given too many times.";
				return;
			}else{
				cout << "Please check your Passport Number." << endl;
				getline(cin, passport); cout << endl;
				
				//έλεγχος αν ο αριθμός διαβατηρίου αποτελείται μόνο από ψηφία
				while(!checkNumber(passport)){
					cout << "Please insert a valid passport number!" << endl;
					getline(cin, passport); cout << endl; 
				}
			}			
			counter++;
		}
		
		cout << "\nWhich flight do you want to cancel (enter the flight number)? "; 
		getline(cin, num);
		counter = 1;
		
		//έλεγχος αν ο αριθμός πτήσης αποτελέιται μόνο από ψηφία
		while(!checkNumber(num)){
			cout << "Please insert a valid flight number!" << endl;
			getline(cin, num); cout << endl; 
		}
		
		//προσπέλαση των πτήσεων του εκάστοτε πελάτη
		for (std::list<Person>::iterator i = plist.begin(); i != plist.end(); ++i){
			if (atoi(passport.c_str()) == i -> passportNo) {	
				
				//έλεγχος εγκυρότητας αριθμού πτήσης και έξοδος από τη συνάρτηση αν δοθεί λάθος κωδικός πτήσης 5 φορές
				do{										
					for (std::list<int>::iterator i2 = (i -> flights).begin(); i2 != (i -> flights).end(); ++i2){
						if (atoi(num.c_str()) == *i2) {
							flightFound = true;
							i2 = flights.erase(i2); //διαγραφή πτήσης από τα στοιχεία του πελάτη
							break;
						}
					}
					
					if (counter == 5){
						cout << "Wrong flight number was given too many times.";
						return;
					}else if(!flightFound){
						cout << "Please check your flight number!.";
						getline(cin, num); cout << endl;
						
						//έλεγχος αν ο αριθμός πτήσης αποτελέιται μόνο από ψηφία
						while(!checkNumber(num)){
						cout << "Please insert a valid flight number!" << endl;
						getline(cin, num); cout << endl; 
						}
					}				
					counter++;
				}while(!flightFound); //έξοδος μόνο αν δοθεί έγκυρος κωδικός πτήσης
				break;
			}
		}
		
		//διαγραφή του αντικειμένου του πελάτη από την ουρά αναμονής της εκάστοτε πτήσης, ΑΝ υπάρχει σε αυτή
		for (std::list<Queue>::iterator i = qlist.begin(); i != qlist.end(); ++i){
			if( atoi(num.c_str()) == i -> getNo() ){
				if(!i -> isEmpty()){
					Node* p = new Node;			
					Node* previousNode; //δείκτης για τη διαχείριση θέσεων κόμβων κατά τη διαγραφή στοιχείου
										//από ουρά αναμονής με παραπάνω από 1 στοιχείο
					p = i -> getFront();
					
					while(p!=NULL){
						if (atoi(passport.c_str()) == p -> person.passportNo){
							isInQueue = true;
							
							//είσοδος εάν ο πελάτης βρίσκεται στην πρώτη θέση της ουράς αναμονής της εκάστοτε πτήσης
							if (p == i -> getFront()){
								i -> setFront(p -> next);
								//είσοδος αν πρόκεται για το μόνο στοιχείο στην ουρά αναμονής
								if (i -> getFront() == i -> getRear()){
									i -> setRear(NULL);
								}						
							}else if(p == i -> getRear()){ //είσοδος εάν ο πελάτης βρίσκεται στην τελευταία θέση της ουράς αναμονής της εκάστοτε πτήσης
								previousNode -> next = NULL;								
							}else{ //είσοδος σε κάθε άλλη περίπτωση
								previousNode -> next = p -> next;								
							}
							delete(p);//διαγραφή από την ουρά αναμονής της εκάστοτε πτήσης
							break;						
						}
						previousNode = p;
						p = p -> next;
					}
				}
			}
		}
		
		//είσοδος ΜΟΝΟ αν ο πελάτης ΔΕΝ υπάρχει στην ουρά αναμονής της εκάστοτε πτήσης
		if (!isInQueue){
			Flight::resSeat(atoi(num.c_str()), -1); //μείωση των κλεισμένων θέσεων κατά μία στην εκάστοτε πτήση		
		
			this -> bookFromQueue(atoi(num.c_str())); //κλήση της bookFromQueue ώστε να γίνει κράτηση για τον αρχαιότερο πελάτη
									// στην ουρά αναμονής της εκάστοτε πτήσης, αν υπάρχει
		}
		cout << "\nYour reservation was successfully removed! \n" << endl;
	}else {
		cout << "There are no registered clients at the moment!" << endl;
	}
}

bool Person::displayPersonInfo(int passport){
	
	for (std::list<Person>::iterator i = plist.begin(); i != plist.end(); ++i){
		
		if(passport == i -> passportNo){
			
			cout << "\n\t\t\t\t PERSONAL INFO" << endl << endl;
			cout << left << setw(15) << "NAME" << left << setw(15) << "SURNAME" << left << setw(15) << "PASSPORT_No" << left << setw(15) << "NATIONALLITY" << left << setw(15) << "ADDRESS" << left << setw(15) << "TELEPHONE" << endl;
			
			cout << left << setw(15) << i -> name << left << setw(15) << i -> surname << left << setw(15) << i -> passportNo << left << setw(15) << i -> nationallity << left << setw(15) << i -> address << left << setw(15) << i -> tel << endl << endl;
			cout << "Your flight(s): ";
			
			for (std::list<int>::iterator i2 = (i -> flights).begin(); i2 != (i -> flights).end(); ++i2){
				
				cout << *i2 << "  ";
			}
			cout << endl;
			return true;
		}
	}
	cout << "Passport number was not found. Check again!" << endl;
	return false;	
}

bool Person::uniquePass(int passport){
	for (std::list<Person>::iterator i = plist.begin(); i != plist.end(); ++i){
		if (passport == i -> getPassport()) {
			return false;
		}
	}
	return true;
}

int main(){
	
	Menu::displayMenu();
	return 0;
}

