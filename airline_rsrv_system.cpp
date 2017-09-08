#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <list>	 //double linked list
#include <iostream>
#include <string> // for the atoi conversion
#include <sstream> // for the stringstream (used to convert into to string)
#include <iomanip> // for organizing output into columns
#include <vector>

using namespace std;

// forward declaration
class Person; 
class Flight;
class Queue;

/* ----CLASSES---- */

class Menu //class for managing the app's menu
{
	public:
		static void displayMenu(); // displays the menu
		static void select(int selection); // receives user's input and performs the corresponding function
		static void exit_prog(); // exits the app
};

struct Time // structure for managing the Arrival and Departing times
{
	int min; 
	int hour;
};

class Flight // class for managing the availabe functions of a flight
{				
	private:
	
		int flightNo, cost, seats, booked_seats;
		string from, to, plane_type;	
		Time t_leave, t_arrive;
		
	public:
		/* --ADD/REMOVE FLIGHTS--*/
		void addFlight(); //διαχειρίζεται την προσθήκη πτήσεων (επιλογή μενού Νο 1)
		static void deleteFlight(int num); //διαχειρίζεται την αφαίρεση πτήσεων (επιλογή μενού Νο 2)
		
		/* --DISPLAY FLIGHTS--*/
		static void displayFlightInfo(int num); //προβάλλει τις πληροφορίες μιας πτήσης (επιλογή μενού Νο 3)
		static void displaySchedule(); //προβάλλει τις πτήσεις που υπάρχουν καταχωρημένες στο σύστημα (επιλογή μενού Νο 4)
		
		/* --BOOK SEATS--*/
		static void resSeat(int num, int val); //αυξομειώνει τις κατοχυρωμένες θέσεις μιας πτήσεις
		
		/* --FLIGHT CHECKERS--*/
		static bool flightExists(int num); // check flight is booked	
		static bool checkForSeats(int num); // checks for already registerd flight in the system
		
		/* --GETTERS--*/
		int getFlightNo() { return this -> flightNo; }
		Time getLeavingTime() { return this -> t_leave; }
		Time getArrivingTime() { return this -> t_arrive; }
		string getDeparture() { return this -> from; }
		string getDestination() { return this -> to; }
};			
	
class Person //class for managing the functions of a passenger				
{
	private:
	
		int passportNo, tel;
		list<int> flights;
		string name, surname, nationallity, address;		
	
	public:
		/* --BOOK FLIGHT-- */
		void book(); // book flight for each customer (Menu Option Νο 6)
		void bookFromQueue(int num); // book flight for the oldest customer in 
					    // (call ONLY when a reservation is cancelled)
		void cancel(); //cancel a reservation (Menu Option Νο 7)
		
		/* --SHOW PASSENGER'S INFO-- */
		static bool displayPersonInfo(int passport);
		
		/* --CHECHKER FOR UNIQUE PASSPORT-- */
		static bool uniquePass(int passport);
		
		/* --GETTERS-- */
		int getPassport() { return this -> passportNo; }
		string getName() { return this -> name; }
		string getSurname() { return this -> surname; }
		
};	

struct Node //structure for managing each flight's queue
{
    Person person;
    Node* next;
};

class Queue // class that stores passengers on each flight's queue
{

    private:

	int queueNo;
        Node* rear;
        Node* front;	
	
	public:
		/* --CREATE NEW QUEUE-- */
        Queue(int queueId); // queueID is the same as the flight number for each flight
		
		/* --ADD/REMOVE ELEMENTS-- */
        void enqueue(Person p); // add a new passenger
        void dequeue(); // remove the passenger add last 
		
		/* --ΠΡΟΒΟΛΗ ΣΤΟΙΧΕΙΩΝ ΟΥΡΑΣ-- */
		static void display(int num); //εμφανίζει τους πελάτες, που βρίσκονται κατοχυρωμένοι 
									 //στην ουρά αναμονής της εκάστοτε πτήσης

