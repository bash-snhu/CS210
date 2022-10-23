#include <Python.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>
#include <conio.h> 
#include <cstring>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

/* ======================
  Begin Custom Functions 
=========================*/

// Print Border for Menus
void printBorder() {
	cout << setfill('=') << setw(45) << "=" << endl;
}

// Verifies input and returns 0 if failed, 1 if successful
int takeInput(int& input) {
	cin >> input;

	// Verifies that cin has received a workable integer as input
	// If not, it breaks cin loop and prints an error
	if (cin.fail()) {
		cin.clear();
		cin.ignore();

		// Display error message
		printBorder();
		printf("\033[41mSorry, please try again.\nExpected input is a number: 1-4");
		printf("\033[0m\n");

		printBorder();
		return 0;
	}
	return 1;
}

// Print record of specific item
void printSearch(string choice, int freq) {
	cout << endl << " " << choice << " were purchased " << freq << " time(s) today." << endl << endl;
}

// Reads frequency.dat and prints histogram of daily sales
void printHistogram() {
	ifstream inFS;
	string itemName;
	int itemFreq;

	// Open frequency.dat
	inFS.open("frequency.dat");
	if (!inFS.is_open()) {
		printf("\033[41mSorry, frequency.dat could not be opened.");
		printf("\033[0m\n");
		return;
	}

	// Print header
	printBorder();
	cout << "           The Corner Grocer" << endl << "         Daily Sales Histogram" << endl;
	printBorder();

	// Loop through frequency.dat, printing each line as histogram
	while (inFS >> itemName >> itemFreq) {
		if (!inFS.fail()) {
			cout << right << setw(20) << setfill(' ') << itemName << " " << left << setw(itemFreq) << setfill('*') << '*' << endl;
		}
	}
	inFS.close();
}

int main() {
	// Create frequency.dat file of counts
	CallProcedure("cacheItems");

	// Menu Loop
	while (true) {
		int menuInput, check;
		string choice;

		// Print user menu
		printBorder();
		cout << "           The Corner Grocer" << endl;
		cout << "        Daily Sales Statistics" << endl;
		printBorder();
		cout << "1: Print Purchase Record" << endl;
		cout << "2: Print Specific Item Sales" << endl;
		cout << "3: Print Sales Histogram" << endl;
		cout << "4: Exit" << endl;
		printBorder();
		cout << "Enter your selection as a number 1-4:" << endl;

		// Input menu option and verify it
		check = takeInput(menuInput);
		if (check == 0) { continue; }

		/* ================================
			RESPOND TO USER'S MENU CHOICE
		===================================*/

		// Print dictionary of item purchases and frequencies
		if (menuInput == 1) {
			CallProcedure("printPurchases");
			cout << endl;
		}
		// Search for specific item and return sales frequency to C++
		else if (menuInput == 2) {
			int frequency = -1;

			cin.ignore();

			printBorder();
			cout << "Which item would you like to search for?" << endl;

			// Input choice
			getline(cin, choice);

			// If user choice is not empty, call python search function
			// Python checks if item actually in list
			if (choice != "") {
				frequency = callIntFunc("itemSearch", choice);
			}
			else {
				printf("\033[41mSorry, not a valid search.\n");
				printf("\033[0m");
				continue;
			}

			// If returned frequency is valid, print record of item
			if (frequency != -1) {
				printSearch(choice, frequency);
			}
		}
		// Print daily sales histogram
		else if (menuInput == 3) {
			printHistogram();
		}
		// Print goodbye and break loop to exit program
		else if (menuInput == 4) {
			cout << "Goodbye!" << endl;
			break;
		}
		// Print error message and continue loop
		else {
			printBorder();
			printf("\033[41mSorry, please try again.\nExpected input is a number: 1-4");
			printf("\033[0m\n");

			printBorder();
		}
	}
	return 0;
}