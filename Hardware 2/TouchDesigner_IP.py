import requests
import socket
import time

td_ip = '192.168.4.2'  # Change this to the IP address of your TouchDesigner machine
td_port = 5005 

# ESP32 server details
esp_ip = '192.168.4.1'  # Change this to the IP address of your ESP32
esp_port = 80

def send_to_touchdesigner(data):
    try:
        # Create a TCP/IP socket
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            # Connect to TouchDesigner
            sock.connect((td_ip, td_port))
            # Send data to TouchDesigner
            sock.sendall(data.encode())
    except Exception as e:
        print(f"Error: {e}")


def read_esp_data():
    try:
        while True:
            # Make an HTTP request to the ESP32 server
            response = requests.get(f'http://{esp_ip}:{esp_port}/')

            # Check if the request was successful (status code 200)
            if response.status_code == 200:
                # Print the received data
                print(response.text)
                send_to_touchdesigner(response.text)
            else:
                print(f"Error: Unable to retrieve data. Status code: {response.status_code}")

            time.sleep(1)  # Adjust the delay as needed
    except KeyboardInterrupt:
        print("Program terminated by user.")

print("346")
read_esp_data()
print("346")