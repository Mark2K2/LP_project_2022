#include "pch.h"
#include "PuntDeInteresBase.h"
#include "Util.h"

XmlElement Botiga = {

	//id_element = 
			"node",

			// atributs = 
			{
				std::make_pair("id", "8606512476"),
				std::make_pair("visible", "true"),
				std::make_pair("version", "1"),
				std::make_pair("changeset", "102562605"),
				std::make_pair("timestamp", "2021-04-08T12:04:11Z"),
				std::make_pair("user", "Interswd"),
				std::make_pair("uid", "4946691"),
				std::make_pair("lat", "41.4902204"),
				std::make_pair("lon", "2.1406477")
			},

	// fills = 
	{
		std::make_pair<std::string,std::vector<std::pair<std::string, std::string>>>
			("tag", {
				std::make_pair<std::string, std::string>("k", "shop"),
				std::make_pair<std::string, std::string>("v", "bakery")
		}),

		std::make_pair<std::string, std::vector<std::pair<std::string, std::string>>>
				("tag", {
					std::make_pair<std::string, std::string>("k", "name"),
					std::make_pair<std::string, std::string>("v", "La Millor Pastisseria")
		}),
		std::make_pair<std::string, std::vector<std::pair<std::string, std::string>>>
					("tag", {
						std::make_pair("k","wheelchair"),
						std::make_pair("v", "yes")
					})
	}


};

XmlElement Restaurant = {
	//id_element =
	"node",
	// atributs =
	{
		std::make_pair("id", "357101444"),
		std::make_pair("visible", "true"),
		std::make_pair("version", "3"),
		std::make_pair("changeset", "77532251"),
		std::make_pair("timestamp", "2019-11-25T15:26:03Z"),
		std::make_pair("user", "MultiDavid2001b"),
		std::make_pair("uid", "4946691"),
		std::make_pair("lat", "41.4902204"),
		std::make_pair("lon", "2.1406477")
	},
	// fills =
	{
		std::make_pair<std::string,std::vector<std::pair<std::string, std::string>>>
		("tag", {
			std::make_pair<std::string, std::string>("k", "amenity"),
			std::make_pair<std::string, std::string>("v", "restaurant")

	}),
		std::make_pair<std::string, std::vector<std::pair<std::string, std::string>>>

	("tag", {
		std::make_pair<std::string, std::string>("k","cuisine"),
		std::make_pair<std::string, std::string>("v", "pizza")

	}),
		std::make_pair <std::string, std::vector<std::pair<std::string, std::string>>>

	("tag", {
		std::make_pair<std::string, std::string>("k", "name"),
		std::make_pair<std::string, std::string>("v", "Pizzeria Manhattan")
	}),

		std::make_pair <std::string, std::vector<std::pair<std::string, std::string>>>

	("tag", {
		std::make_pair("k","wheelchair"),
		std::make_pair("v", "yes")
	})

	}
};

PuntDeInteresBase::PuntDeInteresBase() {
	this->m_coord = Coordinate{ 0.0, 0.0 };
	this->m_name = "undefinit";
}

PuntDeInteresBase::PuntDeInteresBase(Coordinate coord, std::string name) {
	this->m_name = name;
	this->m_coord = coord;
}

Coordinate PuntDeInteresBase::getCoord() {
	return this->m_coord;
}

std::string PuntDeInteresBase::getName() {
	return this->m_name;
}

unsigned int PuntDeInteresBase::getColor() {

	return 0xFFA500;
}


std::string PuntDeInteresRestaurantSolucio::getName()
{

	std::string name;

	if (Restaurant.id_element == "node")
	{
		for (int i = 0; i < Restaurant.fills.size(); i++)
		{
			if (Restaurant.fills[i].first == "tag")
			{
				std::pair<std::string, std::string> valorTag =
					Util::kvDeTag(Restaurant.fills[i].second);
				if (valorTag.first == "name")
				{
					name = valorTag.second;
				}
			}
		}
	}

	return name;

}


unsigned int PuntDeInteresRestaurantSolucio::getColor()
{
	bool restaurant = false;
	unsigned int color = (0xFFA550);
	if (Restaurant.id_element == "node")
	{
		for (int i = 0; i < Restaurant.fills.size(); i++)
		{
			if (Restaurant.fills[i].first == "tag")  //evaluamos todos los tags y nos guardamos la infromacion
			{
				std::pair<std::string, std::string> valorTag =
					Util::kvDeTag(Restaurant.fills[i].second);
				if (valorTag.first == "cuisine") //nos guardamos lo que nos interese, en este caso el tipo de cocina y si tiene 
												 //movilidad reducida, lo demas nos da igual
				{
					m_tipusCuina = valorTag.second;
				}
				if (valorTag.first == "wheelchair")
				{
					if (valorTag.second == "yes")
					{
						m_mobilitat = true;
					}
				}
			}
		}

	}

	if (m_tipusCuina == "pizza" && m_mobilitat == true)
	{
		return 0x03FCBA;
	}
	if (m_tipusCuina == "chinese")
	{
		return 0xA6D9F7;
	}
	if (m_mobilitat == true)
	{
		return 0x251351;
	}

	return color;

}

std::string PuntDeInteresBotigaSolucio::getName() {

	std::string name;

	if (Botiga.id_element == "node")
	{
		for (int i = 0; i < Botiga.fills.size(); i++)
		{
			if (Botiga.fills[i].first == "tag")
			{
				std::pair<std::string, std::string> valorTag =
					Util::kvDeTag(Botiga.fills[i].second);
				if (valorTag.first == "name")
				{
					name = valorTag.second;
				}
			}
		}
	}

	return name;

}

unsigned int PuntDeInteresBotigaSolucio::getColor()
{
	unsigned int color = 0xEFD6AC;
	if (Botiga.id_element == "node")  
	{
		for (int i = 0; i < Botiga.fills.size(); i++)
		{
			if (Botiga.fills[i].first == "tag")
			{
				std::pair<std::string, std::string> valorTag =
					Util::kvDeTag(Botiga.fills[i].second);
				if (valorTag.first == "shop") 
				{
					m_tagShop = valorTag.second;
				}
			}
		}
	}

	if (m_tagShop == "supermarket")
		return 0xA5BE00;
	else
	{
		if (m_tagShop == "tobacco")
			return 0xFFAD69;
		else
		{
			if (m_tagShop == "bakery")
				return 0xE85D75;
			else
				return 0xEFD6AC;
		}
	}
}