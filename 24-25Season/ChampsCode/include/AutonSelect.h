#pragma once
#include <string>
#include <functional>
#include <vector>

class Auton
{
public:
    Auton(std::string name, std::function<void(void)> function) : m_id(m_lastId++), m_name(name), m_function(function) {}

    int getId() { return m_id; }
    std::string getName() { return m_name; }
    void runAuton()
    {
        if (m_function)
            m_function();
    }

private:
    int m_id;
    std::string m_name{"Unnamed Auton"};
    std::function<void(void)> m_function;

    inline static int m_lastId{0};
};

class AutonSelect
{
public:
    AutonSelect(std::vector<Auton> autons) : m_autons(autons) {}

    void addAuton(Auton auton)
    {
        m_autons.push_back(auton);
    }

    std::string getAutonName (int id)
    {
        for (int i = 0; i < m_autons.size(); i++)
        {
            if (m_autons[i].getId() == id)
            {
                return m_autons[i].getName();
            }
        }
        return "Auton not found";
    }

    int getAutonId (std::string name)
    {
        for (int i = 0; i < m_autons.size(); i++)
        {
            if (m_autons[i].getName() == name)
            {
                return m_autons[i].getId();
            }
        }
        return -1;
    }

    void runAuton(int id)
    {
        for (int i = 0; i < m_autons.size(); i++)
        {
            if (m_autons[i].getId() == id)
            {
                m_autons[i].runAuton();
            }
        }
    }

private:
    std::vector<Auton> m_autons;
};

extern AutonSelect autonSelect;
extern int currentAutonId;
extern int currentAutonView;

void incAutonView();
void decAutonView();
void resetAutonView();

void selectAutonLeft();
void selectAutonRight();

extern Auton Skills;

extern Auton RedCenterRingsPos;
extern Auton BlueCenterRingsPos;

extern Auton RedCenterRingsNeg;
extern Auton BlueCenterRingsNeg;

extern Auton RedFlippingAWPPos;
extern Auton BlueFlippingAWPPos;

extern Auton RedFlippingAWPNeg;
extern Auton BlueFlippingAWPNeg;

extern Auton RedRingsToCorner;
extern Auton BlueRingsToCorner;