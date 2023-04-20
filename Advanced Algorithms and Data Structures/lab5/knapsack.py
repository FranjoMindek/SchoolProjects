from typing import List
from collections import namedtuple

Item = namedtuple('Item', ['weight', 'value'])


def createKnapsackTable(n_items: int, capacity: int) -> List[List[int]]:
    return [[0] * (capacity + 1) for _ in range(n_items + 1)]


# 0-1 Knapsack bottomup
# def knapsack(items: List[Item], capacity: int) -> List[List[int]]:
#
#     table = createKnapsackTable(len(items), capacity)

def knapsack(items: List[Item], capacity: int) -> List[List[int]]:

    table = createKnapsackTable(len(items), capacity)

    for i in range(1, len(items) + 1):
        for j in range(1, capacity + 1):
            if j < items[i - 1].weight:
                # the item is too heavy, we cannot include it
                table[i][j] = table[i - 1][j]
            else:
                # we need to decide whether to include the item or not
                # we take the maximum value of either including the item or not
                table[i][j] = max(table[i - 1][j],
                                  table[i - 1][j - items[i - 1].weight] + items[i - 1].value)

    return table

test_items = [Item(3, 9), Item(10, 20), Item(1, 2), Item(9, 15), Item(5, 12), Item(3, 9)]

res = knapsack(test_items, 15)

for j in range(0, len(res[0])):
    for i in range(0, len(res)):
        print(res[i][j], end=" ")
    print()
print(res)