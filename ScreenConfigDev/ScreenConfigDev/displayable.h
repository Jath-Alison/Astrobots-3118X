#pragma once
class displayable
{
public:
	virtual void display() = 0;
	void setActive(bool active) { m_active = active; };
protected:
	bool m_active{ true };
};

