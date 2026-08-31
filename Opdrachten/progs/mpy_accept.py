while True:
    client, client_address = server.accept()
    print("Verbonden met", client_address)
    try: # Probeer de code vang fouten af
        # Hier versturen we straks gegevens.
        pass
    finally: # Sluit de verbinding altijd netjes, ook bij een fout.
        client.close()
