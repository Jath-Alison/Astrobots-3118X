#include "Jath\Graph.h"
#include <iostream>

namespace Jath
{

    Graph::Graph() {}

    Graph::Graph(Graph &g)
    {
        m_datasets.clear();

        for (size_t i = 0; i < g.m_datasets.size(); i++)
        {
            Dataset temp;
            temp = g.m_datasets[i];
            
            temp.m_data = std::array<double,100>();

            m_datasets.push_back(temp);
        }

    }

    Graph &Graph::addDataset(std::string name, std::function<double(void)> function)
    {
        Dataset temp;
        temp.m_name = name;
        temp.m_function = function;

        m_datasets.push_back(temp);
        return *this;
    }

    std::string Graph::getData()
    {
        std::stringstream out;
        out << "Graph: \n";
        for (size_t i = 0; i < m_datasets.size(); i ++)
        {
            Dataset& d = m_datasets[i];
            out << "\t" << d.m_name << ": " << d.getData() << "\n";
        }
        out << std::endl;

        return out.str();
    }

    void Graph::drawGraph(Vec2 loc, Vec2 dim)
    {
        std::array<vex::color, 9> colors = {
            vex::color::blue,
            vex::color::green,
            vex::color::red,
            vex::color::white,
            vex::color::purple,
            vex::color::orange,
            vex::color::yellow,
            vex::color::cyan,
            vex::color::cyan
            };
        size_t colorIndex = 0;
        
        for (size_t j = 0; j < m_datasets.size(); j++)
        {
            Dataset& d = m_datasets[j];
            Brain.Screen.setPenColor(colors[colorIndex]);

            float sum = 0;
            for (size_t i = 0; i < d.m_data.size() - 1; i++)
            {
                Vec2 start = Vec2::XandY(
                    loc.x + dim.x * (double(i) / double(d.m_data.size())),
                    loc.y - d.m_data[i] * dim.y / double(10 * 2)
                );
                Vec2 end = Vec2::XandY(
                    loc.x + dim.x * (double(i+1) / double(d.m_data.size())),
                    loc.y - d.m_data[i + 1] * dim.y / double(10 * 2)
                );
                sum += d.m_data[i];

                Brain.Screen.drawLine(start.x, start.y, end.x, end.y);


            }
                float result = d.m_data.back();// (d.m_data.back() + sum)/double(d.m_data.size());
                Brain.Screen.printAt(60*colorIndex,100,d.m_name.c_str());
                Brain.Screen.printAt(60*colorIndex,125,"%4.2f", result);

            colorIndex++;
        }
        Brain.Screen.setPenColor(vex::color::white);
        Brain.Screen.drawLine(loc.x, loc.y, loc.x+dim.x, loc.y);
    }  


    double Dataset::getData()
    {
        double out = 0;
        for (size_t i = 0; i < m_data.size() - 1; i++)
        {
            m_data[i] = m_data[i + 1];
        }

        if (m_function)
        {
            out = m_function();
            m_data[m_data.size() - 1] = out;
        }


        return out;
    }
}