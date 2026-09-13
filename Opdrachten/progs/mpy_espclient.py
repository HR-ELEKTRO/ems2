import socket

PC_IP = "192.168.1.100"
PORT = 2000
address = (PC_IP, PORT)

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
    sock.connect(address)
    data = sock.recv(100)
    print("Ontvangen:", data.decode("utf-8").strip())
finally:
    sock.close()
