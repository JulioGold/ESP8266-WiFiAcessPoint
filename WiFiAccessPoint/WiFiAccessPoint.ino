#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

/* Configuração para o WiFi */
const char *ssid = "SmartTech"; // Nome da rede
const char *password = "12345678"; // Senha conforme desejar, minimo 8 caracteres

ESP8266WebServer server(80); // Definindo o servidor na porta 80

// HTML master
char HTML[] = "<html><body><h1>Funcionando a encrenca</h1><h2>SmartTechSystems</h2><button><a href=\"toggle\">Alterar LED</a></button></body></html>";

// Função principal, será chamada sempre que chamar o IP do módulo
void handleRoot() 
{
    server.send(200, "text/html", HTML);
}

// Essa função será chamada sempre que acessar o endereço 192.168.4.1/toggle
void toggle()
{
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    server.send(200, "text/html", HTML);
}

void setup() {
    delay(1000); // Da um tempo para tudo subir antes de iniciar a brincadeira
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    Serial.println();
    Serial.print("Configuring access point...");
    /* Se você remover a senha será uma conexão aberta */
    WiFi.softAP(ssid, password); // Esta linha define o módulo como um AP
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("Endrereço IP do AP: ");
    Serial.println(myIP);
    server.on("/", handleRoot); // Define a rota principal
    server.on("/toggle", toggle); // Define a rota de toggle do LED
    server.begin(); // Inicia o servidor
    Serial.println("Servidor HTTP iniciado");
}

void loop() {
    server.handleClient();
}
