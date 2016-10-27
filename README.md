# Code and datasets for our WWW'17 paper 'Balancing information exposure in social networks'

In this paper, we address the problem of balancing the information exposure in a social network.
We assume that two opposing campaigns (or viewpoints) are present in the network, and network nodes have different preferences to- wards these campaigns. Our goal is to find two sets of nodes to employ in the respective campaigns, so that the overall information-exposure balance in the network is maximized.

The folder contains the 8 algorithms, 4 for each setting Heterogeneous and Correlated.

1. Greedy_{Heterogeneous,Correlated} (The greedy algorithm that selects to add to a campaign the node that optimizes the objective function.)
2. Cover_{Heterogeneous,Correlated} (Cover algorithm, presented in the paper )
3. Common_{Heterogeneous,Correlated} (greedy algorithm that only adds common seeds)
4. Hedge_{Heterogeneous,Correlated} (Algorithm 2)

To run each algorithm, in the respective folder 'make' and run.


e.g. To select 20 seeds using the Greedy algorithm for the Heterogeneous setting, the command would be:

cd Greedy_Heterogeneous/; make; ./Greedy_Heterogeneous ../datasets/brexit/brexit_network_heterogeneous.txt ../datasets/brexit/side1_seeds.txt ../datasets/brexit/side2_seeds.txt 20

------------------------------

datasets/ contains the 6 Twitter datasets we collected.

1. uselections
2. brexit
3. iphone_samsung
4. obamacare
5. abortion
6. fracking

Each folder contains the following files: 

(i) <dataset>_network_{heterogeneous,correlated}.txt -- the network file, of the format <node1> \t <node2> \t <side1 probability> \t <side2 probability> (side2 probability doesnt exist for the correlated case).
(ii) The seed files side1_seeds.txt, side2_seeds.txt

