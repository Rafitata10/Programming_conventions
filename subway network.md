# Problem A: Subway Network

The city of Metropolis is planning the construction of its new metro network. The mayor has decided that all metro lines must start from the central station located at coordinates (0, 0). Additionally, to minimize costs, it is important that the number of metro lines is as small as possible while ensuring that all key points in the city are connected.

Each metro line can extend in a straight direction from the central station. A key point in the city is considered "covered" by a metro line if the perpendicular distance from that point to the line is less than or equal to a maximum allowed distance $d$.

Given a set of coordinates for the key points in the city, your task is to determine the minimum number of metro lines required to cover all the points.

## Input:
The program will receive multiple datasets. The format for each dataset is as follows:
- The first line contains two integers $n$ and $d$:
  - $n$ $(1 ≤ n ≤ 1000)$: the number of key points.
  - $d$ $(0 ≤ d ≤ 1000)$: the maximum allowed distance for a point to be considered covered by a metro line.
- The following $n$ lines each contain two integers $x$ and $y$ $(-1000 ≤ x, y ≤ 1000)$, which represent the coordinates of a key point in the city.

The input ends when no more datasets are provided.

## Output:
For each dataset, print a single line containing the minimum number of metro lines required to cover all the key points.

## Sample Input
3 1.0 // 
1 0 // 
0 1 // 
-1 0 // 
4 0.5 // 
1 1 // 
1 -1 // 
-1 1 // 
-1 -1 // 

## Sample Output
1 // 
2
