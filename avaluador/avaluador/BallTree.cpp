#include "pch.h"
#include "BallTree.h"



void BallTree::construirArbre(const std::vector<Coordinate>& datapoints)
{
	std::vector<Coordinate> bola; //vector de coordenadas de los nodos de cada nodo en el que estamos trabajando
	std::vector<Coordinate> BolaIzq, BolaDreta; //vectores de coordenadas que irán a la bola derecha o izquierda
	Coordinate centre; //centro
	double max = 0.0; //distancia maxima desde los centros al nodo mas lejano
	int posicioA = 0, posicioB = 0; //indice del nodo que esta mas lejano del centro
	std::vector<double> distancia1, distancia2; //vector de las distancias desde el centro


	//NOS GUARDAMOS LOS DATOS ENTRANTES EN UN VECTOR
	bola.clear();
	for (int i = 0; i < datapoints.size(); i++) //nos guardamos todas las coordenadas que nos pasan
	{											//en un vector
		bola.push_back(datapoints[i]);
	}

	//SI EL ARBOL AUN NO ESTA CREADO, LO CREAMOS
	if (m_arrel == nullptr)
	{
		Ball* arrel = new Ball();
		arrel->setCoordenades(bola);
		arrel->setDreta(nullptr);
		arrel->setEsquerre(nullptr);
		centre = Util::calcularPuntCentral(bola);
		arrel->setPivot(centre);

		for (int i = 0; i < bola.size();i++)
		{
			m_data.push_back(bola[i]);
		}

		for (int i = 0; i < bola.size(); i++)
		{
			distancia1.push_back(Util::DistanciaHaversine(centre, bola[i]));
		}
		for (int i = 0; i < distancia1.size(); i++)
		{
			if (distancia1[i] > max)
			{
				max = distancia1[i]; //calculamos la posicion donde esta el nodo A (nodo más lejano al centro)
				posicioA = i; //posicion nodo A
			}
		}
		arrel->setRadius(distancia1[posicioA]);
		m_arrel = arrel;
		//construirArbre(m_arrel->getCoordenades());
	}

	//SI EL ARBOL YA ESTA CREADO, CREAMOS LAS DOS BOLAS LEFT Y RIGHT Y VOLVEMOS A LLAMAR A LA FUNCION
	distancia1.clear();
	distancia2.clear();
	for (int i = 0; i < bola.size(); i++)
	{
		centre = Util::calcularPuntCentral(bola);
		distancia1.push_back(Util::DistanciaHaversine(centre, bola[i])); //distancia del centro a todos los nodos
	}

	for (int i = 0; i < distancia1.size(); i++)
	{
		if (distancia1[i] > max)
		{
			max = distancia1[i]; //calculamos la posicion donde esta el nodo A (nodo más lejano al centro)
			posicioA = i; //posicion nodo A
		}
	}

	distancia1.clear();

	for (int i = 0; i < bola.size(); i++)
	{
		distancia1.push_back(Util::DistanciaHaversine(bola[posicioA], bola[i])); //distancia de todos los nodos al nodo A 
	}

	max = 0;

	for (int i = 0; i < distancia1.size(); i++)
	{
		if (distancia1[i] > max)
		{
			max = distancia1[i]; //distancia de A a B
			posicioB = i; //posicion del nodo B (nodo mas lejano al nodo A)
		}
	}

	distancia1.clear();
	distancia2.clear();
	for (int i = 0; i < bola.size(); i++)
	{
		//distancia del nodo[i] al nodo A
		distancia1.push_back(Util::DistanciaHaversine(bola[i], bola[posicioA]));
		//distancia del nodo[i] al nodo B
		distancia2.push_back(Util::DistanciaHaversine(bola[i], bola[posicioB]));

		if (distancia1[i] < distancia2[i]) //si la distancia al nodo B es mas grande que al nodo A lo guardamos en el Ball izq
		{
			//ASSIGNAR COORDENADES NODE-I A LA BOLA ESQUERRA
			BolaIzq.push_back(bola[i]);
		}
		else //sino en el Ball der
		{
			//ASSIGNAR COORDENADES NODE-I A LA BOLA DRETA
			BolaDreta.push_back(bola[i]);
		}
	}

	distancia1.clear();
	max = 0;


	if (BolaIzq.size() > 1)
	{
		Ball* fill_esquerre = new Ball();
		fill_esquerre->setCoordenades(BolaIzq);
		fill_esquerre->setDreta(nullptr);
		fill_esquerre->setEsquerre(nullptr);
		fill_esquerre->setPivot(Util::calcularPuntCentral(BolaIzq));

		for (int i = 0; i < BolaIzq.size(); i++)
		{
			distancia1.push_back(Util::DistanciaHaversine(fill_esquerre->getPivot(), BolaIzq[i]));
		}
		for (int i = 0; i < distancia1.size(); i++)
		{
			if (distancia1[i] > max)
			{
				max = distancia1[i]; //calculamos la posicion donde esta el nodo A (nodo más lejano al centro)
				posicioA = i; //posicion nodo A
			}
		}
		fill_esquerre->setRadius(distancia1[posicioA]);
		m_left = fill_esquerre;
		construirArbreRec(m_left);
	}
	else
	{
		Ball* fulla_esquerra = new Ball();
		fulla_esquerra->setCoordenades(BolaIzq);
		fulla_esquerra->setDreta(nullptr);
		fulla_esquerra->setEsquerre(nullptr);
		fulla_esquerra->setPivot(Util::calcularPuntCentral(BolaIzq));
		fulla_esquerra->setRadius(0);
		m_left = fulla_esquerra;
	}
	distancia1.clear();
	max = 0;
	if (BolaDreta.size() > 1)
	{
		Ball* fill_dret = new Ball();
		fill_dret->setCoordenades(BolaDreta);
		fill_dret->setDreta(nullptr);
		fill_dret->setEsquerre(nullptr);
		fill_dret->setPivot(Util::calcularPuntCentral(BolaDreta));
		for (int i = 0; i < BolaDreta.size(); i++)
		{
			distancia1.push_back(Util::DistanciaHaversine(fill_dret->getPivot(), BolaDreta[i]));
		}
		for (int i = 0; i < distancia1.size(); i++)
		{
			if (distancia1[i] > max)
			{
				max = distancia1[i]; //calculamos la posicion donde esta el nodo A (nodo más lejano al centro)
				posicioA = i; //posicion nodo A
			}
		}
		fill_dret->setRadius(distancia1[posicioA]);
		m_right = fill_dret;
		construirArbreRec(m_right);
	}
	else
	{
		Ball* fulla_dreta = new Ball();
		fulla_dreta->setCoordenades(BolaDreta);
		fulla_dreta->setDreta(nullptr);
		fulla_dreta->setEsquerre(nullptr);
		fulla_dreta->setPivot(Util::calcularPuntCentral(BolaDreta));
		fulla_dreta->setRadius(0);
		m_right = fulla_dreta;
	}
}

