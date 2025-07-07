#pragma once

class MapaSolucio : public MapaBase {

	virtual void getPdis(std::vector<PuntDeInteresBase*>&) {

	}
	virtual void getCamins(std::vector<CamiBase*>&) {

	}

	virtual void parsejaXmlElements(std::vector<XmlElement>& xmlElements) {

	}

	virtual CamiBase* buscaCamiMesCurt(PuntDeInteresBase* desde, PuntDeInteresBase* a) {
		return nullptr;
	}


};
