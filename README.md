# Crash Detection & Airbag Trigger Simulator

A C-based simulation of an automotive crash detection system designed to detect vehicle impacts using simulated sensor data.

The system analyzes accelerometer, gyroscope, and vehicle speed signals to detect crashes and determine whether an airbag deployment event should be triggered.

This project simulates the basic logic used inside **airbag control units (ACU)** and **crash sensing modules** used in modern vehicles.



# Overview

Modern vehicles use multiple sensors to detect collisions within milliseconds.
This simulator processes sensor data in real time and determines:

* if an impact occurred
* what type of crash happened
* how severe the crash is
* whether the airbag deployment condition is met

The program reads simulated sensor data from a CSV file and processes it sample-by-sample, similar to how an embedded automotive ECU would process sensor input.



# Features

* Real-time sensor monitoring
* Crash detection algorithm
* Airbag deployment logic
* Crash severity classification
* Crash type detection
* Sensor signal filtering
* Configurable detection thresholds
* Crash event logging
* CSV export of detected impacts
* Terminal dashboard for live monitoring



# Project Structure
```
crash-detection-simulator
│
├── src
│   └── main.c                # Crash detection algorithm
│
├── data
│   └── crash_data.csv        # Simulated vehicle sensor data
│
├── config
│   └── config.txt            # Detection thresholds
│
├── output
│   ├── crash_log.txt         # Logged crash events
│   └── crashes.csv           # Exported crash data
│
├── README.md
└── .gitignore
```



# Sensors Used

The simulator processes three types of signals typically used in crash detection systems.

### Accelerometer

Detects strong deceleration during impact.

Large negative acceleration values often indicate a frontal crash.

### Gyroscope

Detects rotational movement of the vehicle.

High rotation rates can indicate:

* side impact
* rollover events

### Vehicle Speed

Used to estimate crash severity and filter false positives.



# Crash Detection Algorithm

The system calculates a **crash score** using multiple sensor signals.

The score is based on:

* high negative acceleration
* strong rotational movement
* vehicle speed

If the score exceeds a threshold for a short duration, the system confirms a crash event.

This helps prevent false positives caused by noise or sudden braking.



# Airbag Deployment Logic

Once a crash is detected, the system evaluates the severity of the event.

If the impact is strong enough, the simulator triggers an **airbag deployment event**.

Example conditions:

* strong deceleration
* sustained crash score
* significant rotational forces

When these conditions are met, the system prints:

```
 IMPACT DETECTED 
Impact type: OFFSET
Severity: MODERATE

Airbag: DEPLOYED
```

---

# Crash Classification

The simulator attempts to identify the type of crash.

### Crash Types

* **FRONTAL** – strong forward deceleration
* **LATERAL** – strong side rotation
* **ROLLOVER** – extreme gyroscope values
* **OFFSET** – mixed acceleration and rotation
* **MINOR** – low impact

### Severity Levels

* MINOR
* MODERATE
* SEVERE

---

# Signal Processing

The simulator applies a **moving average filter** to the acceleration signal.

This reduces noise and simulates basic signal conditioning typically used in embedded systems.

Additionally, the program calculates **jerk**, which represents the rate of change of acceleration and is commonly used in crash detection algorithms.

---

# Logging

Detected crash events are stored in:

```
output/crash_log.txt
```

Example log entry:

```
CRASH DETECTED
Time: 63 ms
Acceleration: -6.50 g
Jerk: -2.10
Impact type: OFFSET
Severity: MODERATE
GPS: 45.6580 25.6012
Timestamp: Wed Mar 12 13:05:32 2026
```

Crash data is also exported to:

```
output/crashes.csv
```

for further analysis.



# Configuration

Detection parameters can be tuned in:

```
config/config.txt
```

Example configuration:

```
CRASH_THRESHOLD=-6
SEVERE_THRESHOLD=-9
JERK_THRESHOLD=-4
SOS_DELAY=5
```

This allows adjusting the sensitivity of the crash detection algorithm.

---

# Technologies Used

* C programming language
* File I/O
* Sensor data simulation
* Basic signal filtering
* Crash detection algorithms
* Terminal dashboard interface



# Possible Improvements

Future improvements could include:

* multi-axis accelerometer support
* real-time sensor generation
* graphical visualization of sensor signals
* integration with embedded hardware platforms


