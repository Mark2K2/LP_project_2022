#pragma once
#include "pch.h"

#include "Common.h"
#include "PuntDeInteresBase.h"
#include "CamiBase.h"


class MapaBase {

	public:
		virtual void getPdis(std::vector<PuntDeInteresBase*>&) = 0;
		virtual void getCamins(std::vector<CamiBase*>&) = 0;
		virtual void parsejaXmlElements(std::vector<XmlElement>& xmlElements) = 0;

};

class MapaSolucio : public MapaBase
{
	public:
		void getPdis(std::vector<PuntDeInteresBase*>&) = 0;
		void getCamins(std::vector<CamiBase*>&) = 0;
		void parsejaXmlElements(std::vector<XmlElement>& xmlElements) = 0;

	private:
		std::vector<PuntDeInteresBase*> pdis;
		std::vector<CamiBase*> camins;
		std::vector<XmlElement> m_nodes;
		std::vector<XmlElement> m_camins;
};

