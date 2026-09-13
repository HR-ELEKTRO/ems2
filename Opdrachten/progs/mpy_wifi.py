import network
import time

from wifi_secrets import SSID, PASSWORD

wlan = network.WLAN(network.STA_IF)
wlan.active(True)

wlan.connect(SSID, PASSWORD)  # Verbinden

print("Verbinding maken", end="")
while not wlan.isconnected():
    print(".", end="")
    time.sleep_ms(500)

print()

ip, subnet, gateway, dns = wlan.ifconfig()
print("IP-adres:\t", ip)
print("Subnetmasker:\t", subnet)
print("Gateway:\t", gateway)
print("DNS-server:\t", dns)
