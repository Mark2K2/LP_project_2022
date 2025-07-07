#pragma once
#include "pch.h"


#include <algorithm>  
#include <list>
#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include "Common.h"



class GrafSolucio
{
public:
	GrafSolucio(bool dirigit);
	GrafSolucio(std::vector<Coordinate>& nodes, std::vector<std::vector<int>>& parellesNodes, bool dirigit);
	GrafSolucio(std::vector<Coordinate>& nodes, std::vector<std::vector<int>>& parellesNodes, std::vector<int>& pesos, bool dirigit);
	~GrafSolucio();
	int getNumNodes() { return m_numNodes; }

	void inserirAresta(int posNode1, int posNode2); //
	void inserirAresta(int posNode1, int posNode2, int pes); //
	void eliminarAresta(int posNode1, int posNode2); //

	void afegirNode(Coordinate node); //
	void eliminarNode(Coordinate node); //

	std::vector<std::vector<std::string>> cicles();
	int grauOutNode(Coordinate node);
	int grauInNode(Coordinate node);
	void camins(Coordinate node1, Coordinate node2, std::vector<std::list<std::string>>& camins);

	void mostra();

private:
	
	std::vector<std::list<std::pair<int, double>>> m_veins;
	std::vector<Coordinate> m_nodes;  //LOS NODOS QUE FORMAN EL GRAFO SON LAS COORDENADAS DE LOS CAMINOS
	int m_numNodes;
	int m_numArestes;
	bool m_dirigit;
};
