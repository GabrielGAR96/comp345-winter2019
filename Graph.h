#ifndef GRAPH_H
#define GRAPH_H

/* #include <unordered_set> */
/* #include <unordered_map> */
/* #include <vector> */
#include <deque>
#include <iostream>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <vector>
using namespace std;

/* #include <boost/serialization/unordered_set.hpp> */
/* #include <boost/serialization/unordered_map.hpp> */
/* #include <boost/serialization/vector.hpp> */
/* using namespace boost::serialization; */

/* #include <boost/archive/text_oarchive.hpp> */
/* #include <boost/archive/text_iarchive.hpp> */

/* NOTE: I tried to research how to separate definition from implementation for
 * template classes. Any solution I found was either beyond my understanding or
 * in someway unsatisfactory.
 */

/* NOTE: I realize for the purpose of this game this graph
 * implmentation is overkill but I had already started it as my own personal
 * project. It also made programming required methods more simple in my opinion
 * and so the tradeoff for the simplicity of this implementation is worth it.
 */

// Simple edge container for use in adjacency list graph implementations
// This is barebones and provides no checks on edge equality
// NOTE: Due to implementation below lots of duplication of stored data...
// Consider using pointers for source and dest
template<typename T>
struct Edge {
    // One end vertex
    T source;

    // The other end vertex
    T dest;

    // cost if applicable can be ignored if not needed
    // NOTE: consider making overloaded constructor for this situation
    double cost;

    // Consturctors

    Edge() {}
    Edge(T source, T dest, double cost) : source(source), dest(dest), cost(cost) {}

    // Destructor

    virtual ~Edge() {}
};

/* namespace boost { */
/* namespace serialization { */

/*     template<typename Archive, typename T> */
/*     void serialize(Archive & ar, Edge<T>& edge, const unsigned int version) */
/*     { */
/*         ar & edge.source; */
/*         ar & edge.dest; */
/*         ar & edge.cost; */
/*     } */
/* } */
/* } */

// Useful for Powergrid because source and dest are interchangeable
template<typename T>
struct UndirectedEdge : public Edge<T> {
    // Needed for hashing and undirected graph logic
    bool operator==(const UndirectedEdge<T>& rhs) const;

    // Constructors

    UndirectedEdge() {}
    UndirectedEdge(T source, T dest, double cost) : Edge<T>(source, dest, cost) {}
};

template<typename T>
bool UndirectedEdge<T>::operator==(const UndirectedEdge<T>& rhs) const
{
    // Edges are equal in the case that both endpoints are equal and Cost is
    // equal
    return (this->source == rhs.source || this->source == rhs.dest) &&
        (this->dest == rhs.source || this->dest == rhs.dest) &&
        this->cost == rhs.cost;
}

/* namespace boost { */
/* namespace serialization { */

/*     template<typename Archive, typename T> */
/*     void serialize(Archive & ar, UndirectedEdge<T>& edge, const unsigned int version) */
/*     { */
/*         ar & boost::serialization::base_object<Edge<T> >(edge); */
/*     } */
/* } */
/* } */

// Specialization of hash<> so we can put edges in a hashset
namespace std {
    template<typename T> struct hash<UndirectedEdge<T> > {
        size_t operator()(const UndirectedEdge<T>& edge) const
        {
            // Note that XOR is commutative
            return (((hash<T>()(edge.source) ^ hash<T>()(edge.dest)) << 1 ^ hash<double>()(edge.cost)) << 1) >> 1;
        }
    };
}

// Output undirected edges for use in Powergrid game
template<typename T>
ostream& operator<<(ostream& out, const UndirectedEdge<T>& edge)
{
    out << edge.source << " <-> " << edge.dest;
    return out;
}

// Abstract graph class
template<typename T>
class Graph
{
    protected:
        // Data members
        unordered_set<T> verts;
        unordered_map<T, vector<Edge<T> > > adjList;

    private:

        /* friend class boost::serialization::access; */
        /* template<typename Archive> */
        /* void serialize(Archive & ar, const unsigned int version) */
        /* { */
        /*     ar & verts; */
        /*     ar & adjList; */
        /* } */

    public:

        // Constructors

        Graph();
        Graph(const Graph<T>& other);

        // Destructor

        virtual ~Graph();

        // Accessors and mutators
        // NOTE: this is a subset of typical data structure functionality but it
        // is sufficient
        int numVertices() const;
        virtual int numEdges() const = 0;
        bool addVertex(const T& x);

        // TODO: The necessity of this method is questionable find better way to
        // implment what it's needed for
        // See: Map.h
        T delVertex(const T& x);

        // We don't know what kind of edge we want to add yet
        virtual bool addEdge(const T& u, const T& v, double cost) = 0;

        unordered_set<T> getVerts() const;
        vector<Edge<T> > getEdges(T v) const;

        // Check if a graph is connected (i.e., for all vertex v, u there exists a path between v and u)
        static bool isConnected(const Graph<T>& g);
};

template<typename T>
Graph<T>::Graph()
{
}

