 
#ifdef WINDOWS
 extern "C" void __cdecl __Trace(const char * , ...);
 extern "C" void __cdecl __TraceL(int level, const char * format , ...); 

#else
 extern "C" void  __Trace(const char * , ...);
 extern "C" void  __TraceL(int level, const char * format , ...); 
#endif

#ifndef _dbgUtils_h
#define _dbgUtils_h


// this part compiles even if we are in AFX project.
#ifdef _DEBUG
	#define TRACEL __TraceL // use Noam's function
#else
	#define TRACEL 	1 ? (void)0 : __TraceL
#endif

// Trace level constants for TRACEL.
// These values are used in conjuction with the global gTraceLevelMin defined in _Trace.cpp
extern  int gTraceLevelMin;

extern bool gbTraceOutputToStdErr;

#define T_FullVerbose		0	// use for very detaild info
#define	T_Verbose			2	// use for detailed info
#define T_Info				4	// use for usual trace printing
#define T_Dbg				6	// use for debug messages
#define T_Warn				8	// 
#define T_Err				10

//{ noam 26-Nov-01
// this macro is define the same way for debug and release builds !!
#ifndef CheckPointer
#define CheckPointer(p, ret) {if((p)==NULL) return (ret);}
#endif //checkPointer
//}

//{
#ifdef VXWORKS
	#ifdef ASSERT_SUSP
	#include <vxWorks.h>
	#include <taskLib.h>
	//#include <windows.h>

	#ifdef assert
	#undef assert
	#endif

	#define assert(a)	 if(!(a))\
 	   {\
 	   int tId=taskIdSelf();\
 	   fdprintf(2, "Assertionn failed: %s ; task ID: 0x%x\n\
 	    file: "__FILE__", line: %d.  Task suspended\a\n",\
             #a, tId, __LINE__);\
  	  taskSuspend(tId);\
   	 }
	#else
	#include <assert.h>
	#endif	/* ASSERT_SUSP */
#endif // VXWORKS
//}


#ifndef _AFX_H
	#ifndef ASSERT // avoid redefinitions
	#ifdef _WIN32
		#include "crtdbg.h"
	#else
		// #include <assert.h>
		#define _ASSERT(e) assert(e)
		#define _ASSERTE(e) assert(e)
	#endif
		#ifdef _DEBUG
			#define ASSERT( e ) _ASSERTE( e )

			#define TRACE __Trace // use Noam's function

			#define TRACE1(f,a1)        __Trace(f,a1)
			#define TRACE2(f,a1,a2)     __Trace(f,a1,a2)
			#define TRACE3(f,a1,a2,a3)  __Trace(f,a1,a2,a3)
			#define VERIFY(f)	ASSERT( f )
			#define	ASSERT_VALID(pObj) (pObj)->AssertValid();


		#else // _DEBUG
			#define ASSERT( e ) 
			#define TRACE 	1 ? (void)0 : __Trace
			#define TRACE1(f,a1)        
			#define TRACE2(f,a1,a2)    
			#define TRACE3(f,a1,a2,a3)  
			#define VERIFY(f)          ((void)(f))
			#define	ASSERT_VALID(pObj) ((void)0)
		#endif // ifdef _DEBUG
	#endif // ifndef ASSERT
#endif // _dbgUtils_h
#endif // _AFX_H

