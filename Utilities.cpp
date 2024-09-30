#include "Utilities.h"

namespace sdds {
	char Utilities::m_delimiter{};

	void trim(std::string& str) {
		size_t begin = str.find_first_not_of(' ');
		size_t end = str.find_last_not_of(' ');
		str = str.substr(begin, end - begin + 1);
	}

	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}
	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		std::string token;
		int next;

		if (str[next_pos] == m_delimiter) {
			more = false;
			throw -1;
		}

		std::string temp = str.substr(next_pos);
		next = temp.find(m_delimiter);
		if (next != -1) {
			token = temp.substr(0, next);
			trim(token);
			next_pos += next + 1;
			more = true;
		}
		else {
			token = temp;
			trim(token);
			more = false;
		}

		if (token.length() > m_widthField) {
			m_widthField = token.length();
		}
		return token;
	}
	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}
	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
}