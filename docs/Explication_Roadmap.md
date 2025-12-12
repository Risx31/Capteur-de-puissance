Roadmap de Développement
Capteur Connecté de Mesure de Puissance et d’Environnement
Version 2026–2027

Ce document détaille la roadmap R&D qui permettra de faire évoluer le prototype actuel vers une version stable et pré-industrielle.
Il complète le fichier « Roadmap capteur puissance.pdf » et en propose une analyse technique approfondie.

1. Objectif général

L’objectif est de faire passer le capteur du niveau TRL 4 (prototype fonctionnel) au niveau TRL 6/7 (pré-série) en suivant cinq grandes étapes réparties sur l’année 2026.
Chaque étape présente :

un objectif technique,

les tâches prévues,

le livrable associé,

un coût estimatif,

la valeur ajoutée pour le client.

2. Détails des étapes
2.1. Janvier – Février 2026
Optimisation des mesures électriques

Objectif : améliorer la précision et la stabilité des mesures.
Contexte : le prototype actuel atteint environ ±5 %. Une optimisation matérielle et logicielle permet de réduire cette marge.

Actions prévues

Recalage temporel entre tension et courant

Filtrage numérique (fenêtre Hanning, moyenne glissante)

Calibration sur charges résistives, inductives et capacitives

Révision du firmware avec module dédié au calcul de puissance

Livrable

Firmware v1.2 – précision cible : ±3 %

Coût estimé

600 €

Valeur ajoutée

Précision accrue, meilleure détection des anomalies, conformité renforcée au cahier des charges.

2.2. Mars – Avril 2026
Intégration de la connectivité LoRaWAN

Objectif : proposer une communication longue portée adaptée aux environnements industriels.

Actions prévues

Intégration du module LoRa SX1276

Bascule automatique Wi-Fi / LoRaWAN

Tests de portée en intérieur et extérieur

Adaptation du format des données (payload compact)

Livrable

Firmware v2.0 – transmission hybride Wi-Fi + LoRaWAN

Coût estimé

990 €

Valeur ajoutée

Adapté aux sites isolés, réseau longue distance, faible consommation.

2.3. Mai – Juin 2026
Compatibilité InfluxDB 3.0 et API Cloud

Objectif : permettre l’analyse longue durée et le stockage structuré des mesures.

Actions prévues

Refonte du format JSON pour InfluxDB 3.0

API REST + MQTT sécurisée

Mise à jour du tableau de bord

Scripts d’intégration Node-RED → InfluxDB

Livrable

Dashboard v3.1 – historique complet + alertes cloud

Coût estimé

791 €

Valeur ajoutée

Suivi énergétique réel, analyses temporelles, intégration simple aux outils de supervision.

2.4. Juillet – Septembre 2026
Conception du boîtier 3D

Objectif : transformer un prototype nu en un dispositif utilisable et sécurisé.

Actions prévues

Conception CAO (Fusion 360)

Prototypes successifs FDM puis SLA

Ajout d’un système de fixation murale / rail DIN

Étude thermique et ventilation

Livrable

Boîtier v1.0 – prêt pour une petite série

Coût estimé

495 €

Valeur ajoutée

Sécurité améliorée, présentation professionnelle, installation facilitée.

2.5. Octobre – Décembre 2026
Pré-série TRL 6/7

Objectif : stabiliser l’ensemble et préparer une production de 20 unités.

Actions prévues

Réécriture modulaire du firmware avec tests unitaires

Conception d’un PCB dédié

Vérifications thermiques et électriques

Rédaction du dossier technique de production

Fabrication de cinq unités de test

Livrable

Capteur v3.0 – version pré-série

Coût estimé

1 240 €

Valeur ajoutée

Produit proche du niveau industriel, maintenance facilitée, production reproductible.

3. Synthèse budgétaire
Période	Étape	Coût
Jan–Fév 2026	Optimisation des mesures	600 €
Mar–Avr 2026	Connectivité LoRaWAN	990 €
Mai–Jun 2026	InfluxDB 3.0 et API Cloud	791 €
Juil–Sep 2026	Boîtier 3D pré-industriel	495 €
Oct–Déc 2026	Version pré-série TRL 6/7	1 240 €
Total		4 116 €
4. Conclusion

Cette roadmap propose une évolution structurée et réaliste du capteur, permettant de passer d’un prototype fonctionnel à une solution presque industrielle. Elle offre une vision claire des coûts, du calendrier et des bénéfices associés à chaque étape, en garantissant une montée en maturité technique cohérente avec les besoins du client.
