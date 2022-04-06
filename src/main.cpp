//
// Created by mikec_g1kgiu8 on 4/4/2022.
//
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/parameter/parameters.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <boost/range/irange.hpp>

using namespace std;
using namespace boost;

int main() {
    typedef adjacency_list<vecS, vecS, undirectedS, no_property, no_property> Graph;
    typedef dynamic_properties Dproperty;

    Graph g;
    Dproperty dp;

    
}