#import DES
import Binary
import random

print(Binary.bit_to_dec("0110"))


# des = DES("This is a test doc")

# key = ''
# while(len(key) < 64):
#     key += Binary.dec_to_bin(random() % 100)

# while(len(key) > 64):
#     key = key[:len(key) - 1]

# des.OFB("This is a test doc", key, 'E')
# ciphertxt = Binary.bin2hex(des.comtxt('E'))

# print(f"The encrypted value is {ciphertxt}")

# desdcrypt = DES(ciphertxt)

# desdcrypt.OFB(ciphertxt, key, 'D', 0)

# plaintxt = Binary.hex2bin(Binary.bin2hex(desdcrypt.comtxt('D')));

# print(f"The Decrypted value is{plaintxt}")