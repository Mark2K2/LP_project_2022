#pragma once
#include "pch.h"
#include "Ball.h"
#include "GrafSolucio.h"
#include "Util.h"
#include "Common.h"
#include <list>
#include <vector>


class BallTree {

public:

	BallTree() {
		m_right = nullptr;
		m_left = nullptr;
		m_father = nullptr;
		m_data = {};
	}
	~BallTree();
	bool fulla(Ball* bola) const { if ((bola->getDreta() == nullptr) &&  (bola->getEsquerre() == nullptr) && (bola->getCoordenades().size() > 0)) return true; else return false; }
	//bool isEmpty() const { if (m_data.size() == 0) return true; else return false; }
	Ball* getRight() { return m_right; }
	Ball* getLeft() { return m_left; }
	Ball* getFather() { return m_father; }
	std::vector<Coordinate> getData() { return m_data; }
	void setLeft(Ball* esquerra) { m_left = esquerra; }
	void setRight(Ball* dreta) { m_right = dreta; }
	void setFather(Ball* pare) { m_father = pare; }
	void setData(std::vector<Coordinate> data) { m_data = data; }
	void construirArbreRec(Ball* fill);
	void inOrdreRec(std::vector<std::list<Coordinate>>& out, Ball* fill);
	void preOrdreRec(std::vector<std::list<Coordinate>>& out, Ball* fill);
	void postOrdreRec(std::vector<std::list<Coordinate>>& out, Ball* fill);


	void construirArbre(const std::vector<Coordinate>& datapoints);
	Ball* getArrel() { return m_arrel; }
	void inOrdre(std::vector<std::list<Coordinate>>& out);
	void postOrdre(std::vector<std::list<Coordinate>>& out);
	void preOrdre(std::vector<std::list<Coordinate>>& out);
	Coordinate nodeMesProper(Coordinate pdi, Coordinate& Q, Ball* bola);
	Coordinate nodeMesProperRec(Coordinate pdi, Coordinate& Q, Ball* bola);

private:

	Ball* m_right;
	Ball* m_left;
	Ball* m_father;
	Ball* m_arrel;
	std::vector<Coordinate> m_data;

};

