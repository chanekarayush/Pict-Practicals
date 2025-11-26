import pickle
from collections import Counter

class Node:
    def __init__(self, char=None, freq=0):
        self.char = char
        self.freq = freq
        self.left = None
        self.right = None

def calculate_frequencies(data):
    frequencies = Counter(data)
    return [Node(byte, freq) for byte, freq in frequencies.items()]

def build_huffman_tree(nodes):
    nodes = nodes[:]  # copy list to avoid mutation outside
    while len(nodes) > 1:
        nodes.sort(key=lambda x: x.freq)
        left = nodes.pop(0)
        right = nodes.pop(0)
        merged = Node(freq=left.freq + right.freq)
        merged.left = left
        merged.right = right
        nodes.append(merged)
    return nodes[0]

def generate_huffman_codes(node, current_code, codes):
    if node is None:
        return
    if node.char is not None:
        codes[node.char] = current_code if current_code else '0'  # Handle single-char edge case
    generate_huffman_codes(node.left, current_code + '0', codes)
    generate_huffman_codes(node.right, current_code + '1', codes)

def encode_data(data, codes):
    return ''.join(codes[byte] for byte in data)

def pad_encoded_bits(encoded_bits):
    padding = 8 - (len(encoded_bits) % 8)
    if padding == 8:
        padding = 0
    encoded_bits += '0' * padding
    padded_info = f"{padding:08b}"  # Store padding in first byte
    return padded_info + encoded_bits

def get_byte_array(padded_encoded_bits):
    byte_array = bytearray()
    for i in range(0, len(padded_encoded_bits), 8):
        byte = padded_encoded_bits[i:i+8]
        byte_array.append(int(byte, 2))
    return byte_array

def compress_file(input_path, output_path):
    with open(input_path, 'rb') as f:
        data = f.read()

    nodes = calculate_frequencies(data)
    root = build_huffman_tree(nodes)
    codes = {}
    generate_huffman_codes(root, '', codes)

    encoded_bits = encode_data(data, codes)
    padded_encoded_bits = pad_encoded_bits(encoded_bits)
    byte_array = get_byte_array(padded_encoded_bits)

    # Save compressed data and codebook with pickle
    with open(output_path, 'wb') as f:
        pickle.dump((byte_array, codes), f)

    print(f"File compressed and saved to {output_path}")

def remove_padding(padded_encoded_bits):
    padded_info = padded_encoded_bits[:8]
    padding = int(padded_info, 2)
    encoded_bits = padded_encoded_bits[8:]
    if padding > 0:
        encoded_bits = encoded_bits[:-padding]
    return encoded_bits

def decode_data(encoded_bits, codes):
    # Reverse codes to map bits -> byte
    reversed_codes = {v: k for k, v in codes.items()}

    current_code = ''
    decoded_bytes = bytearray()
    for bit in encoded_bits:
        current_code += bit
        if current_code in reversed_codes:
            decoded_bytes.append(reversed_codes[current_code])
            current_code = ''
    return bytes(decoded_bytes)

def decompress_file(input_path, output_path):
    with open(input_path, 'rb') as f:
        byte_array, codes = pickle.load(f)

    # Convert bytes back to bit string
    bit_string = ''
    for byte in byte_array:
        bit_string += f"{byte:08b}"

    encoded_bits = remove_padding(bit_string)
    decoded_data = decode_data(encoded_bits, codes)

    with open(output_path, 'wb') as f:
        f.write(decoded_data)

    print(f"File decompressed and saved to {output_path}")

# Example usage:
if __name__ == "__main__":
    compress_file("image.jpg", "compressed_image.huff")
    # compress_file("input_file.txt", "compressed.huff")
    decompress_file("compressed_image.huff", "decompressed_image.jpg")


