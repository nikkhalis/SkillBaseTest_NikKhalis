import socket

def main():
    host = 'localhost'
    port = 8443

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((host, port))

    pressure_bar = float(input("Enter the pressure in bar: "))

    client_socket.send(str(pressure_bar).encode())

    atmosphere_standard = client_socket.recv(1024)
    atmosphere_standard = float(atmosphere_standard.decode())

    print("Atmosphere Standard value received from server:", atmosphere_standard)

    client_socket.close()

if __name__ == "__main__":
    main()
