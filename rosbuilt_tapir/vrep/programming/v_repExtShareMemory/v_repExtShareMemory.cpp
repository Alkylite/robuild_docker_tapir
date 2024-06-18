/* Author : Ing. Diego Daniel Santiago. INAUT - CONICET */

#include "v_repExtShareMemory.h"
#include "access.h"
#include <iostream>
#include "v_repLib.h"


#ifdef _WIN32
	#include <shlwapi.h> // required for PathRemoveFileSpec function
	#define WIN_AFX_MANAGE_STATE AFX_MANAGE_STATE(AfxGetStaticModuleState())
#endif /* _WIN32 */
#if defined (__linux) || defined (__APPLE__)
	#define WIN_AFX_MANAGE_STATE
#endif /* __linux || __APPLE__ */

LIBRARY vrepLib; // the V-REP library that we will dynamically load and bind
#define PLUGIN_VERSION 1


void simExtShareMemoryOpen(SLuaCallBack* p)
{ 
	WIN_AFX_MANAGE_STATE

    // LUA prototype: "number result,number ID=simExtOpenShareMemory(string Name,int size)"
	int result=-1; // -1 means error
	int ID;
	
	if (p->inputArgCount>0){ // Ok, we have at least 1 input arguments : One for Memory Name
		if (p->inputArgTypeAndSize[0*2+0]==sim_lua_arg_string && strlen(p->inputChar)>2){ // Ok, we have and string and it has at least 3 characters
			if(CAccess::shareMemoryContainer->getFromName(p->inputChar)==NULL){//Check if the share memory already exist 
				if(p->inputArgCount>1 && p->inputArgTypeAndSize[1*2+0]>0){ //the size of the memory was specified
					shareMemory *newShareMemory=new shareMemory(p->inputChar,(p->inputInt[0])); //Create New Share Memory with custom size
					if(newShareMemory->openShareMemory()==true){
						ID=CAccess::shareMemoryContainer->insert(newShareMemory); //Store and Asign an ID	
						result=1;			
					}else simSetLastError("simExtShareMemoryOpen","Undable to Open Share Memory with custom size"); // output an error
				}else{//the size of the memory wasn't specified
					shareMemory *newShareMemory=new shareMemory(p->inputChar); //Create New Share Memory with default size
					if(newShareMemory->openShareMemory()==true){
						ID=CAccess::shareMemoryContainer->insert(newShareMemory); //Store and Asign an ID
						result=1;			
					}else simSetLastError("simExtShareMemoryOpen","Undable to Open Share Memory with default size"); // output an error
				}
			}else{
				simSetLastError("simExtShareMemoryOpen","Share Memory is Already Open"); // output an error
				ID=(CAccess::shareMemoryContainer->getFromName(p->inputChar))->getID();
				result=0; //It means that any error occurred, but the result is valid.
			}
		}else simSetLastError("simExtShareMemoryOpen","Wrong argument type/size."); // output an error
	}else simSetLastError("simExtShareMemoryOpen","Not enough arguments."); // output an error

	// Now we prepare the return value(s):

	p->outputArgCount=2; // 2 return values (function succeeded)

	p->outputArgTypeAndSize=(simInt*)simCreateBuffer(p->outputArgCount*2*sizeof(simInt)); // x return values takes x*2 simInt for the type and size buffer
	
	p->outputInt=(simInt*)simCreateBuffer(2*sizeof(int)); // 2 integer return value

	p->outputArgTypeAndSize[2*0+0]=sim_lua_arg_int;		// The first return value is an int
	p->outputArgTypeAndSize[2*0+1]=1;					// Not used (table size if the return value was a table)
	p->outputArgTypeAndSize[2*1+0]=sim_lua_arg_int;		// The second return value is a int
	p->outputArgTypeAndSize[2*1+1]=1;					// Not used (table size if the return value was a table)

	p->outputInt[0]=result; 
	if (result!=-1)
		p->outputInt[1]=ID; 
	else
		p->outputInt[1]=-1; 
}

