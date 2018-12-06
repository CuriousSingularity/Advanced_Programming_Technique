/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : main.cpp
* Author          : Bharath Ramachandraiah
* Description     : The entry file for the Navigation System Application.
*
****************************************************************************/

//System Include Files
#include <iostream>
#include <iomanip>

//Own Include Files
#include "CNavigationSystem.h"

//Namespaces
using namespace std;

//Macros
/**
 * main function:
 * An entry point to Navigation System Application.
 */
int main (void)
{
	cout << "Navigation System:" << endl << endl;

	// Set the precision to 6 decimal places
	cout << std::fixed << std::setprecision(6);

	CNavigationSystem navigationSystem;

	navigationSystem.run();

	return 0;
}
