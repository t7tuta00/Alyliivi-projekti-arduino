const int Ntc_Pin = A0;
const int zpin = A1;
const int xpin = A2;
const int ypin = A3;
const int led = 4;
double Raw_Data = 0;
double  Ntc_Data = (3.70 * pow(10,-7)) * pow(Raw_Data,3) - (5.09 * pow(10,-4)) * pow(Raw_Data,2) + (3.14 * pow(10,-1)) * Raw_Data - (5.50 * 10);

float xData, yData, zData; //kalibroidut x,y,z arvot
float axisData; //x,y,z arvojen vektorin itseisarvo

float xOri, yOri, zOri; //x- ja y-akselin kierto

unsigned long time = 0; //ajastin
int state = 0; //eri tasot varmistaakseen kaatumisen

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int x = analogRead(xpin);
  int y = analogRead(ypin);
  int z = analogRead(zpin);
  digitalWrite(led,LOW);
  
  Raw_Data = analogRead(Ntc_Pin);
  Ntc_Data = (3.70 * pow(10,-7)) * pow(Raw_Data,3) - (5.09 * pow(10,-4)) * pow(Raw_Data,2) + (3.14 * pow(10,-1)) * Raw_Data - (5.50 * 10);
  
  //float zero_G = 512.0; //zero g output equal to Vs/2 = 1024/2
  //float scale = 102.4; //sensitivity 330mv/g, 330 * 1024/3.3/1000
  //Näitä voitaisiin käyttää kalibroimiseen

  //kalibrointi
  xData = (((float)x-340.3)/67);
  yData = (((float)y-337.2)/65);
  zData = (((float)z-340)/68);
  
  //x ja y akselin kulmat radiaaneina
  xOri = atan(xData/sqrt(pow(yData,2))+(pow(zData,2)));
  yOri = atan(yData/sqrt(pow(xData,2))+(pow(zData,2)));
  zOri = atan(zData/sqrt(pow(xData,2))+(pow(yData,2)));

  //x ja y akselin kulmat asteiksi
  xOri = xOri * (180/PI);
  yOri = yOri * (180/PI);
  zOri = zOri * (180/PI);

  //itseisarvo x+y+z
  axisData = sqrt((xData*xData)+(yData*yData)+(zData*zData));
  
  fallDetection();
  
  Serial.print("Lämpötila: ");
  Serial.println(Ntc_Data);
  //Serial.print(xData);
  //Serial.print("\t");
  //Serial.print(yData);
  //Serial.print("\t");
  //Serial.print(zData);
  //Serial.print("\t");
  //Serial.print(abs(xOri));
  //Serial.print("\t");
  //Serial.print(abs(yOri));
  //Serial.print("\t");
  //Serial.print(abs(zOri));
  //Serial.print("\t");
  Serial.print(axisData);
  Serial.print("\n");
  
  delay(50);
}

void fallDetection()
{
  if(axisData<0.5 && state == 0){
    state = 1;
    digitalWrite(led,LOW);
    time = millis();
  }

  if(state == 1){
    if(axisData>2.5){
      if(abs(yOri>60) || abs(zOri>60)){
        state = 2;
        digitalWrite(led,LOW);
      }
      if((millis()-time)>2000){
        state = 0;
      }
    }
    if((millis()-time)>2000){
      state = 0;
    }
  }
  if(state == 2){
    digitalWrite(led,HIGH);
  }
}
