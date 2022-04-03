//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <iostream>

#include <ctime>

int main() {
    using namespace boost;
    typedef adjacency_list<vecS, vecS, undirectedS, no_property, no_property> Graph;
    typedef dynamic_properties Dproperty;
    Graph g;
    Dproperty dp;

    std::ifstream graphFile ("../RandomGraphs/randomGraph.graphml");

    read_graphml(graphFile, g, dp);



}