import DES
import Binary
import BCM
from random import random


des = DES.DES("This is a test doc", 'E')

for i in range(1,1000):
    print(int(round(random(), 0)))

# Initalize key
key = ''
while(len(key) < 64):
    key += Binary.Dec_to_Bin(int(round(random(), 0)))

while(len(key) > 64):
    key = key[:len(key) - 1]

# initalize Block Mode
ofb = BCM.BCM("This is a test doc", 'E')

# Compute Block mode into ciphertxt
ofb.OFB("This is a test doc", key, 'E', 0)
ciphertxt = Binary.bin2hex(ofb.comtxt('E'))

print(f"The encrypted value is {ciphertxt}")

# Initalize new Block Mode
desdcrypt = BCM.BCM(ciphertxt, 'D')

# Compute Block mode into plaintxt
desdcrypt.OFB(ciphertxt, key, 'D', 0)

# Convert binary into characters for comprehension
plaintxt = Binary.hex2char(Binary.bin2hex(desdcrypt.comtxt('D')));

print(f"The Decrypted value is {plaintxt}")