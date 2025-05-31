#include <DHT11.h>

/*tout d'abord je declare mes variables 
ainsi que les broche qui seront utilise
sur la carte arduino/**/

int soil_humidity;
int capteur_de_sol=3;/*pour dire que le capteur de sol 
sera connecter a la broche numero 3 de la carte*/

int relai_pompe=7;/*pour dire que le relais relier a la pompe
sera connecter a la broche numero 7 de la carte*/

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

pinMode(capteur_de_sol,INPUT);/*pour dire que la
broche du capteur aura pour fontion de faire entree
le courant de la broche 3*/

pinMode(relai_pompe,OUTPUT);/*pour dire que la
broche du relais relier a la pompe aura pour fontion de faire sorti
le courant de la broche 7*/

}

void loop() {
  
soil_humidity=analogRead(capteur_de_sol);/*pour recevoire les valeur
du capteur dans la broche 3 et le stocke dans une varable <<val>>*/


/*pour afficher les donnee recu
du capteur dans le moniteur serie */
Serial.print(",\"soil_humidity\":");      
Serial.print(soil_humidity);
Serial.println("}");

if (soil_humidity<=300){
 digitalWrite(relai_pompe,HIGH);/*pour fait sorti le courant
dans la broche 7 afin d'activer le relai*/ 
}else{

digitalWrite(relai_pompe,HIGH);/*pour fait sorti le courant
dans la broche 7 afin d'activer le relai*/
}

tempe();

}

void tempe() {
  // declare les variable et je les affectes la valeur 0 par defaut a chaque boucle
    int temperature = 0;
    int humidity = 0;

    
    //lire les valeur de la temperature et l'humidite
    int result = dht11.readTemperatureHumidity(temperature, humidity);

  // si la temperature est reussie,affiche la temperature et humidite
    if (result == 0) {
        Serial.print("{\"temperature\":");
        Serial.print(temperature);
        Serial.print(",\"humidity\":");
        Serial.print(humidity);
        Serial.println("}");
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
