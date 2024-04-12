#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "VotreSSID";
const char* password = "VotreMotDePasse";

const int relayPin = 2; // Broche à laquelle le relais est connecté

WebServer server(80);

void setup() {
  Serial.begin(115200);

  // Connexion au réseau WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion au WiFi en cours...");
  }
  Serial.println("Connecté au réseau WiFi");

  // Configuration de la broche du relais en sortie
  pinMode(relayPin, OUTPUT);

  // Définition des routes pour l'interface web
  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);

  server.begin();
  Serial.println("Serveur Web démarré");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  server.send(200, "text/html", "<h1>Contrôle du relais</h1><p><a href=\"/on\"><button>ON</button></a>&nbsp;<a href=\"/off\"><button>OFF</button></a></p>");
}

void handleOn() {
  digitalWrite(relayPin, HIGH); // Activer le relais
  server.send(200, "text/html", "<h1>Relais activé</h1><p><a href=\"/\">Retour</a></p>");
}

void handleOff() {
  digitalWrite(relayPin, LOW); // Désactiver le relais
  server.send(200, "text/html", "<h1>Relais désactivé</h1><p><a href=\"/\">Retour</a></p>");
}