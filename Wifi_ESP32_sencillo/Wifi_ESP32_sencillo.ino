/* Super TOOLS LP
Este es un ejemplo sencillo, de como usar la ESP32 conectado con el Wifi,
puedes guiarte para que puedas crear tus proyectos con tus necesidades.
Recuerda seguirme en youtube y apoyarme para crear mas contenido.
youtube: https://www.youtube.com/@SuperTOOLSLP/featu
facebook: https://www.facebook.com/people/Super-TOOLS-LP/100083303172492/?ref
Página web  https://supertoolslp.blogspot.com/
*/

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Nombre de tu wifi";
const char* password = "clave de tu wifi";

WebServer server(80);

const int ledPin = 2; /// pin que usamos para el led

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.println("Configurando WiFi en modo estación");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado!!!");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, handleRoot);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<h1>Control de LED</h1><p><a href=\"/encender\">Encender LED</a></p><p><a href=\"/apagar\">Apagar LED</a></p>";
  server.send(200, "text/html", html);
}

void handleNotFound() {

  String cadena = server.uri();

  if (cadena == "/encender" || cadena == "/Encender") {
    digitalWrite(ledPin, HIGH); /// Enciende el led
    server.send(200, "text/plain", "LED encendido");

  } else if (cadena == "/apagar" || cadena == "/Apagar") {
    digitalWrite(ledPin, LOW); /// Apaga el led
    server.send(200, "text/plain", "LED apagado");

  } else {
    server.send(404, "text/plain", "Comando no reconocido");
  }
}