void simExtShareMemoryClose(SLuaCallBack* p){ // Callback of the Lua simExtCloseShareMemory command
	WIN_AFX_MANAGE_STATE
	// LUA prototype: "number result=simExtShareMemoryClose(number ID)"
	//				  "number result=simExtShareMemoryClose()"

	int result=-1; // -1 means error
	if (p->inputArgCount>0){ //The Id from memory to close
		if ( (p->inputArgTypeAndSize[0]==(sim_lua_arg_int))){ //Find the share memory already exist 
			if(CAccess::shareMemoryContainer->getFromID(p->inputInt[0])!=NULL){
				CAccess::shareMemoryContainer->removeFromID(p->inputInt[0]);
				result=1;
			}else simSetLastError("simExtShareMemoryClose","Shared Memory does not exist or is already closed"); // output an error
		}else simSetLastError("simExtShareMemoryClose","Wrong argument type/size."); // output an error
	}else{ //no entry specified, close all shared memories
		CAccess::shareMemoryContainer->removeAll();
		result=1;
	}

	// Now we prepare the return value(s):

	p->outputArgCount=1; // 2 return values (function succeeded)

	p->outputArgTypeAndSize=(simInt*)simCreateBuffer(p->outputArgCount*2*sizeof(simInt)); // x return values takes x*2 simInt for the type and size buffer
	
	p->outputInt=(simInt*)simCreateBuffer(1*sizeof(int)); // 2 integer return value

	p->outputArgTypeAndSize[2*0+0]=sim_lua_arg_int;		// The first return value is an int
	p->outputArgTypeAndSize[2*0+1]=1;					// Not used (table size if the return value was a table)

	p->outputInt[0]=result; 
}

void simExtShareMemoryRead(SLuaCallBack* p){ 
	//LUA prototyoe: "number result,charbuff data=simExtShareMemoryRead(int ID)"

	WIN_AFX_MANAGE_STATE
	int result=-1; // -1 means error
	int size=0;

	//Prepare the return value(s):
	p->outputArgCount=2; // 2 return values (function succeeded)
	p->outputArgTypeAndSize=(simInt*)simCreateBuffer(p->outputArgCount*2*sizeof(simInt)); 
	p->outputArgTypeAndSize[2*0+0]=sim_lua_arg_int;		
	p->outputArgTypeAndSize[2*0+1]=1;					
	p->outputArgTypeAndSize[2*1+0]=sim_lua_arg_charbuff;	
	p->outputArgTypeAndSize[2*1+1]=0;
	p->outputInt=(simInt*)simCreateBuffer(1*sizeof(int)); 

	if (p->inputArgCount>0){ 
		if (p->inputArgTypeAndSize[0*2+0]==sim_lua_arg_int){
			shareMemory *theMemory=CAccess::shareMemoryContainer->getFromID(p->inputInt[0]);
			if(theMemory!=NULL){ //Check if the share memory exist 
				size=theMemory->getSize();
				p->outputArgTypeAndSize[2*1+1]=size; 
				p->outputCharBuff=(simChar*)simCreateBuffer(size);	
				if (theMemory->readShareMemory(p->outputCharBuff)==true){
					result=1;
				}else simSetLastError("simExtShareMemoryRead","Error reading data"); // output an error
			}else simSetLastError("simExtShareMemoryRead","Share Memory wasn't found"); // output an error
		}else simSetLastError("simExtShareMemoryRead","Wrong argument type/size."); // output an error
	}else simSetLastError("simExtShareMemoryRead","Not enough arguments."); // output an error
	
	p->outputInt[0]=result; 
}

