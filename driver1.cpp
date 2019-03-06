#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
using namespace std;

#include "Graph.h"
#include "Map.h"
#include "City.h"

void addEdge(UndirectedGraph<City>& graph, UndirectedEdge<City>& edge);
void goodMap(unordered_set<City>& cities, unordered_map<string, UndirectedEdge<City> >& edges);
void smallBadMap(unordered_set<City>& cities, unordered_map<string, UndirectedEdge<City> >& edges);
void disconnectedBadMap(unordered_set<City>& cities, unordered_map<string, UndirectedEdge<City> >& edges);

bool assertAllCitiesOnMap(unordered_set<City>& cities, Map& m);
bool assertMapIsConnected(Map& m);

int main(int argc, char *argv[])
{
    City montreal("Montreal", 1);
    City quebec("Quebec City", 1);
    City toronto("Toronto", 2);
    City ottawa("Ottawa", 2);

    unordered_set<City> cities({montreal, quebec, toronto, ottawa});
    cout << "##These are the cities that will be on our maps##" << endl;
    for(City city : cities)
    {
        cout << city << endl;
    }
    cout << endl;

    UndirectedEdge<City> mt(montreal, toronto, 7);
    UndirectedEdge<City> mq(montreal, quebec, 3);
    UndirectedEdge<City> mo(montreal, ottawa, 3.5);
    UndirectedEdge<City> tq(toronto, quebec, 11);
    UndirectedEdge<City> to(toronto, ottawa, 4);
    UndirectedEdge<City> qo(quebec, ottawa, 7);

    unordered_map<string, UndirectedEdge<City> > edges({{"mt", mt},
                                                        {"mq", mq},
                                                        {"mo", mo},
                                                        {"tq", tq},
                                                        {"to", to},
                                                        {"qo", qo}});

    cout << "##These are the possible edges##" << endl;
    for(auto edge : edges)
    {
        cout << edge.second << endl;
    }
    cout << endl;

    goodMap(cities, edges);
    smallBadMap(cities, edges);
    disconnectedBadMap(cities, edges);

    return 0;
}

void addEdge(UndirectedGraph<City>& graph, UndirectedEdge<City>& edge)
{
    graph.addEdge(edge.source, edge.dest, edge.cost);
    cout << "added edge " << edge << endl;
}

void goodMap(unordered_set<City>& cities, unordered_map<string, UndirectedEdge<City> >& edges)
{
    cout << "##Constructing good map##" << endl;
    UndirectedGraph<City> powerGrid;
    for(City city : cities)
    {
        powerGrid.addVertex(city);
        cout << "added " << city << endl;
    }
    cout << endl;

    addEdge(powerGrid, edges["mt"]);
    addEdge(powerGrid, edges["mq"]);
    addEdge(powerGrid, edges["qo"]);

    cout << endl;
    Map good(powerGrid);

    // Are all cities on the map;
    bool all = assertAllCitiesOnMap(cities, good);

    bool conn = assertMapIsConnected(good);

    if(all && conn)
    {
        cout << "VALID" << endl;
    } else {
        cout << "INVALID" << endl;
    }
    cout << endl;

    cout << "#Add remaining edges to graph to make it complete#" << endl;
    addEdge(powerGrid, edges["mo"]);
    addEdge(powerGrid, edges["tq"]);
    addEdge(powerGrid, edges["to"]);
    cout << endl;

    assertMapIsConnected(good);
    cout << endl;
}

void smallBadMap(unordered_set<City>& cities, unordered_map<string, UndirectedEdge<City> >& edges)
{
    cout << "##Constructing small map##" << endl;
    UndirectedGraph<City> powerGrid;
    int stopAt = cities.size() - 1;
    int i = 0;
    for(City city : cities)
    {
        powerGrid.addVertex(city);
        cout << "added " << city << endl;
        if(++i == stopAt) break;
    }
    cout << endl;

    addEdge(powerGrid, edges["to"]);
    addEdge(powerGrid, edges["qo"]);

    cout << endl;
    Map small(powerGrid);

    // Are all cities on the map;
    bool all = assertAllCitiesOnMap(cities, small);

    bool conn = assertMapIsConnected(small);

    if(all && conn)
    {
        cout << "VALID" << endl;
    } else {
        cout << "INVALID" << endl;
    }
    cout << endl;
}

void disconnectedBadMap(unordered_set<City>& cities, unordered_map<string, UndirectedEdge<City> >& edges)
{
    cout << "##Constructing disconnected map##" << endl;
    UndirectedGraph<City> powerGrid;
    for(City city : cities)
    {
        powerGrid.addVertex(city);
        cout << "added " << city << endl;
    }
    cout << endl;

    addEdge(powerGrid, edges["to"]);
    addEdge(powerGrid, edges["qo"]);

    cout << endl;
    Map disconnected(powerGrid);

    // Are all cities on the map;
    bool all = assertAllCitiesOnMap(cities, disconnected);

    bool conn = assertMapIsConnected(disconnected);

    if(all && conn)
    {
        cout << "VALID" << endl;
    } else {
        cout << "INVALID" << endl;
    }
    cout << endl;
}

bool assertAllCitiesOnMap(unordered_set<City>& cities, Map& m)
{
    bool answer = m.getCities() == cities;
    if(answer)
    {
        cout << "#All cities are on map#" << endl;
    } else {
        cout << "#Some cities not on map#" << endl;
    }
    return answer;
}

bool assertMapIsConnected(Map& m) {
    bool answer = m.isValid();
    if(answer)
    {
        cout << "#Map is connected#" << endl;
    } else {
        cout << "#Map is DISconnected#" << endl;
    }
    return answer;
}
