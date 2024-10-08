import socket
import os

# Function to send "Hello" to the server


def say_hello(client_socket):
    client_socket.sendall(b"1")  # Option 1
    server_message = client_socket.recv(1024).decode()
    print("Server says:", server_message)
    client_socket.sendall(b"Hello from the client!")

# Function to send a file to the server


def send_file(client_socket):
    client_socket.sendall(b"2")  # Option 2

    file_name = input("Enter the file name to send: ")
    client_socket.sendall(file_name.encode())

    if os.path.exists(file_name):
        with open(file_name, 'rb') as file:
            data = file.read(1024)
            while data:
                client_socket.sendall(data)
                data = file.read(1024)
        print(f"File {file_name} sent successfully!")
    else:
        print(f"File {file_name} not found.")

# Function to perform a calculator operation


def calculator(client_socket):
    client_socket.sendall(b"3")  # Option 3

    expression = input("Enter the arithmetic expression (e.g., 5 + 3): ")
    client_socket.sendall(expression.encode())

    result = client_socket.recv(1024).decode()
    print(f"Result: {result}")

# Main client logic


def client_program():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('localhost', 12345))

    print("Connected to the server.")

    while True:
        print("\nChoose an option:")
        print("1. Say Hello")
        print("2. File Transfer")
        print("3. Calculator")
        print("Type 'exit' to quit.")

        option = input("Enter your option: ")

        if option == "1":
            say_hello(client_socket)
        elif option == "2":
            send_file(client_socket)
        elif option == "3":
            calculator(client_socket)
        elif option == "exit":
            client_socket.sendall(b"exit")
            break
        else:
            print("Invalid option. Try again.")

    client_socket.close()


# Start the client
if __name__ == "__main__":
    client_program()