		/* --ΕΠΙΣΤΡΟΦΗ ΑΡΧΑΙΟΤΕΡΟΥ ΧΡΗΣΤΗ-- */
		Person oldest(); //επιστρέφει το αντικέιμενο του αρχαιότερου πελάτη, μέσω της κλάσης Person
		
		/* --CHECK FOR EMPTY QUEUE-- */
		bool isEmpty(); // returns true if queue is empty
		
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

/* ----FUNCTIONS-CHECKERS FOR THE INPUTS---- */

/* --CHECKERS FOR DIRECT FLIGHTS-- */
bool checkTime(string time) { // check the validity of the time (must be xx:xx, where x = Natural number)
	
	// enter ONLY if string is NOT empty
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
	}else{ 
		return false;
	}
	
}

bool checkNumber(string s){ // checks if the input string consists ONLY of numbers
	
	// enter if string is NOT empty
	if(!s.empty()){
		for (int i = 0; i < s.length(); i++){
			if ( ((s.at(i) >= 'a' && s.at(i) <= 'z') || (s.at(i) >= 'A' && s.at(i) <= 'Z') || (s.at(i) == ' ')) ){
				return false;
			}
		}
	
		// check if string is a postive number
		if ( atoi(s.c_str()) > 0 ){
			return true;
		}else{
			return false;
		}
	}else{
		return false;
	}
	
	
}

bool checkString(string s){ // checks if string consists only of letters
	
	if(!s.empty()){
		for (int i = 0; i < s.length(); i++){
			if ( !((s.at(i) >= 'a' && s.at(i) <= 'z') || (s.at(i) >= 'A' && s.at(i) <= 'Z')) ){
				return false;
			}
		}
		return true;
	}
	else{ //return false
		return false;
	}
	
	
}

/* --CHECKER FOR NON-DIRECT FLIGHTS-- */
bool checkTime2(Time tLeaving, Time tArriving){	// checks the validity of arrival and departure time
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


/* ----GLOBAL VARS---- */

list<Flight> flist; // store the flights of the system
list<Person> plist; // store the passengers 
list<Queue> qlist; // store the customers in the flights' waiting queues

/* ----FUNCTION OF CLASS Queue---- */

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


/* ----FUNCTIONS OF CLASS Menu---- */

void Menu::displayMenu(){
	
	int selection;	// user's menu choice
	string temp; // temp to store user's input
	
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
			
			// check validity of input
			while (!checkNumber(temp)) {
				cout << "Please enter a number!" << endl;
				cin.clear();
				cin.ignore(256,'\n');
				cin >> temp;
			}
			cout << endl;
			
			selection = atoi(temp.c_str());
			select(selection);
	
	}while(true);
}

void  Menu::select(int selection){
	
	Flight f; // FLight's object
	Person p; // class Person's object
	string temp; // temp to store input
	
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
	exit(1); // exit
}

/* ----FUNCTIONS OF CLASS Flight---- */

