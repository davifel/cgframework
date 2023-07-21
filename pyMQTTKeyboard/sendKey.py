import paho.mqtt.client as mqtt
import json, math, threading, os
import time

def on_connect(client, userdata, flags, rc):
    print('Connected')
    
client = mqtt.Client()
client.on_connect = on_connect
client.connect('10.1.1.243',1883,60)
client.loop_start()

time.sleep(5)
client.publish('sendkey','A')
time.sleep(2)
client.publish('sendkey','S')
time.sleep(2)
client.publish('sendkey','W')
time.sleep(2)
client.publish('sendkey','D')
time.sleep(2)
client.publish('sendkey','J')
time.sleep(2)
client.publish('sendkey','K')
time.sleep(2)
client.publish('sendkey','I')
time.sleep(2)
client.publish('sendkey','L')
time.sleep(2)

client.loop_stop()
