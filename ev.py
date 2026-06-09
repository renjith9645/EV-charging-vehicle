from flask import Flask, request, jsonify, render_template_string
import time

app = Flask(__name__)

#################################################
# GLOBAL VARIABLES
#################################################

command = "stop"

temperature = 0
humidity = 0
battery_voltage = 0
coil_voltage = 0

charging = False
battery_level = "UNKNOWN"

last_update = time.time()

#################################################
# DASHBOARD HTML
#################################################

HTML_PAGE = """
<!DOCTYPE html>
<html>
<head>
<title>EV Wireless Charging Dashboard</title>

<meta http-equiv="refresh" content="2">

<style>

body{
    font-family: Arial;
    background: #111;
    color: white;
    text-align:center;
}

.box{
    background:#222;
    padding:20px;
    margin:10px;
    border-radius:10px;
    display:inline-block;
    min-width:200px;
}

button{
    width:120px;
    height:50px;
    font-size:18px;
    margin:5px;
}

.charging{
    color:lime;
    font-size:30px;
}

.notcharging{
    color:red;
    font-size:30px;
}

.low{color:red;}
.medium{color:orange;}
.full{color:lime;}

</style>

</head>

<body>

<h1>Wireless EV Charging System</h1>

<div class="box">
<h2>Temperature</h2>
<h3>{{temperature}} °C</h3>
</div>

<div class="box">
<h2>Humidity</h2>
<h3>{{humidity}} %</h3>
</div>

<div class="box">
<h2>Battery Voltage</h2>
<h3>{{battery_voltage}} V</h3>
</div>

<div class="box">
<h2>Coil Voltage</h2>
<h3>{{coil_voltage}} V</h3>
</div>

<div class="box">
<h2>Battery Level</h2>
<h3 class="{{battery_level_class}}">{{battery_level}}</h3>
</div>

<div class="box">
<h2>Charging Status</h2>

{% if charging %}
<h3 class="charging">CHARGING</h3>
{% else %}
<h3 class="notcharging">NOT CHARGING</h3>
{% endif %}

</div>

<h2>Motor Control</h2>

<button onclick="send('forward')">Forward</button><br>

<button onclick="send('left')">Left</button>
<button onclick="send('stop')">Stop</button>
<button onclick="send('right')">Right</button><br>

<button onclick="send('back')">Back</button>

<script>

function send(cmd)
{
fetch("/"+cmd)
}

</script>

</body>
</html>
"""

#################################################
# RECEIVE SENSOR DATA FROM ESP32
#################################################

@app.route("/data")
def receive():

    global temperature
    global humidity
    global battery_voltage
    global coil_voltage
    global charging
    global battery_level
    global last_update

    temperature = float(request.args.get("temp", 0))
    humidity = float(request.args.get("hum", 0))
    battery_voltage = float(request.args.get("battery", 0))
    coil_voltage = float(request.args.get("coil", 0))

    last_update = time.time()

    #################################################
    # CHARGING DETECTION
    #################################################

    if coil_voltage > 2.0:
        charging = True
    else:
        charging = False

    #################################################
    # BATTERY LEVEL DETECTION
    #################################################

    if battery_voltage < 7.5:
        battery_level = "LOW"

    elif battery_voltage < 12.2:
        battery_level = "MEDIUM"

    else:
        battery_level = "FULL"

    #################################################
    # PRINT TO TERMINAL
    #################################################

    print("\n------ SENSOR DATA ------")

    print("Temperature:", temperature, "°C")
    print("Humidity:", humidity, "%")
    print("Battery Voltage:", battery_voltage, "V")
    print("Coil Voltage:", coil_voltage, "V")
    print("Battery Level:", battery_level)

    if charging:
        print("CHARGING: YES")
    else:
        print("CHARGING: NO")

    print("-------------------------")

    return command

#################################################
# DASHBOARD PAGE
#################################################

@app.route("/")
def dashboard():

    level_class = "low"

    if battery_level == "MEDIUM":
        level_class = "medium"

    elif battery_level == "FULL":
        level_class = "full"

    return render_template_string(
        HTML_PAGE,
        temperature=temperature,
        humidity=humidity,
        battery_voltage=battery_voltage,
        coil_voltage=coil_voltage,
        charging=charging,
        battery_level=battery_level,
        battery_level_class=level_class
    )

#################################################
# STATUS API
#################################################

@app.route("/status")
def status():

    return jsonify({
        "temperature": temperature,
        "humidity": humidity,
        "battery_voltage": battery_voltage,
        "coil_voltage": coil_voltage,
        "battery_level": battery_level,
        "charging": charging,
        "command": command
    })

#################################################
# MOTOR CONTROL ROUTES
#################################################

@app.route("/forward")
def forward():
    global command
    command = "forward"
    print("Motor: FORWARD")
    return "OK"

@app.route("/back")
def back():
    global command
    command = "back"
    print("Motor: BACK")
    return "OK"

@app.route("/left")
def left():
    global command
    command = "left"
    print("Motor: LEFT")
    return "OK"

@app.route("/right")
def right():
    global command
    command = "right"
    print("Motor: RIGHT")
    return "OK"

@app.route("/stop")
def stop():
    global command
    command = "stop"
    print("Motor: STOP")
    return "OK"

#################################################
# START SERVER
#################################################

print("\nServer Started")
print("Open browser:")
print("http://localhost:5000")
print("or")
print("http://YOUR_IP:5000\n")

app.run(host="0.0.0.0", port=5000)
