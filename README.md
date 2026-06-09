# EV Charging Vehicle – Wireless EV Charging and Smart Monitoring System

## Overview

EV Charging Vehicle is an IoT-enabled wireless electric vehicle charging system designed to demonstrate smart charging, real-time monitoring, and remote vehicle control. The project combines wireless power transfer technology with embedded systems, sensor monitoring, and a web-based dashboard to create an intelligent and user-friendly charging platform.

The system uses wireless inductive power transfer to charge a vehicle battery without physical charging connectors. Environmental and electrical parameters such as temperature, humidity, battery voltage, and charging coil voltage are continuously monitored and transmitted to a Flask-based web server. Users can access a responsive dashboard through any web browser to view charging status and system health in real time.

In addition to monitoring, the platform provides remote vehicle movement control through Wi-Fi communication. Commands such as Forward, Backward, Left, Right, and Stop can be sent from the dashboard and executed by the vehicle controller.

## Features

* Wireless EV charging using inductive power transfer
* Real-time battery voltage monitoring
* Charging status detection
* Temperature monitoring
* Humidity monitoring
* Flask-based web dashboard
* Remote vehicle control through Wi-Fi
* Battery level classification (LOW, MEDIUM, FULL)
* Real-time data visualization
* REST API support for sensor communication
* Cross-platform browser access
* Lightweight and scalable architecture

## System Components

### Hardware

* ESP32 Microcontroller
* Wireless Charging Transmitter Coil
* Wireless Charging Receiver Coil
* Battery Pack
* Motor Driver Module
* DC Motors
* Temperature and Humidity Sensor
* Voltage Monitoring Circuit
* Wi-Fi Network

### Software

* Python
* Flask
* HTML
* CSS
* JavaScript
* Arduino IDE
* ESP32 Libraries

## Working Principle

1. Sensors continuously measure temperature, humidity, battery voltage, and coil voltage.
2. ESP32 sends sensor data to the Flask server using HTTP requests.
3. Flask processes incoming data and updates system variables.
4. The dashboard displays real-time charging and battery information.
5. Users can remotely control vehicle movement through dashboard buttons.
6. Control commands are returned to the ESP32 during communication.
7. The ESP32 executes received commands and drives the motors accordingly.
8. Charging status is automatically detected based on coil voltage measurements.

## Dashboard Functions

* Live temperature display
* Live humidity display
* Battery voltage monitoring
* Coil voltage monitoring
* Charging status indication
* Battery level status
* Remote motor control
* Automatic dashboard refresh

## API Endpoints

### Sensor Data Upload

GET /data

Parameters:

* temp
* hum
* battery
* coil

Example:
http://SERVER_IP:5000/data?temp=30&hum=60&battery=12.5&coil=4.2

### System Status

GET /status

Returns JSON containing:

* temperature
* humidity
* battery_voltage
* coil_voltage
* battery_level
* charging
* command

### Vehicle Control

* /forward
* /back
* /left
* /right
* /stop

## Applications

* Smart Electric Vehicles
* Autonomous Charging Systems
* Industrial AGVs
* Smart Transportation
* Research and Educational Projects
* Wireless Energy Transfer Systems
* IoT-Based Vehicle Monitoring

## Advantages

* No physical charging connectors required
* Reduced connector wear and maintenance
* Real-time system monitoring
* Remote accessibility
* Improved user convenience
* Low-cost implementation
* Expandable architecture
* Suitable for future smart charging infrastructure

## Future Enhancements

* Mobile application integration
* GPS tracking
* Live camera streaming
* Cloud data storage
* AI-based charging optimization
* Battery health prediction
* Solar-powered charging support
* Automatic parking and charging alignment
* Multi-vehicle charging management

## Author

Renjith M

## License

This project is intended for educational, research, and development purposes.
