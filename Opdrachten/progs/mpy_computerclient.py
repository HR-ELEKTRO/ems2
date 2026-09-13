import socket

ESP_IP = "192.168.1.123"
PORT = 2000

address = (ESP_IP, PORT)
socket_naar_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket_naar_server.connect(address)
data = socket_naar_server.recv(100)
print("Ontvangen:", data.strip())