void simExtShareMemoryWrite(SLuaCallBack* p){ // Callback of the Lua simExtWriteShareMemory command
	WIN_AFX_MANAGE_STATE
    //LUA prototype : "number result=simExtShareMemoryWrite(int Id,charbuff data)"
	int result=-1; // -1 means error
	int size;
	if (p->inputArgCount>1){ // Ok, we have at least 2 input arguments : One for Memory Id and One for Memory data
		if ((p->inputArgTypeAndSize[0*2+0]==(sim_lua_arg_int))&&(p->inputArgTypeAndSize[1*2+0]==sim_lua_arg_charbuff))
		{ //Check if the share memory already exist 
			size=p->inputArgTypeAndSize[1*2+1];
			shareMemory *theMemory=CAccess::shareMemoryContainer->getFromID(p->inputInt[0]);
			if(theMemory!=NULL){
				if(size>0 && size<=theMemory->getSize()){	
					if(theMemory->writeShareMemory(p->inputCharBuff,size)==true)
						result=1;
					else simSetLastError("simExtShareMemoryWrite","Shared memory was not written."); // output an error
				}else simSetLastError("simExtShareMemoryWrite","The data size is larger than the memory size or null"); // output an error
			}else simSetLastError("simExtShareMemoryWrite","Share Memory wasn't found"); // output an error
		}else simSetLastError("simExtShareMemoryWrite","Wrong argument type/size."); // output an error
	}else simSetLastError("simExtShareMemoryWrite","Not enough arguments."); // output an error

	// Now we prepare the return value(s):
	p->outputArgCount=1; // 1 return values (function succeeded)
	p->outputArgTypeAndSize=(simInt*)simCreateBuffer(p->outputArgCount*2*sizeof(simInt)); // x return values takes x*2 simInt for the type and size buffer	
	p->outputInt=(simInt*)simCreateBuffer(1*sizeof(int)); // 2 integer return value
	p->outputArgTypeAndSize[2*0+0]=sim_lua_arg_int;		// The first return value is an int
	p->outputArgTypeAndSize[2*0+1]=1;					// Not used (table size if the return value was a table)
	p->outputInt[0]=result; 
}

void simExtShareMemoryGetId(SLuaCallBack* p)
{ 
	//LUA prototype : "number result,number ID=simExtShareMemoryGetId(string Name)"
	WIN_AFX_MANAGE_STATE
	int result=-1; // -1 means error
	int ID;
	if (p->inputArgCount>0){  
		if ( (p->inputArgTypeAndSize[0]==(sim_lua_arg_string))){ //The memory Id
			shareMemory* theShareMemory=CAccess::shareMemoryContainer->getFromName(p->inputChar);
			if(theShareMemory!=NULL){//Check if the share memory already exist 
				ID=theShareMemory->getID(); //Store and Asign an ID
				result=1;
			}else simSetLastError("simExtShareMemoryGetId","Shared Memory was not found"); // output an error
		}else simSetLastError("simExtShareMemoryGetId","Wrong argument type/size."); // output an error
	}else simSetLastError("simExtShareMemoryGetId","Not enough arguments."); // output an error

	// Now we prepare the return value(s):

	p->outputArgCount=2; // 2 return values (function succeeded)

	p->outputArgTypeAndSize=(simInt*)simCreateBuffer(p->outputArgCount*2*sizeof(simInt)); // x return values takes x*2 simInt for the type and size buffer
	
	p->outputInt=(simInt*)simCreateBuffer(2*sizeof(int)); // 2 integer return value

	p->outputArgTypeAndSize[2*0+0]=sim_lua_arg_int;		// The first return value is an int
	p->outputArgTypeAndSize[2*0+1]=1;					// Not used (table size if the return value was a table)
	p->outputArgTypeAndSize[2*1+0]=sim_lua_arg_int;		// The second return value is a int
	p->outputArgTypeAndSize[2*1+1]=1;					// Not used (table size if the return value was a table)

	p->outputInt[0]=result; 
	if (result!=-1)
		p->outputInt[1]=ID; 
	else
		p->outputInt[1]=-1; 
}

