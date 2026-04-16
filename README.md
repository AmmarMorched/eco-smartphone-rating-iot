# Eco Smartphone Rating IoT System

## Overview

This project is an end-to-end IoT system that evaluates and displays the environmental impact (eco rating) of smartphones.

It combines a web API, a Raspberry Pi backend, and multiple ESP8266/ESP32 microcontrollers with RFID technology to create an interactive experience for users in a smart retail or exhibition environment.

---

## System Architecture

### 1. Web Server (Device Detection API)

* A web application that detects the smartphone model when a user scans a QR code
* Hosted online using Render
* Uses device detection to extract phone specifications

🔗 Application URL:
https://device-detection-51degree-api-2.onrender.com

> ⚠️ Deployment note:

* Push code to GitHub
* Connect repository to Render
* Add database credentials in environment variables
* Deploy directly from Render dashboard

---

### 2. Raspberry Pi Backend

Contains:

* **output.csv**
  Dataset of smartphones including:

  * eco rating score
  * durability
  * recyclability

* **send_data_to_esp.py**

  * Receives detected phone model from the web server
  * Searches for the corresponding device in `output.csv`
  * Extracts eco rating data
  * Connects to ESP8266 over HTTP
  * Sends processed data to the microcontroller

---

### 3. ESP Receiver (ESP8266 / ESP32)

Responsible for:

* Receiving data from Raspberry Pi
* Extracting the eco rating score
* Displaying the score using a **servo motor (fan-shaped indicator from 0–100)**
* Waiting for RFID interaction
* Writing the following data to RFID tag:

  * smartphone model
  * eco rating score

---

### 4. RFID Reader System (Second ESP)

* Reads data stored on RFID card
* Extracts smartphone eco rating
* Compares it with other devices (e.g., in a showcase environment)

---

## Features

* Smartphone detection via QR code
* Remote API deployment (Render)
* Data processing on Raspberry Pi
* Real-time communication with ESP devices
* Physical eco score visualization using servo motor
* RFID-based storage and comparison system

---

## Technologies Used

* Raspberry Pi
* ESP8266 / ESP32 (C++ / Arduino)
* Python
* Web API (Node.js / 51Degrees)
* CSV dataset processing
* RFID (RC522)
* Servo Motor Control
* HTTP Communication

---

## Use Cases

* Smart retail product comparison
* Environmental awareness systems
* Interactive IoT demonstrations
* Embedded systems + AI integration projects

---

## System Workflow

1. User scans QR code with smartphone
2. Web API detects device model
3. Raspberry Pi retrieves eco rating from dataset
4. Data is sent to ESP8266
5. Eco score is displayed physically using servo motor
6. User stores result on RFID card
7. RFID card is used for comparison on another system

---

## Setup

```bash
git clone https://github.com/AmmarMorched/eco-smartphone-rating-iot.git
```

### Requirements:

* Raspberry Pi (Python environment)
* ESP8266/ESP32 with Arduino setup
* RFID module (RC522)
* Servo motor
* Internet connection for API

---

## Future Improvements

* Replace CSV with real-time database
* Add web dashboard for monitoring
* Integrate machine learning for eco score prediction
* Improve UI/UX interaction

---

## 👨‍💻 Author

Morched Ammar
