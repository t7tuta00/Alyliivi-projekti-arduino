#define BETA 3974.0

const int SAMPLE_NUMBER = 10;
const double BALANCE_RESISTOR = 10960.0;  //10960
const double MAX_ADC = 1023.0;
//const double BETA 3974.0;
const double ROOM_TEMP = 298.15;
const double RESISTOR_ROOM_TEMP = 10000.0;

double currentTemperature = 0;

//Input:
int thermistorPin = 0;


void setup() {

  Serial.begin(9600);

}

void loop() {

  currentTemperature = readThermistor();
  delay(3000);

  Serial.print("Lämpötila: ");
  Serial.println(currentTemperature);

}

double readThermistor()
{
  double rThermistor = 0;
  double tKelvin     = 0;
  double tCelsius    = 0;
  double adcAverage  = 0;
  int    adcSamples[SAMPLE_NUMBER];

  for (int i = 0; i < SAMPLE_NUMBER; i++) 
  {
    adcSamples[i] = analogRead(thermistorPin);
    delay(10);
  }

  for (int i = 0; i < SAMPLE_NUMBER; i++) 
  {
    adcAverage += adcSamples[i];
  }
  adcAverage /= SAMPLE_NUMBER;

  rThermistor = BALANCE_RESISTOR * ( (MAX_ADC / adcAverage) - 1);

  tKelvin = (BETA * ROOM_TEMP) / 
            (BETA + (ROOM_TEMP * log(rThermistor / RESISTOR_ROOM_TEMP)));

  tCelsius = tKelvin - 273.15;
  return tCelsius;
}
