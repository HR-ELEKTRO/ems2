import time

set_led(np , 255, 0 ,0) # rood
time.sleep_ms(2000)		   # wacht 2 seconden
set_led(np , 0 ,255 ,0) # groen
time.sleep_ms(2000)		   # wacht 2 seconden
set_led(np , 0 ,0 ,255) # blauw
time.sleep_ms(2000)		   # wacht 2 seconden
set_led(np , 0 ,0 ,0) # uit