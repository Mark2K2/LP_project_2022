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

		virtual CamiBase* buscaCamiMesCurt(PuntDeInteresBase* desde, PuntDeInteresBase* a) = 0;
};

class MapaSolucio : public MapaBase {

public:

	MapaSolucio();
	~MapaSolucio();

	void getPdis(std::vector<PuntDeInteresBase*>& out_pdis) override;
	void getCamins(std::vector<CamiBase*>& out_camins) override;
	void parsejaXmlElements(std::vector<XmlElement>& xmlNode) override;
	CamiBase* buscaCamiMesCurt(PuntDeInteresBase* desde, PuntDeInteresBase* a) override;

private:
	std::vector<PuntDeInteresBase*> pdis;
	std::vector<CamiBase*> camins;
	std::vector<XmlElement> m_nodes;
	std::vector<XmlElement> m_camins;

};

