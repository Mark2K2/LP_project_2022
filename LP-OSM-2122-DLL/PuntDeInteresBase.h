#pragma once

#include <string>
#include "Common.h"

class PuntDeInteresBase {

	protected:
		Coordinate m_coord;
		std::string m_name;

	public:		
		PuntDeInteresBase();
		PuntDeInteresBase(Coordinate coord, std::string name);

		virtual std::string getName();
		Coordinate getCoord();
		virtual unsigned int getColor();

};

class PuntDeInteresBotigaSolucio :public PuntDeInteresBase {

public:

	//PuntDeInteresBotigaSolucio();
	PuntDeInteresBotigaSolucio(Coordinate coord, std::string name, std::string tagShop, unsigned int color) { m_coord = coord, m_name = name, m_tagShop = tagShop, m_color = color; } //constructor parametros pdibs
	~PuntDeInteresBotigaSolucio() {};

	std::string getName() { return m_name; }
	Coordinate getCoord() { return m_coord; }
	unsigned int getColor() { return m_color; }


private:

	//Coordinate m_coord;
	//std::string m_name;
	std::string m_tagShop;
	unsigned int m_color;
};

class PuntDeInteresRestaurantSolucio :public PuntDeInteresBase {

public:

	//PuntDeInteresRestaurantSolucio();
	PuntDeInteresRestaurantSolucio(Coordinate coord, std::string name, std::string cuisine, unsigned int color, bool wheelchair) { m_coord = coord, m_name = name, m_cuisine = cuisine, m_color = color, m_wheelchair = wheelchair; } //constructor parametros pdirs
	~PuntDeInteresRestaurantSolucio() {};


	std::string getName() { return m_name; }
	Coordinate getCoord() { return m_coord; }
	unsigned int getColor() { return m_color; }


private:

	//Coordinate m_coord;
	//std::string m_name;
	std::string m_cuisine;
	unsigned int m_color;
	bool m_wheelchair;
};
