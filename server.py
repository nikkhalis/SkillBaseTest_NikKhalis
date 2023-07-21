import socket

def convert_to_atmosphere(pressure_bar):
    # Conversion formula from bar to atmosphere
    atmosphere_standard = pressure_bar / 1.01325
    return atmosphere_standard

def main():
    host = 'localhost'
    port = 8443

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(1)

    print("Server is listening on {}:{}".format(host, port))

    while True:
        conn, addr = server_socket.accept()
        print("Connected to:", addr)

        data = conn.recv(1024)
        pressure_bar = float(data.decode())

        atmosphere_standard = convert_to_atmosphere(pressure_bar)

        conn.send(str(atmosphere_standard).encode())

        conn.close()
        print("Connection closed with:", addr)

if __name__ == "__main__":
    main()
