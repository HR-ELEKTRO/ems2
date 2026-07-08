import time
from machine import Pin
from neopixel import NeoPixel

pin = Pin(8, Pin.OUT)   
np = NeoPixel(pin, 1)   
np[0] = (255, 255, 255) # begin met wit
np.write()              

#hier is de knop aangesloten tussen GPIO 10 en ground
knop = Pin(10, Pin.IN, Pin.PULL_UP)

toestand = "rood"
knop_flank = False
vorige_knop=0


while 1:
    #flankdetectie
    if knop.value() == 0 and vorige_knop == 1:
        knop_flank=True
    
    #de statemachine
    if toestand == "rood":
        if knop_flank:
            toestand = "groen"
            #maak de led groen...
            np[0] = (0, 255, 0) 
            np.write() 
    elif toestand == "groen":
        if knop_flank:
            toestand = "rood"
            #maak de led rood....
            np[0] = (255, 0, 0) 
            np.write()
    
    #update flankdetectie
    knop_flank=False
    vorige_knop = knop.value()
    #wachten 
    time.sleep_ms(200)
