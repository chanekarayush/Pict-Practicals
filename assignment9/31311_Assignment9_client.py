import socket
import os

BUFFER_SIZE = 1024

# Function to send file to server


def send_file(client_socket, file_type, file_path, server_addr):
    file_name = os.path.basename(file_path)
    # Sending the file name to server
    client_socket.sendto(file_name.encode(), server_addr)

    # Open the file and send its contents
    with open(file_path, "rb") as file:
        while True:
            data = file.read(BUFFER_SIZE)
            if not data:
                break
            client_socket.sendto(data, server_addr)
            # Wait for acknowledgment from server
            client_socket.recvfrom(BUFFER_SIZE)

    # Send 'END' to indicate the end of file transfer
    client_socket.sendto(b'END', server_addr)
    print(f"{file_type.capitalize()} file {file_name} sent successfully!")

# Main client program


def client_program():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_addr = ('localhost', 12345)

    print("Connected to server.")

    # Loop to send different types of files
    while True:
        print("\nChoose a file type to send:")
        print("1. Script")
        print("2. Text")
        print("3. Audio")
        print("4. Video")
        print("Type 'exit' to quit.")

        choice = input("Enter your option: ")

        if choice == "1":
            file_path = input("Enter the path of the script file: ")
            file_type = "script"
        elif choice == "2":
            file_path = input("Enter the path of the text file: ")
            file_type = "text"
        elif choice == "3":
            file_path = input("Enter the path of the audio file: ")
            file_type = "audio"
        elif choice == "4":
            file_path = input("Enter the path of the video file: ")
            file_type = "video"
        elif choice.lower() == 'exit':
            print("Exiting the program.")
            break
        else:
            print("Invalid option. Try again.")
            continue

        # Ensure the file exists
        if not os.path.exists(file_path):
            print(f"File {file_path} not found!")
            continue

        # Send file type first
        client_socket.sendto(file_type.encode(), server_addr)
        send_file(client_socket, file_type, file_path, server_addr)

    client_socket.close()


# Start the client
if __name__ == "__main__":
    client_program()
