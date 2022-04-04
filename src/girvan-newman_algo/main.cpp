//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <iostream>
#include <boost/parameter/parameters.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <boost/range/irange.hpp>

using namespace boost;

//// This class is apart of tests, trying to see how to calculate shortest paths and stuff
template < typename TimeMap >
class bfs_time_visitor : public default_bfs_visitor
{
    typedef typename property_traits< TimeMap >::value_type T;

public:
    bfs_time_visitor(TimeMap tmap, T& t) : m_timemap(tmap), m_time(t) {}
    template < typename Vertex, typename Graph >
    void discover_vertex(Vertex u, const Graph& g) const
    {
        put(m_timemap, u, m_time++);
    }
    TimeMap m_timemap;
    T& m_time;
};

int main() {
    typedef adjacency_list<vecS, vecS, undirectedS, no_property, no_property> Graph;
    typedef dynamic_properties Dproperty;
    Graph g;
    Dproperty dp;

    std::ifstream graphFile ("../RandomGraphs/test.graphml");


    read_graphml(graphFile, g, dp);

    //// Testing a few things here
    //// Will most likely scrap unless I am onto something....
    // Typedefs
    typedef graph_traits< Graph >::vertices_size_type Size;

    // a vector to hold the discover time property for each vertex
    std::vector< Size > dtime(num_vertices(g));
    typedef iterator_property_map< std::vector< Size >::iterator,
            property_map< Graph, vertex_index_t >::const_type >
            dtime_pm_type;
    dtime_pm_type dtime_pm(dtime.begin(), get(vertex_index, g));

    Size time = 0;

    bfs_time_visitor< dtime_pm_type > vis(dtime_pm, time);
    breadth_first_search(g, vertex(4, g), visitor(vis));

    // Use std::sort to order the vertices by their discover time
    std::vector< graph_traits< Graph >::vertices_size_type > discover_order(6);
    integer_range< int > range(0, 6);
    std::copy(range.begin(), range.end(), discover_order.begin());
    std::sort(discover_order.begin(), discover_order.end(),
              indirect_cmp< dtime_pm_type, std::less< Size > >(dtime_pm));

    std::cout << "order of discovery: ";
    for (int i = 0; i < 6; ++i)
        std::cout << discover_order[i] << " ";
    std::cout << std::endl;

    //// End of testing things

    // Printing edges
    for (auto v : boost::make_iterator_range(vertices(g))) {
        for (auto oe : make_iterator_range(out_edges(v, g))){
            std::cout << "Edge " << oe << std::endl;
        }
    }


//    for (auto vd : boost::make_iterator_range(vertices(g))) {
//        std::cout << vd << std::endl;
//    }

//    Graph::vertex_iterator iter, iterEnd;
//
//    for (boost::tie(iter, iterEnd) = vertices(g); iter != iterEnd; ++iter) {
//        std::cout << *iter << std::endl;
//    }

    /*for (int i = 0; i < g.m_edges.size(); i++){
        std::cout << g.m_edges[0].m_source << "-" << g.m_edges[0].m_target << std::endl;
    }*/
    int i = 0;
}