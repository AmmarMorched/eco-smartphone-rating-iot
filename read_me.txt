1- web-server:
contains web application who runs the api wich extract the phone model
# the application was deployed on render wich is easy to use just push your app on github, open an account in render using github, choose the repository of your app then  hit deploy 
#### don't forget to add your database in the environement 
application url :https://device-detection-51degree-api-2.onrender.com

2-raspbery: 
contains 2 files:
1)output.csv: contains data of smartphones with there eco_rating score, durability, recyclability, ...
2)send_data_to_esp.py: 
-receive the model detected by the server
-extract the smartphone data from the output.csv with the same model number
-connect to esp8266 server
-send the data to the esp8266

3-esp_receiver: 
-receives data send from raspbery pi
-extract ecorating_score from the data
-display the ecorating_score using a fan 
-An rfid writer will be waiting fo a tag to be placed near it
-writing the model number and ecorating_score on the tag

4-readRFID:
reading data from the previous card writen on
retreive the data from the card and compare it with the smartphones placed in the showcase

 