//
// Created by mikec_g1kgiu8 on 4/11/2022.
//

#include "LabelPropagationAlgo.h"

void LabelPropagationAlgo::runAlgo() {
    struct VertexProperty { //stores the data key in football.graphml
        long dataKey;
    };

    typedef adjacency_list<vecS, vecS, undirectedS, VertexProperty> Graph;
    typedef dynamic_properties Dproperty;

    Graph g;
    Dproperty dp;

    dp.property("value", boost::get(&VertexProperty::dataKey, g));

    std::ifstream graphFile("../RandomGraphs/football.graphml");

    read_graphml(graphFile, g, dp);

    std::map<int, int> node_labels; //holds the current label for each node
    std::map<int, std::vector<int>> neighbor_nodes; //holds the labels of the current node's neighbors

    std::vector<int> nodes; //holds each node in the graph

    for (auto v : boost::make_iterator_range(vertices(g))) {
        //std::cout << "Node " << v << std::endl; FIXME
        node_labels[v] = v; //Initializing each node with its own unique label

        nodes.push_back(v); //adds the current node to the vector of nodes in the graph

        //the following code was found at: https://stackoverflow.com/questions/49898415/boost-library-how-to-get-neighbouring-nodes
        auto neighbors = boost::adjacent_vertices(v, g);
        for (auto vd : make_iterator_range(neighbors)) {
            //std::cout << v << " has adjacent vertex " << vd << std::endl; FIXME
            neighbor_nodes[v].push_back(vd); //adds each neighboring node to the vector
        }
    }

    int counter = 1;
    while (true) { //loop that runs until all nodes have the same label as the majority of their neighbor nodes
//        std::cout << "Iteration " << counter << std::endl; FIXME
        std::shuffle(nodes.begin(), nodes.end(), std::mt19937(std::random_device()())); //randomly shuffles the order in which the nodes will be visited
//        for (int i : nodes) { FIXME
//            std::cout << i << " ";
//        }
//        std::cout << std::endl;

        for (int v : nodes) { //loops through each node (which are randomly sorted)
            //std::cout << "Currently on node " << v << std::endl; //FIXME
            std::unordered_map<int, int> label_frequency;

            int new_label = -1;
            int new_label_frequency = 0;

            std::vector<int> new_label_options;

            for (int i = 0; i < neighbor_nodes[v].size(); i++) {
                label_frequency[node_labels[neighbor_nodes[v].at(i)]] += 1;

                //std::cout << label_frequency[node_labels[neighbor_nodes[v].at(i)]] << std::endl; //FIXME
                if (label_frequency[node_labels[neighbor_nodes[v].at(i)]] > new_label_frequency) {
                    new_label = node_labels[neighbor_nodes[v].at(i)];
                    new_label_frequency = label_frequency[node_labels[neighbor_nodes[v].at(i)]]; //updates the label frequency

                    new_label_options.clear(); //clears the vector of options
                } else if (label_frequency[node_labels[neighbor_nodes[v].at(i)]] == new_label_frequency) { //if multiple neighbor node labels have the same frequency
                    if (new_label_options.empty()) {
                        new_label_options.push_back(new_label);
                    }
                    new_label_options.push_back(node_labels[neighbor_nodes[v].at(i)]);
                }
            }

//            std::cout << "Old label: " << node_labels[v] << std::endl; FIXME
            if (!new_label_options.empty()) { //if multiple neighbor node labels appear the same number of times
                std::shuffle(new_label_options.begin(), new_label_options.end(), std::mt19937(std::random_device()())); //randomly shuffles the options
                node_labels[v] = new_label_options.at(0);
            } else {
                node_labels[v] = new_label;
            }
//            std::cout << "New label: " << node_labels[v] << std::endl; FIXME

        }

//        for (auto v: boost::make_iterator_range(vertices(g))) { FIXME
//            std::cout << "Node " << v << "'s label is " << node_labels[v] << std::endl;
//        }

        bool endAlgo = true; //variable that tells the label propagation to stop

        for (auto v: boost::make_iterator_range(vertices(g))) { //loops through every node
            int inCommon = 0; //counts how many neighbor nodes have the same label as the current node
            //label propagation can stop if the current node has the most frequent label among its neighbor nodes
            std::unordered_map<int, int> label_frequency;
            int most_frequent_frequency = 0;

            for (int i = 0; i < neighbor_nodes[v].size(); i++) {
                if (node_labels[neighbor_nodes[v].at(i)] == node_labels[v]) { //if the current node and the neighbor node have the same label
                    inCommon++;
                }

                label_frequency[node_labels[neighbor_nodes[v].at(i)]] += 1;

                if (label_frequency[node_labels[neighbor_nodes[v].at(i)]] > most_frequent_frequency) {
                    //most_frequent = node_labels[neighbor_nodes[v].at(i)];
                    most_frequent_frequency = label_frequency[node_labels[neighbor_nodes[v].at(i)]];
                }
            }

            if (inCommon < most_frequent_frequency) { //if the current node has a different label than the most frequent label among its neighbor nodes
//                std::cout << "FAILED ON " << v << std::endl; FIXME
                endAlgo = false; //continue label propagation
                break;
            }
        }

        if (endAlgo) {
            break;
        }
        counter++;
//        std::cout << std::endl; FIXME
    }

    std::vector<int> labels; //holds all the labels that define each community

    std::ofstream output("../extra/outputForGraph.txt");

    for (auto v: boost::make_iterator_range(vertices(g))) {
        if (std::find(labels.begin(), labels.end(), node_labels[v]) == labels.end()) {
            labels.push_back(node_labels[v]);
        }
        output << node_labels[v] << std::endl;
    }

    output.close();

    std::sort(labels.begin(), labels.end()); //sorts the vector by increasing numerical order

    output.open("../output/LabelPropagationOutput.txt"); //output file containing data on the communities

    for (int i = 0; i < labels.size(); i++) { //outputs the communities generated
        std::cout << "Community " << i + 1 << std::endl;
        output << "Community " << i + 1 << std::endl;
        std::ifstream input("../extra/schoolNames.txt");
        int counter2 = 0;
        while (!input.eof()) {
            std::string name;
            input >> name;
            if (node_labels[counter2] == labels.at(i)) {
                std::cout << name << "'s label is " << node_labels[counter2] << std::endl;
                output << name << "'s label is " << node_labels[counter2] << std::endl;
            }
            counter2++;
        }
        input.close();
        std::cout << std::endl;
        output << std::endl;
    }
}
