// #### DRIVER 1 ####
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
using namespace std;

#include "Graph.h"
#include "Map.h"
#include "City.h"

// Utility functions

void addEdge(UndirectedGraph<City>& graph, UndirectedEdge<City>& edge);

// Construct two good maps
void goodMap(unordered_set<City>& cities, unordered_map<string, UndirectedEdge<City> >& edges);

// Construct a map that is connected but does not contain all the cities
void smallBadMap(unordered_set<City>& cities, unordered_map<string, UndirectedEdge<City> >& edges);

// Constuct a map with all cities but that is disconnected
void disconnectedBadMap(unordered_set<City>& cities, unordered_map<string, UndirectedEdge<City> >& edges);

// Test if all cities are on map and also print a message with the result of
// that test
bool assertAllCitiesOnMap(unordered_set<City>& cities, Map& m);
// Like above but tests for connectedness
bool assertMapIsConnected(Map& m);

int main(int argc, char *argv[])
{
    // Initialize some cities
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

    // Initialize some edges (all possible edges with arbitrary cost given the
    // vertices)
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

    // Print results of tests on various maps
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

    // Add all cities
    for(City city : cities)
    {
        powerGrid.addVertex(city);
        cout << "added " << city << endl;
    }
    cout << endl;

    // Path graph on 4 vertices
    addEdge(powerGrid, edges["mt"]);
    addEdge(powerGrid, edges["mq"]);
    addEdge(powerGrid, edges["qo"]);

    cout << endl;
    Map good(powerGrid);

    // Are all cities on the map?
    bool all = assertAllCitiesOnMap(cities, good);

    // Is the map connected?
    bool conn = assertMapIsConnected(good);

    // Final verdict.. is the map valid?
    if(all && conn)
    {
        cout << "VALID" << endl;
    } else {
        cout << "INVALID" << endl;
    }
    cout << endl;

    // Test the complete graph on 4 vertices
    cout << "#Add remaining edges to graph to make it complete#" << endl;
    addEdge(powerGrid, edges["mo"]);
    addEdge(powerGrid, edges["tq"]);
    addEdge(powerGrid, edges["to"]);
    cout << endl;

    // We already know that assertAllCitiesOnMap passes so we just need to
    // test that adding edges doesn't break connectedness (a contradiction)
    assertMapIsConnected(good);
    cout << endl;
}

