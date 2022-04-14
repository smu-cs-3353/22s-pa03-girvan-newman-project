# Project 3 - Community Detection in Networks

By: Braiden Hook and Michael Doherty

Medium Article Links:

Part 1: https://medium.com/@bghook/community-detection-label-propagation-vs-girvan-newman-part-1-c7f8680062c8

Part 2: https://medium.com/@mikecamdo/community-detection-label-propagation-vs-girvan-newman-part-2-c2fb78726db9

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

This output is for every graph that is not the college football graph (the one in the RandomGraph folder). It will list each community and the vertex ids that are inside said community.

![alt text](OutputImages/Barbell_Output_Pic.png)

There will be two output files, one for girvan-newman, and one for label propagation.

### Football Output

When reading in the football graph inside the RandomGraphs folder, it will print out the names followed by the node id in parentheses.

(football output pic)

There will be four output files, one for the community structure like above picture, and another .txt found in the extra folder that will be necessary for the footballOutputGrapher.py.

## Girvan-Newman Algorithm

The Girvan-Newman algorithm is one of the two algorithms we used to separate each of the graphs into communities. The algorithm follows these 4 steps:

1. The betweenness of all existing edges in the network is calculated first.
2. The edge(s) with the highest betweenness are removed.
3. The betweenness of all edges affected by the removal is recalculated.
4. Steps 2 and 3 are repeated until no edges remain.

We slightly adjusted the last part to have the program stop by calculating the modularity of the graph. Whenever the modularity of the graph after removal of the edge with the highest betweenness went below the previous graph’s modularity, the algorithm would stop itself and regress back to the previous graph before removal. That way, the resulting graph would have the best modularity possible.

### Time Efficiency

As the number of edges increased, the time it took for the algorithm to finish grew exponentially. Below is a graph of 100 vertices showcasing this:

(picture of time efficiency for GN)

As such, this algorithm won’t be as viable on larger datasets.

### Output consistency

Every input as one output, meaning you will receive the same number of communities for one dataset no matter how many times you rerun it. As such, if you run the randomGraph2.graphml in the RandomGraphs folder, you will receive the same output as this:

	Communities For Girvan-Newman:

	Community 1

	0
	6
	11
	19
	20
	24
	25
	28

	Community 2

	1
	3
	10
	27
	29

	Community 3

	2
	5

	Community 4

	4
	12
	23

	Community 5

	7
	8
	14
	16
	26

	Community 6

	9
	15
	21
	22

	Community 7

	13
	17
	18

This is unlike other algorithms like the label propagation algorithm (the second one we used) which would output a different number of communities on larger datasets. 

### Football Graph

The average time to run the Girvan-Newman algorithm on the football graph was 27 seconds. It outputted 12 communities with many of the football teams in the correct conference. The only hit was that Central Florida was left all alone in one community. The reason is unknown, it could be due to the dataset itself, or it could be because of how Girvan-Newman works. Below here is the graph output after running it through the footballOutputGrapher.py:

(football graph)

## Label Propagation

The label propagation algorithm is the second algorithm we used to separate each of the graphs into communities.

You can find the comparison on Medium.com at these links:

Part 1: https://medium.com/@bghook/community-detection-label-propagation-vs-girvan-newman-part-1-c7f8680062c8

Part 2: https://medium.com/@mikecamdo/community-detection-label-propagation-vs-girvan-newman-part-2-c2fb78726db9

## How to Build and Execute Python Programs:

To Generate your own graphs or to run the football graph follow these two simple steps:

1. Navigate to the src folder on your command line
2. Run this command:

		python3 RandomGraphGenerator.py

If you want to get the football graph, run footballOutputGrapher.py instead of RandomGraphGenerator.py. It is set to print out the result of the Girvan-Newman Algorithm, however if you wish to output the label propagation football result, swap out ../extra/outputForGraph_GN.txt for ../extra/outputForGraph.txt on line 12.

## Full Football Output for Girvan-Newman

	Communities For Girvan-Newman:

	Community 1

	BrighamYoung (0)
	NewMexico (4)
	SanDiegoState (9)
	Wyoming (16)
	Utah (23)
	ColoradoState (41)
	AirForce (93)
	NevadaLasVegas (104)

	Community 2

	FloridaState (1)
	NorthCarolinaState (25)
	Virginia (33)
	GeorgiaTech (37)
	Duke (45)
	NorthCarolina (89)
	Clemson (103)
	WakeForest (105)
	Maryland (109)

	Community 3

	Iowa (2)
	PennState (6)
	Northwestern (13)
	Wisconsin (15)
	Michigan (32)
	Purdue (39)
	OhioState (47)
	Minnesota (60)
	Illinois (64)
	NotreDame (82)
	MichiganState (100)
	Indiana (106)

	Community 4

	KansasState (3)
	TexasTech (5)
	Baylor (10)
	Colorado (40)
	Kansas (52)
	IowaState (72)
	Nebraska (74)
	TexasA&amp;M (81)
	Oklahoma (84)
	Texas (98)
	Missouri (102)
	OklahomaState (107)

	Community 5

	SouthernCalifornia (7)
	ArizonaState (8)
	UCLA (21)
	Arizona (22)
	Washington (51)
	Oregon (68)
	Stanford (77)
	WashingtonState (78)
	OregonState (108)
	California (111)

	Community 6

	NorthTexas (11)
	ArkansasState (24)
	BoiseState (28)
	Idaho (50)
	NewMexicoState (69)
	UtahState (90)

	Community 7

	NorthernIllinois (12)
	WesternMichigan (14)
	Akron (18)
	BallState (26)
	BowlingGreenState (31)
	Buffalo (34)
	CentralMichigan (38)
	Connecticut (42)
	EasternMichigan (43)
	Kent (54)
	MiamiOhio (61)
	Ohio (71)
	Toledo (85)
	Marshall (99)

	Community 8

	Auburn (17)
	Alabama (20)
	Florida (27)
	Kentucky (56)
	LouisianaTech (58)
	LouisianaMonroe (59)
	Vanderbilt (62)
	MiddleTennesseeState (63)
	MississippiState (65)
	SouthCarolina (70)
	Tennessee (76)
	Mississippi (87)
	Georgia (95)
	LouisianaState (96)
	LouisianaLafayette (97)
	Arkansas (113)

	Community 9

	VirginiaTech (19)
	BostonCollege (29)
	WestVirginia (30)
	Syracuse (35)
	Pittsburgh (55)
	Temple (79)
	Navy (80)
	Rutgers (94)
	MiamiFlorida (101)

	Community 10

	CentralFlorida (36)

	Community 11

	EastCarolina (44)
	Houston (48)
	Louisville (57)
	Memphis (66)
	SouthernMississippi (75)
	Tulane (86)
	Army (91)
	Cincinnati (92)
	AlabamaBirmingham (112)

	Community 12

	FresnoState (46)
	Rice (49)
	SouthernMethodist (53)
	Nevada (67)
	SanJoseState (73)
	TexasElPaso (83)
	Tulsa (88)
	TexasChristian (110)
	Hawaii (114)
