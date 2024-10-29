#define ANALOG_INPUT_PIN 36
#define SAMPLING_FREQUENCY 5000
#define LED_PIN LED_BUILTIN
#define BUFFER_LENGTH 1024

hw_timer_t *timer = NULL;
volatile unsigned int analogReadBuffer[BUFFER_LENGTH]; //[BUFFER_LENGTH];
volatile bool fullBufferFlag = false;


void ARDUINO_ISR_ATTR onTimer() {

    if (fullBufferFlag) return; 

    static unsigned int bufferIndex = 0;
    analogReadBuffer[bufferIndex] = analogRead(ANALOG_INPUT_PIN);

    if (++bufferIndex >= BUFFER_LENGTH) {
        bufferIndex = 0; 
        fullBufferFlag = true;
    }
}

// ================================================================
void setup() {
  Serial.begin(115200);
  Serial.println("Initializiny me progreme");
  Serial.println(__DATE__);
  
  //pinMode(LED_PIN, OUTPUT);
  
  timer = timerBegin(1000000);
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, (1000000/SAMPLING_FREQUENCY), true, 0);
}

void loop() {

  if (fullBufferFlag) { 
    Serial.println("Buffer full:");
    float AVG = calculateAverage(analogReadBuffer);
    //for (int i = 0; i < BUFFER_LENGTH; i++) {Serial.println(analogReadBuffer[i]);}
    Serial.println(AVG);
    fullBufferFlag = false;
    }
  }
//=================================================================  

float calculateAverage(volatile unsigned int arr[]) {
  int sum = 0;

  for (int i = 0; i < BUFFER_LENGTH; i++) {
    sum += arr[i];
  }

  return static_cast<float>(sum) / BUFFER_LENGTH;
}