void simExtShareMemoryGetName(SLuaCallBack* p){
	WIN_AFX_MANAGE_STATE
	//LUA prototyoe: "number result,string name=simExtShareMemoryGetName()"
	int result=-1; // -1 means error
	char *name;
	if (p->inputArgCount>0)	{ // Ok, we have at least 1 Memory Id 
		if ( (p->inputArgTypeAndSize[0]==(sim_lua_arg_int))){ 
			shareMemory* theShareMemory=CAccess::shareMemoryContainer->getFromID(p->inputInt[0]);
			if(theShareMemory!=NULL){//Check if the share memory already exist 
				name=theShareMemory->getName(); //Store and Asign an ID
				result=1;
			}else simSetLastError("simExtShareMemoryGetName","Shared Memory was not found"); // output an error
		}else simSetLastError("simExtShareMemoryGetName","Wrong argument type/size."); // output an error
	}else simSetLastError("simExtShareMemoryGetName","Not enough arguments."); // output an error

	// Now we prepare the return value(s):

	p->outputArgCount=2; // 2 return values (function succeeded)

	p->outputArgTypeAndSize=(simInt*)simCreateBuffer(p->outputArgCount*2*sizeof(simInt)); // x return values takes x*2 simInt for the type and size buffer
	
	p->outputInt=(simInt*)simCreateBuffer(sizeof(int)); // integer return value
	p->outputChar=(simChar*)simCreateBuffer((strlen(name)+1)); // integer return value

	p->outputArgTypeAndSize[2*0+0]=sim_lua_arg_int;		// The first return value is an int
	p->outputArgTypeAndSize[2*0+1]=1;					// Not used (table size if the return value was a table)
	
	p->outputArgTypeAndSize[2*1+0]=sim_lua_arg_string;	// The first return value is an int
	p->outputArgTypeAndSize[2*1+1]=1;					// Not used (table size if the return value was a table)

	p->outputInt[0]=result; 
	if (result!=-1){
		strcpy(p->outputChar,name); 
	}
}

void simExtShareMemoryList(SLuaCallBack* p){
	//LUA prototype: "table ID,table names,table sizes=simExtShareMemoryList()"
	char *stringOut=new char[200];
	int count=CAccess::shareMemoryContainer->getCount();
	shareMemory* theShareMemory;
	char *pt;
	p->outputArgCount=3; // 2 return values (function succeeded)
	p->outputArgTypeAndSize=(simInt*)simCreateBuffer(p->outputArgCount*2*sizeof(simInt)); // x return values takes x*2 simInt for the type and size buffer
	
	p->outputArgTypeAndSize[2*0+0]=sim_lua_arg_int|sim_lua_arg_table;			// The first return value is an int
	p->outputArgTypeAndSize[2*0+1]=count;					// table size
	p->outputArgTypeAndSize[2*1+0]=sim_lua_arg_string|sim_lua_arg_table;		// The second return value is a string
	p->outputArgTypeAndSize[2*1+1]=count;					// table size
	p->outputArgTypeAndSize[2*2+0]=sim_lua_arg_int|sim_lua_arg_table;			// The second return value is a int
	p->outputArgTypeAndSize[2*2+1]=count;					// table size

	p->outputInt =(simInt*) simCreateBuffer(2*count*sizeof(int)); // size for "Id" and "size" of memory
	p->outputChar=(simChar*)simCreateBuffer(30*count*sizeof(char)); // size for each name
	pt=p->outputChar;

	for(int i=0;i<count;i++){
		theShareMemory=CAccess::shareMemoryContainer->getFromIndex(i);
		p->outputInt[i]=theShareMemory->getID();
		strcpy(pt,theShareMemory->getName());
		pt+=strlen(theShareMemory->getName())+1;
		p->outputInt[i+count]=theShareMemory->getSize();
	}
}


