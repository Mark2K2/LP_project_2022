#include "pch.h"
#include "MapaBase.h"
#include <vector>


void MapaSolucio::parsejaXmlElements(std::vector<XmlElement>& xmlElements)
{
	for (int i = 0; i < xmlElements.size(); i++)
	{
		if (xmlElements[i].id_element == "node")
			m_nodes.push_back(xmlElements[i]);
		if (xmlElements[i].id_element == "way")
			m_camins.push_back(xmlElements[i]);
	}
	for (int i = 0; i < m_nodes.size(); i++)
	{
		//pdis = &m_nodes[i];
	}
}

void MapaSolucio::getPdis(std::vector<PuntDeInteresBase*>&)
{

}
void MapaSolucio::getCamins(std::vector<CamiBase*>&)
{

}