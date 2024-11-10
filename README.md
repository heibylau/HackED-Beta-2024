# HackED Beta 2024-Weather Buddy
Group members: Heiby Lau, Arthur Witte, Ruslan Kurbanov
## Inspiration
The need for comfortable and healthy indoor spaces is essential, not only for people but also for indoor plants. Our goal was to create an easy way to monitor temperature and humidity, helping people optimize their environment and support plant health.

## Project overview
Our project features a sensor that tracks both temperature and humidity levels in real-time. The sensor is connected to a microcontroller, which transmits the collected data to AWS for storage and further analysis. 
## How we built it
**Hardware:** 
-We used ESP8266, DHT22 sensor, LED lights, and breadboard
-We used circuits to control the LED lights and wires to connect the sensor to the ESP8266

**Software:**
-The hardware was coded in Arduino IDE
-Sensor data was sent to AWS for storage and organization before being queried in python
-Weather Buddy was built using Dash and Plant Buddy was built using Flask
-Plant Buddy leveraged OpenAI API for data information and the chat function

## Challenges we faced
-**IoT data organization complexity:**We originally planned to use Azure to store sensor data in order to visualize it on Power BI. However, we were unable to create a Power BI account and loading data using Python was too complicated.
-**LCD display failure:**We were not able to set up an LCD display to show humidity and temperature

## What we learned
-**Arduino programming:**We learned how to program in Arduino IDE
-**Hardware:**We gained a deeper knowledge in ESP boards, LED lights, sensors, and circuits
-**Cloud storage:**We gained knowledge in different cloud services offered by AWS and Azure

## Opportunities for improvement
-Integrate both weather buddy and plant buddy together into a single webpage
-Make the hardware into a smaller scale so we can 3D print a case for the sensor
-Add a LCD Display
