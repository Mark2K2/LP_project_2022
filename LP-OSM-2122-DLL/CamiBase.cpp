#include "pch.h"
#include "CamiBase.h"
#include <vector>
using namespace std;


XmlElement camiBotiga = {
	// id_element =
	"way",
	// atributs =
	{
	make_pair("id", "31889094"),
	make_pair("visible", "true"),
	make_pair("version", "6"),
	make_pair("changeset", "1002251634"),
	make_pair("timestamp", "2021 - 04 - 03T21:17 : 17Z"),
	make_pair("user", "Interswd"),
	make_pair("uid", "3414856")
	},
	// fills =
	{
	make_pair<string, vector<pair<string, string>>>
	("nd", {make_pair("ref", "357125056")}),
	make_pair< string, vector<pair<string, string>>>
	("nd", {make_pair("ref", "8591278795")}),
	make_pair< string, vector<pair<string, string>>>
	("nd", {make_pair("ref", "357124693")}),
	make_pair< string, vector<pair<string, string>>>
	("nd", {make_pair("ref", "357125054")}),
	
	}
};

XmlElement Nodo1 = {
	//id_element =
	"node",
	// atributs =
	{
	make_pair("id", "357125056"),
	make_pair("visible", "true"),
	make_pair("version", "3"),
	make_pair("changeset", "77532251"),
	make_pair("timestamp", "2019-11-25T15:26:03Z"),
	make_pair("user", "MultiDavid2001b"),
	make_pair("uid", "4946691"),
	make_pair("lat", "41.4928803"),
	make_pair("lon", "2.1452381"),
	},
	
};

XmlElement Nodo2 = {
	//id_element =
	"node",
	// atributs =
	{
	make_pair("id", "8591278795"),
	make_pair("visible", "true"),
	make_pair("version", "3"),
	make_pair("changeset", "77532251"),
	make_pair("timestamp", "2019-11-25T15:26:03Z"),
	make_pair("user", "MultiDavid2001b"),
	make_pair("uid", "4946691"),
	make_pair("lat", "41.4929072"),
	make_pair("lon", "2.1452474")
	},
	
};

XmlElement Nodo3 = {
	//id_element =
	"node",
	// atributs =
	{
	make_pair("id", "357124693"),
	make_pair("visible", "true"),
	make_pair("version", "3"),
	make_pair("changeset", "77532251"),
	make_pair("timestamp", "2019-11-25T15:26:03Z"),
	make_pair("user", "MultiDavid2001b"),
	make_pair("uid", "4946691"),
	make_pair("lat", "41.4933070"),
	make_pair("lon", "2.1453852")
	},
	
};

XmlElement Nodo4 = {
	//id_element =
	"node",
	// atributs =
	{
	make_pair("id", "357125054"),
	make_pair("visible", "true"),
	make_pair("version", "3"),
	make_pair("changeset", "77532251"),
	make_pair("timestamp", "2019-11-25T15:26:03Z"),
	make_pair("user", "MultiDavid2001b"),
	make_pair("uid", "4946691"),
	make_pair("lat", "41.4939882"),
	make_pair("lon", "2.1456419")
	},
	
};





std::vector<Coordinate> CamiSolucio::getCamiCoords()
{
	m_nodes.push_back(Nodo1);
	m_nodes.push_back(Nodo2);
	m_nodes.push_back(Nodo3);
	m_nodes.push_back(Nodo4);

	std::vector<Coordinate> cordenadas_camino;
	bool trobat = false;
	std::string lat, lon;
	double lat_double, lon_double;
	std::pair<std::string, std::string> valor_node;
	if (camiBotiga.id_element == "way") //miramos si es un camino
	{
		for (int i = 0; i < camiBotiga.fills.size(); i++) // recorremos los hijos del camino 
		{
			if (camiBotiga.fills[i].first == "nd") //miramos que sea un nodo para saber la referencia
			{
				std::pair<std::string, std::string> valor_node =
					Util::id_node(camiBotiga.fills[i].second);
				m_ref.push_back(valor_node.first);
			}
		}
	}
	for(int i = 0; i < m_nodes.size();i++)
	{
		if(m_nodes[i].id_element == "node")
		{
			for(int j = 0; j < m_nodes[j].atributs.size(); j++) // recorremos los atributos del nodo
			{
				if (m_nodes[i].atributs[j].first == "id") //miramos el id que guarda la referencia
				{
					for (int n = 0; n < m_ref.size(); n++) //recorremos todo el vector de referencias para ver si coincide
					{
						if (m_nodes[i].atributs[j].second == m_ref[n])
						{
							trobat = true; // el atributo id coincide con la referencia del nodo que tenemos
						}
					}
				}
				if (trobat == true) //si coincide nos guardamos la latitud y la longitud de ese nodo
				{
					if (m_nodes[i].atributs[j].first == "lat")
						lat = m_nodes[i].atributs[j].second;
					if (m_nodes[i].atributs[j].first == "lon")
						lon = m_nodes[i].atributs[j].second;
				}
			}
			trobat = false;

			lat_double = stod(lat);
			lon_double = stod(lon);
			Coordinate cordenada;
			cordenada.lat = lat_double;
			cordenada.lon = lon_double;
			
			cordenadas_camino.push_back(cordenada);
		}
	}
	return cordenadas_camino;
};
