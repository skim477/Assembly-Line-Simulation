#include "CustomerOrder.h"
#include "Utilities.h"


namespace sdds {
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder(const std::string& str)
	{
		Utilities utility;
		size_t next_pos = 0;
		bool more = true;
		m_name = utility.extractToken(str, next_pos, more);
		m_product = utility.extractToken(str, next_pos, more);
		std::vector<Item*> tempVec;
		Item* tempItemPtr;
		while (more) {
			tempItemPtr = new Item(utility.extractToken(str, next_pos, more));
			tempVec.push_back(tempItemPtr);
		}
		m_cntItem = tempVec.size();
		m_lstItem = new Item * [m_cntItem];
		for (size_t i = 0; i < m_cntItem; i++) {
			m_lstItem[i] = tempVec[i];
		}

		if (m_widthField < utility.getFieldWidth()) {
			m_widthField = utility.getFieldWidth();
		}
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& I) {
		throw - 1;
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& I) noexcept
	{
		*this = std::move(I);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept
	{
		if (this != &other) {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			m_name = other.m_name;
			m_product = other.m_product;
			m_cntItem = other.m_cntItem;
			m_lstItem = other.m_lstItem;
			other.m_lstItem = nullptr;
			other.m_cntItem = 0;
			other.m_name = "";
			other.m_product = "";
		}
		return *this;
		// TODO: insert return statement here
	}

	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}

	bool CustomerOrder::isOrderFilled() const
	{
		bool result = true;
		for (size_t i = 0; i < m_cntItem && result; i++) {
			if (!(m_lstItem[i]->m_isFilled)) {
				result = false;
			}
		}

		return result;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool result = true;
		for (size_t i = 0; i < m_cntItem && result; i++) {
			if (m_lstItem[i]->m_itemName == itemName && !(m_lstItem[i]->m_isFilled)) {
				result = false;
			}
		}

		return result;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		bool isFound = false;
		for (size_t i = 0; i < m_cntItem && !isFound; i++) {
			if (m_lstItem[i]->m_itemName == station.getItemName() && !(m_lstItem[i]->m_isFilled)) {

				if (station.getQuantity() >= 1) {
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
					isFound = true;
				}
				else {
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << std::setw(6) << std::right << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] " << std::left << std::setw(m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
		}
	}

}