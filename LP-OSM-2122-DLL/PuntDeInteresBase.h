#pragma once

#include <string>
#include "Common.h"

class PuntDeInteresBase {
	public:		
		PuntDeInteresBase();
		PuntDeInteresBase(Coordinate coord, std::string name);

		virtual std::string getName();
		Coordinate getCoord();
		virtual unsigned int getColor();
	private:
		Coordinate m_coord;
		std::string m_name;

};

class PuntDeInteresRestaurantSolucio : public PuntDeInteresBase
{
	public:
		std::string getName();
		unsigned int getColor();

	private:
	std::string m_tipusCuina;
	bool m_mobilitat;

};

class PuntDeInteresBotigaSolucio : public PuntDeInteresBase
{
	public:
		std::string getName();
		unsigned int getColor();

	private:
	std::string m_tagShop;

};
