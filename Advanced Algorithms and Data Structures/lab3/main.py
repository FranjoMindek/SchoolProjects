from typing import Tuple


class TrieNode:
    """
    A class to represent a node in a trie
    that contains only the pointers to the used characters
    (as opposed to the whole vocabulary array).

    ...

    Attributes
    ----------

    children : dict[str, TrieNode]
        pointers to the children nodes (for successive characters)
    """

    def __init__(self) -> None:
        self.children = {}


class Trie:

    def __init__(self, terminal: str = '$'):
        self.root = TrieNode()
        self.terminal = terminal

    def insert(self, word: str) -> None:
        """Inserts a word into the trie.

        Args:
            word (str): word to insert
        """
        if self.terminal in word:
            raise Exception(
                f'Explicit terminal ({self.terminal}) use is not allowed within words!')

        node = self.root
        for char in word:

            # if char in node.children:
            if char in node.children:
                node = node.children[char]
            else:
                new_node = TrieNode()
                node.children[char] = new_node
                node = new_node
            # pass
            # TODO: implement the remainder of insertion
        pointer_dict = node.children  # TODO: fill in with the right object

        # proper terminating the word
        if self.terminal not in pointer_dict:
            pointer_dict[self.terminal] = None

    def search_prefix(self, prefix: str) -> Tuple[bool, TrieNode]:
        """Searches for given prefix in the trie

        Args:
            prefix (str): search term

        Returns:
            bool: True, if the prefix exists in trie
            TrieNode: - THE node that contains all suffixes of the prefix in trie,
                           if the prefix is contained
                      - None, if the prefix is not found
        """
        if self.terminal in prefix:
            raise Exception(
                f'Explicit terminal ({self.terminal}) use is not allowed within words!')
        node = self.root
        for char in prefix:
            if char not in node.children:
                return False, None
            node = node.children[char]
            # pass
            # TODO: fill in the missing code

        return True, node

    def search(self, word: str) -> bool:
        """Returns if the word is in the trie.

        Args:
            word (str): searching term

        Returns:
            bool: True, if the word is in trie
                  False, otherwise
        """
        found, node = self.search_prefix(word)
        return found and self.terminal in node.children
        # TODO: implement the function


test_trie1 = Trie()

vocabulary = ['cikla', 'cifar', 'aminokiselina', 'aminosulfat', 'amino']
[test_trie1.insert(word) for word in vocabulary]

print(list(test_trie1.root.children.keys()))
print(list(test_trie1.root.children['c'].children.keys()))
print(list(test_trie1.root.children['c'].children['i'].children.keys()))
# print(list(test_trie1.root.children['c'].children['i'].children['k'].children.keys()))
# print(list(test_trie1.root.children['c'].children.keys()))

search_terms = ['ami', 'amino', 'cikla', 'zirafa', 'cifara']
search_results = []
prefix_results = []
for term in search_terms:
    search_results.append(test_trie1.search(term))
    prefix_results.append(test_trie1.search_prefix(term)[0])

print('search results: ', search_results)
print('prefix search results: ', prefix_results)

# test_trie1.insert('ami$') # causes exception
# test_trie1.search('ami$') # causes exception

# ['c', 'a']
# search results:  [False, True, True, False, False]
# prefix search results:  [True, True, True, False, False]

