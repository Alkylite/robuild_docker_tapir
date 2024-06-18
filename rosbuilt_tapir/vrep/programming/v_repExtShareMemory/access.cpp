/* Author : Ing. Diego Daniel Santiago. INAUT - CONICET */
#include "access.h"
#include "v_repLib.h"

CShareMemoryContainer* CAccess::shareMemoryContainer=NULL;
CEventContainer* CAccess::eventContainer=NULL;

CAccess::CAccess()
{ // Fully static class
}

CAccess::~CAccess()
{ // Fully static class
}

void CAccess::createNonGui()
{ // Set-up of data structures:
	shareMemoryContainer=new CShareMemoryContainer();
	eventContainer=new CEventContainer();
}

void CAccess::destroyNonGui()
{ // Clean-up all non-GUI stuff
	delete shareMemoryContainer;
	shareMemoryContainer=NULL;
	delete eventContainer;
	eventContainer=NULL;
}


