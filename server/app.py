from flask import Flask, redirect, request, send_file, jsonify, render_template, abort
from flask_cors import CORS

import DES
import BCM
import Binary
from random import random
import secrets

# Used to encapslate Encrypting and Decrypting
def EncDFunction(key, scheme, Text, EncryptOrDcrypt ):

    ofb = None
    if(scheme == 'Elgamal'):
        # use elgamal Encryption scheme
        print("elgamal")
    else:
        # use des Encryption scheme
        ofb = BCM.BCM(key, scheme, EncryptOrDcrypt)
        ofb.OFB(Text, key, EncryptOrDcrypt, 0)
    return ofb

def genKey(key):

    # Convert keys to Binary
    key = Binary.txttoBits(key)

    print(f"****************************\n The key prior to adjunction is {key}")
    
    # Find # of bits need to fill a block
    bitDif = 64 - len(key)
    
    if(bitDif < 64):
        key += bin(secrets.randbits(bitDif))[2:].zfill(bitDif)  # number of needed bits are returned as a
        # random sequence of bits, extra bit identifiers are concatonated off, and leading # of bits are added to complete block

    if(bitDif > 64):
        key = key[:len(key) - bitDif]

    # converted to byte-like object
    bytekey = bytes.fromhex(Binary.bin2hex(key))
    bytekey = bytekey.decode('utf-8','replace')

    print(f" The key prior to adjunction is {bytekey}")
    # NOTE: replace is NEEDED used to keep key consistency with data that could not be 
    # interpretated as utf-8. Not the best implementation

    return bytekey

app = Flask(__name__)
CORS(app)

@app.route('/')
def home():
    print("We are at home!")
    return"<h1> Home Page</h1>"

# Description: Encrypts a message
# Input: message in plain txt. The message will be encoded in UTF-8
# Output: message as cipher text. The message will be encoded in UTF-8
@app.route('/encrypt', methods=['POST'])
def Encrypt():

    cipherParams = {
        "Scheme" : "",
        "Text" : "",
        "CipherMode": "",
        "EncryptOrDcrypt": "",
        "Userkey": ""
                    }
    ciphertxt = ''
    key = ''
    ofb = None  # CipherBlock Object. Where cipher data is held

    try:

        print("************** INPUTS FROM CLIENT ***************")
        # Tries to access request of form
        for key in request.form:
            print(f"{key:15} : {request.form[key]}")
            cipherParams[key] = request.form[key]

        if len(cipherParams["Userkey"]) != 0:
            cipherParams["Userkey"] = genKey(cipherParams["Userkey"])

        # need to convert whatever input is given to binary

        if(cipherParams["EncryptOrDcrypt"] == "D"):
            cipherParams["Text"] = Binary.hex2bin(cipherParams["Text"])

            ofb = EncDFunction(cipherParams["Userkey"], cipherParams["Text"], cipherParams["Scheme"], cipherParams["EncryptOrDcrypt"])

            ciphertxt = Binary.hex2char(Binary.bin2hex(ofb.comtxt('D')));
            print(f"The ciphertext is: {ciphertxt}")
        else:

            ofb = EncDFunction(cipherParams["Userkey"], cipherParams["Text"], cipherParams["Scheme"], cipherParams["EncryptOrDcrypt"])
            ciphertxt = bytes.fromhex(Binary.hex2char(Binary.bin2hex(ofb.comtxt('E'))))
            ciphertxt = ciphertxt.decode("utf-8", "replace")
            # if(request.form.get('Scheme') == 'Elgamal'):
            #     # use elgamal Encryption scheme
            #     print("elgamal")
            # elif(request.form.get('Scheme') == 'DES'):
            #     # use des Encryption scheme
            #     ofb = BCM.BCM(key, cipherParams["Scheme"], cipherParams["EncryptOrDcrypt"])
            #     ofb.OFB(cipherParams["Scheme"], key, cipherParams["EncryptOrDcrypt"], 0)
            #     ciphertxt = Binary.bin2hex(ofb.comtxt(cipherParams["EncryptOrDcrypt"]))
            #     print(ciphertxt)

            # Return success Resposnse
            return {'status': 'Good', 'message': 'Message is clear', 'cipher': ciphertxt}

    except Exception as ex:
        print(f'Exception occurred: {ex}')

        return {'status': 'error', 'message': str(ex)}

app.run(debug=True, host='127.0.0.1', port='5000')