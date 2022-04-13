//
// Created by mikec_g1kgiu8 on 4/11/2022.
//

#ifndef INC_22S_PA03_GIRVAN_NEWMAN_A_LONER_S_REGRET_LABELPROPAGATIONALGO_H
#define INC_22S_PA03_GIRVAN_NEWMAN_A_LONER_S_REGRET_LABELPROPAGATIONALGO_H

#include <iostream>
#include <map>
#include <random>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/range/irange.hpp>

#include <boost/graph/graph_utility.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/graph/connected_components.hpp>

using namespace boost;

class LabelPropagationAlgo {
    public:
        void runAlgo(char*);
};


#endif //INC_22S_PA03_GIRVAN_NEWMAN_A_LONER_S_REGRET_LABELPROPAGATIONALGO_H
