#include "Workstation.h"

namespace sdds {
	std::deque<CustomerOrder> g_pending;
	std::deque<CustomerOrder> g_completed;
	std::deque<CustomerOrder> g_incomplete;

	Workstation::Workstation(const std::string& str) : Station(str)
	{
	}
	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty()) {
			m_orders.front().fillItem(*this, os);
		}
	}
	bool Workstation::attemptToMoveOrder()
	{
		bool result = false;
		if (!m_orders.empty()) {
			if (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0) {
				if (m_pNextStation) {
					//(*m_pNextStation).m_orders.push_back(m_orders.front());
					(*m_pNextStation) += std::move(m_orders.front());
				}
				else if (m_orders.front().isOrderFilled()) {
					g_completed.push_back(std::move(m_orders.front()));
				}
				else {
					g_incomplete.push_back(std::move(m_orders.front()));
				}
				m_orders.pop_front();
				result = true;
			}
			
		}
		return result;
	}
	void Workstation::setNextStation(Workstation* station)
	{
		if (station) {
			m_pNextStation = station;
		}

	}
	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}
	void Workstation::display(std::ostream& os) const
	{
		os << getItemName() << " --> " << (m_pNextStation ? m_pNextStation->getItemName() : "End of Line") << std::endl;

	}
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
		// TODO: insert return statement here
	}
}