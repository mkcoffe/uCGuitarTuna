#define AUDIO_IN_PIN 36
#define BUFFER_SIZE 1024
#define ITERATIONS  100

volatile unsigned int adc_buffer[BUFFER_SIZE];
unsigned long totalTime = 0;
float averageFrequency = 0;
float frequencies[ITERATIONS]; // Array to store the frequencies

void setup() {
  Serial.begin(115200);

  Serial.println("");
  Serial.println("ESP32 sampling speed testing program");
  Serial.print("Program calculates average frequency of measuring samples from AnalogRead() at pin: ");
  Serial.println(AUDIO_IN_PIN);
  Serial.print("It fills up the buffer of length: ");
  Serial.print(BUFFER_SIZE);
  Serial.print(" over ");
  Serial.print(ITERATIONS);
  Serial.println(" iterations.");
  Serial.println(__DATE__);
  Serial.println(__TIME__);
  Serial.println("");
}

void loop() {  

  for (int iteration = 0; iteration < ITERATIONS; iteration++) {
    unsigned long newTime = micros();

    for (int i = 0; i < BUFFER_SIZE; i++) {
      adc_buffer[i] = analogRead(AUDIO_IN_PIN);
    }

    unsigned long fillTime = micros() - newTime; 
    totalTime += fillTime;

    frequencies[iteration] = (float)(BUFFER_SIZE) / (fillTime / 1000000.0); // Frequency in Hz
  }

  averageFrequency = (float)(ITERATIONS * BUFFER_SIZE) / (totalTime / 1000000.0);
  Serial.print("Average frequency over ");
  Serial.print(ITERATIONS);
  Serial.print(" iterations: ");
  Serial.print(averageFrequency);
  Serial.println(" Hz");

  // Calculate standard deviation of frequencies
  float meanFrequency = 0;
  for (int i = 0; i < ITERATIONS; i++) {
    meanFrequency += frequencies[i];
  }
  meanFrequency /= ITERATIONS;

  float variance = 0;
  for (int i = 0; i < ITERATIONS; i++) {
    variance += pow(frequencies[i] - meanFrequency, 2);
  }
  variance /= ITERATIONS;
  float standardDeviation = sqrt(variance);

  Serial.print("Standard Deviation of frequencies: ");
  Serial.print(standardDeviation);
  Serial.println(" Hz");

  Serial.println("");

  while(true);
}



