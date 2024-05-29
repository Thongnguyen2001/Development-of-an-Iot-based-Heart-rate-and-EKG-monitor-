# Development-of-an-Iot-based-Heart-rate-and-EKG-monitor
A final year project of a biomedical student.
## About this project
Wearable Holter for Home User - Overall Appearance
![image](https://github.com/discoverycomputer/Development-of-an-Iot-based-Heart-rate-and-EKG-monitor-/assets/140111334/8a00b08d-baa9-4c3e-993a-a55a00e70e15)
# The main circuit design using STM32F103C8T6 microprocessor 
Altium Designer
![image](https://github.com/discoverycomputer/Development-of-an-Iot-based-Heart-rate-and-EKG-monitor-/assets/140111334/5d98eea8-b1b2-4eb5-a3af-44765aab99c6)

Complete ECG circuit
![image](https://github.com/discoverycomputer/Development-of-an-Iot-based-Heart-rate-and-EKG-monitor-/assets/140111334/d43671db-ba81-42b6-b1a4-67e8c9a53b61)
The GUI to process the heart signal and heart beat detected from the circuit (Qt Creator)
![image](https://github.com/discoverycomputer/Development-of-an-Iot-based-Heart-rate-and-EKG-monitor-/assets/140111334/54bf468b-dc3e-4c56-a1c2-dee0b7f863cb)
# Working Principle 
![image](https://github.com/discoverycomputer/Development-of-an-Iot-based-Heart-rate-and-EKG-monitor-/assets/140111334/1a06e796-c9f2-4446-a101-6c03966563ad)
The flow was sketched in this block diagram for the overview of the device. First, the device uses 3-electrode placement to conduct 1 lead ECG acquisition. The MCU is responsible for ADC and DAC main processing units. The calculated heart-beat is displayed on OLED, the ECG signal is transmitted to the GUI application by using UART. An integration of client/sever from cloud database. To qualify this feature, the patient information is then saved to csv format locally for further management.
# Result
