#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace sdds {
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;

	Station::Station(const std::string& str)
	{
		Utilities utility;
		size_t next_pos = 0;
		bool more = true;
		m_id = ++id_generator;
		m_item = utility.extractToken(str, next_pos, more);
		m_serialNumber = stoul(utility.extractToken(str, next_pos, more));
		m_quantity = stoul(utility.extractToken(str, next_pos, more));
		if (m_widthField < utility.getFieldWidth()) {
			m_widthField = utility.getFieldWidth();
		}
		m_desc = utility.extractToken(str, next_pos, more);

	}
	const std::string& Station::getItemName() const
	{
		return m_item;
		// TODO: insert return statement here
	}
	size_t Station::getNextSerialNumber()
	{
		return m_serialNumber++;
	}
	size_t Station::getQuantity() const
	{
		return m_quantity;
	}
	void Station::updateQuantity()
	{
		if (m_quantity > 0) {
			m_quantity--;
		}

	}
	void Station::display(std::ostream& os, bool full) const
	{
		os << std::setw(3) << std::right << std::setfill('0') << m_id << " | " << std::setw(m_widthField) << std::left << std::setfill(' ') << m_item << " | " << std::setw(6) << std::right << std::setfill('0') << m_serialNumber << " | ";

		if (full) {
			os << std::setw(4) << std::right << std::setfill(' ') << m_quantity << " | " << m_desc;
		}

		os << std::endl;
	}
}