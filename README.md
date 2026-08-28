![Status](https://img.shields.io/badge/status-active%20development-orange)

# Photobioreaktor
## Overview
An open-source ESP32-based control and monitoring system for a low-cost photobioreactor for the cultivation of microalgae and cyanobacteria.

This repository contains the software and embedded control system for the photobioreactor.

Further information about the educational project, construction materials, and assembly instructions can be found on the project website:

https://lernenmitcirculareconomy.de/kulitivierung-von-cyanobaktieren-und-mikroalgen/

<br>

## Features
### Monitoring
- Real-time sensor data acquisition:
    - Temperature
    - Conductivity
    - Turbidity
    - Water Level

- Live visualization through the web dashboard
- Historical sensor data visualization

### Control
- Actuators:
    - Stirrer
    - Heatpad
    - Growing Light

- Configurable parameters:
    - Max. Temperature
    - Min. Temperature
    - Stirring Interval
    - Stirring Duration
    - Light On Hour
    - Light Off Hour
    - Measure Interval

### Web Interface
- Locally hosted web application
- No external web server required
- Real-time updates via WebSocket
- Interactive charts using Chart.js

### Embedded System
- Wi-Fi access point
- LittleFS for local filesystem storage
- Configuration using Preferences library
- PlatformIO-based development environment

<br>

## Hardware

### Sensors
| Sensor	  |  Purpose                                |
|-------------|-----------------------------------------|
| DS18B20	  |  Temperature              |
| KS0429      |  Total dissolved solids (TDS)  |
| HC-SR04	  |  Water-level    |

