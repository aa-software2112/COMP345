/*
 * main.cpp
 *
 *  Created on: Sep. 23, 2018
 *      Author: Anthony Andreoli
 */
#include <iostream>

#include "MapLoader.h"

int main()
{

	MapLoader p;

	p.mapLoader_LoadMap("C:/Users/Anthony Andreoli/Desktop/Concordia/2018 - FALL/COMP 345/REPOSITORY/COMP345/RiskApplication/MapFiles/World.map");

	//p.mapLoader_LoadMap("C:/Users/Anthony Andreoli/Desktop/Concordia/2018 - FALL/COMP 345/REPOSITORY/COMP345/RiskApplication/MapFiles/WorldMissingMap.map");


	std::cout << "IN MAIN" << std::endl;


	return 0;
}



