# j'importe mes bibliotechque
import time
import Adafruit_DHT
import RPi.GPIO as GPIO
import spidev

from pygame.examples.midi import Keyboard

# je configure mes broches
DHT_SENSOR= Adafruit_DHT.DHT11 #type de capteur
DHT_PIN=4
RELAY_PIN=17
FAN_PIN=27

# JE CONFIGURE EN MODE GPIO
GPIO.setmode(GPIO.BCM)#mode de numérotation facon GPIO
GPIO.setup(RELAY_PIN,GPIO.OUT)
GPIO.setup(FAN_PIN,GPIO.OUT)

# JE CONFIGURE LE SPI POUR MCP3008
spi=spidev.SpiDev()#jouvre la communication spi
spi.open(0,0)#selectionne le bus SPIO,CSO(se sont les broches 19 , 24)
spi.max_speed_hz=1350000#ca cest la vitesse de communication
#fonction pour lhumidite du sol
def read_adc(channel):
    adc=spi.xfer2([1,(8+channel)<<4,0])# envoie des donnée et recoit les valeurs
    data=((adc[1] & 3)<<8)+ adc[2]
    return data #retourne la valeur entre 0 et 1023(tres sec)
try:
  while True:
    #lecture de l'humiditer du sol
    soil_moisture=read_adc(0)
    print(f"Humidite du sol:{soil_moisture}")
    #lecture de la temperature et l'humiditer ambiante
    humidity,temperature= Adafruit_DHT.read(DHT_SENSOR,DHT_PIN)
    if humidity is not None and temperature is not None:
         print(f"temperature={temperature:.1f}°C Humidité={humidity:.1f}%")
         #controle du ventillateur
         if temperature>=30:
            GPIO.output(FAN_PIN,GPIO.HIGH)
            print("ventillateur active")
         else:
            GPIO.output(FAN_PIN, GPIO.LOW)
            print("ventilateur désactivé")
    else:
        print("Echec de la lecture du capteur DHT")
    # controle la pompe
    if soil_moisture < 300: #Seuil
        GPIO.output(RELAY_PIN,GPIO.HIGH)#j'active la pompe
        print("pompe activée")
    else:
        GPIO.output(RELAY_PIN,GPIO.LOW)# desactive la pompe
        print("pompe desactivée")
    time.sleep(10)

except KeyboardInterrupt:
      print("Arret du programme")
      GPIO.cleanup()#pour liberées les broches proprement apres l'arret du code
      spi.close()#ON FEMR LA COMMUNICATION SERIE


