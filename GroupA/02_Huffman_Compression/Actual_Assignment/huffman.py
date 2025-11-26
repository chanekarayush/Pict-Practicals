"""
    Write a program to encode a message using huffman encoding and greedy strategy.
    Maybe we'll also write a decompression algorithm to decipher the message too.
"""
from collections import Counter 
import heapq

class Node:
    def __init__(self, char, freq=0):
        """The freq will be used to count the frequency and the char will contain the dword character"""
        self.freq: int = freq
        self.left = None
        self.right = None
        self.char = char
global freq_heap
freq_heap = []

def calc_freq(data):
    """Counts the frequency of values in the input stream of data."""
    freq_table = Counter(data)
    global freq_heap
    freq_heap = [Node(char, freq) for char, freq in freq_table.items()]
    heapq.heapify(freq_heap)
    return freq_heap


def build_huffman_tree(freq_heap:list):
    """Building the huffman tree using frequency table from `calc_freq`"""
    while len(freq_heap)>1:
        left = heapq.heappop(freq_heap) 
        right = heapq.heappop(freq_heap)
        
        merged = Node(None, freq.left+freq.right)
        heapq.heappush(freq_heap, merged)
    
    return freq_heap[0]


def generate_huffman_tree(node, curr_code, codes):
    if node is None:
        return None
    
    if node.char is not None:
        codes[node.char] = curr_code

        generate_huffman_tree(node.left, curr_code+'0', codes)
        generate_huffman_tree(node.right, curr_code+'1', codes)


def huffman_encoding(word):
    global nodes
    nodes = []
    calc_freq(word)
    root = build_huffman_tree()
    codes = {}
    generate_huffman_tree(root, '', codes)
    return codes



word = "lossless"
codes = huffman_encoding(word)
encoded_word = ''.join(codes[char] for char in word)

print("Word:", word)
print("Huffman code:", encoded_word)
print("Conversion table:", codes)


