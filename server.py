'''
ochen jalko
russia ura
'''

import wave, random,struct,math
import socket
sampleRate = 8000.0
durations = 1
frequency = 440.0

HOST = '192.168.88.250'
PORT = 12345 
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR,1)
print('Socket created')

try:
    s.bind((HOST, PORT))
except socket.error:
    print ('Bind failed ')

s.listen(5)
print ('Socket awaiting messages')
(conn, addr) = s.accept()
print ('Connected')

while(1):
    if True:
        data = str(conn.recv(1024))[2:-1]
        if(data == "-2 "):
            print("[RANEC] Log: start priem")
        f = open("draft.txt", "w")
        while True:
            data = str(conn.recv(1024))[2:-1]
            print(data)
            if(data[-3:] == "-1 "):
                print("[RANEC] Log: stop")
                break;
            f.write(data)
        
        print("[RANEC] Log: stop")
        f.close()
        dr = open("draft.txt", "r")
        audio = list(map(int, dr.read().split()))
        dr.close()
        print("[RANEC] Log: length = " + str(len(audio)))
        f = wave.open("a.wav", "w")
        f.setnchannels(1)
        f.setsampwidth(2)
        f.setframerate(sampleRate)
        j = 0
        for i in audio:
                value = i
                data = struct.pack('<h', value)
                f.writeframesraw(data)
        print("[RANEC] Log: Wav created")
        f.close()
