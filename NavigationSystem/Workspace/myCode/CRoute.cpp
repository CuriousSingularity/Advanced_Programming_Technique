#include "CRoute.h"
#include "CWaypoint.h"
#include "CPOI.h"
#include "CPoiDatabase.h"

/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CROUTE.CPP
* Author          :
* Description     :
*
*
****************************************************************************/


//System Include Files


//Own Include Files

//Method Implementations

void CRoute::operation1(){}
CRoute::CRoute(unsigned int maxWp, unsigned int maxPoi){}
CRoute::CRoute(int origin){}
CRoute::CRoute(CRoute& origin){}
CRoute::~CRoute(){}
void CRoute::connectToPoiDatabase(CPoiDatabase* pPoiDB){}
void CRoute::addWaypoint(CWaypoint& wp){}
void CRoute::addPoi(string namePoi){}
double CRoute::getDistanceNextPoi(int wp, CPOI& poi){}
void CRoute::print(){}
