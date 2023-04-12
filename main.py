from flask import Flask, request, jsonify
import numpy as np
import json
import sklearn
from flask_cors import CORS
from numpyencoder import NumpyEncoder
import joblib

app = Flask(__name__)
cors = CORS(app, resources={r"/api/*": {"origins": "*"}})


@app.route('/')
def index():
  return 'Hello, I Learn BMI Prediction!'


@app.route('/api/predict', methods=['POST'])
def predict():

  file = open("modelbmi.sav", "rb")
  trained_model = joblib.load(file)

  datas = request.get_json(force=True)

  pred = []

  for data in datas:
    prediction = trained_model.predict(
      [np.array([data["gender"], data["height"]])])
    output = prediction[0]
    pred.append(output)

  return jsonify(json.dumps(pred, cls=NumpyEncoder))


app.run(host='0.0.0.0', port=5000, debug=True)
