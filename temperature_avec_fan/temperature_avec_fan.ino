#include <DHT11.h>

// cree une variable qui sera sur la broche 2

DHT11 dht11(2);

//variable du ventillateur

int relai_fan=8;

void setup() {
  Serial.begin(9600);/*pour initialiser le moniteur serie
afin de visualise les donnee
qui seront recolte par le capteur */
  

    pinMode(relai_fan,OUTPUT);/*pour dire que la
broche du relais relier au fan aura pour fontion de faire sorti
le courant de la broche 8*/
}

void loop() {
  // declare les variable et je les affectes la valeur 0 par defaut a chaque boucle
    int temperature = 0;
    int humidity = 0;

    //lire les valeur de la temperature et l'humidite
    int result = dht11.readTemperatureHumidity(temperature, humidity);

  // si la temperature est reussie,affiche la temperature et humidite
    if (result == 0) {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C\tHumidity: ");
        Serial.print(humidity);
        Serial.println(" %");
        if (temperature >=30){

           digitalWrite(relai_fan,HIGH);/*pour fait sorti le courant
dans la broche 8 afin d'activer le relai*/ 
          
        }else{
                     digitalWrite(relai_fan,LOW);/*pour fait annulé le courant
dans la broche 8 afin d'activer le relai*/ 
          
        }
    } else { 
        // affich un message d'erreur
        Serial.println(DHT11::getErrorString(result));
    }
}
