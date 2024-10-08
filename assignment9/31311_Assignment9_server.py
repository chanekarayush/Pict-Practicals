import socket
import os

BUFFER_SIZE = 1024

# Function to receive file from client


def receive_file(server_socket, file_type, addr):
    # Receiving the file name
    file_name, _ = server_socket.recvfrom(BUFFER_SIZE)
    file_name = file_name.decode()
    print(f"Receiving {file_type} file: {file_name}")

    # Open a file to write the received data
    with open(f"received_{file_name}", "wb") as file:
        while True:
            data, _ = server_socket.recvfrom(BUFFER_SIZE)
            if data == b'END':
                break
            file.write(data)
            # Send acknowledgment to client
            server_socket.sendto(b'ACK', addr)

    print(f"{file_type.capitalize()} file {file_name} received successfully!\n")

# Main server program


def server_program():
    # Create UDP socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_socket.bind(('localhost', 12345))

    print("Server is listening on port 12345...")

    while True:
        # Receiving file type from client
        file_type, addr = server_socket.recvfrom(BUFFER_SIZE)
        file_type = file_type.decode()

        if file_type in ['script', 'text', 'audio', 'video']:
            receive_file(server_socket, file_type, addr)
        else:
            print("Unknown file type received.")


# Start the server
if __name__ == "__main__":
    server_program()
