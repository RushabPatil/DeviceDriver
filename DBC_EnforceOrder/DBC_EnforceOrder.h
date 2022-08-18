/*
 
Enforcing function call order (in C++)

  When declaring an interface, there is a need to define the allowed calling order of functions.
  For example, Init() must be called before any other function, and nothing should be called after Shutdown().

  In the spirit of Design By Contract, I wrote this tiny class + macros to make such rules enforceable in runtime.

  see also:
  http://www.codeproject.com/debug/debuggingtestingmadeeasy.asp

  This code was tested on VC 6 and should work on any C++ compiler

  Drawbacks:
  - In every function (of interest) you must add ' Enter("function_name"). In another article I wrote, there is a way around it 
  using symbol table engine lookup - but this complicates the code enormously.

  - I could add special rules such as LAST_FUNCTION, and then check for this status in the Enter() call. I chose not to do it
    for the tradeoff between simplicity and elegance.

  Future additions:
  - So far, only REQUIRE (i.e. precondition) is implemented. It would be nice to add ENSURE for 
  postcondition checking as well.
  - call STACK_TRACE() from Enter() to have the full monti


  NOTE: current version in NOT multi thread safe. This means that when accessing a single object
  from more than one thread, either upgrade CallStates class to be MT safe, or call the macros
  only after you entered a critical section (or whatever is the case).

Sample usage:
//
// This class shows how to add the precondition rules to the function implementation.
class B
{
public:
    void Init()
	{
		Require(FirstCall); // must be BEFORE Enter() !
		Enter("Init");
	}
	void foo()
	{
		Enter("foo");
		Require(Called("Init"));
		Require(!Called("shutdown"));
		// do something here
	}	
}; // class B
	
------------------------------------------------------------------------	
	
  For comments / suggestion etc. : mailto: noam at bitBand dot com
  //noam 2003-09-25 17:30:57

 */


// uncomment the next line to enable the macros. 
#define  _EnforceCallOrder

#ifndef _DEBUG
#pragma message(">>>>>>>>>>>>>>>>>>>>>>>>> WARNING!: debug code enabled in RELEASE build!")
#endif

//{{ start DBC section
#ifndef _DCB_enforce
#define _DCB_enforce

#pragma warning(disable:4786)
#include <set>
#include "DbgUtils.h" // my implementation of ASSERT. use your own here.

class CallStates
{
public:
	CallStates() : _pseudoPrev(0){};
	
	void Enter(const char* s)
	{
		// add to the set of already called functions
		_called.insert(s);
		// remember who was called, for the next function call...
		// I use the _pseudo to allow for convenient order of:
		// C::f(){
		//     Enter("f");
		//     Require(Prev("g"));
		//     ...
		//}
		_prevFuncCalled = _pseudoPrev;
		_pseudoPrev = s;
	}

	// return true if 'name' was ever called.
	bool Called(const char* name)
	{
		return _called.find(name) != _called.end();
	}

	// return true if nobody was called till now.
	// Call this function BEFORE calling Enter() !!
	bool FirstCall()
	{
		return _called.empty();
	}

	// return true if previous function called is 'name' (most recent call before current test)
	bool Prev(const char* name)
	{
		return (_prevFuncCalled != NULL) && (0 == strcmp(name, _prevFuncCalled));
	}
	
protected:
	std::set<const char*>	_called;
	const char* _prevFuncCalled, *_pseudoPrev;
};

#ifdef _EnforceCallOrder

#define Enter(s) _states.Enter(s)
#define Called(s) _states.Called(s)
#define FirstCall _states.FirstCall()
#define Prev(s)	_states.Prev(s)

#define Require(cond) _ASSERTE(cond)

#define DBC_Data CallStates	_states

#else // null declarations.

#define Enter(s) 
#define Called(s) 
#define FirstCall
#define Require(cond) 
#define Prev(s)
#define DBC_Data 
#endif

#endif // _EnforceCallOrder
// end DBC section }}
