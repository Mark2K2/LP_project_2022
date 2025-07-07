// MODIFICA AQUEST FITXER AMB EL TEU  MAPA SOLUCIO
#include "pch.h"

#include "MapaSolucio.h"
#include "CamiBase.h"

MapaSolucio::MapaSolucio() {

}

MapaSolucio::~MapaSolucio()
{

	for (int i = 0; i < pdis.size(); i++)
	{
		delete[] pdis[i];
	}
	

}

void MapaSolucio::getPdis(std::vector<PuntDeInteresBase*>& result) {
	result = pdis;
}

void MapaSolucio::getCamins(std::vector<CamiBase*>& result) {
	result = camins;
}

void MapaSolucio::parsejaXmlElements(std::vector<XmlElement>& xmlElements) {

	

	pdis.clear();  //limpiar los vectores guardados anteriormente ya que pueden variar los datos al entrar en esta función, para que no se acumulen
	camins.clear();
	m_nodes.clear();
	m_camins.clear();
	
	//-------------------------------------------------------DIVIDIR TODOS LOS XMLELEMENTS EN CAMINOS Y NODOS-------------------------------------------
	for (int i = 0; i < xmlElements.size(); i++)
	{
		//dividir el vector entrante de xmlElements en dos vectores de nodos
		//y caminos para facilitarnos el trabajo
		if (xmlElements[i].id_element == "node")
			m_nodes.push_back(xmlElements[i]);
		if (xmlElements[i].id_element == "way")
			m_camins.push_back(xmlElements[i]);
	}
	//-------------------------------------------------------------------------------------------------------------------------------------------------

	//--------------------------------------------------------GUARDAR CAMINOS EN VECTOR DE CAMIBASE*-------------------------------------------------

	for (int i = 0; i < m_camins.size(); i++) //recorremos nuestro vector de xmlElements donde guardamos los caminos
	{
		std::vector <std::string> ref_nodes;
		std::vector<Coordinate> cordenadas_camino;
		std::string lat, lon;
		double lat_double, lon_double;
		std::pair<std::string, std::string> valor_node;
		bool trobat = false;

		ref_nodes.clear();
		cordenadas_camino.clear();
		for (int j = 0; j < m_camins[i].fills.size(); j++) // recorremos los hijos del camino 
		{
			if (m_camins[i].fills[j].first == "nd") //miramos que sea un nodo para saber la referencia y guardarla
			{
				std::pair<std::string, std::string> valor_node =
					Util::id_node(m_camins[i].fills[j].second);
				ref_nodes.push_back(valor_node.first);
			}
		}

		for (int j = 0; j < ref_nodes.size(); j++) //recorremos primero de 1 en 1 las referencias de los nodos de un camino
												   //y lo comparamos con todos los nodos de xmlElements del conjunto que sea
		{
			for (int k = 0; k < m_nodes.size(); k++) //recorremos todos los nodos del conjunto y los comparamos con una referencia
			{
				std::string id;
				//nos guardamos los atributos para usarlos mas adelante
				if (m_nodes[k].atributs[0].first == "changeset")
				{
					id = m_nodes[k].atributs[1].second;
					lat = m_nodes[k].atributs[2].second;
					lon = m_nodes[k].atributs[3].second;
				}
				else
				{
					id = m_nodes[k].atributs[0].second;
					lat = m_nodes[k].atributs[1].second;
					lon = m_nodes[k].atributs[2].second;
				}
				

				//si el id del nodo coindice con la referencia en la que stamos nos guardamos la latitud y longitud

				if (id == ref_nodes[j])
				{
					lat_double = stod(lat);
					lon_double = stod(lon);					//SI EL ID DE LA REFERENCIA COINCIDE CON EL ID DEL NODO, GUARDAMOS LAS COORDENADAS
					Coordinate cordenada;
					cordenada.lat = lat_double;
					cordenada.lon = lon_double;
					cordenadas_camino.push_back(cordenada);
					k = m_nodes.size();
				}				
			}
		}
		camins.push_back(new CamiSolucio(cordenadas_camino));
	}
	//-------------------------------------------------------------------------------------------------------------------------------------------

	//--------------------------------------------------GUARDAR PUNTS DINTERES EN PUNTS DE INTERES BASE*-------------------------------------------

	for (int i = 0; i < m_nodes.size(); i++) //recorremos los nodos ya que los pdis solo pueden ser nodos
	{
		std::string name, lat, lon, tagShop, cuisine;
		Coordinate cordenadas_nodo;
		unsigned int color = 0xEFD6AC;
		bool shop = false, restaurant = false;
		double lat_double, lon_double;
		bool wheelchair = false;
		std::string openingHours;


		
		//miramos solo los nodos que tengan algun hijo, porque solo esos pueden ser pdis
		if (m_nodes[i].fills.size() > 0)
		{
			//si tiene hijos, hay que buscar los tags "shop" y "cuisine" que determinan los dos tipos de puntos de interes que hay
			//si no tienen estos tags, no son puntos de interes aunque tengan hijos (TRAMPAS)
			if (m_nodes[i].atributs[0].first == "id") {
				lat = m_nodes[i].atributs[1].second;
				lon = m_nodes[i].atributs[2].second;
			}
			else
			{
				lat = m_nodes[i].atributs[2].second;
				lon = m_nodes[i].atributs[3].second;
			}
			

			for (int j = 0; j < m_nodes[i].fills.size(); j++)
			{
				if (m_nodes[i].fills[j].first == "tag") //recorremos todos los tags del nodo
				{
					// nos guardamos el valor de ese tag
					std::pair<std::string, std::string> valorTag =
						Util::kvDeTag(m_nodes[i].fills[j].second);
					if (valorTag.first == "shop") { shop = true; }			//miramos que sea shop o
					if (valorTag.first == "amenity") { restaurant = true; } //restarante para seguir mirando (antes cuisine)
					
				}
			}

			if (shop) //que hacemos si es tienda
			{
				//volvemos a recorres los hijos esta vez guardando todo lo que haga falta
				for (int j = 0; j < m_nodes[i].fills.size(); j++)
				{
					if(m_nodes[i].fills[j].first == "tag") { //miramos los tag 1 por 1 y nos guardamos el valor
						std::pair<std::string, std::string> valorTag =
							Util::kvDeTag(m_nodes[i].fills[j].second);

						//----------------GUARDAMOS LOS DIFERENTES VALORES DE LOS TAG DE LA TIENDA-------------------

						if (valorTag.first == "name") { name = valorTag.second; } //guardamos nombre
						if (valorTag.first == "shop") { tagShop = valorTag.second; } //guardamos tipo de tienda
						if (valorTag.first == "opening_hours") { openingHours = valorTag.second; }


						if (tagShop == "supermarket") { color = 0xA5BE00; } //guardamos tipo de color
						else {
							
							if (tagShop == "tobacco") { color = 0xFFAD69; }
							else {

								if (tagShop == "bakery") {
									
										if (wheelchair) color = 0x4CB944;
										if (openingHours == "Mo-Su,PH 06:00-22:00") color = 0xFFA500;
										color = 0xE85D75;
								}

								else { color = 0xEFD6AC; }
							}
						}

					}
				}

				//añadimos la lon y lat para hacer la coordenada del nodo
				lat_double = stod(lat);
				lon_double = stod(lon);
				cordenadas_nodo.lat = lat_double;
				cordenadas_nodo.lon = lon_double;
				if (name.size() > 1)
					pdis.push_back(new PuntDeInteresBotigaSolucio(cordenadas_nodo, name, tagShop, color));
			}
			if (restaurant) //que hacemos si es restaurante
			{
				//volvemos a recorres los hijos esta vez guardando todo lo que haga falta
				for (int j = 0; j < m_nodes[i].fills.size(); j++)
				{
					if (m_nodes[i].fills[j].first == "tag") { //miramos los tag 1 por 1 y nos guardamos el valor
						std::pair<std::string, std::string> valorTag =
							Util::kvDeTag(m_nodes[i].fills[j].second);

						//----------------GUARDAMOS LOS DIFERENTES VALORES DE LOS TAG DEL RESTAURANTE-------------------

						if (valorTag.first == "name") { name = valorTag.second; } //guardamos nombre
						if (valorTag.first == "cuisine") { cuisine = valorTag.second; } //guardamos tipo cocina
						if (valorTag.first == "wheelchair") 
						{ 
							if (valorTag.second == "yes") { wheelchair = true; }
						} //guardamos movilidad
					}
				}
				if (cuisine == "pizza" && wheelchair) { color = 0x03FCBA; } //guardamos tipo de color
				else {

					if (cuisine == "chinese") { color = 0xA6D9F7; }
					else {
						if (wheelchair) { color = 0x251351; }
						else {
							// se tiene que devolver el color por defecto, pero no dice cual es.
							color = 0xFFA500;
						}
					}
				}

				lat_double = stod(lat);
				lon_double = stod(lon);
				cordenadas_nodo.lat = lat_double;
				cordenadas_nodo.lon = lon_double;
				if (name.size() > 1)
					pdis.push_back(new PuntDeInteresRestaurantSolucio(cordenadas_nodo, name, cuisine, color, wheelchair));
			}
		}
	}



}

CamiBase* MapaSolucio::buscaCamiMesCurt(PuntDeInteresBase* desde, PuntDeInteresBase* a)
{
	CamiBase* cami = {};

	return cami;
}

