#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <WiFi.h>
#include "esp_wpa2.h"
#include <PubSubClient.h>
#include <math.h>

const int PIN_TENSION = 35;
const int PIN_COURANT = 34;
const int N_VALEURS = 100;

const float K_V = 0.078;
const float K_I = -0.0161;
const float PHASE_ERROR_OFFSET = 9.0;

int valeurs_tension[N_VALEURS];
int valeurs_courant[N_VALEURS];

float V_rms = 0;
float I_rms = 0;
float P_apparent = 0;
float P_active = 0;
float phase_degrees = 0;

// ======================= WIFI / MQTT =============================
WiFiClient espClient;
PubSubClient client(espClient);

#define EAP_IDENTITY  "titouan.gardy-lognon@etu.univ-amu.fr"
#define EAP_USERNAME  "titouan.gardy-lognon@etu.univ-amu.fr"
#define EAP_PASSWORD  "Titouan11*"
const char* ssid = "eduroam";

const char* mqtt_server = "172.23.55.233";
const int   mqtt_port   = 1883;
const char* mqtt_topic  = "capteur/puissance";

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g(U8G2_R0, U8X8_PIN_NONE);

// Taille de l'image
#define LOGO_WIDTH  64
#define LOGO_HEIGHT 32

// 'Orange Black Minimalist Gear Electric Logo', 64x32px
const unsigned char logo_bits [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xc0, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xc0, 0x03, 0x07, 0x00, 0x00, 
	0x00, 0x00, 0x30, 0xc0, 0x03, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x10, 0xc0, 0x02, 0x0c, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x60, 0x06, 0x18, 0x00, 0x00, 0x00, 0x00, 0x18, 0x60, 0x06, 0x18, 0x00, 0x00, 
	0x00, 0x00, 0x08, 0x20, 0x04, 0x10, 0x00, 0x00, 0x00, 0x00, 0x08, 0x20, 0x04, 0x10, 0x00, 0x00, 
	0x00, 0x00, 0x08, 0x60, 0x06, 0x18, 0x00, 0x00, 0x00, 0x00, 0x18, 0x60, 0x06, 0x18, 0x00, 0x00, 
	0x00, 0x00, 0x10, 0x60, 0x02, 0x18, 0x00, 0x00, 0x00, 0x00, 0x30, 0xc0, 0x03, 0x0c, 0x00, 0x00, 
	0x00, 0x00, 0x60, 0x80, 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe1, 0x87, 0x03, 0x00, 0x00, 
	0x00, 0x00, 0x80, 0x3f, 0xfe, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xc9, 0x32, 0x86, 0x99, 0x39, 0xcf, 0x03, 
	0xe0, 0xcb, 0x7a, 0xcf, 0x99, 0x7d, 0xcf, 0x00, 0x60, 0xca, 0x1a, 0xc3, 0xb9, 0x07, 0xc1, 0x03, 
	0xe0, 0xcb, 0x7a, 0x4e, 0xfb, 0x07, 0xc7, 0x06, 0x60, 0xc8, 0x42, 0xe8, 0xdb, 0x47, 0x01, 0x06, 
	0x60, 0x78, 0x7a, 0x6f, 0x9a, 0x7d, 0x8f, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x10, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 272)
const int epd_bitmap_allArray_LEN = 1;
const unsigned char* epd_bitmap_allArray[1] = {
	logo_bits
};

void drawScreen() {
  u8g.setFont(u8g2_font_6x12_tf);  

  u8g.drawStr(0, 10, "  Capteur Puissance");

  char line[32];   // plus large = plus safe

  snprintf(line, sizeof(line), " Vrms : %.2f V", V_rms);
  u8g.drawStr(0, 22, line);

  snprintf(line, sizeof(line), " Irms : %.2f A", I_rms);
  u8g.drawStr(0, 32, line);

  snprintf(line, sizeof(line), " S   : %.2f V.A", P_apparent);
  u8g.drawStr(0, 42, line);

  snprintf(line, sizeof(line), " P_A : %.2f W", P_active);
  u8g.drawStr(0, 52, line);

  snprintf(line, sizeof(line), " Phi : %.2f degres", phase_degrees);
  u8g.drawStr(0, 62, line);
}