void simExtEventCreate(SLuaCallBack* p){
	WIN_AFX_MANAGE_STATE

    // LUA prototype: "number result,number ID=simExtCreateEvent(string Name)"
	int result=-1; // -1 means error
	int ID;
	
	if (p->inputArgCount>0){ // Ok, we have at least 1 input arguments : One for Memory Name
		if (p->inputArgTypeAndSize[0*2+0]==sim_lua_arg_string && strlen(p->inputChar)>2){ // Ok, we have and string and it has at least 3 characters
			if(CAccess::eventContainer->getFromName(p->inputChar)==NULL){//Check if the share memory already exist 
				Cevent *newEvent=new Cevent(p->inputChar); //Create New Share Memory with custom size
				if(newEvent->create()==true){
					ID=CAccess::eventContainer->insert(newEvent); //Store and Asign an ID	
					result=1;			
				}else simSetLastError("simExtCreateEvent","Undable to Create the event"); // output an error
			}else{
				simSetLastError("simExtCreateEvent","Event already exist"); // output an error
				ID=(CAccess::eventContainer->getFromName(p->inputChar))->getID();
				result=0; //It means that any error occurred, but the result is valid.
			}
		}else simSetLastError("simExtCreateEvent","Wrong argument type/size."); // output an error
	}else simSetLastError("simExtCreateEvent","Not enough arguments."); // output an error

	// Now we prepare the return value(s):

	p->outputArgCount=2; // 2 return values (function succeeded)

	p->outputArgTypeAndSize=(simInt*)simCreateBuffer(p->outputArgCount*2*sizeof(simInt)); // x return values takes x*2 simInt for the type and size buffer
	
	p->outputInt=(simInt*)simCreateBuffer(2*sizeof(int)); // 2 integer return value

	p->outputArgTypeAndSize[2*0+0]=sim_lua_arg_int;		// The first return value is an int
	p->outputArgTypeAndSize[2*0+1]=1;					// Not used (table size if the return value was a table)
	p->outputArgTypeAndSize[2*1+0]=sim_lua_arg_int;		// The second return value is a int
	p->outputArgTypeAndSize[2*1+1]=1;					// Not used (table size if the return value was a table)

	p->outputInt[0]=result; 
	if (result!=-1)
		p->outputInt[1]=ID; 
	else
		p->outputInt[1]=-1; 
}

void simExtEventDelete(SLuaCallBack* p){
		WIN_AFX_MANAGE_STATE
	// LUA prototype: "number result=simExtDeleteEvent(number ID)"
	//				  "number result=simExtDeleteEvent()"

	int result=-1; // -1 means error
	if (p->inputArgCount>0){ //The Id of the event
		if ( (p->inputArgTypeAndSize[0]==(sim_lua_arg_int))){ //Find the share memory already exist 
			if(CAccess::eventContainer->getFromID(p->inputInt[0])!=NULL){
				CAccess::eventContainer->removeFromID(p->inputInt[0]);
				result=1;
			}else simSetLastError("simExtDeleteEvent","Event does not exist or is already closed"); // output an error
		}else simSetLastError("simExtDeleteEvent","Wrong argument type/size."); // output an error
	}else{ //no entry specified, close all events
		CAccess::eventContainer->closeAll();
		result=1;
	}

	// Now we prepare the return value(s):

	p->outputArgCount=1; // 2 return values (function succeeded)

	p->outputArgTypeAndSize=(simInt*)simCreateBuffer(p->outputArgCount*2*sizeof(simInt)); // x return values takes x*2 simInt for the type and size buffer
	
	p->outputInt=(simInt*)simCreateBuffer(1*sizeof(int)); // 2 integer return value

	p->outputArgTypeAndSize[2*0+0]=sim_lua_arg_int;		// The first return value is an int
	p->outputArgTypeAndSize[2*0+1]=1;					// Not used (table size if the return value was a table)

	p->outputInt[0]=result; 
}

