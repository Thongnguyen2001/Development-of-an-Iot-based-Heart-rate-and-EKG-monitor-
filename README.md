# Development-of-an-Iot-based-Heart-rate-and-EKG-monitor
A final year project of a biomedical student.
## About this project
Wearable Holter for Home User - Overall Appearance
![image](https://github.com/discoverycomputer/Development-of-an-Iot-based-Heart-rate-and-EKG-monitor-/assets/140111334/40549966-2e4e-4eba-94d8-34fd179081f4)
# The main circuit design using STM32F103C8T6 microprocessor 
Altium Designer
![image](https://github.com/discoverycomputer/Development-of-an-Iot-based-Heart-rate-and-EKG-monitor-/assets/140111334/96420b73-dd9c-477a-baae-5af555ddfd53)
Complete ECG circuit
![image](https://github.com/discoverycomputer/Development-of-an-Iot-based-Heart-rate-and-EKG-monitor-/assets/140111334/2eeb0b42-d11f-4454-89ae-a6610ee2dfe6)
The GUI to process the heart signal and heart beat detected from the circuit (Qt Creator)
![image](https://github.com/discoverycomputer/Development-of-an-Iot-based-Heart-rate-and-EKG-monitor-/assets/140111334/8e3171ab-567c-4345-b61b-d6fcd5d19bbf)
# Working Principle 
![image](https://github.com/discoverycomputer/Development-of-an-Iot-based-Heart-rate-and-EKG-monitor-/assets/140111334/8423f796-f7d7-401f-8946-ebe6b826715e)
The flow was sketched in this block diagram for the overview of the device. First, the device uses 3-electrode placement to conduct 1 lead ECG acquisition. The MCU is responsible for ADC and DAC main processing units. The calculated heart-beat is displayed on OLED, the ECG signal is transmitted to the GUI application by using UART. An integration of client/sever from cloud database. To qualify this feature, the patient information is then saved to csv format locally for further management.
# Result
