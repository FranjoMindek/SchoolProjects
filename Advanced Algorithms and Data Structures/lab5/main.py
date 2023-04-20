from typing import Tuple


def rabin_karp(pattern: str, txt: str, q: int = 101, d: int = 256) -> list:
    """
    Implementation of the Rabin Karp algorithm for 
    searching longest prefix in dictionary.
    Args:
        pattern (str): Input pattern.
        txt (str): Input text.
        d (int): Number of characters in the input alphabet.
    Returns:
        list: Starting indices.
    """
    M, N, i, j, p, t, h = len(pattern), len(txt), 0, 0, 0, 0, 1
    res = []
    for i in range(M - 1):
        h = (h * d) % q
    for i in range(M):
        p = (d * p + ord(pattern[i])) % q
        t = (d * t + ord(txt[i])) % q
    for i in range(N - M + 1):
        if p == t:
            for j in range(M):
                if txt[i + j] != pattern[j]:
                    break
                else:
                    j += 1
            if j == M:
                res.append(i)
        if i < N - M:
            t = (d * (t - ord(txt[i]) * h) + ord(txt[i + M])) % q
            if t < 0:
                t = t + q
    return res


def search_string(D: list, L: list, dict_len: int = 4) -> Tuple[int, int]:
    """
    Search string in dictionary.
    Args:
        D (list): Dictionary list.
        L (list): Lookahead list.
        dict_len (int): Length of dictionary.
    Returns:
        Tuple [int, int]: Tuple containing distance from the end 
             of the dictionary of the longest prefix and length of the
             longest prefix (is always less or equal than the length of lookahead).
             If no prefix is found in dictionary return (-1, -1).
    """
    for j in range(len(L), 0, -1):
        r1 = rabin_karp(L[0:j], D + L)
        r2 = list(filter(lambda x: x < dict_len, r1))
        if len(r2) > 0:
            i = (dict_len - 1) - max(r2)
            return (i, j)
    return (-1, -1)


def LZ77Encode(input: str, dict_len: int = 4, la_len: int = 4) -> list:
    """
    Function implements the LZ77 encoding algorithm.
    Args:
        input (str): Input string to the algorithm.
        dict_len (int): Lenght of the dictionary.
        la_len (int): Lenght of the lookahead.
    Returns:
        list: List where the first element is the first character and subsequent elements are tuple (i,j,k)
    """
    # TODO: Implement the LZ77 encoding algorithm`
    lookahead, input = input[:la_len], input[la_len:]
    dictionary = lookahead[0]*dict_len  # initialize the dict
    response = []
    response.append(lookahead[0])
    while len(lookahead) > 0:
        (i, j) = search_string(dictionary, lookahead, dict_len)
        if i == -1:
            i, j, k = 0, 0, lookahead[0]  # slucaj kada nema prefixa lookaheada
        else:
            if j == len(lookahead):
                j, k = j-1, lookahead[-1]  # osiguramo da uvijek uzmemo '1 znak' kao trecu vrijednsot, cak i ako imamo max lookahead
            else:
                k = lookahead[j]
        response.append((i, j, k))
        temp = dictionary + lookahead + input
        dictionary = temp[j+1 : j+1+dict_len]
        lookahead = temp[j+1+dict_len : j+1+dict_len+la_len]
        input = temp[j+1+dict_len+la_len:]
    return response


ress = LZ77Encode("ABECEDA")
print(ress)
