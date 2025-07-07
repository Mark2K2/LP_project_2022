#pragma once
#include "PuntDeInteresBase.h"
#include "Common.h"
#include <vector>
#include "Util.h"

class CamiBase {
	public:
		virtual std::vector<Coordinate> getCamiCoords() = 0;
	private:
		
};


class CamiSolucio : public CamiBase {

	public: 
		std::vector<Coordinate> getCamiCoords();

	private:
		std::vector<std::string> m_ref;
		std::vector<XmlElement> m_nodes;
};
