# Roadmap de Développement
**Capteur Connecté de Mesure de Puissance et d’Environnement**  
Version 2026–2027

Ce document décrit la roadmap R&D permettant de faire évoluer le prototype (TRL 4) vers une solution pré-industrielle (TRL 6/7). Il présente les étapes, les livrables, les coûts estimés et la valeur ajoutée pour le client.

---

## 1. Objectif général

Faire passer le capteur du stade prototype (TRL 4) à une pré-série industrielle (TRL 6/7) sur l'année 2026, via cinq étapes prioritaires. Pour chaque étape sont indiqués : l'objectif, les actions, le livrable, le coût estimé et la valeur ajoutée.

---

## 2. Étapes détaillées

### 2.1 Janvier – Février 2026 — Optimisation des mesures électriques  
**Objectif** : améliorer la précision et la stabilité des mesures (réduire l'incertitude d'environ ±5 % à ±3 %).  

**Actions** :
- Recalage temporel entre tension et courant.  
- Filtrage numérique (fenêtre Hanning, moyenne glissante).  
- Calibration sur charges résistives, inductives et capacitives.  
- Révision du firmware (module de calcul énergétique dédié).

**Livrable** : Firmware v1.2 — précision cible : ~±3 %.  
**Coût estimé** : 1160 €  
**Valeur ajoutée** : mesures plus fiables, meilleure détection d’anomalies, conformité renforcée.

---

### 2.2 Mars – Avril 2026 — Intégration LoRaWAN  
**Objectif** : ajouter une option de transmission longue portée pour sites sans Wi-Fi fiable.  

**Actions** :
- Intégration module LoRa (SX1276 ou équivalent).  
- Gestion Wi-Fi / LoRaWAN avec bascule automatique.  
- Tests de portée en intérieur / extérieur.  
- Compression et adaptation du payload.

**Livrable** : Firmware v2.0 — Wi-Fi + LoRaWAN.  
**Coût estimé** : 1880 €  
**Valeur ajoutée** : couverture réseau étendue, meilleure résilience en milieu industriel.

---

### 2.3 Mai – Juin 2026 — Intégration InfluxDB 3.0 & API Cloud  
**Objectif** : fournir stockage historique exploitable et API pour supervision et analyses.  

**Actions** :
- Refonte du format JSON pour InfluxDB 3.0.  
- API REST sécurisée et intégration MQTT.  
- Dashboard historique et système d’alertes.  
- Scripts d’intégration Node-RED → InfluxDB.

**Livrable** : Dashboard v3.1 — historique longue durée + alertes.  
**Coût estimé** : 1561 €  
**Valeur ajoutée** : exploitation métier des données, détection de dérives, intégration BMS.

---

### 2.4 Juillet – Septembre 2026 — Conception boîtier 3D pré-industriel  
**Objectif** : produire un boîtier sécurisé, compact et facilement installable.  

**Actions** :
- CAO (Fusion 360) et itérations design.  
- Prototypes FDM puis SLA.  
- Fixations murales / rail DIN.  
- Étude thermique et ventilation passive.

**Livrable** : Boîtier v1.0 — prêt pour petite série.  
**Coût estimé** : 1395 €  
**Valeur ajoutée** : sécurité, esthétique, facilité d’installation.

---

### 2.5 Octobre – Décembre 2026 — Pré-série TRL 6/7  
**Objectif** : stabiliser le produit et préparer une production pilote (≈20 unités).  

**Actions** :
- Réécriture modulaire du firmware + tests unitaires.  
- Conception PCB dédié.  
- Vérifications électriques et thermiques.  
- Dossier technique de production.  
- Fabrication de 5 unités de validation.

**Livrable** : Capteur v3.0 — version pré-série.  
**Coût estimé** : 1 240 €  
**Valeur ajoutée** : produit industriel, maintenance facilitée, coûts de production optimisés.

---

## 3. Synthèse budgétaire

| Période        | Étape                          | Coût  |
|----------------|--------------------------------|-------|
| Jan–Fév 2026   | Optimisation mesures           | 600 € |
| Mar–Avr 2026   | Connectivité LoRaWAN           | 990 € |
| Mai–Jun 2026   | InfluxDB 3.0 & API Cloud       | 791 € |
| Juil–Sep 2026  | Boîtier 3D                     | 495 € |
| Oct–Déc 2026   | Pré-série TRL 6/7              | 1 240 € |
| **Total 2026** |                                | **4 116 €** |

---

## 4. Points de risque et atténuations

- **Précision des mesures** : risque lié au bruit ou aux erreurs de synchronisation — mitigation : banc de tests étendu et procédures de calibration automatisées.  
- **Intégration LoRa** : risque d'interférences et contraintes de payload — mitigation : tests terrain et optimisation du format des messages.  
- **Compatibilité back-end** : évolution des versions de bases (InfluxDB) — mitigation : API versionnée et tests d'intégration continus.  
- **Délai d'approvisionnement composants** : risque sur PCB et modules — mitigation : sourcing alternatif et commandes anticipées.

---

## 5. Livrables attendus (par étape)

- Firmware (versions intermédiaires et changelog).  
- Schémas électriques et PCB Gerber pour la pré-série.  
- Protocoles et résultats du banc de test.  
- Dashboard et scripts d’intégration (Node-RED, API).  
- Dossier technique (manuel d’installation, maintenance, sécurité).  
- Boîtier CAO + prototypes photos.

---

## 6. Conclusion

Roadmap progressive, priorisant la qualité métrologique puis la robustesse et la déployabilité. Les coûts proposés sont estimatifs et peuvent varier selon choix de composants, contraintes terrain ou demandes supplémentaires. Le plan vise une montée en maturité claire et mesurable, compatible avec un déploiement pilote à court terme.

---

## 7. Contact / Références

- Documents complémentaires : `Roadmap capteur puissance.pdf` (fichier joint au dépôt).  
- Pour questions techniques ou ajustement du planning, consulter la section « Issues » du dépôt ou contacter l’équipe projet.

