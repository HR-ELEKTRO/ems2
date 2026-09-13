#functie om signed getal te maken
def signed_getal(getal, bits):
	masker = (1<<bits) - 1
	if getal & (1 << (bits - 1)):
		return getal | ~masker #alternatieve manier
	else:
		return getal 

def voeg_samen(data, aantalBits, endian=0):    
    aantalBytes = ((aantalBits-1) // 8)+1
    schuifRechts =  aantalBytes*8-aantalBits
    schuifLinks = 8-schuifRechts
    
    if endian==0:
        begin = aantalBytes-1
        eind=-1
        stap=-1
    else:
        begin = 0
        eind=aantalBytes
        stap=1

    eindWaarde = data[begin] >>schuifRechts
    byte=1
    for i in range(begin+stap,eind,stap):
        eindWaarde += data[i]<<(schuifLinks+(8*(byte-1)))
        byte+=1
        
    #Geef het samengevoegde signed getal terug
    return signed_getal(eindWaarde,aantalBits)
