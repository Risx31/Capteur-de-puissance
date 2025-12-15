# Capteur de Puissance Connecté (Projet Puissance 5)

Ce projet propose un **capteur IoT de mesure de puissance électrique** (active, réactive, apparente) conçu par une équipe d'étudiants du **BUT Mesures Physiques** d'Aix-Marseille Université.
- Tom Russo  
- Bruno Gaubert  
- Léonard Deloi  
- Eliot Vendenelsken--Robert  
- Titouan Gardy--Lognon  

L'objectif est de fournir une solution économique (< 80 €) et open-source pour le suivi énergétique dans les bâtiments intelligents, capable de transmettre les données via **Wi-Fi** et **MQTT** vers une interface de supervision (ex: Node-RED, InfluxDB).

![Schéma de montage](hardware/Schéma%20montage.jpeg)

## Organisation du Dépôt

Le projet est structuré en trois répertoires principaux :

* **`/firmware`** : Contient tout le code source pour l'ESP32 (environnement PlatformIO).
    * `src/main.cpp` : Programme principal (acquisition capteurs, calculs P/U/I, affichage OLED, client MQTT).
    * `platformio.ini` : Fichier de configuration du projet (dépendances bibliothèques, type de carte).
    * `lib/` & `include/` : Dossiers pour les bibliothèques et fichiers d'en-tête personnalisés.

* **`/hardware`** : Dossier technique matériel.
    * Schémas électriques (`Schéma montage.jpeg`, `Schéma conditionneur.png`) pour reproduire le circuit.
    * Liste des composants et budget (`Lise pièce et prix.xlsx`).

* **`/docs`** : Documentation détaillée du projet.
    * **Rapports** : Rapport complet du projet et roadmap de développement (`Roadmap capteur puissance.pdf`, `Explication_Roadmap.md`).
    * **Node-red** : Fichiers de configuration pour l'interface de supervision (`Flow_Node-red.json`).
    * **Imprimante_3D** : Documents relatifs à la fabrication du boîtier et amortissement de l'imprimante.
    * **Métrologie** : Fichiers de relevés et calculs d'incertitudes (`Fichier de métrologie.xlsx`).

## Fonctionnalités

* **Mesures en temps réel** :
    * Tension RMS ($V_{rms}$)
    * Courant RMS ($I_{rms}$)
    * Puissance Apparente ($S$ en VA)
    * Puissance Active ($P$ en W)
    * Déphasage ($\varphi$) et Facteur de puissance ($\cos \varphi$)
* **Affichage local** : Écran OLED pour visualiser les données directement sur le capteur.
* **Connectivité** : Connexion Wi-Fi (supporte WPA2-Enterprise / Eduroam) et transmission des données via MQTT.
* **Indicateurs** : Logo de démarrage et interface utilisateur sur l'écran OLED.

## Matériel Requis

La liste complète des pièces et les coûts sont détaillés dans le dossier `hardware`.

| Composant | Modèle / Référence | Prix approx. |
| :--- | :--- | :--- |
| **Microcontrôleur** | ESP32 (uPesy Wroom ou équivalent) | ~8.50 € |
| **Capteur de Courant** | Pince Ampèremétrique SCT013-030 (30A) | ~8.00 € |
| **Capteur de Tension** | Module Grove AC Voltage Sensor | ~4.00 € |
| **Affichage** | Écran OLED 1.3" I2C (SH1106/SSD1306) | ~10.00 € |
| **Conditionnement** | Module "Analog AC Current Sensor" (pour le SCT013) | ~5.00 € |
| **Divers** | Câbles, connecteurs | ~6.00 € |

## Câblage

Le microcontrôleur ESP32 est connecté aux capteurs selon les broches définies dans le firmware (`src/main.cpp`) :

* **Capteur de Tension** : Pin `35` (Entrée analogique)
* **Capteur de Courant** : Pin `34` (Entrée analogique, via conditionneur)
* **Écran OLED** : Bus I2C (SDA/SCL par défaut sur l'ESP32)

> **Note** : Un schéma du conditionneur de signal pour la pince ampèremétrique est disponible dans `hardware/Schéma conditionneur.png`.

## Installation et Configuration (Firmware)

Le firmware est développé sous **PlatformIO** (VS Code).

### Pré-requis
1.  Installer [Visual Studio Code](https://code.visualstudio.com/).
2.  Installer l'extension **PlatformIO IDE**.

### Installation
1.  Cloner ce dépôt :
    ```bash
    git clone [https://github.com/votre-username/Capteur-de-puissance.git](https://github.com/votre-username/Capteur-de-puissance.git)
    ```
2.  Ouvrir le dossier dans PlatformIO.
3.  Les bibliothèques nécessaires seront installées automatiquement (définies dans `platformio.ini`) :
    * `PubSubClient` (Communication MQTT)
    * `U8g2` (Gestion de l'écran OLED)

### Configuration
Ouvrez `src/main.cpp` et modifiez les paramètres suivants selon votre réseau :

```cpp
// Identifiants Wi-Fi (WPA2 Enterprise / Eduroam par défaut dans le code)
#define EAP_IDENTITY  "votre_identite"
#define EAP_USERNAME  "votre_username"
#define EAP_PASSWORD  "votre_mot_de_passe"
const char* ssid = "votre_ssid"; // ex: "eduroam" ou votre box

// Configuration MQTT
const char* mqtt_server = "IP_DE_VOTRE_BROKER"; // ex: "172.23.55.233"
const char* mqtt_topic  = "capteur/puissance";
