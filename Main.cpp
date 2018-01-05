#include "NewBie_Lang.hpp"
#include "Graph.hpp"
#include <fstream>
#include <iostream>

using namespace std;
int main(int argc, char **argv)
{
    //zyd2001::NewBie::Interpreter inter;
    //inter.setFile("test");
    //inter.parse();
    //inter.run();
    fstream f("tinyDG.txt");
    DirectedGraph<int> g(true);
    for (int i = 0; i < 13; i++)
        g.addVertex(i);
    int v, w;
    while (f)
    {
        f >> v >> w;
        g.addEdge(v, w);
    }
    g.delVertex(2);
    auto r = g.dfs(0);
}