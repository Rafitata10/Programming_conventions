# Problem J: Juice

In the Favela of Rio de Janeiro there was a flicker of light. After months of careful building, they finally connected the generator to the thousands of extension cords and the slum was illuminated by millions of bright lights. . . However, the capacity of the extension cords was not enough to meet the energy demands of all the houses in the slum. Thus, the engineers had to carefully select which houses should be powered, and which should not, prior to connecting the power generator. Their idea was to power as many houses as possible, based on the energy demands of each house, and the capacity of the extension cords. More specifically, the generator and each of the houses are represented by nodes, and extension cords are represented by edges between these. Thus, each node gets power from exactly one other node. In addition, each node except the generator node has a non-negative power demand. The generator produces an amount of energy that far surpasses the total capacity of the extension cords connected to it, and can thus be treated as an infinite energy source. Given the same data, find out how many houses the engineers were able to cover the energy demands of.

## Input:
The first line of the input contains a single integer $0 ≤ n ≤ 1000$, the number of houses in the slum. Then follow $n$ lines in the format $p_i\; r_i\; c_i$, where $0 ≤ p_i ≤ n$ is the parent node of house $i$, $0 ≤ r_i ≤ 100$ is the energy demand of house $i$ and $1 ≤ c_i ≤ 100$ is the capacity of the extension cord connecting house $i$ to house $p_i$. The power generator has index 0.

## Output:
Output the maximum number of power requirements that can be met.

## Sample Input
3 - 
0 3 2 - 
0 100 100 - 
1 1 1 - 

## Sample Output
2
