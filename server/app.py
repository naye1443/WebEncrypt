from flask import Flask, redirect, request, send_file, jsonify, render_template, abort
from flask_cors import CORS

import DES
import BCM
import Binary
from random import random

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
        "EncryptOrDcrypt": ""
                    }
    ciphertxt = ''
    key = ''

    try:

        # Tries to access request of form
        for key in request.form:
            print(request.form[key])
            cipherParams[key] = request.form[key]
    
        if(request.form.get('Scheme') == 'Elgamal'):
            # use elgamal Encryption scheme
            print("elgamal")
        elif(request.form.get('Scheme') == 'DES'):
            # use des Encryption scheme
            ofb = BCM.BCM(cipherParams["Scheme"], cipherParams["EncryptOrDcrypt"])
            ofb.OFB(cipherParams["Scheme"], key, cipherParams["EncryptOrDcrypt"], 0)
            ciphertxt = Binary.bin2hex(ofb.comtxt(cipherParams["EncryptOrDcrypt"]))
            print(ciphertxt)

        # Return success Resposnse
        return {'status': 'Good', 'message': 'Message is clear', 'cipher': ciphertxt}

    except Exception as ex:
        print(f'Exception occurred: {ex}')

        return {'status': 'error', 'message': str(ex)}

app.run(debug=True, host='127.0.0.1', port='5000')