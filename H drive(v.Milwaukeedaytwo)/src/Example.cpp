//-------------------------------
//
// use this as an example for making other files.
//
// For instance, someone may replace "Example" with Motor
//
//-------------------------------
//

class Example
{
	//include variables that are needed for multiple functions here. Most classes won't need many.
	int myVariable;

//Things in this public section can be seen and used by other files.
public:

	//When this file gets used, and someone makes an "Example" I want myVariable to be set to 0
	Example():
		myVariable(0)
	{
		//It will also run code I put here
		//Such as a printout
		cout << "'Example' object created" << endl;
	}

	//have example doSomething when this is called. and return a bool(true/false) if it succeded or not
	bool doSomething()
	{
		//Do some code here
		//I'm going to call my private helper function
		helperFunction();
		return true;
	}

//Things that get put here can't be used by other files/objects. We will use them inside of here as "helper" functions
private:

	//void means we don't 'return' (or give a value back)
	void helperFunction()
	{
		//Do some code here
	}
}
