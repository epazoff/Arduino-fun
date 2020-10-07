int a=0;
int c=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(5,OUTPUT);
  Serial.begin(9600);
  analogReference(DEFAULT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  a=analogRead(0);
  c=map(a,0,1023,0,255);
  Serial.print(a);
  Serial.print("\t");
  Serial.println(c);
  analogWrite(5,c);
  delay(10);

}
