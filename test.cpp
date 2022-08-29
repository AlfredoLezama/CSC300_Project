/* Test File */

#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <fstream>

using namespace std;

const int SIZE = 4;

string toppings[4] = { "sprinkles", "chocolate chips", "whipped cream", "caramel"};
string stdDrinks[SIZE] = { "Espresso", "Americano", "Latte", "Frappe" };

class StandardDrinkOrder {
public:
	StandardDrinkOrder() {
		drink = "";
		price = 0.00;
	}
	StandardDrinkOrder(int sel) {
		drink = stdDrinks[sel-1];
		price = sel * 1.00;
	}
	double getPrice() {
		return price;
	}
	void setPrice(double newPrice) {
		price = newPrice;
	}
	string getDrinkName() {
		return drink;
	}
private:
	string drink;
	double price;
};
class CustomizedDrinkOrder : public StandardDrinkOrder{
public:
	void setSize(char size) {
		this->size = size;
	}
	void setType(string type) {
		this->type = type;
	}
	void setTemp(int temp) {
		this->temperature = temp;
	}
	void setSweetness(int temp) {
		this->temperature = temp;
	}
	void setToppings(int sel) { //gets toppings from global array
		this->toppings = toppings[sel];
	}
private:
	char size;
	string type;
	int temperature;
	int sweetness;
	string toppings;
};
class Customer {
public: 
	Customer(string n) {
		name = n;
	}
	string getName() {
		return name;
	}
	void setName(string n) {
		name = n;
	}

private:
	string name;
};
class DrinkOrder {
public:
	DrinkOrder() {
		total = 0;
		numDrinks = 0;
	}
	void addDrink(StandardDrinkOrder d) {
		drinkArray[numDrinks] = d;
		total += d.getPrice();
		numDrinks++;
	}
	double getTotal() {
		return total;
	}
	void displayWholeOrder() {
		cout << "Order\n----------------------------\n";
		for (int i = 0; i < numDrinks; i++) {
			cout << i + 1 << "." << setw(9) << drinkArray[i].getDrinkName() << "\tPrice: $" << drinkArray[i].getPrice() << endl;
		}
	}
	void saveReceipt() {
		fstream receipts;
		receipts.open("C:\\Users\\jakzi\\Documents\\Receipts.txt", ios::app);
		receipts << "\nNumber of Drinks: " << numDrinks << "\t Total: $" << getTotal();
		receipts.close();
	}
	int numDrinks;
	StandardDrinkOrder drinkArray[10];
private:
	
	double total;
};

class Cashier {
public:
	Cashier(string name) {
		this->name = name;
	}
	string getName() {
		return name;
	}
	void setName(string name) {
		this->name = name;
	}
private: 
	string name;
};
class OrderQueue {
public:
	int getNumOfOrders() {
		return numberOfOrders;
	}
	void displayOrder() {

	}
	void incNumOrders() {
		numberOfOrders++;
	}
	void addOrder(DrinkOrder orderToQueue) {
		queue[numberOfOrders] = orderToQueue;
		incNumOrders();
	}	
private:
	int numberOfOrders =0;
	DrinkOrder queue[10];
};
class Barista {
public:
	string name;
};
class Payment {
public:
	Payment() {
		counter = 0;
		ccReturn = "";
	}
	void creditCheck(DrinkOrder d1, OrderQueue q1) {
		cout << "Credit Card payment is ";
		fstream cc;
		cc.open("C:\\Users\\jakzi\\Documents\\CreditCardProcessor.txt", ios::in);
		for (int i = 0; i <= counter % 4; i++) {
			cc >> ccReturn;
		}
		cc.close();
		cout << ccReturn;
		counter++;
		if (ccReturn == "Declined.") {
			cout << "\nYour Card was declined by our processor." << endl;
		}
		else {
			cout << "\nYour card was processed successfully" << endl;
			q1.addOrder(d1);
			d1.saveReceipt();
		}
	}
	void payCash(DrinkOrder d1, OrderQueue q1) {
		double cashGiven;
		cout << "Enter Cash Amount: $";
		cin >> cashGiven;
		if (cashGiven < d1.getTotal()) {
			cout << "\nNot enough cash given, can not complete purchase.";
		}
		else {
			cout << "\nYour change will be $" << cashGiven - d1.getTotal() << endl;
			q1.addOrder(d1);
			d1.saveReceipt();
		}
	}
	void paymentScreen(DrinkOrder d1, OrderQueue q1) {
		d1.displayWholeOrder();
		cout << "The total for the order is $" << d1.getTotal() << endl;
		cout << "Did you want to pay with (1)Cash Or (2)Credit? Enter Selection: " << endl;
		int sel;
		cin >> sel;
		if (sel == 1) {
			payCash(d1, q1);			
		}
		if (sel == 2) {
			creditCheck(d1, q1);
		}

	}
	int counter = 0;
	string ccReturn;
};
class POSGUI {
public:
	void displayMenu(DrinkOrder d1) {
		cout << "\nMake a Selection for a drink" << endl;
		cout << "1. Espresso\t2. Americano\t 3. Latte\t4. Frappe\n";
	}
	void displaySplashScreen(DrinkOrder d1) {
		/*StandardDrinkOrder temp[10];
		for (int i = 0; i < 10; i++) {
			d1.drinkArray[i] = temp[i];
		}*/
		for (int i = 0; i < 5; i++) {
			cout << "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|" << endl;
		}
		cout << setw(9) << " " << "Welcome to Cafe au Lait" << endl;
		for (int i = 0; i < 5; i++) {
			cout << "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|" << endl;
		}
	}
private:
	string name;
};

int main()
{
	DrinkOrder d1;
	OrderQueue q1;
	Payment p1;
	POSGUI POS1;

	char blank;
	cin >> blank;

	POS1.displaySplashScreen(d1);
	cout << "Enter any character to Start order ";	

	char orderSel = 'y';
	for (int i = 0; i < 3; i++) {
		cout << "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|" << endl;
	}
	POS1.displayMenu(d1);
	while (d1.numDrinks < 10 && orderSel != 'n'){
		int drinkSel; //3
		cin >> drinkSel;
		StandardDrinkOrder beverage(drinkSel);
		d1.addDrink(beverage);
		cout << "Can I get you any more drinks? (y/n)";
		cin >> orderSel;
		POS1.displayMenu(d1);
	}
	for (int i = 0; i < 3; i++) {
		cout << "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|" << endl;
	}
	p1.paymentScreen(d1,q1);