void BallTree::construirArbreRec(Ball* fill)
{
	std::vector<Coordinate> bola; //vector de coordenadas de los nodos de cada nodo en el que estamos trabajando
	std::vector<Coordinate> BolaIzq, BolaDreta; //vectores de coordenadas que irán a la bola derecha o izquierda
	Coordinate centre; //centro
	double max = 0.0; //distancia maxima desde los centros al nodo mas lejano
	int posicioA = 0, posicioB = 0; //indice del nodo que esta mas lejano del centro
	std::vector<double> distancia1, distancia2; //vector de las distancias desde el centro

	bola.clear();
	bola = fill->getCoordenades();

	distancia1.clear();
	distancia2.clear();


	for (int i = 0; i < bola.size(); i++)
	{
		//m_data.push_back(bola[i]);
		centre = Util::calcularPuntCentral(bola);
		distancia1.push_back(Util::DistanciaHaversine(centre, bola[i])); //distancia del centro a todos los nodos
	}

	for (int i = 0; i < distancia1.size(); i++)
	{
		if (distancia1[i] > max)
		{
			max = distancia1[i]; //calculamos la posicion donde esta el nodo A (nodo más lejano al centro)
			posicioA = i; //posicion nodo A
		}
	}

	distancia1.clear();

	for (int i = 0; i < bola.size(); i++)
	{
		distancia1.push_back(Util::DistanciaHaversine(bola[posicioA], bola[i])); //distancia de todos los nodos al nodo A 
	}

	max = 0;

	for (int i = 0; i < distancia1.size(); i++)
	{
		if (distancia1[i] > max)
		{
			max = distancia1[i]; //distancia de A a B
			posicioB = i; //posicion del nodo B (nodo mas lejano al nodo A)
		}
	}

	distancia1.clear();
	distancia2.clear();
	for (int i = 0; i < bola.size(); i++)
	{
		//distancia del nodo[i] al nodo A
		distancia1.push_back(Util::DistanciaHaversine(bola[i], bola[posicioA]));
		//distancia del nodo[i] al nodo B
		distancia2.push_back(Util::DistanciaHaversine(bola[i], bola[posicioB]));

		if (distancia1[i] < distancia2[i]) //si la distancia al nodo B es mas grande que al nodo A lo guardamos en el Ball izq
		{
			//ASSIGNAR COORDENADES NODE-I A LA BOLA ESQUERRA
			BolaIzq.push_back(bola[i]);
		}
		else //sino en el Ball der
		{
			//ASSIGNAR COORDENADES NODE-I A LA BOLA DRETA
			BolaDreta.push_back(bola[i]);
		}
	}

	if (BolaIzq.size() > 1)
	{
		Ball* fill_esquerre = new Ball();
		fill_esquerre->setCoordenades(BolaIzq);
		fill_esquerre->setDreta(nullptr);
		fill_esquerre->setEsquerre(nullptr);
		fill_esquerre->setPivot(Util::calcularPuntCentral(BolaIzq));
		for (int i = 0; i < BolaIzq.size(); i++)
		{
			distancia1.push_back(Util::DistanciaHaversine(fill_esquerre->getPivot(), BolaIzq[i]));
		}
		for (int i = 0; i < distancia1.size(); i++)
		{
			if (distancia1[i] > max)
			{
				max = distancia1[i]; //calculamos la posicion donde esta el nodo A (nodo más lejano al centro)
				posicioA = i; //posicion nodo A
			}
		}
		fill_esquerre->setRadius(distancia1[posicioA]);
		fill->setEsquerre(fill_esquerre);
		construirArbreRec(fill->getEsquerre());
	}
	else
	{
		Ball* fulla_esquerra = new Ball();
		fulla_esquerra->setCoordenades(BolaIzq);
		fulla_esquerra->setDreta(nullptr);
		fulla_esquerra->setEsquerre(nullptr);
		fulla_esquerra->setPivot(Util::calcularPuntCentral(BolaIzq));
		fulla_esquerra->setRadius(0);
		fill->setEsquerre(fulla_esquerra);
	}

	distancia1.clear();
	max = 0;
	if (BolaDreta.size() > 1)
	{
		Ball* fill_dret = new Ball();
		fill_dret->setCoordenades(BolaDreta);
		fill_dret->setDreta(nullptr);
		fill_dret->setEsquerre(nullptr);
		fill_dret->setPivot(Util::calcularPuntCentral(BolaDreta));
		for (int i = 0; i < BolaDreta.size(); i++)
		{
			distancia1.push_back(Util::DistanciaHaversine(fill_dret->getPivot(), BolaDreta[i]));
		}
		for (int i = 0; i < distancia1.size(); i++)
		{
			if (distancia1[i] > max)
			{
				max = distancia1[i]; //calculamos la posicion donde esta el nodo A (nodo más lejano al centro)
				posicioA = i; //posicion nodo A
			}
		}
		fill_dret->setRadius(distancia1[posicioA]);
		fill->setDreta(fill_dret);
		construirArbreRec(fill->getDreta());
	}
	else
	{
		Ball* fulla_dreta = new Ball();
		fulla_dreta->setCoordenades(BolaDreta);
		fulla_dreta->setDreta(nullptr);
		fulla_dreta->setEsquerre(nullptr);
		fulla_dreta->setPivot(Util::calcularPuntCentral(BolaDreta));
		fulla_dreta->setRadius(0);
		fill->setDreta(fulla_dreta);
	}

}

