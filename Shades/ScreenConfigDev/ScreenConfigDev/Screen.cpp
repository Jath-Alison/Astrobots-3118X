#include "Screen.h"

void Screen::addData(std::string name, double* dataPtr) {
	m_data[name] = dataPtr;
}

void Screen::display() {
	for (size_t i = 0; i < m_displayables.size(); i++)
	{
		if (m_displayables[i]) {
			m_displayables[i]->display();
		} else {
			m_displayables.erase(m_displayables.begin() + i);
		}
	}
}