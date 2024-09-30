#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <string>
#include <iostream>

namespace sdds {
	class Station {
		//instance variables
		int m_id{};
		std::string m_item{};
		std::string m_desc{};
		size_t m_serialNumber{};
		size_t m_quantity{}; //num of items;

		//class variables
		static size_t m_widthField;
		static size_t id_generator;

		//public functions
	public:
		Station(const std::string& str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};

}

#endif