void Flight::addFlight(){ 
	
	/* ----INITIALISE VARS----*/
	bool flag = false; // used in loops
	
	/* --Check for arrival, departure time validity (USED ONLY IN BOARDING & ARRIVING TIME)-- */
	vector<string> fields; // stores, splitted,  user input to be checked
	string temp; // stores user's input temp
	char* pch; // stores result of function strtok() 
	int hour; // stores hour
	int min; // store minutes

	cout << "Add new flights by giving the following attributes: \n";
	
	// clean stream
	cin.clear();
	cin.ignore(256,'\n');
	
	/* --FLIGHT NUBMER-- */
	cout << "Flight Number: "; 
	// get user's input
	getline(cin, temp);
	
	do{
		flag = true;
		
		// check input
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
	
	/* --DEPARTURE-- */
	cout << "Departure: ";
	flag = false;
	
	// check input
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
	
	/* --DESTINATION-- */
	cout << "Destination: "; 
	flag = false;
	
	// check input
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
	
	/* --DEPARTURE TIME-- */
	cout << "Boarding time (e.g. 19:40): "; //ask from user for the boarding time
	flag = false;
	
	// check input
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
			fields.push_back(pch); 
			pch = strtok(NULL, ":");
		}
		
		hour = atoi(fields[0].c_str()); 
		min = atoi(fields[1].c_str()); 
		
		// check time
		if ((hour >=0 && hour<=23) && (min>=0 && min <=59)){ 
			this -> t_leave.hour = hour; 
			this -> t_leave.min = min; 
			flag = true;
		}else{
			cout << "Please insert a valid boarding time (e.g. 19:40)! ";
			fields.clear();		
		}	
		
	}while(!flag); 
	
	/* --ARRIVAL TIME-- */
	cout << "Arriving time (e.g. 21:40): ";
	flag = false;
	fields.clear();	// clear fields (because it was used before, at "DEPARTURE TIME")
	
	// check input
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
			fields.push_back(pch); 
			pch = strtok(NULL, ":");
		}
		
		hour = atoi(fields[0].c_str());
		min = atoi(fields[1].c_str());
		
		// check validity of time
		if ((hour >=0 && hour<=23) && (min>=0 && min <=59)){ 
			this -> t_arrive.hour = hour; 
			this -> t_arrive.min = min; 
			flag = true;
		}else{
			cout << "Please insert a valid arriving time (e.g. 19:40)! ";
			fields.clear();		
		}	
		
	}while(!flag); 
	
	/* --TICKET COST-- */
	cout << "Ticket price: ";
	LOOP5:do{
		
		getline(cin, temp);
		flag = true;
		
		// check input
		if (!checkNumber(temp)){
			cout << "Please insert a valid ticket price!" << endl;
			flag = false;
			goto LOOP5;
		}else{
			flag = true;
			this -> cost = atoi(temp.c_str());
		}
	}while(!flag);
	
	/* --AIRCRAFT TYPE-- */
	cout << "Aeroplane type: ";
	getline(cin, this -> plane_type);
	while(this -> plane_type.empty()){
		cout << "Please insert a valid Aeroplane type!" << endl;
		getline(cin, this -> plane_type);
	}
	
	/* --No OF SEATS-- */
	cout << "Number of seats: ";
	LOOP6:do{
		
		getline(cin, temp);
		flag = true;
		
		// check input
		if (!checkNumber(temp)){
			cout << "Please insert a valid number of seats!" << endl;
			flag = false;
			goto LOOP6;
		}else{
			flag = true;
			this -> seats = atoi(temp.c_str());
		}
	}while(!flag);
	
	/* --No of BOOKED SEATS-- */
	cout << "Number of booked seats: ";
	LOOP7:do{
		
		getline(cin, temp);
		flag = true;
		
		// check input
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
	
	
	flist.push_back(*this); // add object to the flist
	
	Queue q(this -> flightNo); // create new queue for the newly added flight
	qlist.push_back(q); // add object to the qlist
	
	cout << "Flight No: "<< this -> flightNo << " was successfully added!" << endl;
	
}

