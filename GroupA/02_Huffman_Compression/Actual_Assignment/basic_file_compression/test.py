import os
from collections import Counter

class Node:
    def __init__(self, char='', freq=0) -> None:
        self.char = char
        self.freq = freq 
        self.right = None
        self.left = None


def calcFrequencies(word: str, nodes: list)->list:
    frequencies = dict(Counter(word))
    for char, freq in frequencies.items():
        nodes.append(Node(char, freq))
    return nodes


def buildHuffmanTree(nodes: list):
    while len(nodes) > 1:
        nodes.sort(key= lambda x:x.freq)
        left = nodes.pop(0)
        right = nodes.pop(0)

        mergedNode = Node(freq=left.freq+right.freq)
        mergedNode.left = left 
        mergedNode.right = right

        nodes.append(mergedNode)

    return nodes[0]


def generate_huffman_codes(node, current_code, codes):
    if node is None:
        return

    if node.char is not None:
        codes[node.char] = current_code

    generate_huffman_codes(node.left, current_code + '0', codes)
    generate_huffman_codes(node.right, current_code + '1', codes)


def huffman_encoding(word):
    nodes = calcFrequencies(word, [])
    root = buildHuffmanTree(nodes)
    codes = {}
    generate_huffman_codes(root, '', codes)
    return codes


def addPadding(encoded_word: str) -> str:
    charsRequired = ((8 - len(encoded_word) % 8) % 8)*'0'
    return encoded_word+charsRequired


def convertToBytes(epWord: str) -> list:
    byteList = []
    for i in range(0, len(epWord), 8):
        byteList.append(int(epWord[i:i+8], 2))
    return byteList


def writeToFile(byteList: list, filePath: str)->None:

    try:
        with open(filePath, 'wb') as f:
            f.write(bytes(byteList))
    except Exception as e:
        print(e.__cause__)

def readFromFile(filePath: str)->str:
    input = ""
    with open(filePath, 'r') as f:
        input = f.read()
    return input



if __name__ == "__main__":
    menustring="""
    Enter 1. CLI Input 
          2. File Input 
    """
    menu = int(input(menustring))

    if menu == 1:
        inputStream = input("Please Enter text to be encoded: ")
        codes = huffman_encoding(inputStream)
        encoded_word = ''.join(codes[char] for char in inputStream)
        
        print(codes)
        print(encoded_word)
    elif menu == 2:
        files = os.listdir()
        print(f"Displaying contents in current working directory: {os.getcwd()}")
        for i, x in enumerate(files):
            print(f"{i}\t\b\b: {x}")
        
        inputFilePath = input("Please Enter the path to your input file: ").strip()
        inputStreamData = readFromFile(inputFilePath)
        huffman_codes = huffman_encoding(inputStreamData)
        enc_word = ''.join(huffman_codes[char] for char in inputStreamData)
        ep_word = addPadding(enc_word)
        byteList = convertToBytes(ep_word)
        writeToFile(byteList, input("Please Enter the path to your output file.").strip())


