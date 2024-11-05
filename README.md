# IoT Environmental Monitoring System

This project is an IoT-based environmental monitoring system built using an ESP32 microcontroller, various sensors, and ThingSpeak. It monitors soil moisture, water level, carbon monoxide (CO) levels, motion, light intensity, temperature, and humidity, sending the data to ThingSpeak for real-time visualization and analysis.

## Features
- **Soil Moisture Monitoring**: Tracks soil moisture levels.
- **Water Level Monitoring**: Detects water levels, triggers an alarm when the level is low.
- **Carbon Monoxide Detection (MQ-7)**: Measures CO concentration in the air.
- **Motion Detection**: Detects motion and updates the status.
- **Light Intensity Monitoring (LDR)**: Measures ambient light levels.
- **Temperature and Humidity Monitoring (DHT22)**: Reads temperature and humidity.
- **ThingSpeak Integration**: Sends sensor data to ThingSpeak for remote monitoring.
- **Buzzer Alert**: Activates an alarm based on water level readings.

## Hardware Required
- ESP32 microcontroller
- DHT22 sensor (for temperature and humidity)
- Soil moisture sensor
- Water level sensor
- MQ-7 sensor (for carbon monoxide detection)
- Motion sensor
- LDR (Light Dependent Resistor) sensor
- Buzzer

## Pin Configuration
| Sensor               | Pin            |
|----------------------|----------------|
| Soil Moisture        | 34             |
| Water Level          | 35             |
| MQ-7 (CO sensor)     | 32             |
| Motion Sensor        | 18             |
| LDR                  | 25             |
| DHT22                | 2              |
| Buzzer               | 4              |

## Setup Instructions
1. **Connect Sensors**: Follow the pin configuration table to wire the sensors to the ESP32.
2. **Install Libraries**:
   - Install the `DHT` library for the DHT22 sensor.
   - Install the `ThingSpeak` library to communicate with the ThingSpeak API.
3. **Configure WiFi**:
   - Update `ssid` and `password` in the code with your WiFi credentials.
4. **ThingSpeak Settings**:
   - Set `myChannelNumber` and `myWriteAPIKey` with your ThingSpeak channel details.

## Code Overview

### WiFi and ThingSpeak Initialization
```cpp
WiFi.begin(ssid, password);
ThingSpeak.begin(client);
```
Establishes WiFi connection and initializes ThingSpeak.

## Sensor Data Reading
**Reads data from:**
 - Soil moisture sensor
 - Water level sensor
 - MQ-7 sensor
 - Motion sensor
 - LDR
 - DHT22 sensor for temperature and humidity

## Buzzer Control
```cpp
if (waterLevelValue < 100) {
  digitalWrite(buzzer_pin, HIGH); // Turn on buzzer
} else {
  digitalWrite(buzzer_pin, LOW);  // Turn off buzzer
}
```
Activates the buzzer if water level is below a certain threshold.

## Data Transmission to ThingSpeak
Sends sensor readings to ThingSpeak fields.
```cpp
ThingSpeak.setField(1, waterLevelValue);
ThingSpeak.setField(2, mq7Value);
ThingSpeak.setField(3, ldrValue);
ThingSpeak.setField(4, humidity);
ThingSpeak.setField(5, temperature);
ThingSpeak.setField(6, soilMoistureValue);
ThingSpeak.setField(7, motionValue);
```

## Delay Between Updates
```cpp
delay(5000);
```
Delays 5 seconds between updates.
## Usage
 - Open the serial monitor to view real-time sensor readings.
 - Monitor data remotely via ThingSpeak.
## Troubleshooting
 - Ensure all sensor connections are secure.
 - Check WiFi credentials if unable to connect.
 - Verify ThingSpeak API key and channel number for successful data updates.
## License
This project is licensed under the MIT License.
