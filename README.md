# Project 3 - Community Detection in Networks

By: Braiden Hook and Michael Doherty

Medium Article Links:

https://medium.com/@bghook/community-detection-label-propagation-vs-girvan-newman-part-1-c7f8680062c8

https://medium.com/@mikecamdo/community-detection-label-propagation-vs-girvan-newman-part-2-c2fb78726db9

## Scenario

In this project we impletemented the community detection algorithm proposed by Girvan and Newman on computer randomized graphs and the college football dataset.

## How to build and execute

Follow these steps using the command line to execute the program:

1. Clone the git repo using the command line:

        git clone https://github.com/smu-cs-3353/22s-pa03-girvan-newman-a-loner-s-regret
        
2. Navigate back to the main directory which contains the CMakeLists.txt.
3. Create a build directory with:

        mkdir build

4. cd into the new build folder.
5. Build cmake with:

        cmake ..
        
6. Then to get the executable use:

        cmake --build .
        
7. Lastly to run the program (executable, then the graphml pathname):
  
        ./22s_pa03_girvan_newman_a_loner_s_regret ../RandomGraphs/football.graphml
        
There are graphs available for you to use in the RandomGraphs folder, however you can provide your own as well. It simply needs to be in graphml format.

## Output

After the program is complete, you will receive an output showing the community structure for the inputted graph.

There are two different types of output. The first outputs the community structure while labeling the nodes with integers. The other is specialized for the college football graph.

### Normal Output

![alt text](OutputImages/Barbell_Output_Pic.png)

This output is for every graph that is not the college football graph (the one in the RandomGraph folder). It will list each community and the vertex ids that are inside said community. There will be two output files, one for girvan-newman, and one for label propagation.






Football Output

When reading in the football graph inside the RandomGraphs folder, it will print out the names followed by the node id in parentheses.

(football output pic)


It will also give you an output .txt file (found in extra) that will be necessary for the footballOutputGrapher.py. 


Girvan-Newman Algorithm

The Girvan-Newman algorithm is one of the two algorithms we used to separate each of the graphs into communities. The algorithm follows these 4 steps:

1.	The betweenness of all existing edges in the network is calculated first.
2.	The edge(s) with the highest betweenness are removed.
3.	The betweenness of all edges affected by the removal is recalculated.
4.	Steps 2 and 3 are repeated until no edges remain.

We slightly adjusted the last part to have the program stop by calculating the modularity of the graph. Whenever the modularity of the graph after removal of the edge with the highest betweenness went below the previous graph’s modularity, the algorithm would stop itself and regress back to the previous graph before removal. That way, the resulting graph would have the best modularity possible.

	Time Efficiency

As the number of edges increased, the time it took for the algorithm to finish grew exponentially. Below is a graph of 100 vertices showcasing this:

(picture of time efficiency for GN)

As such, this algorithm won’t be as viable on larger datasets.

	Output consistency

Every input as one output, meaning you will receive the same number of communities for one dataset no matter how many times you rerun it. As such, if you run the randomGraph2.graphml in the RandomGraphs folder, you will receive the same output as this:

(output for randomGraph2)
This is unlike other algorithms like the label propagation algorithm (the second one we used) which would output a different number of communities on larger datasets. 

	Football Graph

The average time to run the Girvan-Newman algorithm on the football graph was 27 seconds. It outputted 12 communities with many of the football teams in the correct conference. The only hit was that Central Florida was left all alone in one community. The reason is unknown, it could be due to the dataset itself, or it could be because of how Girvan-Newman works. Below here is the graph output after running it through the footballOutputGrapher.py:

(football graph)

Label Propagation

The label propagation algorithm is the second algorithm we used to separate each of the graphs into communities.

You can find the comparison on Medium.com at these links:

Part 1: Medium link
Part 2: Medium link

How to Build and Execute Python Programs:

To Generate your own graphs or to run the football graph follow these two simple steps:

1.	Navigate to the src folder on your command line
2.	Run this command:
 python3 RandomGraphGenerator.py

If you want to get the football graph run footballOutputGrapher.py instead of RandomGraphGenerator.py. It is set to print out the result of the Girvan-Newman Algorithm, however if you wish to output the label propagation football result, swap out ../extra/outputForGraph_GN.txt for ../extra/outputForGraph.txt.

Full Football Output for Girvan-Newman

…