void BallTree::inOrdre(std::vector<std::list<Coordinate>>& out)
{
	std::list<Coordinate> lista;
	std::vector<Coordinate> nodos;

	if (m_data.size() != 0)
	{
		if (m_left->getCoordenades().size() > 1)
		{
			BallTree::inOrdreRec(out, m_left);
		}
		else
		{
			nodos = m_left->getCoordenades();
			lista.push_back(nodos[0]);
			out.push_back(lista);
		}
		
		nodos = m_arrel->getCoordenades();
		for (int i = 0; i < nodos.size(); i++)
		{
			lista.push_back(nodos[i]);
		}
		out.push_back(lista);
		nodos.clear();
		lista.clear();

		if (m_right->getCoordenades().size() > 1)
		{
			BallTree::inOrdreRec(out, m_right);
		}
		else
		{
			nodos = m_right->getCoordenades();
			lista.push_back(nodos[0]);
			out.push_back(lista);
		}
	}
}

void BallTree::postOrdre(std::vector<std::list<Coordinate>>& out)
{
	std::list<Coordinate> lista;
	std::vector<Coordinate> nodos;

	if (m_data.size() != 0)
	{
		if (m_left->getCoordenades().size() > 1)
		{
			BallTree::postOrdreRec(out, m_left);
		}
		else
		{
			nodos = m_left->getCoordenades();
			lista.push_back(nodos[0]);
			out.push_back(lista);
		}

		if (m_right->getCoordenades().size() > 1)
		{
			BallTree::postOrdreRec(out, m_right);
		}
		else
		{
			nodos = m_right->getCoordenades();
			lista.push_back(nodos[0]);
			out.push_back(lista);
		}

		nodos.clear();
		lista.clear();
		nodos = m_arrel->getCoordenades();
		for (int i = 0; i < nodos.size(); i++)
		{
			lista.push_back(nodos[i]);
		}
		out.push_back(lista);
		
	}
	
}

