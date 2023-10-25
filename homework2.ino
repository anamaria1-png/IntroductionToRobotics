const int redPin=9;
const int greenPin=10;
const int bluePin=11;

const int potentionmeterRedPin=A0;
const int potentionmeterGreenPin=A1;
const int potentionmeterBluePin=A2;

const int analoglimit=1023;
const int pwmlimit=255;

void setup(){
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop(){
  int redValue=map(analogRead(potentionmeterRedPin),0,analoglimit,0,pwmlimit);
  int greenValue=map(analogRead(potentionmeterGreenPin),0,analoglimit,0,pwmlimit);
  int blueValue=map(analogRead(potentionmeterBluePin),0,analoglimit,0,pwmlimit);

  analogWrite(redPin,redValue);
  analogWrite(greenPin,greenValue);
  analogWrite(bluePin,blueValue);
}