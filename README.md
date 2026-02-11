#  SmartCut – Planche intelligente RFID

Projet réalisé lors de la **GarageWeek 2025** projet académique à l’ISEN Méditerranée, en collaboration avec Sodexo.

---

##  Problématique

Les accidents liés aux coupures en cuisine professionnelle sont fréquents.  
L’objectif du projet **SmartCut** est de sécuriser l’utilisation des planches à découper en vérifiant automatiquement le port d’un gant anti-coupure grâce à la technologie RFID.

---

##   Solution proposée

SmartCut est une planche à découper intelligente intégrant :

- 🟢 Capteur de pression (FSR)
- 🏷 Module RFID RC522
- 💡 LED de signalisation
- 🔊 Buzzer d’alerte
- ⚙ Arduino UNO

###  Fonctionnement

1. Le capteur détecte qu’un appui est exercé sur la planche.
2. Le module RFID vérifie la présence d’un badge intégré au gant.
3. Si le gant est détecté → LED verte.
4. Si le gant est absent → LED rouge + alerte sonore.

---

##  Architecture technique

- Lecture analogique du capteur de pression
- Moyenne glissante pour stabiliser la mesure
- Détection RFID via SPI
- Système de verrouillage logique (latch)
- Feedback visuel et sonore

Le code Arduino est disponible dans le dossier `/arduino`.

---

## 🖼 Poster du projet

![Poster SmartCut](Documentation/Poster Garageweek.png)

---

##  Documentation

Le dossier `/Documentation` contient :

- 📄 Charte_projet.pdf → Organisation et planification
- 🎤 Pitch.pdf → Présentation finale du projet
- 🖼 Poster Garageweek.pdf → Présentation du projet

---

##  Équipe projet – GarageWeek 2025

Projet développé en équipe :

- Humberta ABALO  
- Shamina FRUTEAU  
- Jassime ZAIETER  
- Lucas RIBEIRO  
- Rebecca AHIALE  
- Aissatou DIALLO  

---

##  Mon implication

Dans ce projet collaboratif, j’ai contribué à :

- La programmation Arduino
- Le montage électronique 
- Rédaction des livrables
- La présentation finale

---

##  Résultat

Prototype fonctionnel validé lors de la GarageWeek 2025.

- Temps de réponse < 0,5 seconde  
- Détection fiable du port du gant  
- Prototype opérationnel présenté à Sodexo  

---