void simExtEventSet	  (SLuaCallBack* p){
	WIN_AFX_MANAGE_STATE
    //LUA prototype : "number result=simExtSetEvent(int Id)"
	int result=-1; // -1 means error
	int size;
	if (p->inputArgCount>0){
		if (p->inputArgTypeAndSize[0*2+0]==sim_lua_arg_int)
		{
			Cevent *theEvent=CAccess::eventContainer->getFromID(p->inputInt[0]);
			if(theEvent!=NULL){
				if(theEvent->set()==true)
					result=1;
				else simSetLastError("simExtSetEvent","The event couldn't be set"); // output an error
			}else simSetLastError("simExtSetEvent","Event wasn't found"); // output an error
		}else simSetLastError("simExtSetEvent","Wrong argument type/size."); // output an error
	}else simSetLastError("simExtSetEvent","Not enough arguments."); // output an error

	// Now we prepare the return value(s):
	p->outputArgCount=1; // 1 return values (function succeeded)
	p->outputArgTypeAndSize=(simInt*)simCreateBuffer(p->outputArgCount*2*sizeof(simInt)); // x return values takes x*2 simInt for the type and size buffer	
	p->outputInt=(simInt*)simCreateBuffer(1*sizeof(int)); // 2 integer return value
	p->outputArgTypeAndSize[2*0+0]=sim_lua_arg_int;		// The first return value is an int
	p->outputArgTypeAndSize[2*0+1]=1;					// Not used (table size if the return value was a table)
	p->outputInt[0]=result; 
	printf("set\n");
}

void simExtEventReset (SLuaCallBack* p){
	WIN_AFX_MANAGE_STATE
    //LUA prototype : "number result=simExtResetEvent(int Id)"
	int result=-1; // -1 means error
	int size;
	if (p->inputArgCount>0){
		if (p->inputArgTypeAndSize[0*2+0]==sim_lua_arg_int){
			Cevent *theEvent=CAccess::eventContainer->getFromID(p->inputInt[0]);
			if(theEvent!=NULL){
				if(theEvent->reset()==true)
					result=1;
				else simSetLastError("simExtResetEvent","The event couldn't be reset"); // output an error
			}else simSetLastError("simExtResetEvent","Event wasn't found"); // output an error
		}else simSetLastError("simExtResetEvent","Wrong argument type/size."); // output an error
	}else simSetLastError("simExtResetEvent","Not enough arguments."); // output an error

	// Now we prepare the return value(s):
	p->outputArgCount=1; // 1 return values (function succeeded)
	p->outputArgTypeAndSize=(simInt*)simCreateBuffer(p->outputArgCount*2*sizeof(simInt)); // x return values takes x*2 simInt for the type and size buffer	
	p->outputInt=(simInt*)simCreateBuffer(1*sizeof(int)); // 2 integer return value
	p->outputArgTypeAndSize[2*0+0]=sim_lua_arg_int;		// The first return value is an int
	p->outputArgTypeAndSize[2*0+1]=1;					// Not used (table size if the return value was a table)
	p->outputInt[0]=result; 
	printf("reset\n");
}

void simExtEventWait(SLuaCallBack* p){
	//LUA prototyoe: "number result,charbuff data=simExtWaitForEvent(int ID,int time_ms)"
	//if time_ms=0 the function dont enter in wait state
	//if 0<time_ms<INFINITE the function waits time_ms milli seconds for the event to be signaled 
	//if time_ms=INFINITE the function will return only if event is signaled.
	
	WIN_AFX_MANAGE_STATE
		printf("\n simExtEventWait");
	int result=-1; // -1 means error
	int size=0;
	bool state = false;
	if (p->inputArgCount>0){ 
		if (p->inputArgTypeAndSize[0*2+0]==sim_lua_arg_int){
			Cevent *theEvent=CAccess::eventContainer->getFromID(p->inputInt[0]);
			if(theEvent!=NULL){
				if(p->inputArgCount>1 && p->inputArgTypeAndSize[1*2+0]==sim_lua_arg_int){
					state = theEvent->waitForEvent((DWORD)p->inputInt[1]);
				}else{
					state= theEvent->waitForEvent(600000); //wait 10 minutes
				}
			}else simSetLastError("simExtEventWait","Event not found"); // output an error
		}else simSetLastError("simExtEventWait","Wrong argument type/size."); // output an error
	}else simSetLastError("simExtEventWait","Not enough arguments."); // output an error
	
	//Prepare the return value(s):
	p->outputArgCount=2; // 2 return values (function succeeded)
	p->outputArgTypeAndSize=(simInt*)simCreateBuffer(p->outputArgCount*2*sizeof(simInt)); 
	p->outputArgTypeAndSize[2*0+0]=sim_lua_arg_int;		
	p->outputArgTypeAndSize[2*0+1]=1;					
	p->outputArgTypeAndSize[2*1+0]=sim_lua_arg_bool;	
	p->outputArgTypeAndSize[2*1+1]=1;
	p->outputInt=(simInt*)simCreateBuffer(1*sizeof(simInt)); 
	p->outputInt[0]=result; 
	p->outputBool=(simBool*)simCreateBuffer(1*sizeof(simBool)); 
	p->outputBool[0]=state; 
	printf("wait\n");
}

