from collections import namedtuple
from typing import List
import math

def create_table(N: int, M: int) -> List[List[int]]:
    """
    Creates a table (list of lists) with M columns and N rows, filled with 0.
    The table is of dimension (N+1)x(M+1).

    Args:
        N (int): The number of rows (+1) in the table. The index of the last row.
        M (int): The number of columns (+1) in the table. The index of the last column.
    """
    return [[0] * (M + 1) for _ in range(N + 1)]


InvestmentOption = namedtuple(
    "InvestmentOption", ["required_investment", "potential_profit"]
)
"""
A tuple class representing a single investment option.

Attributes:
    required_investment: int
        The required amount you need to invest to get the potential profit.
    potential_profit: int
        The potential amount you can earn by investing.
"""

def optimize_investment(
    options: List[InvestmentOption],
    max_budget: int
) -> List[List[int]]:
    """
    Calculates the table of best profits for the given maximal budget.

    Args:
        options (List[InvestmentOption]): List of InvestmentOption objects representing different options.
        max_budget (int): The maximum amount of money to invest.

    """
    # TODO: Create the table with the appropriate dimensions. Replace the '<N_rows>' and '<M_columns' arguments.
    # gcd = math.gcd(*[option.required_investment for option in options])
    m = max_budget // 1000
    table = create_table(len(options), m)
    for i in range(1, len(options) + 1):
        for j in range(1, m + 1):
            if j*1000 < options[i - 1].required_investment:
                # the item is too heavy, we cannot include it
                table[i][j] = table[i - 1][j]
            else:
                # we need to decide whether to include the item or not
                # we take the maximum value of either including the item or not
                table[i][j] = max(table[i - 1][j],
                                  table[i - 1][(j*1000 - options[i - 1].required_investment)//1000] + options[i - 1].potential_profit)

    # TODO: Iterate through the options in O(n*m) and calculate the optimal profits.
    return table



options = [
    InvestmentOption(required_investment=4000, potential_profit=41000),
    InvestmentOption(required_investment=3000, potential_profit=40000),
    InvestmentOption(required_investment=8000, potential_profit=42000),
    InvestmentOption(required_investment=1000, potential_profit=48000),
    InvestmentOption(required_investment=5000, potential_profit=34000),
    InvestmentOption(required_investment=2000, potential_profit=44000),
]
budget = 15000
print(optimize_investment(options, budget))
assert optimize_investment(options, budget) == [
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [
        0,
        0,
        0,
        0,
        41000,
        41000,
        41000,
        41000,
        41000,
        41000,
        41000,
        41000,
        41000,
        41000,
        41000,
        41000,
    ],
    [
        0,
        0,
        0,
        40000,
        41000,
        41000,
        41000,
        81000,
        81000,
        81000,
        81000,
        81000,
        81000,
        81000,
        81000,
        81000,
    ],
    [
        0,
        0,
        0,
        40000,
        41000,
        41000,
        41000,
        81000,
        81000,
        81000,
        81000,
        82000,
        83000,
        83000,
        83000,
        123000,
    ],
    [
        0,
        48000,
        48000,
        48000,
        88000,
        89000,
        89000,
        89000,
        129000,
        129000,
        129000,
        129000,
        130000,
        131000,
        131000,
        131000,
    ],
    [
        0,
        48000,
        48000,
        48000,
        88000,
        89000,
        89000,
        89000,
        129000,
        129000,
        129000,
        129000,
        130000,
        163000,
        163000,
        163000,
    ],
    [
        0,
        48000,
        48000,
        92000,
        92000,
        92000,
        132000,
        133000,
        133000,
        133000,
        173000,
        173000,
        173000,
        173000,
        174000,
        207000,
    ],
]