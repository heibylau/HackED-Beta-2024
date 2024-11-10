from flask import Flask, render_template, request, jsonify
from openai import OpenAI
import os
from dotenv import load_dotenv


# Load environment variables from .env file
load_dotenv()


# Initialize OpenAI client
client = OpenAI(api_key=os.getenv("OPENAI_API_KEY"))


app = Flask(__name__)

'''
TEST VALUES:

T = 15 H = 80 (Boston Ferns, Bird's Nest, Anthurium)
T = 15 H = 30 (Cactus, Jade Plant, Cast Iron Plant,)
T = 22 H = 55 (Nicest looking plants)
T = 20 H = 50 
'''
plants = [
    {"name": "Snake Plant", "humidity_range": (30, 50), "temp_range": (15, 28), "icon": "snake.jpg"},
    {"name": "Fiddle Leaf Fig", "humidity_range": (40, 60), "temp_range": (18, 24), "icon": "fiddle.jpg"},
    {"name": "Spider Plant", "humidity_range": (40, 80), "temp_range": (15, 30), "icon": "spider.jpg"},
    {"name": "Peace Lily", "humidity_range": (40, 70), "temp_range": (18, 28), "icon": "peace.jpg"},
    {"name": "Pothos", "humidity_range": (30, 60), "temp_range": (18, 30), "icon": "pothos.jpg"},
    {"name": "Boston Fern", "humidity_range": (60, 90), "temp_range": (15, 25), "icon": "boston.jpg"},
    {"name": "Calathea", "humidity_range": (50, 80), "temp_range": (18, 26), "icon": "calathea.jpg"},
    {"name": "Aloe Vera", "humidity_range": (40, 50), "temp_range": (13, 29), "icon": "aloe.jpg"},
    {"name": "Moth Orchid", "humidity_range": (40, 70), "temp_range": (15, 32), "icon": "moth.jpeg"},
    {"name": "ZZ Plant", "humidity_range": (30, 50), "temp_range": (15, 27), "icon": "zz.jpg"},
    {"name": "Rubber Plant", "humidity_range": (40, 60), "temp_range": (15, 29), "icon": "rubber.jpg"},
    {"name": "Monstera", "humidity_range": (60, 80), "temp_range": (18, 30), "icon": "monstera.jpg"},
    {"name": "Philodendron", "humidity_range": (40, 60), "temp_range": (18, 26), "icon": "philodendron.jpg"},
    {"name": "Dumb Cane", "humidity_range": (50, 70), "temp_range": (15, 30), "icon": "dumb.jpg"},
    {"name": "Bird’s Nest Fern", "humidity_range": (60, 80), "temp_range": (18, 24), "icon": "bird.jpg"},
    {"name": "Chinese Money Plant", "humidity_range": (40, 60), "temp_range": (15, 24), "icon": "chinese.jpg"},
    {"name": "Jade Plant", "humidity_range": (30, 50), "temp_range": (10, 24), "icon": "jade.jpg"},
    {"name": "Parlor Palm", "humidity_range": (40, 60), "temp_range": (15, 26), "icon": "parlor.jpg"},
    {"name": "Croton", "humidity_range": (40, 70), "temp_range": (18, 24), "icon": "croton.jpg"},
    {"name": "English Ivy", "humidity_range": (40, 60), "temp_range": (12, 22), "icon": "english.jpg"},
    {"name": "Majesty Palm", "humidity_range": (50, 80), "temp_range": (15, 26), "icon": "majesty.jpg"},
    {"name": "String of Pearls", "humidity_range": (30, 50), "temp_range": (18, 24), "icon": "string.jpg"},
    {"name": "Anthurium", "humidity_range": (60, 80), "temp_range": (18, 24), "icon": "anthurium.jpg"},
    {"name": "Bird of Paradise", "humidity_range": (50, 70), "temp_range": (18, 30), "icon": "birdparadise.jpg"},
    {"name": "Polka Dot Plant", "humidity_range": (50, 70), "temp_range": (15, 24), "icon": "polka.jpg"},
    {"name": "Aglaonema", "humidity_range": (40, 60), "temp_range": (18, 24), "icon": "aglaonema.jpg"},
    {"name": "Hoya", "humidity_range": (40, 60), "temp_range": (15, 26), "icon": "hoya.jpg"},
    {"name": "Dracaena", "humidity_range": (30, 60), "temp_range": (18, 27), "icon": "dracaena.jpg"},
    {"name": "Cast Iron Plant", "humidity_range": (30, 50), "temp_range": (10, 27), "icon": "castiron.jpg"},
    {"name": "Alocasia", "humidity_range": (60, 80), "temp_range": (18, 26), "icon": "alocasia.jpg"},
    {"name": "Prayer Plant", "humidity_range": (50, 80), "temp_range": (18, 26), "icon": "prayer.jpg"},
    {"name": "African Violet", "humidity_range": (40, 60), "temp_range": (18, 24), "icon": "african.jpg"},
    {"name": "Spiderwort", "humidity_range": (40, 60), "temp_range": (15, 26), "icon": "spiderwort.jpg"},
    {"name": "Areca Palm", "humidity_range": (50, 70), "temp_range": (18, 26), "icon": "areca.jpg"},
    {"name": "Bromeliad", "humidity_range": (60, 80), "temp_range": (15, 27), "icon": "bromeliad.jpg"},
    {"name": "Umbrella Tree", "humidity_range": (50, 70), "temp_range": (18, 30), "icon": "umbrella.jpg"},
    {"name": "Silver Pothos", "humidity_range": (40, 60), "temp_range": (18, 27), "icon": "silver.jpg"},
    {"name": "Cactus", "humidity_range": (20, 40), "temp_range": (10, 30), "icon": "cactus.jpg"}
]


# Function to recommend plants based on temperature and humidity
def recommend_plants(avg_temp, avg_humidity):
    plant_scores = []
    for plant in plants:
        temp_mid = (plant["temp_range"][0] + plant["temp_range"][1]) / 2
        humidity_mid = (plant["humidity_range"][0] + plant["humidity_range"][1]) / 2
        temp_diff = abs(avg_temp - temp_mid)
        humidity_diff = abs(avg_humidity - humidity_mid)
        closeness_score = temp_diff + humidity_diff
        plant_scores.append((plant, closeness_score))


    sorted_plants = sorted(plant_scores, key=lambda x: x[1])
    return [plant[0] for plant in sorted_plants[:3]]


@app.route("/", methods=["GET", "POST"])
def index():
    recommendations = []
    if request.method == "POST":
        try:
            avg_temp = float(request.form["temperature"])
            avg_humidity = float(request.form["humidity"])
            recommendations = recommend_plants(avg_temp, avg_humidity)
        except ValueError:
            recommendations = ["Please enter valid numerical values for temperature and humidity."]
    return render_template("index.html", recommendations=recommendations)


@app.route('/chat', methods=['POST'])
def chat():
    user_input = request.json.get('user_input')
    plant_name = request.json.get('plant_name')

    if not user_input or not plant_name:
        return jsonify({'error': 'No input or plant selected'}), 400

    try:
        prompt = f"You are {plant_name}, a friendly plant, here to answer questions about {plant_name} in max 40 words max. Be original and use a distinct personality based on your plant type."
        response = client.chat.completions.create(
            model="gpt-4o",
            messages=[{"role": "system", "content": prompt}, {"role": "user", "content": user_input}]
        )
        chat_gpt_response = response.choices[0].message.content.strip()
        return jsonify({'response': chat_gpt_response})
    except Exception as e:
        return jsonify({'error': str(e)}), 500


if __name__ == "__main__":
    app.run(debug=True)



