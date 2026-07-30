kleuren = {
    "wit":     (255, 255, 255),
    "rood":    (255, 0, 0),
    "groen":   (0, 255, 0),
    "blauw":   (0, 0, 255),
    "geel":    (255, 255, 0),
    "cyaan":   (0, 255, 255),
    "paars":   (255, 0, 255),
    "oranje":  (255, 64, 0),
}

#voorbeeld van hoe je een kleur kunt ophalen uit de dictionary
print(kleuren["blauw"])

#r,g,b waarden van een kleur ophalen
rgb = kleuren["rood"] #geeft tuple (255, 0, 0) terug
r, g, b = kleuren["geel"] #geeft r=255, g=255, b=0 terug

#### Drie voorbeelden van het doorlopen van een dictionary ####
#1
for kleur in kleuren: 
    #kleur is de key, bijv. "wit", "rood", "groen", etc.
    print(f"{kleur}: {kleuren[kleur]}")

#2: items() geeft beide de key en value terug
for kleur, rgb in kleuren.items():
    print(f"{kleur}: {rgb}")

#3: values() geeft alleen de value terug
for (r, g, b) in kleuren.values():
    print(f"Rood: {r}, Groen: {g}, Blauw: {b}")
