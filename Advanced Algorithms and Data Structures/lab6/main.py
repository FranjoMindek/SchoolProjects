from typing import Tuple
import numpy as np

# infinite value
INF = 10 ** 6 - 1


def wfi(weight_matrix: np.ndarray, start: int, end: int) -> Tuple[np.ndarray, list]:
    """
    Implementation of the WFI algorithm with recreation of the route between two edges.
    Args:
        weight_matrix (np.ndarray): Weight matrix representation of the graph.
        start (int): Starting node in the route.
        end (int): Ending node in the route.
    Returns:
        np.ndarray: Distance matrix of the WFI algorithm.
        list: List of nodes on the route between starting and ending node including starting
            and ending node.
    """
    distance = weight_matrix
    next = np.full_like(weight_matrix, -1)  # init all values to -1

    # TODO: Implement the rest of the function.

    # initialize the next matrix - assign value where the distance is not inf
    for i in range(distance.shape[0]):
        for j in range(distance.shape[1]):
            if distance[i][j] != np.inf:
                next[i][j] = i  # mora biti i

    # WFI algorithm implementation with the next array update
    for k in range(distance.shape[0]):
        for i in range(distance.shape[0]):
            for j in range(distance.shape[1]):                        # po uzoru na pseudokod:
                if distance[i][k] + distance[k][j] < distance[i][j]:  # nova udaljenost je manja
                    distance[i][j] = distance[i][k] + distance[k][j]  # promijeni udaljenost
                    next[i][j] = next[k][j]                           # promijeni putanju

    # reconstruct the shortest path from start to end - create a list named path
    path = [end]
    node = end
    while node != start:
        node = next[start][node]
        path.append(node)
    path.reverse()

    return distance, path


W = np.array([
    [0, 2, INF, INF],
    [INF, 0, 3, -1],
    [-1, INF, 0, 7],
    [3, INF, INF, 0]])

distance, path = wfi(W, 0, 3)
print(distance, path)
assert distance == [[0, 2, 5, 1], [2, 0, 3, -1], [-1, 1, 0, 0], [3, 5, 8, 0]]
assert path == [0, 1, 3]

