
#include <SPI.h>
#include <MFRC522.h>

// Broches LEDs (common-anode)
#define LED_R        2        // Rouge
#define LED_G        3        // Verte
#define BUZZER_PIN   5        // Buzzer sur D5 (PWM)

// Capteur de pression
#define PRESS_PIN    A0       // FSR connecté sur A0

// RFID
#define RST_PIN      9
#define SS_PIN       10
MFRC522 mfrc522(SS_PIN, RST_PIN);

const int THRESHOLD       = 600;   // Seuil pour détecter un appui
const int NUM_SAMPLES     = 10;    // Nombre d'échantillons pour la moyenne
int   samples[NUM_SAMPLES];        // Tampon circulaire
int   sampleIndex    = 0;
long  total          = 0;
int   averagePress   = 0;

bool latchedTag      = false;      // Mémoire de détection du tag sous appui

void setup() {
  // LEDs en sorties, HIGH = éteint (common-anode)
  pinMode(LED_R, OUTPUT);    digitalWrite(LED_R, HIGH);
  pinMode(LED_G, OUTPUT);    digitalWrite(LED_G, HIGH);
  // Buzzer en sortie, off
  pinMode(BUZZER_PIN, OUTPUT);
  analogWrite(BUZZER_PIN, 0);

  pinMode(PRESS_PIN, INPUT);
  Serial.begin(9600);
  while (!Serial);

  SPI.begin();
  mfrc522.PCD_Init();

  // Initialiser le tampon d'échantillons
  for (int i = 0; i < NUM_SAMPLES; i++) {
    samples[i] = analogRead(PRESS_PIN);
    total    += samples[i];
  }
  averagePress = total / NUM_SAMPLES;
}

void loop() {
  // 1) Mettre à jour la fenêtre glissante
  total      -= samples[sampleIndex];               // retire l'ancien
  samples[sampleIndex] = analogRead(PRESS_PIN);     // lit nouveau
  total      += samples[sampleIndex];               // ajoute nouveau
  sampleIndex = (sampleIndex + 1) % NUM_SAMPLES;    // avance index
  averagePress = total / NUM_SAMPLES;               // calcule moyenne

  bool weight = (averagePress > THRESHOLD);         // appui si moyenne > seuil

  // 2) Armement du latch si appui + tag
  if (weight && !latchedTag) {
    if (mfrc522.PICC_IsNewCardPresent() 
        && mfrc522.PICC_ReadCardSerial()) {
      latchedTag = true;
    }
  }
  // Réarmement quand la main se lève
  if (!weight) {
    latchedTag = false;
  }

  // 3) Debug
  Serial.print("avgPress=");    Serial.print(averagePress);
  Serial.print("  weight=");    Serial.print(weight);
  Serial.print("  latchedTag=");Serial.println(latchedTag);

  // 4) Éteindre tout
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_G, HIGH);
  analogWrite(BUZZER_PIN, 0);

  // 5) Pilotage
  if (weight && latchedTag) {
    digitalWrite(LED_G, LOW);        // verte fixe
  }
  else if (weight) {
    digitalWrite(LED_R, LOW);        // rouge fixe
    analogWrite(BUZZER_PIN, 255);    // buzzer plein PWM
  }

  delay(50);  // ~20 Hz
}
