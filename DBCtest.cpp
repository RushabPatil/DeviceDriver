
/*
 * Sample code showing how to use Noam's simple call order enforce.
 *
 * Last edited: 2003-09-29 23:42:30
 */

#include "DBC_EnforceOrder.h"

/*
This class shows how to add the precondition rules to the function implementation.
The class contract requires the following:
1. Init() is the first function to call.
2. shutdown() is the last function to call. no calls to any function after this one.
3. foo() must be called immediatly before calling bar().
*/
class B
{
public:

    void Init()
	{
		Require(FirstCall); // NOTE: only here you must put the Require() before the Enter()
		Enter("Init");
	}
	
	void foo()
	{
		Enter("foo");
		Require(Called("Init"));
		Require(!Called("shutdown"));
		// do something here
	}	

    void shutdown()
	{// last call, but we don't check it here.
		Enter("shutdown");

		// if you want to be really firm:
		// AnounceDBC(LastCall)  -- but it is not implemented 
	}

	void bar()
	{
		Enter("bar"); // but you must say that you entered it anyhow!
		Require(Prev("foo"));
	}

	void ha()
	{
		Enter("ha");
		// deliberately forget to require other things here.
	}
private:
	DBC_Data; // add this macro to your data declaration section
};



// sample usage of a class with rules builtin.
void test1()
{
    B b;
	b.ha();  // ok, no rules on this, but a mine is triggered...
	b.Init(); // error: Init should be the first function called
    b.foo(); // if you comment the Init():  error: "Init() should be called before"
    b.shutdown();
    b.foo(); // error: "nothing should be called after shutdown"
}

void test2()
{
    B b;
	b.Init(); // ok: Init is the first function called
    b.foo();  // ok
	b.bar();  // ok
	b.bar();  // error: prev function should be foo()
    b.shutdown(); // ok
    b.shutdown(); // error, but not detected, since we don't check it within shutdown()
}

void test3()
{
    B b;
    b.foo(); // error: "Init() should be called before"
}

void main()
{
	test1();
	test2();
	test3();
}

// end of source.