void smallBadMap(unordered_set<City>& cities, unordered_map<string, UndirectedEdge<City> >& edges)
{
    cout << "##Constructing small map##" << endl;
    UndirectedGraph<City> powerGrid;

    // Add all but 1 available City
    int stopAt = cities.size() - 1;
    int i = 0;
    for(City city : cities)
    {
        powerGrid.addVertex(city);
        cout << "added " << city << endl;
        if(++i == stopAt) break;
    }
    cout << endl;

    // Path graph on 3 vertices
    addEdge(powerGrid, edges["to"]);
    addEdge(powerGrid, edges["qo"]);

    cout << endl;
    Map small(powerGrid);

    // Logic simiallr to goodMap()
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

    // Add all cities to map
    for(City city : cities)
    {
        powerGrid.addVertex(city);
        cout << "added " << city << endl;
    }
    cout << endl;


    // There is no way to connect 4 vertices with 2 edges
    addEdge(powerGrid, edges["to"]);
    addEdge(powerGrid, edges["qo"]);

    cout << endl;
    Map disconnected(powerGrid);

    // Logic simillar as above
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

// ##### DRIVER 2 ####
// #include <iostream>
// #include <fstream>
// #include <string>
// using namespace std;
//
// #include "Map.h"
// #include "MapLoader.h"
//
// // Wrapper around MapLoader::Load that checks for validity explicitly
// void loadAndCheck(string fname);
//
// int main(int argc, char *argv[])
// {
//     // Files that have a valid map, a disconnected map and a garbage file
//     // respectively
//     string goodFile = "map.txt";
//     string disconnectedFile = "disconnected_map.txt";
//     string badFile = "badmap.txt";
//
//     loadAndCheck(goodFile);
//     loadAndCheck(disconnectedFile);
//     loadAndCheck(badFile);
//     return 0;
// }
//
// void loadAndCheck(string fname)
// {
//     cout << "##Checking " << fname << "##" << endl;
//     Map* g = MapLoader::load(fname);
//     if(g == nullptr) {
//         // Getting NULL means that we couldn't read the file
//         cout << "Invalid map" << endl;
//     } else {
//         // We read the file successfully but is it connected?
//         cout << *g << endl;
//         cout << (g->isValid() ? "valid connected map file" : "well formatted but disconnected") << endl;
//     }
//     cout << endl;
//
//     // Cleanup
//     delete g;
// }

// #### DRIVER 3 ####
// #include <fstream>
// #include <iostream>
// #include <unordered_set>
// #include <unordered_map>
// #include <string>
// #include <vector>
// using namespace std;
//
// #include "MapLoader.h"
// #include "Map.h"
// #include "Resource.h"
// #include "House.h"
// #include "HouseColor.h"
//
// // Wrappers around functions for Map class that also write to savefile
// // See: Map.h
// void addResourceToMarket(Resource r, Map& game, string fname);
// void addResourceToPool(Resource r, Map& game, string fname);
// void addElektroToBank(int amount, Map& game, string fname);
// void buyCity(City city, House house, Map& game, string fname);
// void printMapToFile(Map& game, string fname);
//
// int main(int argc, char *argv[])
// {
//     // Valid map file
//     string mapFile = "map.txt";
//     Map* game = MapLoader::load(mapFile);
//     if(game == nullptr) {
//         cout << "Could not load " << mapFile << endl;
//     } else {
//         cout << "Successfully loaded " << mapFile << endl;
//     }
//
//     // We will save the game in a new file
//     string saveFile = "saved_map.txt";
//
//     // Add tokens to Map
//     addResourceToPool(OIL, *game, saveFile);
//     cout << "Saved an oil token to the market" << endl;
//     addResourceToMarket(COAL, *game, saveFile);
//     cout << "Saved a coal resource to the resource pool" << endl;
//     addElektroToBank(100, *game, saveFile);
//     cout << "Give the bank 100 Elektro" << endl;
//
//     // Give a city a house
//     unordered_set<City> cities = game->getCities();
//
//     City city = *(cities.begin());
//     House house(PURPLE);
//     buyCity(city, house, *game, saveFile);
//     cout << "Gave a purple house to 1 city" << endl;
//     cout << "See " << saveFile << " to see these results" << endl;
//
//     // Cleanup
//     delete game;
//
//     return 0;
// }
//
// void addResourceToMarket(Resource r, Map& game, string fname)
// {
//     game.addResourceToMarket(r);
//     printMapToFile(game, fname);
// }
//
// void addResourceToPool(Resource r, Map& game, string fname)
// {
//     game.addResourceToPool(r);
//     printMapToFile(game, fname);
// }
//
// void addElektroToBank(int amount, Map& game, string fname)
// {
//     game.addElektroToBank(amount);
//     printMapToFile(game, fname);
// }
//
// void buyCity(City city, House house, Map& game, string fname)
// {
//     game.buyCity(city, house);
//     printMapToFile(game, fname);
// }
//
// void printMapToFile(Map& game, string fname)
// {
//     ofstream out(fname);
//     string mapText = game.printMap();
//     const char* data = mapText.c_str();
//     out.write(data, mapText.length());
//     out.close();
// }

// #### DRIVER 4 ####
// #include <iostream>
// #include <string>
// using namespace std;
//
// #include "Player.h"
// #include "PowerplantCard.h"
// #include "HouseColor.h"
//
// int main(int argc, char* argv[])
// {
//     // Setup new player
//     Player player1(BLACK);
//     cout << "Player 1 has been created...." << '\n';
//     cout << "\nPlayer 1:" << '\n';
//
//     // Print new player info (should be pretty boring)
//     player1.toString();
//
//     // Initialize player items (Powerplants, Resources, etc)
//     PowerplantCard card(17, 2, 1, URANIUM);
//     cout << "\nAdding a card to player...\n";
//     player1.purchaseCard(card, 17);
//
//     cout << "Buying resources for player..." << endl;
//     player1.buyResource(0, URANIUM, 1, 10);
//
//     cout << "Buying City for player....\n";
//     player1.buyCities("Montreal");
//     cout << "\nPlayer 1:" << '\n';
//
//     // Print player should now have items
//     player1.toString();
// }

//#### DRIVER 5 ####
// #include <iostream>
// #include <cstdlib>
// #include <ctime>
// #include <string>
// #include <fstream>
// #include <list>
// using namespace std;
//
// #include "Card.h"
// #include "PowerplantCard.h"
// #include "SummaryCard.h"
// #include "Step3Card.h"
// #include "Resource.h"
//
// // Shuffle the deck according to Powergrid rules
// void shuffle(PowerplantCard cards[], int size);
//
// int main(int argc, char *argv[])
// {
//     // Seed randomness for shuffling
//     srand(time(NULL));
//
//     const int NUM_POWER_PLANTS = 42;
//     const int MARKET_SIZE = 8;
//
//     PowerplantCard cards[NUM_POWER_PLANTS];
//
//     // We will read the definition of the cards from text... This is better than
//     // hardcoding here
//     fstream input;
//
//     // Info from the text file will be stored here
//     int name;
//     string resources;
//     int powerable;
//
//     input.open("powerplants.txt");
//
//     // Loop over lines of the text file to collect cards
//     int i = 0;
//     while(input >> name >> resources >> powerable)
//     {
//         PowerplantCard c;
//
//         int needed = stoi(resources.substr(0, 1));
//
//         // Skip if we read an ecological plant
//         if(needed > 0)
//         {
//             string types[2];
//             size_t size = 0;
//             size_t start = 2;
//             size_t end = resources.find(",");
//
//             // Resources need some special parsing because a plant might use
//             // more than one type of resource
//             while(end != string::npos)
//             {
//                 // Resource records are stored as:
//                 // resource1[:resource2]
//                 types[size++] = resources.substr(start, end - start);
//                 start = end + 1;
//                 end = resources.find(",", start);
//
//             }
//
//             types[size++] = resources.substr(start, end);
//
//             // Did we find one resource or two
//             if(size == 1) c = PowerplantCard(name, powerable, needed, getResourceByName(types[0]));
//
//             else c = PowerplantCard(name, powerable, needed, getResourceByName(types[0]), getResourceByName(types[1]));
//
//         } else {
//             // Ecological card
//             c = PowerplantCard(name, powerable, needed);
//         }
//         // Deck of only Powerplant cards
//         cards[i++] = c;
//     }
//
//     // We're done
//     input.close();
//
//     // First 8 Powerplants get put in fixed size Market
//     PowerplantCard market[8] = {cards[0], cards[1], cards[2], cards[3], cards[4], cards[5], cards[6], cards[7]};
//
//     const int FULL_DECK_SIZE = NUM_POWER_PLANTS - MARKET_SIZE;
//
//     // Get the remaining Powerplants for the deck
//     PowerplantCard deckCards[FULL_DECK_SIZE];
//     for(int i = 0; i < FULL_DECK_SIZE; i++)
//     {
//         deckCards[i] = cards[i + MARKET_SIZE];
//     }
//
//     // First ecological Powerplant goes on top of the deck after shuffling so
//     // let's remove it
//     PowerplantCard ecoOne = cards[10];
//
//     // The Step 3 card goes on the bottom of the deck after shuffling
//     Step3Card s3Card;
//
//     // Shuffle the remaining deck cards
//     shuffle(deckCards, FULL_DECK_SIZE);
//
//     // Create a deck with a linked list
//     list<Card*> deck;
//     for(PowerplantCard& c: deckCards)
//     {
//         // We actually shuffled card 13 into the deck anyway so don't add it
//         // to the real deck
//         if(c == ecoOne) continue;
//         deck.push_back(&c);
//     }
//
//     // Add special cards to their special places
//     deck.push_front(&ecoOne);
//     deck.push_back(&s3Card);
//
//     // Print Market, Deck and SummaryCard for demonstration
//     cout << "MARKET:" << endl;
//
//     for(PowerplantCard& c : market)
//     {
//         cout << c.info() << endl << endl;
//     }
//
//     cout << endl << "DECK:" << endl;
//
//     for(Card* cPtr : deck)
//     {
//         cout << cPtr->info() << endl << endl;
//     }
//
//     cout << endl << "SUMMARY:"<< endl;
//
//     SummaryCard summary;
//     cout << summary.info() << endl;
//
//     return 0;
// }
//
// void shuffle(PowerplantCard cards[], int size)
// {
//     // Start at the bottom of the deck and swap cards to random locations
//     // skipping positions that have already been swaped FROM
//     int max = size - 1;
//     while(max > 0) {
//         int r = rand() % max ;
//         PowerplantCard temp = cards[r];
//         cards[r] = cards[max];
//         cards[max--] = temp;
//     }
// }
