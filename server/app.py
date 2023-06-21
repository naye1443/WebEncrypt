from flask import Flask

app = Flask(__name__)

@app.route('/')
def home():
    print("We are at home!")
    return"<h1> Home Page</h1>"

app.run(debug=True, host='127.0.0.1', port='5000')