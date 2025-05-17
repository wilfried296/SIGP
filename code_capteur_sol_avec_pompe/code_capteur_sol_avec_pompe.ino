/*tout d'abord je declare mes variables 
ainsi que les broche qui seront utilise
sur la carte arduino/**/

int val;
int capteur_de_sol=3;/*pour dire que le capteur de sol 
sera connecter a la broche numero 3 de la carte*/

int relai_pompe=7;/*pour dire que le relais relier a la pompe
sera connecter a la broche numero 7 de la carte*/

void setup() {
  
Serial.begin(9600);/*pour initialiser le moniteur serie
afin de visualise les donnee
qui seront recolte par le capteur */

pinMode(capteur_de_sol,INPUT);/*pour dire que la
broche du capteur aura pour fontion de faire entree
le courant de la broche 3*/

pinMode(relai_pompe,OUTPUT);/*pour dire que la
broche du relais relier a la pompe aura pour fontion de faire sorti
le courant de la broche 7*/
}

void loop() {
  
val=analogRead(capteur_de_sol);/*pour recevoire les valeur
du capteur dans la broche 3 et le stocke dans une varable <<val>>*/

Serial.println(val);/*pour afficher les donnee recu
du capteur dans le moniteur serie */

digitalWrite(relai_pompe,HIGH);/*pour fait sorti le courant
dans la broche 7 afin d'activer le relai*/
}