// This is the plugin start routine (called just once, just after the plugin was loaded):
VREP_DLLEXPORT unsigned char v_repStart(void* reservedPointer,int reservedInt)
{
	WIN_AFX_MANAGE_STATE
	// Dynamically load and bind V-REP functions:
	// ******************************************
	// 1. Figure out this plugin's directory:
	char curDirAndFile[1024];
#ifdef _WIN32
	GetModuleFileName(NULL,curDirAndFile,1023);
	PathRemoveFileSpec(curDirAndFile);
#elif defined (__linux) || defined (__APPLE__)
	getcwd(curDirAndFile, sizeof(curDirAndFile));
#endif
	std::string currentDirAndPath(curDirAndFile);
	// 2. Append the V-REP library's name:
	std::string temp(currentDirAndPath);
#ifdef _WIN32
	temp+="\\v_rep.dll";
#elif defined (__linux)
	temp+="/libv_rep.so";
#elif defined (__APPLE__)
	temp+="/libv_rep.dylib";
#endif /* __linux || __APPLE__ */
	// 3. Load the V-REP library:
	vrepLib=loadVrepLibrary(temp.c_str());
	if (vrepLib==NULL)
	{
		std::cout << "Error, could not find or correctly load the V-REP library. Cannot start 'PluginSkeleton' plugin.\n";
		return(0); // Means error, V-REP will unload this plugin
	}
	if (getVrepProcAddresses(vrepLib)==0)
	{
		std::cout << "Error, could not find all required functions in the V-REP library. Cannot start 'PluginSkeleton' plugin.\n";
		unloadVrepLibrary(vrepLib);
		return(0); // Means error, V-REP will unload this plugin
	}
	// ******************************************

	// Check the version of V-REP:
	// ******************************************
	int vrepVer;
	simGetIntegerParameter(sim_intparam_program_version,&vrepVer);
	if (vrepVer<20604) // if V-REP version is smaller than 2.06.04
	{
		std::cout << "Sorry, your V-REP copy is somewhat old. Cannot start 'PluginSkeleton' plugin.\n";
		unloadVrepLibrary(vrepLib);
		return(0); // Means error, V-REP will unload this plugin
	}
	// ******************************************

	// Here you could handle various initializations
	CAccess::createNonGui();

	// Here you could also register custom Lua functions or custom Lua constants

	//Input Arguments: 
	int inArgsNameSize[]={2,sim_lua_arg_string,sim_lua_arg_int}; // 2 input arguments: one string (The share memory name) AND one iteger (The share memory size)
	int inArgsId[]={1,sim_lua_arg_int}; // 1 input arguments:  one int (The share memory Id)
	int inArgsName[]={1,sim_lua_arg_string}; // 1 input argument: The share memory name
	int inArgsIdData[]={2,sim_lua_arg_int,sim_lua_arg_charbuff}; 
	int inArgsIdTime[]={2,sim_lua_arg_int,sim_lua_arg_int}; 
	int inArgsNil[]={0,sim_lua_arg_nil}; // 0 input argument
	// Register Share Memory Lua commands:
	
	simRegisterCustomLuaFunction("simExtShareMemoryOpen","number result,number ID=simExtOpenShareMemory(string Name,int size)",inArgsNameSize,simExtShareMemoryOpen);
	simRegisterCustomLuaFunction("simExtShareMemoryClose","number result=simExtShareMemoryClose(number ID)",inArgsId,simExtShareMemoryClose);
	simRegisterCustomLuaFunction("simExtShareMemoryRead","number result,charbuff data=simExtShareMemoryRead(int ID)",inArgsId,simExtShareMemoryRead);
	simRegisterCustomLuaFunction("simExtShareMemoryGetName","number result,string name=simExtShareMemoryGetName(int ID)",inArgsId,simExtShareMemoryGetName);
	simRegisterCustomLuaFunction("simExtShareMemoryWrite","number result=simExtShareMemoryWrite(int Id,charbuff data)",inArgsIdData,simExtShareMemoryWrite);
	simRegisterCustomLuaFunction("simExtShareMemoryGetId","number result,number ID=simExtShareMemoryGetId(string Name)",inArgsName,simExtShareMemoryGetId);
	simRegisterCustomLuaFunction("simExtShareMemoryList","table ID,table names,table sizes=simExtShareMemoryList()",inArgsNil,simExtShareMemoryList);
	
	//Register Event Lua Command
	simRegisterCustomLuaFunction("simExtEventCreate","number result,number ID=simExtEventCreate(string Name)",inArgsName,simExtEventCreate);
	simRegisterCustomLuaFunction("simExtEventDelete","number result=simExtEventDelete(number ID)",inArgsId,simExtEventDelete);
	simRegisterCustomLuaFunction("simExtEventSet","number result=simExtEventSet(int Id)",inArgsId,simExtEventSet);
	simRegisterCustomLuaFunction("simExtEventReset","number result=simExtEventReset(int Id)",inArgsId,simExtEventReset);
	simRegisterCustomLuaFunction("simExtEventWait","bool state=simExtEventWait(int Id, int time_ms)",inArgsIdTime,simExtEventWait);

	return(PLUGIN_VERSION); // initialization went fine, we return the version number of this plugin (can be queried with simGetModuleName)
}

