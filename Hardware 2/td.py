import socket
import time

# TouchDesigner server details
td_ip = '192.168.4.2'  # Change this to the IP address of your TouchDesigner machine
td_port = 12345  # Change this to the port number you are using in TouchDesigner

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
            # Your code to read data from the ESP32 goes here
            # For the sake of this example, let's assume you have some data to send
            esp_data = "Data from ESP32"

            # Send the data to TouchDesigner
            send_to_touchdesigner(esp_data)

            # Wait before sending the next data
            time.sleep(1)  # Adjust the delay as needed
    except KeyboardInterrupt:
        print("Program terminated by user.")

print("346")
read_esp_data()
print("346")
