import binascii
import time

import network
from machine import Pin, unique_id
from neopixel import NeoPixel
from umqtt.simple import MQTTClient

from wifi_secrets import SSID, PASSWORD

KLEUREN = {
    "rood": (40, 0, 0),
    "groen": (0, 40, 0),
    "blauw": (0, 0, 40),
    "wit": (20, 20, 20),
    "uit": (0, 0, 0),
}

def zet_led(rgb):
    led[0] = rgb
    led.write()

#maakt de wifi verbinding en geeft het wlan object terug
def verbind_wifi():
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)

    if not wlan.isconnected():
        wlan.connect(SSID, PASSWORD)
        print("Verbinding maken met wifi", end="")

        while not wlan.isconnected():
            print(".", end="")
            time.sleep_ms(500)

        print()

    print("IP-adres:", wlan.ifconfig()[0])
    return wlan

#de MQTT callback functie die wordt aangeroepen als er een bericht is ontvangen
def bericht_ontvangen(topic, bericht):
    topic_tekst = topic.decode()
    #we gaan ervan uit dat de payload een kleur is
    kleur = bericht.decode().strip().lower()
    print("Ontvangen:", topic_tekst, kleur)

    if kleur in KLEUREN:
        zet_led(KLEUREN[kleur])
    else:
        print("Onbekende kleur")

BROKER = "broker.hivemq.com"
APPARAAT_ID = binascii.hexlify(unique_id()).decode()

BASISTOPIC = "ems2/" + APPARAAT_ID
TOPIC_LED = (BASISTOPIC + "/led").encode() #topic waarop de kleur binnenkomt
TOPIC_TEMPERATUUR = (BASISTOPIC + "/temperatuur").encode() #topic waarop de temperatuur wordt gepubliceerd
CLIENT_ID = ("ems2-c6-" + APPARAAT_ID).encode() # een unieke ID om mee aan te melden bij de broker

led = NeoPixel(Pin(8, Pin.OUT), 1)
wlan = verbind_wifi()
client = MQTTClient(CLIENT_ID, BROKER, port=1883, keepalive=60)
client.set_callback(bericht_ontvangen)
client.connect()
client.subscribe(TOPIC_LED)

print("Verbonden met MQTT-broker:", BROKER)
print("Geabonneerd op:", TOPIC_LED.decode())
print("Publiceer temperatuur op:", TOPIC_TEMPERATUUR.decode())

laatste_ping = time.ticks_ms()

try:
    while True:
        client.check_msg() #checken op berichten van de broker,
        time.sleep_ms(50) #elke 50 ms.

        #elke 30 seconden een ping sturen om de verbinding met de broker te behouden
        #we gebruiken ticks_diff om rekening te houden met overflow van de ticks_ms() timer
        # functioneel is het gewoon huige_tijd_in_ms - laatste_ping_in_ms >= 30 000 ms
        if time.ticks_diff(time.ticks_ms(), laatste_ping) >= 30000:
            client.ping()
            laatste_ping = time.ticks_ms()
finally:
    zet_led(KLEUREN["uit"])
    client.disconnect()