void BallTree::preOrdre(std::vector<std::list<Coordinate>>& out)
{
	std::list<Coordinate> lista;
	std::vector<Coordinate> nodos;

	nodos = m_arrel->getCoordenades();
	for (int i = 0; i < nodos.size(); i++)
	{
		lista.push_back(nodos[i]);
	}
	out.push_back(lista);
	nodos.clear();
	lista.clear();

	if (m_data.size() != 0)
	{
		if (m_left->getCoordenades().size() > 1)
		{
			BallTree::preOrdreRec(out, m_left);
		}
		else
		{
			nodos = m_left->getCoordenades();
			lista.push_back(nodos[0]);
			out.push_back(lista);
		}
		nodos.clear();
		lista.clear();

		if (m_right->getCoordenades().size() > 1)
		{
			BallTree::preOrdreRec(out, m_right);
		}
		else
		{
			nodos = m_right->getCoordenades();
			lista.push_back(nodos[0]);
			out.push_back(lista);
		}
	}
}

void BallTree::inOrdreRec(std::vector<std::list<Coordinate>>& out, Ball* fill)
{
	std::list<Coordinate> lista;
	std::vector<Coordinate> nodos;
	Ball* izq = new Ball;
	Ball* der = new Ball;

	izq = (fill->getEsquerre());
	der = (fill->getDreta());

	if (izq->getCoordenades().size() > 1)
	{
		BallTree::inOrdreRec(out, izq);
	}
	else
	{
		nodos = izq->getCoordenades();
		lista.push_back(nodos[0]);
		out.push_back(lista);
	}
	nodos.clear();
	lista.clear();

	nodos = fill->getCoordenades();
	for (int i = 0; i < nodos.size(); i++)
	{
		lista.push_back(nodos[i]);
	}
	out.push_back(lista);

	nodos.clear();
	lista.clear();

	if (der->getCoordenades().size() > 1)
	{
		BallTree::inOrdreRec(out, der);
	}
	else
	{
		nodos = der->getCoordenades();
		lista.push_back(nodos[0]);
		out.push_back(lista);
	}
}

void BallTree::preOrdreRec(std::vector<std::list<Coordinate>>& out, Ball* fill)
{
	std::list<Coordinate> lista;
	std::vector<Coordinate> nodos;
	Ball* izq = new Ball;
	Ball* der = new Ball;

	nodos = fill->getCoordenades();
	for (int i = 0; i < nodos.size(); i++)
	{
		lista.push_back(nodos[i]);
	}
	out.push_back(lista);
	nodos.clear();
	lista.clear();

	izq = (fill->getEsquerre());
	der = (fill->getDreta());

	if (izq->getCoordenades().size() > 1)
	{
		BallTree::inOrdreRec(out, izq);
	}
	else
	{
		nodos = izq->getCoordenades();
		lista.push_back(nodos[0]);
		out.push_back(lista);
	}

	nodos.clear();
	lista.clear();

	if (der->getCoordenades().size() > 1)
	{
		BallTree::inOrdreRec(out, der);
	}
	else
	{
		nodos = der->getCoordenades();
		lista.push_back(nodos[0]);
		out.push_back(lista);
	}
}

