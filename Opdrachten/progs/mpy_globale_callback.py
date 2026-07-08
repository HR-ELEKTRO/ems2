counter =0 #buiten alle functies gedefinieerd
def callback_functie(pin_object):
    #counter verwijst naar de globale variabele
    global counter 

    counter +=1
    print(counter)