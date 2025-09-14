import serial
import pymongo

# Serial setup
ser = serial.Serial('COM3', 9600)  # Change COM port as per your Arduino
ser.flush()

# MongoDB setup
client = pymongo.MongoClient("mongodb+srv://<username>:<password>@cluster0.mongodb.net/")
db = client["water_quality"]
collection = db["sensor_data"]

print("Listening to Arduino...")

while True:
    try:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()
            data = line.split(",")
            if len(data) == 5:
                record = {
                    "tds": float(data[0]),
                    "turbidity": float(data[1]),
                    "ph": float(data[2]),
                    "temperature": float(data[3]),
                    "humidity": float(data[4])
                }
                collection.insert_one(record)
                print("Inserted:", record)
    except Exception as e:
        print("Error:", e)
