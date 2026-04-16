# Eco Smartphone Rating IoT System

## Overview

This project is an IoT-based system designed to evaluate and display the environmental impact (eco rating) of smartphones.

It combines embedded systems, web technologies, and RFID to create an interactive experience where users can scan their phone, retrieve its eco score, and store it on a physical card.

##  System Architecture

The system is composed of multiple components:

1. **QR Code Interaction**

   * The user scans a QR code using their smartphone
   * A web API hosted on a Raspberry Pi detects the device model

2. **Eco Rating Retrieval**

   * The system searches a database for the smartphone's eco rating
   * The rating is sent to an ESP32 microcontroller

3. **Physical Display**

   * A servo motor displays the eco score using a fan-shaped (0–100 scale) indicator

4. **RFID Storage**

   * The user taps an RFID card to store their smartphone’s eco rating

5. **RFID Comparison**

   * A second ESP32 reads the card and allows comparison with other devices


## Features

* Real-time smartphone identification via QR code
* Eco rating lookup from database
* Embedded visualization using servo motor (fan display)
* RFID-based data storage and retrieval
* Multi-device communication (Raspberry Pi ↔ ESP32)

## Technologies Used

* Raspberry Pi
* ESP32 (C++ / Arduino)
* Python / Node.js (API)
* MongoDB
* CSV dataset
* RFID (RC522)
* Servo Motor Control
* HTTP Communication

## Use Cases

* Smart retail (compare device sustainability)
* Environmental awareness systems
* Interactive IoT installations
* Embedded + AI demonstration projects

## Setup

```bash
git clone https://github.com/AmmarMorched/eco-smartphone-rating-iot.git
```

(Configure Raspberry Pi server, ESP32 firmware, and RFID modules accordingly)

---

## 📈 Future Improvements

* Mobile app integration
* Real-time comparison dashboard
* AI-based eco score prediction
* Cloud-based data storage

---

## 👨‍💻 Author

Morched Ammar
