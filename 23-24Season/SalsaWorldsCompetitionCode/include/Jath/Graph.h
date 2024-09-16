#pragma once

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <functional>

#include "vex.h"
#include "Jath\Vec2.h"


namespace Jath{

    class Dataset
    {
    public:

        std::string m_name;
        std::function<double()> m_function;
        std::array<double, 100> m_data;

        double getData();
        
    };

    class Graph
    {
    public:

        Graph();
        Graph( Graph& g);

        Graph& addDataset(std::string name, std::function<double(void)> function);
        std::string getData();

        void drawGraph(Vec2 loc, Vec2 dim);

    // private:
        std::vector <Dataset> m_datasets;
    };

    /*
    #pragma once

    #include <array>
    #include <vector>
    #include <functional>

    struct Graph
    {

        struct Dataset{
            std::string m_name;

            std::function <double()> m_function;
            std::array<double, 100> m_data;

            void getData();

        };

    public:
        Graph(std::string hi );
        void addDataset( std::string name, std::function <double()> func);
        void test();
    private:
        std::vector<Dataset> m_datasets;

    };

    #include "Graph.hpp"


    Graph::Graph(std::string hi)
    {

    }

    void Graph::addDataset(std::string name, std::function<double()> func)
    {
        Dataset temp;
        temp.m_name = name;
        temp.m_function = func;

        m_datasets.push_back(temp);
    }
    void Graph::test()
    {
    }

    inline void Graph::Dataset::getData()
    {
        for (size_t i = 0; i < m_data.size() - 1; i++)
        {
            m_data[i] = m_data[i + 1];
        }

        *m_data.end() = m_function();

    }

    */
}