void BallTree::postOrdreRec(std::vector<std::list<Coordinate>>& out, Ball* fill)
{
	std::list<Coordinate> lista;
	std::vector<Coordinate> nodos;
	Ball* izq = new Ball;
	Ball* der = new Ball;

	izq = (fill->getEsquerre());
	der = (fill->getDreta());

	if (izq->getCoordenades().size() > 1)
	{
		BallTree::inOrdreRec(out, izq);
	}
	else
	{
		nodos = izq->getCoordenades();
		lista.push_back(nodos[0]);
		out.push_back(lista);
	}
	nodos.clear();
	lista.clear();

	if (der->getCoordenades().size() > 1)
	{
		BallTree::inOrdreRec(out, der);
	}
	else
	{
		nodos = der->getCoordenades();
		lista.push_back(nodos[0]);
		out.push_back(lista);
	}

	nodos.clear();
	lista.clear();

	nodos = fill->getCoordenades();
	for (int i = 0; i < nodos.size(); i++)
	{
		lista.push_back(nodos[i]);
	}
	out.push_back(lista);
}

Coordinate BallTree::nodeMesProper(Coordinate pdi, Coordinate& Q, Ball* bola)
{
	double distancia1 = 0.0, distancia2 = 0.0;
	double min = 10000;
	int index = 0;
	std::vector<double> distancies;
	std::vector<Coordinate> nodes;
	Coordinate centre;
	Ball* aux = new Ball;
	Ball* esq = new Ball;
	Ball* dret = new Ball;
	aux = bola;

	nodes = aux->getCoordenades();
	centre = Util::calcularPuntCentral(nodes);
	distancia1 = Util::DistanciaHaversine(centre, pdi);

	for (int i = 0; i < nodes.size(); i++)
	{
		distancies.push_back(Util::DistanciaHaversine(nodes[i], pdi));
	}

	for (int i = 0; i < distancies.size(); i++)
	{
		if (distancies[i] < min)
		{
			min = distancies[i];
			index = i;
		}
	}

	Q.lat = nodes[index].lat;
	Q.lon = nodes[index].lon;

	distancia2 = Util::DistanciaHaversine(centre, Q);

	if ((distancia1 - bola->getRadi()) > distancia2)
	{
		return Q;
	}

	if (BallTree::fulla(bola) == true)
	{
		return Q;
	}
	else
	{
		esq = bola->getEsquerre();
		dret = bola->getDreta();

		distancia1 = Util::DistanciaHaversine(esq->getPivot(), pdi);
		distancia2 = Util::DistanciaHaversine(dret->getPivot(), pdi);

		if (distancia2 < distancia1)
		{
			BallTree::nodeMesProperRec(pdi, Q, esq);
		}
		else
		{
			BallTree::nodeMesProperRec(pdi, Q, dret);
		}

		return Q;

	}
}

Coordinate BallTree::nodeMesProperRec(Coordinate pdi, Coordinate& Q, Ball* bola)
{
	double distancia1 = 0.0, distancia2 = 0.0;
	double min = 10000;
	int index = 0;
	std::vector<double> distancies;
	std::vector<Coordinate> nodes;
	Coordinate centre;
	Ball* esq;
	Ball* dret;


	nodes = bola->getCoordenades();
	centre = Util::calcularPuntCentral(nodes);
	distancia1 = Util::DistanciaHaversine(centre, pdi);

	for (int i = 0; i < nodes.size(); i++)
	{
		distancies.push_back(Util::DistanciaHaversine(nodes[i], pdi));
	}

	for (int i = 0; i < distancies.size(); i++)
	{
		if (distancies[i] < min)
		{
			min = distancies[i];
			index = i;
		}
	}

	Q.lat = nodes[index].lat;
	Q.lon = nodes[index].lon;

	distancia2 = Util::DistanciaHaversine(centre, Q);

	if ((distancia1 - bola->getRadi()) > distancia2)
	{
		return Q;
	}

	if (BallTree::fulla(bola) == true)
	{
		return Q;
	}
	else
	{
		esq = bola->getEsquerre();
		dret = bola->getDreta();

		distancia1 = Util::DistanciaHaversine(esq->getPivot(), pdi);
		distancia2 = Util::DistanciaHaversine(dret->getPivot(), pdi);

		if (distancia2 < distancia1)
		{
			BallTree::nodeMesProperRec(pdi, Q, esq);
		}
		else
		{
			BallTree::nodeMesProperRec(pdi, Q, dret);
		}

		return Q;

	}
}