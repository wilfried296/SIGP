#include <DHT11.h>
// cree une variable qui sera sur la broche 2
DHT11 dht11(2);

void setup() {
/*pour initialiser le moniteur serie
afin de visualise les donnee
qui seront recolte par le capteur */
    Serial.begin(9600);
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
    } else {
        // affich un message d'erreur
        Serial.println(DHT11::getErrorString(result));
    }
}
