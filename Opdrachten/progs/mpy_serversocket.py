PORT = 2000
address = ("0.0.0.0", PORT)

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(address)
server.listen(1)
print("Server luistert op", ip, "poort", PORT)
