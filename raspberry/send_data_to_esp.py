import pymongo
import json
import csv
import requests

# Connect to your MongoDB database
client = pymongo.MongoClient("mongodb+srv://morcheda62:sYYqEULwRkfm698Y@device8detection.okrnj.mongodb.net/?retryWrites=true&w=majority&appName=device8detection")  # Replace with your connection string
db = client["test"]
collection = db["devs"]

# ESP8266 IP address and port
ESP8266_IP = "192.168.1.100"  
ESP8266_PORT = 80

def send_to_esp8266(data):
    url = f"http://{ESP8266_IP}:{ESP8266_PORT}/data"  # Endpoint on the ESP8266
    try:
        response = requests.post(url, json=data)
        print(f"Data sent to ESP8266: {response.status_code}")
    except requests.exceptions.RequestException as e:
        print(f"Failed to send data to ESP8266: {e}")


# Open CSV file
def read_csv_data():
    data = []
    with open('output.csv', 'r') as csvfile:  
        reader = csv.DictReader(csvfile)
        for row in reader:
            data.append(row)
    return data

csv_data = read_csv_data()
    
    # Function to handle changes
def handle_change(change):
    print("Change detected:", change)
    # Process the latest document from the change
    if 'fullDocument' in change:
        doc = change['fullDocument']
        hardwareVendor = doc.get("hardwareVendor", "N/A")
        hardwareModel = doc.get("hardwareModel", "N/A")
        hardwareName = doc.get("hardwareName", "N/A")
        if isinstance(hardwareName, list):
            hardwareName = ' '.join(hardwareName)  

        print(f"Hardware Vendor: {hardwareVendor}")
        print(f"Hardware Model: {hardwareModel}")
        print(f"Hardware Name: {hardwareName}")

        # Check the CSV file for matching model
        for row in csv_data:
            if row.get("model_number_info") == hardwareModel:  # Replace "model_number_info" with the actual column name
                print(f"Name: {row['brand']}, {row['model']}")
                print(f"Model Number : {row['model_number_info']}")
                print(f"Release Date: {row['release_date']}")
                print(f"Eco Rating: {row['eco_rating']}")
                print(f"Durability: {row['durability']}")
                print(f"Repairability: {row['repairability']}")
                print(f"Recyclability: {row['recyclability']}")
                print(f"Climate Efficiency: {row['climate_efficiency']}")
                print(f"Resource Efficiency: {row['resource_efficiency']}")
                data_to_send = {
                    "brand": row['brand'],
                    "model": row['model'],
                    "model_number_info": row['model_number_info'],
                    "release_date": row['release_date'],
                    "eco_rating": row['eco_rating'],
                    "durability": row['durability'],
                    "repairability": row['repairability'],
                    "recyclability": row['recyclability'],
                    "climate_efficiency": row['climate_efficiency'],
                    "resource_efficiency": row['resource_efficiency'],
                }
                send_to_esp8266(data_to_send)
                break
        else:
            print("No matching model found in CSV.")
    else:
        print("No fullDocument in change.")

# Set up change stream
def monitor_changes():
    change_stream = collection.watch()

    try:
        for change in change_stream:
            handle_change(change)
    except pymongo.errors.PyMongoError as e:
        print("Error in change stream:", e)
    finally:
        client.close()

monitor_changes()