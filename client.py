import socket
HOST = '192.168.88.250' # Enter IP or Hostname of your server
PORT = 12345 # Pick an open Port (1000+ recommended), must match the server port
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST,PORT))

"""s.send(b"START")
reply = str(s.recv(1024))[2:-1]
if(reply != "OK"):
        print("hui2")
"""

print("hui2")
command = len(open("z.jpg", "rb").read())
s.send(str(command).encode())
fl = open("z.jpg", "rb")
#print(fl.read(55))


if(True):
        f = open("z.jpg", "rb")
        for i in range(0, (command+54)//55):
                s.send(fl.read(55));
                d = str(s.recv(1024))[2:-1]
                