template<typename T>
Graph<T>::Graph(const Graph<T>& other)
    : verts(other.verts), adjList(other.adjList)
{
}

template<typename T>
Graph<T>::~Graph()
{
}

template<typename T>
int Graph<T>::numVertices() const
{
    return verts.size();
}

template<typename T>
bool Graph<T>::addVertex(const T& x)
{
    bool inserted = verts.insert(x).second;
    if(inserted) adjList[x];
    return inserted;
}

template<typename T>
T Graph<T>::delVertex(const T& x)
{
    T answer = *(verts.find(x));
    adjList.erase(x);
    verts.erase(x);
    return answer;
}

template<typename T>
unordered_set<T> Graph<T>::getVerts() const
{
    return verts;
}

template<typename T>
vector<Edge<T> > Graph<T>::getEdges(T v) const
{
    return adjList.at(v);
}

// This is a slightly modified BFS
// It either finds a spanning tree and returns true or knows that it wont and
// returs false
template<typename T>
bool Graph<T>::isConnected(const Graph<T>& g)
{
    unordered_set<T> verts = g.getVerts();
    auto v = verts.begin();

    deque<T> unvisited;
    unordered_set<T> visited;

    // Doesn't matter where we start so why not from the .begin()ing
    T root = *v;

    unvisited.push_back(root);

    while(!unvisited.empty()) {
        T cur_node = unvisited.front();
        unvisited.pop_front();
        visited.insert(cur_node);
        vector<Edge<T> > adjs = g.getEdges(cur_node);
        for(Edge<T> e : adjs) {
            T neighbor = e.dest;
            if(visited.find(neighbor) == visited.end()) {
                unvisited.push_back(neighbor);
            }
        }
    }

    // We have reached every vertex we can from the start vertex
    // If that is every node then we have a spanning tree and hence the graph is
    // connected
    if(visited.size() == verts.size()) return true;
    // Otherwise we don't and the graph is disconnected
    return false;
}

// Forward declaration of UndirectedGraph needed so we can declare << operator
// as friend
template<typename T> class UndirectedGraph;
template<typename T> ostream& operator<<(ostream& out, const UndirectedGraph<T>& graph);

// Concrete graph class. Will use UndirectedEdges

// NOTE: This implementation assumes loops and duplicate edges are unecessary so
// it is not as general as it can be
template<typename T>
class UndirectedGraph : public Graph<T>
{
    private:
        // Data members
        unordered_set<UndirectedEdge<T> > edges;

        /* friend class boost::serialization::access; */
        /* template<typename Archive> */
        /* void serialize(Archive & ar, const unsigned int version) */
        /* { */
        /*     ar & boost::serialization::base_object<Graph<T> >(*this); */
        /*     ar & edges; */
        /* } */
    public:
        // Constructors

        UndirectedGraph();
        UndirectedGraph(const UndirectedGraph<T>& other);

        // Accessors and mutators

        int numEdges() const;
        bool addEdge(const T& u, const T& v, double cost);
        unordered_set<UndirectedEdge<T> > allEdges() const;

        friend ostream& operator<< <T> (ostream& out, const UndirectedGraph<T>& graph);
};

template<typename T>
UndirectedGraph<T>::UndirectedGraph()
{
}

template<typename T>
UndirectedGraph<T>::UndirectedGraph(const UndirectedGraph<T>& other)
    : Graph<T>(other), edges(other.edges)
{
}

template<typename T>
int UndirectedGraph<T>::numEdges() const
{
    return edges.size();
}

template<typename T>
bool UndirectedGraph<T>::addEdge(const T& u, const T& v, double cost)
{
    // Make the edge
    UndirectedEdge<T> edge(u, v, cost);

    // Only add edge if it doesn't already exist
    // unordered_set takes care of this for us but I want to know what happens
    // when I try
    // NOTE: Look into if unoredred_set.insert() returns bool and modify
    // accordingly
    if(edges.find(edge) != edges.end()) return false;

    // Do the vertecies actually exist?
    if(Graph<T>::verts.find(u) == Graph<T>::verts.end() || Graph<T>::verts.find(v) == Graph<T>::verts.end()) return false;

    // Do the insertion and return success
    Graph<T>::adjList[u].push_back(UndirectedEdge<T>(u, v, cost));
    Graph<T>::adjList[v].push_back(UndirectedEdge<T>(v, u, cost));
    edges.insert(edge);
    return true;
}

template<typename T>
unordered_set<UndirectedEdge<T> > UndirectedGraph<T>::allEdges() const
{
    return edges;
}

// Output a simple representation of an UndirectedGraph. Just a list of
// vertecies and edges
template<typename T>
ostream& operator<<(ostream& out, const UndirectedGraph<T>& graph)
{
    out << "##Nodes##" << endl;
    for(T v : graph.verts)
    {
        cout << v << " ";
    }
    out << endl << "##Edges##" << endl;
    for(UndirectedEdge<T> edge : graph.edges)
    {
        cout << edge << endl;
    }
    return out;
}

#endif