void Flight::deleteFlight(int num){
		
		for (std::list<Queue>::iterator i = qlist.begin(); i != qlist.end(); ++i){
			if( num == i -> getNo() ){
				
				// enter if waiting queue for the flight is NOT empty
				if (!i -> isEmpty()) {
					// delete object from flist
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
		cout << "This flight number doesn't exist!" << endl;
		return;					
}

void Flight::displayFlightInfo(int num){

	string l_time, a_time; // departure and arrival time
	stringstream convert; 
	stringstream convert2; 
	
	for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i) {
		if (num == i -> flightNo) {
				
			convert.str(std::string()); // clear stringstream "convert"
			convert2.str(std::string()); // clear stringstream "convert2"
			
			convert << i -> t_leave.hour;
			convert2 << i -> t_leave.min;		 
			l_time = convert.str() + ":" + convert2.str();
				
			convert.str(std::string()); // clear stringstream "convert"
			convert2.str(std::string()); // clear stringstream "convert2"
			
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
	
	string l_time, a_time; // departure and arrivale time
	stringstream convert; 
	stringstream convert2; 
	 
		cout << "\n\t\t\t\t FLIGHT SCHEDULE" << endl << endl;
		cout << left << setw(10) << "FLIGHT" << left << setw(10) << "FROM" << left << setw(10) << "TO" << left << setw(10) << "LEAVE" << left << setw(10) << "ARRIVE" << left << setw(10) << "COST" << left << setw(10) << "TYPE" << left << setw(10) << "SEATS" << left << setw(10) << "BOOKED" << endl;
		
		for (std::list<Flight>::iterator i = flist.begin(); i != flist.end(); ++i) {
				convert.str(std::string());	// clear stringstream "convert"
				convert2.str(std::string());	// clear stringstream "convert2"
				
				convert << i -> t_leave.hour;
				convert2 << i -> t_leave.min;		 
				l_time = convert.str() + ":" + convert2.str();
				
				convert.str(std::string());	// clear stringstream "convert"
				convert2.str(std::string());	// clear stringstream "convert2"
				
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

/* ----FUNCTIONS OF CLASS Person---- */	

void Person::book(){
	
	/* ----INITIALISE VARS----*/
	/* --FLIGHTS-- */
	string temp; //temp to store user's input, to be checked
	int num; // stores flight's number, after successful check
	
	/* --VARS FOR NON DIRECT FLIGHTS-- */
	int counter = 1; // stores the amount(>=2) of the non-direct flights
	string choice; // stores user's choice for adding or not more flights to their reservation
	Time tArriving; 
	Time tLeaving; 
	string Departure; 
	string Destination; 
	list<int> nums; // store flights' numbers 
	list<int>::iterator i1 = nums.begin(); //iterator for accessing List nums
	
	/* --VAR FOR LOOPS-- */
	bool flag = true;
	
	// clean stream
	cin.clear();
	cin.ignore(256,'\n');
	
	if (!flist.empty()) {
		cout << "Insert y (yes) for a new client or n (no) for an existing client. ";
		getline(cin, choice);
		
		// enter if client is new
		if (choice == "y" || choice == "Y") {
			
			cout << "Please give us your personal info. " << endl;
		
			/* --NAME-- */
			cout << "Name: ";
			flag = false;
			
			// check input
			LOOP8:do{
				getline(cin, this -> name);
				if ( (this -> name.length() <= 10) && (checkString(this -> name)) ){
					flag = true;
				}else {
					cout << "Please insert a valid Name! ";
					goto LOOP8;
				}
			}while(!flag);
			
			/* --SURNAME-- */
			cout << "Surname: ";
			flag = false;
			
			// check input
			LOOP9:do{
				getline(cin, this -> surname);
				if ( (this -> surname.length() <= 10) && (checkString(this -> surname)) ){
					flag = true;
				}else {
					cout << "Please insert a valid Surname! ";
					goto LOOP9;
				}
			}while(!flag);
			
			/* --PASPPORT No-- */
			cout << "Passport number: ";
			
			// check input
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
			
			/* --NATIONALLITY-- */
			cout << "Nationallity: ";
			flag = false;
			
			// check input
			LOOP11:do{
				
				getline(cin, this -> nationallity);
				
				if ( (this -> nationallity.length() <= 10) && (checkString(this -> nationallity)) ){
					flag = true;
				}else {
					cout << "Please insert a valid Nationallity! ";
					goto LOOP11;
				}
			}while(!flag);
			
			/* --ADDRESS-- */
			cout << "Address: ";
			getline(cin, this -> address);
			
			/* --TEL-- */
			cout << "Telephone: "; 
			getline(cin, temp);
			
			// check input
			while (!checkNumber(temp)) {
				cout << "Please insert a valid telephone number!" << endl;
				getline(cin, temp);
			}
			this -> tel = atoi(temp.c_str());
		}else { // existing customer
			cout << "Pleas give us your passport No: ";
			getline(cin, temp);
			
			// check input
			while(!checkNumber(temp)){
				cout << "Please insert a valid passport number!" << endl;
				flag = false;
				getline(cin, temp);
			}
				
			// check if passport No is unique
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
							
							// after copying the customers info,
							// delete the old object pointing to them
							i = plist.erase(i);
							break;
						}
					}
			}else {
				cout << "Wrong passport number!" << endl;
				return;
			}
		}
		
		
		// display flights
		Flight::displaySchedule(); 
		
		/* --FLIGTH No-- */
		cout << "\n\nEnter the number of the flight you 're intrested in: ";
		getline(cin, temp);
		flag = true;
		
		// check input
		while ( !checkNumber(temp) && !Flight::flightExists(atoi(temp.c_str())) ) {
			cout << "Please insert a valid Flight No!" << endl;
			getline(cin, temp);
		}
		num = atoi(temp.c_str());
		
		/*
		------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ 
							BOOK CUSTOMER'S CHOSEN FLIGHT(S)	 
		------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		*/
		
		//DIRECT FLIGHT
		if(Flight::checkForSeats(num)){ // check for vacancy		
			this -> flights.push_back(num);
			Flight::resSeat(num,1);
			cout << "Your flight with No: " << num << " was successfully booked." << endl;
		
		// NONO-DIRECT FLIGHT	
		}else{
			choice = "y";
			
			cout << "There are no available direct flights for this destination." << endl;
			cout << "Please enter the special numbers for the alternative flights.";
			
			while(choice == "y" || choice == "Y"){ // exit if user doesn't want to add more flights
				
		  LOOP12:cout << "\nNumber #" << counter << " : ";
				getline(cin, temp);
				
				// check input
				while ( !checkNumber(temp) && !Flight::flightExists(atoi(temp.c_str())) ) {
					cout << "Please insert a valid Flight No!" << endl;
					cin >> temp;
				}
				
				num = atoi(temp.c_str());	
								
				if (counter > 1){ // enter if user has entered 2 or more flights			
				
					// store the arrival, departure time and the departure, arriving city
					for (std::list<Flight>::iterator i2 = flist.begin(); i2 != flist.end(); ++i2) {
						if (*i1 == i2 -> getFlightNo()) {					
							tArriving = i2 -> getArrivingTime();
							Destination = i2 -> getDestination();
						}else if (num == i2 -> getFlightNo()) {
							tLeaving = i2 -> getLeavingTime();
							Departure = i2 -> getDeparture();
						}
					}
					
					// check validity of each flight
					if ( !(checkTime2(tLeaving,tArriving) && !Departure.compare(Destination)) ) {
						cout << "Please enter a flight to a valid Destination!" << endl;
						goto LOOP12;	
					}
				}
				
				nums.push_back(num); // add the flight's number		
				i1++;
				
				if(counter >= 2){ 
					cout << "Do you want to add more flight numbers?(y/n) "; 
					getline(cin, choice);
				}
				
				counter++; 
			} 
			
			
			// check for vacancies in the chosen flights
			// and add all of the flight's numbers to the specific node of the list flights
			for (std::list<int>::iterator i = nums.begin(); i != nums.end(); ++i){
				flag = Flight::checkForSeats(*i) and flag;
				this -> flights.push_back(*i);
			}
			
			//enter ONLY if there are vacant seats and reserve a seat to each chosen flight
			if(flag){
				for (std::list<int>::iterator i = nums.begin(); i != nums.end(); ++i){				
					Flight::resSeat(*i,1);
				}
				cout << "Your flights were successfully booked." << endl;
			
			// if, at least, one flight is fully booked add the customer to the queues of each flight
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
		plist.push_back(*this); // add object to plist
	}else{
		cout << "There are no available flights at the moment." << endl;
		return;
	}	
}

void Person::bookFromQueue(int num){  //is called only from cancel()
	
	bool flag = true;
	Person queueFront; // object of the customer added last

	// find the oldest customer
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
	
	// check if all of the customer's chosen flights have vacant seats
	for (std::list<int>::iterator i = queueFront.flights.begin(); i != queueFront.flights.end(); ++i){
		flag = Flight::checkForSeats(*i) and flag;
	}
	
	// enter ONLY if there are vacancies in ALL of the customer's chosen flights
	// and book them
	if(flag){			
		Node* p = new Node; 
		
		// find the flights of the oldest customer
		for (std::list<int>::iterator i = queueFront.flights.begin(); i != queueFront.flights.end(); ++i){
			
			// delete him from the queues
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
		
	string passport, num; 
	int counter = 1; //counter that stores user's wrong inputs
	bool flightFound = false; // is false if customer has already booked a seat in a flight
	bool isInQueue = false; //is false if the customer, that will be deleted, doesn't belong in
				// the queue of each flight
	
	if (!plist.empty()) {
		// clean stream
		cin.clear();
		cin.ignore(256,'\n');
		
		cout << "Please give us your passport number: ";
		getline(cin, passport); cout << endl;
		
		// check input
		while(!checkNumber(passport)){
			cout << "Please insert a valid passport number!" << endl;
			getline(cin, passport); cout << endl; 
		}
		
		while(!Person::displayPersonInfo( atoi(passport.c_str()) )) {
					
			//έξοδος από το πρόγραμμα αν δοθεί λανθασμένος αριθμός διαβατηρίου 5 φορές
			if (counter == 5) {
				cout << "Wrong passporst number was given too many times.";
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
		
		// check input
		while(!checkNumber(num)){
			cout << "Please insert a valid flight number!" << endl;
			getline(cin, num); cout << endl; 
		}
		
		// iterate through the passenger's flights
		for (std::list<Person>::iterator i = plist.begin(); i != plist.end(); ++i){
			if (atoi(passport.c_str()) == i -> passportNo) {	
				
				// check input and exit if counter = 5
				do{										
					for (std::list<int>::iterator i2 = (i -> flights).begin(); i2 != (i -> flights).end(); ++i2){
						if (atoi(num.c_str()) == *i2) {
							flightFound = true;
							i2 = flights.erase(i2); // delete flight from passenger's info
							break;
						}
					}
					
					if (counter == 5){
						cout << "Wrong flight number was given too many times.";
						return;
					}else if(!flightFound){
						cout << "Please check your flight number!.";
						getline(cin, num); cout << endl;
						
						// check input
						while(!checkNumber(num)){
						cout << "Please insert a valid flight number!" << endl;
						getline(cin, num); cout << endl; 
						}
					}				
					counter++;
				}while(!flightFound);
				break;
			}
		}
		
		// delete client from the queue of the flight, if they are a part of it
		for (std::list<Queue>::iterator i = qlist.begin(); i != qlist.end(); ++i){
			if( atoi(num.c_str()) == i -> getNo() ){
				if(!i -> isEmpty()){
					Node* p = new Node;			
					Node* previousNode;
					p = i -> getFront();
					
					while(p!=NULL){
						if (atoi(passport.c_str()) == p -> person.passportNo){
							isInQueue = true;
							
							// enter if the client is on the first position
							if (p == i -> getFront()){
								i -> setFront(p -> next);
								// enter if queue has only one element
								if (i -> getFront() == i -> getRear()){
									i -> setRear(NULL);
								}						
							}else if(p == i -> getRear()){ // enter if client is in the last poitsion of the queue
								previousNode -> next = NULL;								
							}else{ 
								previousNode -> next = p -> next;								
							}
							delete(p);
							break;						
						}
						previousNode = p;
						p = p -> next;
					}
				}
			}
		}
		
		//enter if passenger is NOT part of the current queue
		if (!isInQueue){
			Flight::resSeat(atoi(num.c_str()), -1); 		
		
			this -> bookFromQueue(atoi(num.c_str()));
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

