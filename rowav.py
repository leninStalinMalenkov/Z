import wave, random,struct,math
sampleRate = 8000.0
durations = 1
frequency = 440.0

dr = open("draft.txt", "r")
audio = list(map(int, dr.read().split()))
dr.close()#print(len(audio))

f = wave.open("a.wav", "w")
f.setnchannels(1)
f.setsampwidth(2)
f.setframerate(sampleRate)
j = 0
for i in audio:
        value = i
        data = struct.pack('<h', value)
        f.writeframesraw(data)

f.close()