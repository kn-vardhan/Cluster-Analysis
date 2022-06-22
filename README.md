# Cluster-Analysis

Group Project as part of course evaluation for MA2233 - Data Structures & Applications Lab

Clustering is the task of assigning a set of objects into groups so that the objects in the same cluster are more similar to each other than to those in other clusters.

Given a set of N data points, a minimum spanning tree is a spanning tree that connects all the data points either by a direct edge or by a path and has minimum total weight. 
The total weight is the sum of the weights of all the edges of the spanning tree.

In MST based clustering, the weights of each edge are usually considered as the distance between the end points forming the edge. 
Removal of the longest edge results in 2 clusters. Removal of the next longest edge results in 3 clusters, and so on.


### Implementation

- Generating $N$ random points in 2-D and forming $k$ clusters.
- Using the Euclidean distance formula $D = \sqrt{(x_1-x_2)^2 + (y_1-y_2)^2}$, forming a Minimum Spanning Tree (MST).
- Implementing a menu-driven MST clustering based on two termination criteria.
  - Number of pre-determined clusters
  - Setting maximum threshold of edge weight

> For simplicity purpose, we have fixed the value of $N$ as $15$, i.e., 15 random points
