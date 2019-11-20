#define BETA 3974.0

const double V = 5; //5V
//const int SAMPLE_NUMBER = 10;
const double BALANCE_RESISTOR = 10960.0;
const double MAX_ADC = 1023.0;
//const double BETA 3974.0;
//const double ROOM_TEMP = 298.15;
//const double RESISTOR_ROOM_TEMP = 10000.0;

int Ntc_Pin = 0;
double Raw_Data = 0;
double  Y = (3.70 * pow(10,-7)) * pow(Raw_Data,3) - (5.09 * pow(10,-4)) * pow(Raw_Data,2) + (3.14 * pow(10,-1)) * Raw_Data - (5.50 * 10);
void setup() 
  {
    Serial.begin(9600);
  }

void loop() {

  Raw_Data = analogRead(Ntc_Pin);
 
  /*Raw_Data = Raw_Data+BALANCE_RESISTOR; //rkok/kohm
  Raw_Data = V/Raw_Data;//virta/mA
  Raw_Data = BALANCE_RESISTOR*Raw_Data;//UR:/V
  Raw_Data = Raw_Data/V*MAX_ADC;//AD*/
  
  Y = (3.70 * pow(10,-7)) * pow(Raw_Data,3) - (5.09 * pow(10,-4)) * pow(Raw_Data,2) + (3.14 * pow(10,-1)) * Raw_Data - (5.50 * 10);
  
  //delay(3000);
  Serial.print("Lämpötila: ");
  Serial.println(Y);
}

/*double readThermistor()
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
}*/
