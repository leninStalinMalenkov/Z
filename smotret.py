dr = open("draft.txt", "r")
audio = list(map(int, dr.read().split()))
dr.close();print(len(audio))
"""
for x in audio:
    print(x)
"""
"""
import wave, struct
f = open("draft.txt", "w")
wavefile = wave.open('audio.wav', 'r')

length = wavefile.getnframes()
for i in range(0, length):
    wavedata = wavefile.readframes(1)
    data = struct.unpack("<h", wavedata)
    f.write(str(int(data[0]))+" ")"""