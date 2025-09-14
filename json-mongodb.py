import serial
import pymongo

# Apna Arduino COM port check karke neeche change kar (abhi COM3 hai)
ser = serial.Serial('COM3', 9600, timeout=1)
ser.flush()

# MongoDB Atlas Connection
MONGODB_URI = "mongodb+srv://admin:sanjeevni@cluster0.3haxn5j.mongodb.net/?retryWrites=true&w=majority"
client = pymongo.MongoClient(MONGODB_URI)

# Database = hardware_data, Collection = sensor_data
db = client["hardware_data"]
collection = db["sensor_data"]

print("Connected to MongoDB. Listening Arduino data...")

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
