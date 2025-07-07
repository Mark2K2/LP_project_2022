#pragma once

#include "Common.h"
#include "PuntDeInteresBase.h"
#include "CamiBase.h"

class MapaBase {

private:
	// INDICA EL NUMERO D'ESTUDIANTS QUE FORMEN PART DEL TEU GRUP LP
	int m_numEstudiants = 0;

	// INDICA ELS NIUS DELS ESTUDIANTS QUE FORMEN EL GRUP
	std::string m_estudiantNIU_1 = "";
	std::string m_estudiantNIU_2 = "";
	std::string m_estudiantNIU_3 = "";

public:
	virtual void getPdis(std::vector<PuntDeInteresBase*>&) = 0;
	virtual void getCamins(std::vector<CamiBase*>&) = 0;
	virtual void parsejaXmlElements(std::vector<XmlElement>& xmlElements) = 0;

	virtual CamiBase* buscaCamiMesCurt(PuntDeInteresBase* desde, PuntDeInteresBase* a) = 0;

	int getNumEstudiants() {
		return this->m_numEstudiants;
	}

	std::vector<std::string> getNIUEstudiants() {
		return { m_estudiantNIU_1, m_estudiantNIU_2, m_estudiantNIU_3 };
	}
};



