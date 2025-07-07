#include "pch.h"
#include "GrafSolucio.h"
#include <iomanip>

struct ComparaPair
{
	ComparaPair(int val) : m_valor(val) {}
	bool operator()(const std::pair<int, double>& elem) const
	{
		return m_valor == elem.first;
	}
	bool operator==(const std::pair<int, double>& elem) const
	{
		return m_valor == elem.first;
	}
private:
	int m_valor;
};

GrafSolucio::GrafSolucio(bool dirigit)
{
	m_numNodes = 0;
	m_numArestes = 0;
	m_dirigit = dirigit;
}

GrafSolucio::GrafSolucio(std::vector<Coordinate>& nodes, std::vector<std::vector<int>>& parNodes, bool dirigit)
{
	m_numNodes = nodes.size();
	m_nodes.resize(m_numNodes);
	m_veins.resize(m_numNodes);
	m_dirigit = dirigit;
	m_numArestes = parNodes.size();

	for (int i = 0; i < m_numNodes; i++)
	{
		m_nodes[i] = nodes[i];
	}
	for (int j = 0; j < parNodes.size(); j++)
	{
		if ((parNodes[j][0] < m_numNodes) && (parNodes[j][1] < m_numNodes) &&
			(parNodes[j][0] >= 0) && (parNodes[j][1] >= 0))
		{
			m_veins[parNodes[j][0]].emplace_back(std::pair<int, double>(parNodes[j][1], 1));
			if (!dirigit)
			{
				m_veins[parNodes[j][1]].emplace_back(std::pair<int, double>(parNodes[j][0], 1));
			}
		}
	}
}
GrafSolucio::GrafSolucio(std::vector<Coordinate>& nodes, std::vector<std::vector<int>>& parNodes, std::vector<int>& pesos, bool dirigit)
{
	m_numNodes = nodes.size();
	m_nodes.resize(m_numNodes);
	m_veins.resize(m_numNodes);
	m_dirigit = dirigit;
	m_numArestes = parNodes.size();

	for (int i = 0; i < m_numNodes; i++)
	{
		m_nodes[i] = nodes[i];
	}
	for (int j = 0; j < parNodes.size(); j++)
	{
		if ((parNodes[j][0] < m_numNodes) && (parNodes[j][1] < m_numNodes) &&
			(parNodes[j][0] >= 0) && (parNodes[j][1] >= 0))
		{
			m_veins[parNodes[j][0]].emplace_back(std::pair<int, double>(parNodes[j][1], pesos[j]));
			if (!dirigit)
			{
				m_veins[parNodes[j][1]].emplace_back(std::pair<int, double>(parNodes[j][0], pesos[j]));
			}
		}
	}
}
GrafSolucio::~GrafSolucio()
{
}

void GrafSolucio::afegirNode(Coordinate node)
{
	m_nodes.push_back(node);
	m_numNodes++;
	m_veins.resize(m_numNodes);
}


void GrafSolucio::eliminarNode(Coordinate node)
{
	//busquem la posició del node a esborrar
	std::vector<Coordinate>::iterator it;
	std::vector<Coordinate>::iterator pos;
	Coordinate aux;
	for (it = m_nodes.begin(); it != m_nodes.end(); it++)
	{
		aux = (*it);
		if ((aux.lat == node.lat) && (aux.lon == node.lon))
		{
			pos = it;
		}
	}
	//it = find(m_nodes.begin(), m_nodes.end(), node);

	//mirem si node existeix
	if (pos != m_nodes.end())
	{
		//Obtenim index del node
		int nodeIndex = pos - m_nodes.begin();

		// eliminem el node del vector de nodes
		m_nodes.erase(pos);
		//Eliminem arestes desde el node
		m_veins.erase(m_veins.begin() + nodeIndex);
		//Eliminem arestes cap al node

		for (int i = 0; i < m_veins.size(); i++)
		{//eliminem cada aresta sense ponderar
			m_veins[i].remove_if(ComparaPair(nodeIndex));
		}
		m_numNodes--;
	}
}

void GrafSolucio::inserirAresta(int posNode1, int posNode2)
{
	if ((posNode1 < m_numNodes) && (posNode2 < m_numNodes) && (posNode1 >= 0) && (posNode2 >= 0))
	{
		m_veins[posNode1].emplace_back(std::pair<int, double>(posNode2, 1));
		if (!m_dirigit)
		{
			m_veins[posNode2].emplace_back(std::pair<int, double>(posNode1, 1));
		}
		m_numArestes++;
	}
}

void GrafSolucio::inserirAresta(int posNode1, int posNode2, int pes)
{
	if ((posNode1 < m_numNodes) && (posNode2 < m_numNodes) && (posNode1 >= 0) && (posNode2 >= 0))
	{
		m_veins[posNode1].emplace_back(std::pair<int, double>(posNode2, pes));
		if (!m_dirigit)
		{
			m_veins[posNode2].emplace_back(std::pair<int, double>(posNode1, pes));
		}
		m_numArestes++;
	}
}


void GrafSolucio::eliminarAresta(int posNode1, int posNode2)
{
	std::list<std::pair<int, double>>::iterator itAre = find_if(m_veins[posNode1].begin(), m_veins[posNode1].end(), ComparaPair(posNode2));
	if (itAre != m_veins[posNode1].end())
	{
		m_veins[posNode1].erase(itAre);
		m_numArestes--;
	}
	if (!m_dirigit)
	{
		itAre = find_if(m_veins[posNode2].begin(), m_veins[posNode2].end(), ComparaPair(posNode1));
		if (itAre != m_veins[posNode2].end())
		{
			m_veins[posNode2].erase(itAre);
		}
	}
}

/*
* 




std::vector<std::vector<std::string>> Graf::cicles()
{

}

int Graf::grauOutNode(std::string node)
{
}

int Graf::grauInNode(std::string node)
{
}


void Graf::camins(std::string node1, std::string node2, std::vector<std::list<std::string>>& camins)
{

}


void Graf::mostra()
{
	// imprimim el nom dels vèrtexs
	std::cout << "Graf: NUMNODES: " << m_numNodes << " ; NUMARESTES: " << m_numArestes << ":" << std::endl;
	std::cout << "=====NODES=====" << std::endl;
	for (int i = 0; i < m_numNodes; i++)
	{
		int espai = 20;
		if (i == 0) espai--;
		for (int dig = i; dig > 0; dig /= 10)
		{
			espai -= 1;
		}
		std::cout << i << ":" << std::setw(espai) << m_nodes[i] << " ";
		for (std::list<std::pair<int, int>>::iterator it = m_veins[i].begin(); it != m_veins[i].end(); it++)
		{
			std::cout << "-----> ( " << m_nodes[(*it).first] << "," << (*it).second << " )  ";
		}
		std::cout << std::endl;
	}
}*/