// This is the plugin end routine (called just once, when V-REP is ending, i.e. releasing this plugin):
VREP_DLLEXPORT void v_repEnd()
{
	WIN_AFX_MANAGE_STATE
	// Here you could handle various clean-up tasks
	CAccess::destroyNonGui();
	
	unloadVrepLibrary(vrepLib); // release the library
}

// This is the plugin messaging routine (i.e. V-REP calls this function very often, with various messages):
VREP_DLLEXPORT void* v_repMessage(int message,int* auxiliaryData,void* customData,int* replyData)
{ // This is called quite often. Just watch out for messages/events you want to handle
	WIN_AFX_MANAGE_STATE
	// Keep following 5 lines at the beginning and unchanged:
	static bool refreshDlgFlag=true;
	int errorModeSaved;
	simGetIntegerParameter(sim_intparam_error_report_mode,&errorModeSaved);
	simSetIntegerParameter(sim_intparam_error_report_mode,sim_api_errormessage_ignore);
	void* retVal=NULL;

	// Here we can intercept many messages from V-REP (actually callbacks). Only the most important messages are listed here.
	// For a complete list of messages that you can intercept/react with, search for "sim_message_eventcallback"-type constants
	// in the V-REP user manual.

	if (message==sim_message_eventcallback_refreshdialogs)
		refreshDlgFlag=true; // V-REP dialogs were refreshed. Maybe a good idea to refresh this plugin's dialog too

	if (message==sim_message_eventcallback_menuitemselected)
	{ 
		/*#ifdef _WIN32 // only the Windows version has a dialog!
		if (auxiliaryData[0]==CAccess::shareMemoryDialog->dialogMenuItemHandle)
			CAccess::shareMemoryDialog->setVisible(!CAccess::shareMemoryDialog->getVisible()); // Toggle visibility of the dialog
