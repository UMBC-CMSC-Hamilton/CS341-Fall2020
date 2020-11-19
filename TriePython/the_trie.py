class Node:

    def __init__(self, letter, star=False):
        """
            This is the class constructor.  It's a method called __init__
            notice in a class the first argument is always self in all of the functions
            C++ (this), Python (self).  It forces you to pass self explicitly.
        """
        self.letter = letter
        self.star = star
        self.count = 0
        self.children = {}


class Trie:
    def __init__(self):
        self.root = Node('root')

    def insert_word(self, word):
        current = self.root
        for letter in word:
            if letter not in current.children:
                current.children[letter] = Node(letter) # O(1) access time for each child
                # vector<Node *>
                # for (auto node : children_vector) # O(N) search for the individual child
                # HashTable<Node *> keys = letters. O(1), bit more messy in C++ STL.

            current = current.children[letter]
        current.star = True
        current.count += 1

    def find_word(self, word):
        current = self.root
        for letter in word:
            if letter not in current.children:
                return False
            current = current.chidlren[letter]
        # if it's actually a word
        return current.count

    def autocomplete(self, partial):
        """
        full traversal of the subtree.
        :param partial:
        :return: a list of words which are matches to the partial string.
        """
        results = []
        original_partial = partial
        # python passes lists by reference.
        current = self.root
        while partial:
            letter = partial[0]
            if letter in current.children:
                current = current.children[letter]
            else:
                return []
            # slice that takes the element partial[1], partial[2]... partial[len(partial) - 1]
            # slices off the first letter.
            partial = partial[1:]

        self.autocomplete_help(original_partial, current, results)
        return results

    def autocomplete_help(self, partial, current, results):
        for child_letter in current.children:
            if current.children[child_letter].star:
                results.append(partial + child_letter)
            self.autocomplete_help(partial + child_letter, current.children[child_letter], results)

    def display(self, current, tab_level):
        total_string = '\t' * tab_level + current.letter
        if current.star:
            total_string += "*"
        total_string += "\n"

        for child_letter in current.children:
            total_string += self.display(current.children[child_letter], tab_level + 1)

        return total_string

    def __repr__(self):
        """
        __repr__ is an operator overload in python, basically it overloads the str(...) cast.
        :return: a string
        """
        return self.display(self.root, 0)


if __name__ == '__main__':
    my_trie = Trie()
    s = input('Enter command: ')
    while s.strip().lower() != 'quit':
        split_word = s.lower().split()
        if len(split_word) == 2:
            command, word = s.lower().split()
            if command == 'add':
                my_trie.insert_word(word)
                print(word, 'has been inserted.')
            elif command == 'complete':
                print(my_trie.autocomplete(word))
            elif command == 'find':
                print(my_trie.find_word(word))
            elif command == 'load' and word == 'file':
                with open('words.txt') as word_file:
                    for word in word_file:
                        my_trie.insert_word(word.strip().lower())

        # print(my_trie)
        s = input('Enter command: ')
