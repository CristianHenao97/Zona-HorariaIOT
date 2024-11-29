#include <WiFi.h>
#include <HTTPClient.h>
#include "time.h"

// Credenciales de WiFi
const char* ssid = "SSID";         // Nombre de la red WiFi (puedes simularlo en Wokwi)
const char* password = "PWD"; // Contraseña de la red WiFi

// Configuración de NTP
const char* ntpServer = "pool.ntp.org";     // Servidor NTP
const long gmtOffset_sec = -18000;         // Desfase horario en segundos (-5 horas para Colombia)
const int daylightOffset_sec = 3600;       // Ajuste de horario de verano (1 hora)

// Variables para manejar la hora
struct tm timeinfo;

void printLocalTime() {
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Error obteniendo la hora");
    return;
  }
  // Imprime la hora local en el monitor serial
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S"); // Día, mes, día del mes, año, hora:minuto:segundo
}

void setup() {
  Serial.begin(115200);

  // Conexión al WiFi
  Serial.printf("Conectando a WiFi: %s\n", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado a WiFi!");
  Serial.printf("Dirección IP: %s\n", WiFi.localIP().toString().c_str());

  // Configura NTP con desfase horario y ajuste de horario de verano
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println("Configuración de NTP completada.");
}

void loop() {
  // Llama a la función para imprimir la hora local cada 5 segundos
  printLocalTime();
  delay(5000);
}
