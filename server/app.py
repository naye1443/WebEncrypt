from flask import Flask, redirect, request, send_file, jsonify, render_template, abort

app = Flask(__name__)

@app.route('/')
def home():
    print("We are at home!")
    return"<h1> Home Page</h1>"

# Description: Encrypts a message
# Input: message in plain txt. The message will be encoded in UTF-8
# Output: message as cipher text. The message will be encoded in UTF-8
@app.route('/encrypt', methods=['POST'])
def Encrypt():

    try:
        # Tries to access request of form
        for key in request.form:
            print(request.form[key])

    
        # if(request.form.get('scheme') == 'elgamal'):
        #     # use elgamal Encryption scheme
        # elif(request.form.get('scheme') == 'des'):
        #     # use des Encryption scheme

        # Return success Resposnse
        return {'status': 'Good', 'message': 'Message is clear'}

    except Exception as ex:
        print(f'Exception occurred: {ex}')

        return {'status': 'error', 'message': str(ex)}



app.run(debug=True, host='127.0.0.1', port='5000')