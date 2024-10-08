import random

# Function to perform XOR operation
def xor(a, b):
    result = []
    for i in range(1, len(b)):
        result.append('0' if a[i] == b[i] else '1')
    return ''.join(result)

# Function to perform division (CRC check)
def crc_check(data, divisor):
    pick = len(divisor)
    tmp = data[:pick]
    
    while pick < len(data):
        if tmp[0] == '1':
            tmp = xor(divisor, tmp) + data[pick]
        else:  # If the first bit is 0, use all 0s divisor
            tmp = xor('0' * pick, tmp) + data[pick]
        pick += 1
    
    if tmp[0] == '1':
        tmp = xor(divisor, tmp)
    else:
        tmp = xor('0' * pick, tmp)
    
    return tmp

# Function to generate CRC codeword
def generate_crc(data, divisor):
    n = len(divisor)
    appended_data = data + '0' * (n - 1)
    remainder = crc_check(appended_data, divisor)
    return data + remainder

# Function to introduce random error in data
def induce_error(data):
    data_list = list(data)
    index = random.randint(0, len(data_list) - 1)
    data_list[index] = '1' if data_list[index] == '0' else '0'
    return ''.join(data_list)

# Main function to simulate CRC transmission
def crc_simulation():
    data = "101101"  # Example binary data
    divisor = "1101"  # Example divisor (CRC polynomial)

    print("Original Data: ", data)

    # Generate CRC codeword
    transmitted_data = generate_crc(data, divisor)
    print("Transmitted Data (with CRC): ", transmitted_data)

    # Randomly induce error
    if random.choice([True, False]):
        print("Introducing error in the transmitted data...")
        transmitted_data = induce_error(transmitted_data)

    print("Received Data: ", transmitted_data)

    # Check for errors
    remainder = crc_check(transmitted_data, divisor)
    if '1' in remainder:  # Error detected
        print("Error in message. Requesting retransmission.")
    else:
        print("Success! No errors detected.")

# Run the CRC simulation
crc_simulation()
