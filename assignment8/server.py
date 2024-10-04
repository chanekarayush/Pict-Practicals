import socket
import os

# Function to handle 'Say Hello' feature
def say_hello(client_socket):
    client_socket.sendall(b"Hello from the server!")
    message = client_socket.recv(1024).decode()
    print("Client says:", message)

# Function to handle file transfer
def receive_file(client_socket):
    file_name = client_socket.recv(1024).decode()
    print(f"Receiving file: {file_name}")
    
    with open(file_name, 'wb') as file:
        while True:
            data = client_socket.recv(1024)
            if not data:
                break
            file.write(data)
    print(f"File {file_name} received successfully!")

# Function to handle the calculator operations
def calculator(client_socket):
    expression = client_socket.recv(1024).decode()
    print(f"Calculating expression: {expression}")
    
    try:
        result = eval(expression)
        client_socket.sendall(str(result).encode())
    except Exception as e:
        client_socket.sendall(f"Error: {e}".encode())

# Main server logic
def server_program():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('localhost', 12345))
    server_socket.listen(5)
    print("Server is listening on port 12345...")

    while True:
        client_socket, addr = server_socket.accept()
        print(f"Connected by {addr}")
        
        while True:
            option = client_socket.recv(1024).decode()
            
            if option == "1":
                say_hello(client_socket)
            elif option == "2":
                receive_file(client_socket)
            elif option == "3":
                calculator(client_socket)
            elif option == "exit":
                print(f"Closing connection with {addr}")
                break
            else:
                print("Invalid option.")
        
        client_socket.close()

# Start the server
if __name__ == "__main__":
    server_program()
