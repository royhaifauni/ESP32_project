import socket

UDP_IP = "0.0.0.0"
UDP_PORT = 4210

# Create a UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind the socket to the port
sock.bind((UDP_IP, UDP_PORT))

print(f"Listening for UDP messages on {UDP_IP}:{UDP_PORT}...")

try:
    while True:
        # Receive data from the socket
        data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
        try:
            message = data.decode()
        except UnicodeDecodeError:
            message = data.hex() # Fallback to hex if not UTF-8
            
        print(f"Received message: '{message}' from {addr}")
except KeyboardInterrupt:
    print("\nReceiver stopped.")
finally:
    sock.close()