void showSplashScreen() {
  u8g.clearBuffer();

  // Centrer le logo sur un 128x64
  int x = (128 - LOGO_WIDTH) / 2;
  int y = (64  - LOGO_HEIGHT) / 2;

  u8g.drawXBMP(x, y, LOGO_WIDTH, LOGO_HEIGHT, logo_bits);
  u8g.sendBuffer();

  delay(3000);  // 3 secondes d’affichage

  // On efface l'écran avant de passer aux mesures
  u8g.clearBuffer();
  u8g.sendBuffer();
}

void setup() {
  Wire.begin();
  Serial.begin(115200);
  pinMode(PIN_COURANT, INPUT);
  pinMode(PIN_TENSION, INPUT);
  analogReadResolution(12);

  // init écran
  u8g.begin();

  // Afficher image de démarrage pendant 3 s
  showSplashScreen();

  // WiFi Eduroam
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);

  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_USERNAME, strlen(EAP_USERNAME));
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD));
  esp_wifi_sta_wpa2_ent_enable();
  WiFi.begin(ssid);

  Serial.print("Connexion à Eduroam");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\n✅ WiFi connecté !");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server, mqtt_port);

  /*Serial.print("Connexion MQTT...");
  while (!client.connected()) {
    if (client.connect("ESP32_Puissance")) {
      Serial.println(" OK !");
    } else {
      Serial.println(" Échec, nouvel essai…");
      delay(2000);
    }
  }*/
}

void loop() {

    if (!client.connected()) {
    client.connect("ESP32_Puissance");
  }
  client.loop();

  u8g.clearBuffer();
  drawScreen();
  u8g.sendBuffer();


  for (int k = 0; k < N_VALEURS; k++){
    valeurs_tension[k] = analogRead(PIN_TENSION);
    valeurs_courant[k] = analogRead(PIN_COURANT);
    delay(1);
  }

  long somme_v_corrige = 0;
  long somme_i_corrige = 0;

  for (int k = 0; k < N_VALEURS; k++){
    somme_v_corrige += valeurs_tension[k];
    somme_i_corrige += valeurs_courant[k];
  }

  float offset_U = (float)somme_v_corrige / N_VALEURS;
  float offset_I = (float)somme_i_corrige / N_VALEURS;

  float somme_carree_v = 0;
  float somme_carree_i = 0;
  float somme_vi = 0;

  for (int k = 0; k < N_VALEURS; k++) {
    float u_raw = valeurs_tension[k] - offset_U;
    float i_raw = valeurs_courant[k] - offset_I;

    float u_phys = u_raw * K_V;
    float i_phys = i_raw * K_I;

    somme_carree_v += u_phys * u_phys;
    somme_carree_i += i_phys * i_phys;
    somme_vi += u_phys * i_phys;
  }

  V_rms = sqrt(somme_carree_v / N_VALEURS);
  I_rms = sqrt(somme_carree_i / N_VALEURS);
  P_active = somme_vi / N_VALEURS;
  P_apparent = V_rms*I_rms;

  float facteur_puissance = 0.0;
  if (P_apparent > 0.1) {
    facteur_puissance = P_active/P_apparent;
  }

  if(facteur_puissance > 1.0) facteur_puissance = 1.0;
  if(facteur_puissance < -1.0) facteur_puissance = -1.0;

  float phase_radians = acos(facteur_puissance);

  phase_degrees = phase_radians * (180.0 / M_PI);

  float phase_corrige = phase_degrees - PHASE_ERROR_OFFSET;

  if (phase_corrige < 0) phase_corrige = 0;

  char msg[150];

  snprintf(msg, sizeof(msg),
           "{\"Vrms\":%.2f,\"Irms\":%.2f,\"S\":%.2f,\"P_A\":%.2f,\"Phi\":%.2f}",
           V_rms, I_rms, P_apparent, P_active, phase_degrees);

  Serial.println(msg);

   char jsonData[120];
  snprintf(jsonData, sizeof(jsonData),
           "{\"V_rms\":%.2f,\"I_rms\":%.2f,\"S\":%.2f,\"P_A\":%.2f,\"Phi\":%.2f}",
           V_rms, I_rms, P_apparent, P_active, phase_degrees);

  if (client.publish(mqtt_topic, jsonData)) {
    Serial.println("📤 Données envoyées à Node-RED !");
  } else {
    Serial.println("⚠️ Erreur d’envoi MQTT !");
  }


delay(1000);
}