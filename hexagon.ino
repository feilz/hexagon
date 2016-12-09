#include <Adafruit_Neopixel.h>

#define NUMPIXELS 60
#define TRIGPIN 5
#define ECHOPIN 6

Adafruit_NeoPixel vasen1 = Adafruit_NeoPixel(NUMPIXELS, 7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel vasen2 = Adafruit_NeoPixel(NUMPIXELS, 12, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel oikea1 = Adafruit_NeoPixel(NUMPIXELS, 8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel oikea2 = Adafruit_NeoPixel(NUMPIXELS, 11, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel keski1 = Adafruit_NeoPixel(NUMPIXELS, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel keski2 = Adafruit_NeoPixel(NUMPIXELS, 10, NEO_GRB + NEO_KHZ800);
int i=0,m=0;
boolean stacked=false;
int stackcounter=0;
uint32_t ranCo(){
  return vasen1.Color(random(0,200),random(0,200),random(0,200));
}
uint32_t black = vasen1.Color(0,0,0);
uint32_t white = vasen1.Color(255,255,255);
uint32_t magenta = vasen1.Color(255,0,255);
uint32_t purple = vasen1.Color(204,102,153);
uint32_t yellow = vasen1.Color(255,204,0);
uint32_t gray = vasen1.Color(153,153,102);
uint32_t lblue = vasen1.Color(102,153,255);
uint32_t dgreen = vasen1.Color(0,102,0);
uint32_t turq = vasen1.Color(0,255,204);
uint32_t dblue = vasen1.Color(0,0,102);
uint32_t red = vasen1.Color(240,0,0);
uint32_t green = vasen1.Color(0,240,0);
uint32_t blue = vasen1.Color(0,0,240);
uint32_t colors[8]={magenta,purple,yellow,gray,lblue,dgreen,turq,dblue};
uint32_t rgb[3]={red, green,blue};
void setup() {
  // put your setup code here, to run once:
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  vasen1.begin();
  vasen2.begin();
  oikea1.begin();
  oikea2.begin();
  keski1.begin();
  keski2.begin();
  vasen1.setBrightness(120);
  vasen2.setBrightness(120);
  oikea1.setBrightness(120);
  oikea2.setBrightness(120);
  keski2.setBrightness(120);
  keski1.setBrightness(120);
  }
int q=0,dur,dist,l=1;
void loop() {
  // put your main code here, to run repeatedly:
  i++;
  
  downup(ranCo());
  //rave();
  //stack();
  //circleOn();
  //for (int j=0;j<1000;j++) wave();
  //circleOff();
  /*for (int i=0;i<2;i++) circleHalf();
  finishCircleHalf();*/
  for (int i=0;i<4;i++) circleHalfBack();
  finishCircleHalfBack();
  /*for (int i=0;i<2;i++) circle();
  finishCircle();
  for (int i=0;i<2;i++) circleBack();
  finishCircleBack();*/
  //for (int i=0;i<2;i++) circle34();
  //finish34();
  newStack();
  //delay(1000);
  //jotaki();
  if (i>2000){
  i=0;
 }
 if (m>2500){
  m=0;
 }
}

void circleOn(){
  for (int i=0;i<NUMPIXELS;i++){
    lightOn(oikea1,i,Wheel((i+m)%255));
    lightOn(keski2,i/2,Wheel((i+m)%255));
    delay(30);
  }
  for (int i=0;i<NUMPIXELS;i++){
    lightOn(oikea2,i,Wheel((i+m)%255));
    lightOn(keski2,i/2+NUMPIXELS/2,Wheel((i+m)%255));
    delay(30);
  }
  for (int i=NUMPIXELS;i>0;i--){
    lightOn(vasen2,i,Wheel((i+m)%255));
    lightOn(keski1,i/2+NUMPIXELS/2,Wheel((i+m)%255));
    delay(30);
  }
  for (int i=NUMPIXELS;i>0;i--){
    lightOn(vasen1,i,Wheel((i+m)%255));
    lightOn(keski1,i/2,Wheel((i+m)%255));
    delay(30);
  }
}
void circleOff(){
  for (int i=0;i<NUMPIXELS;i++){
    lightOn(oikea1,i,black);
    lightOn(keski2,i/2,black);
    delay(30);
  }
  for (int i=0;i<NUMPIXELS;i++){
    lightOn(oikea2,i,black);
    lightOn(keski2,i/2+NUMPIXELS/2,black);
    delay(30);
  }
  for (int i=NUMPIXELS;i>0;i--){
    lightOn(vasen2,i,black);
    lightOn(keski1,i/2+NUMPIXELS/2,black);
    delay(30);
  }
  for (int i=NUMPIXELS;i>0;i--){
    lightOn(vasen1,i,black);
    lightOn(keski1,i/2,black);
    delay(30);
  }
}

void vas1(){
  for (int i=0; i<NUMPIXELS;i=i+2){
    vasen1.setPixelColor(i,red);
    vasen2.setPixelColor(i,red);
    oikea1.setPixelColor(i,red);
    oikea2.setPixelColor(i,red);
    keski1.setPixelColor(i,red);
    keski2.setPixelColor(i,red);
    vasen1.setPixelColor(i+1,white);
    vasen2.setPixelColor(i+1,white);
    oikea1.setPixelColor(i+1,white);
    oikea2.setPixelColor(i+1,white);
    keski1.setPixelColor(i+1,white);
    keski2.setPixelColor(i+1,white);
  }
  vasen1.show();
  vasen2.show();
  oikea1.show();
  oikea2.show();
  keski1.show();
  keski2.show(); 
}
void vas2(){
  for (int i=0; i<NUMPIXELS;i=i+2){
    vasen1.setPixelColor(i+1,red);
    vasen2.setPixelColor(i+1,red);
    oikea1.setPixelColor(i+1,red);
    oikea2.setPixelColor(i+1,red);
    keski1.setPixelColor(i+1,red);
    keski2.setPixelColor(i+1,red);
    vasen1.setPixelColor(i,white);
    vasen2.setPixelColor(i,white);
    oikea1.setPixelColor(i,white);
    oikea2.setPixelColor(i,white);
    keski1.setPixelColor(i,white);
    keski2.setPixelColor(i,white);
  }
  vasen1.show();
  vasen2.show();
  oikea1.show();
  oikea2.show();
  keski1.show();
  keski2.show(); 
}
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return vasen1.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return vasen1.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return vasen1.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


void newStack(){
  for (int i=0;i<NUMPIXELS;i++){
    lightOn(vasen1,i,white);
    lightOn(vasen2,i,white);
    lightOn(oikea1,NUMPIXELS-i,white);
    lightOn(oikea2,NUMPIXELS-i,white);
    lightOn(keski1,i,white);
    lightOn(keski2,NUMPIXELS-i,white);
    delay(30);
  }
  for (int j=NUMPIXELS;j>=0;j=j-4){
    for (int i=0;i<j;i++){
      lightOn(vasen1,i,red);
      lightOn(vasen2,i,green);
      lightOn(oikea1,NUMPIXELS-i,blue);
      lightOn(oikea2,NUMPIXELS-i,red);
      lightOn(keski1,i,blue);
      lightOn(keski2,NUMPIXELS-i,green);
      lightOn(vasen1,i-4,white);
      lightOn(vasen2,i-4,white);
      lightOn(oikea1,NUMPIXELS-i+4,white);
      lightOn(oikea2,NUMPIXELS-i+4,white);
      lightOn(keski1,i-4,white);
      lightOn(keski2,NUMPIXELS-i+4,white);
      delay(10);
    }
  }
  for (int i=0;i<NUMPIXELS;i++){
    lightOn(vasen1,i,black);
    lightOn(vasen2,i,black);
    lightOn(oikea1,i,black);
    lightOn(oikea2,i,black);
    lightOn(keski1,i,black);
    lightOn(keski2,i,black);
    delay(30);
  }
}


void stack(){
  if(stacked == true){
    stackcounter=(NUMPIXELS);
  for(int i=0;i<(NUMPIXELS);i++){
    vasen1.setPixelColor(i,50,50,50);
    vasen2.setPixelColor(i,50,50,50);
    oikea1.setPixelColor(i,50,50,50);
    oikea2.setPixelColor(i,50,50,50);
    keski1.setPixelColor(i,50,50,50);
    keski2.setPixelColor(i,50,50,50);
  }
    vasen1.show();
    vasen2.show();
    oikea1.show();
    oikea2.show();
    keski1.show();
    keski2.show();
   stacked = false;
  }
    stackcounter=stackcounter-2;
  for(int i=0;i<(stackcounter+1);i++){
    vasen1.setPixelColor(i,150,0,0);
    vasen1.setPixelColor(i+1,150,0,0);
    vasen2.setPixelColor(i,150,0,0);
    vasen2.setPixelColor(i+1,150,0,0);
    oikea1.setPixelColor(i,150,0,0);
    oikea1.setPixelColor(i+1,150,0,0);
    oikea2.setPixelColor(i,150,0,0);
    oikea2.setPixelColor(i+1,150,0,0);
    keski1.setPixelColor(i,150,0,0);
    keski1.setPixelColor(i+1,150,0,0);
    keski2.setPixelColor(i,150,0,0);
    keski2.setPixelColor(i+1,150,0,0);
    
    vasen1.show();
    vasen2.show();
    oikea1.show();
    oikea2.show();
    keski1.show();
    keski2.show();
    int delay2 = NUMPIXELS-stackcounter;
    int delay3 = map(delay2, 0,NUMPIXELS,0,25);
    delay(delay3);
    if (stackcounter==i-2){
      
    }
    else{
      vasen1.setPixelColor(i-1,50,50,50);
      vasen2.setPixelColor(i-1,50,50,50);
      oikea1.setPixelColor(i-1,50,50,50);
      oikea2.setPixelColor(i-1,50,50,50);
      keski1.setPixelColor(i-1,50,50,50);
      keski2.setPixelColor(i-1,50,50,50);
    }
  }
  if (i==NUMPIXELS-1){
    stacked=true;
  }
delay(10);
}

void wave(){

    for (int q=0; q < 3; q++) {
      for (uint16_t j=0; j < vasen1.numPixels(); j=j+3) {
        
        vasen1.setPixelColor(j+q, Wheel( (j+i) % 255)); 
        vasen2.setPixelColor(j+q, Wheel( (j+i) % 255)); 
        oikea1.setPixelColor(j+q, Wheel( (j+i) % 255)); 
        oikea2.setPixelColor(j+q, Wheel( (j+i) % 255)); 
        keski1.setPixelColor(j+q, Wheel( (j+i) % 255)); 
        keski2.setPixelColor(j+q, Wheel( (j+i) % 255)); 
        }      
      }
  vasen1.show();
  vasen2.show();
  oikea1.show();
  oikea2.show();
  keski1.show();
  keski2.show();
  delay(25);        
}

void jotaki() {
 
  for(int i=0, j=(NUMPIXELS);i<(NUMPIXELS/2) && j>=(NUMPIXELS/2);i++, j--){
    vasen1.setPixelColor(i, (i),(0),(j/i)*10); 
    vasen1.show();
    vasen1.setPixelColor(j, (i),(0),(j/i*10)); 
    vasen1.show();
    vasen2.setPixelColor(i, (i),(0),(j/i)*10); 
    vasen2.show();
    vasen2.setPixelColor(j, (i),(0),(j/i*10)); 
    vasen2.show();
    oikea1.setPixelColor(i, (i),(0),(j/i)*10); 
    oikea1.show();
    oikea1.setPixelColor(j, (i),(0),(j/i*10)); 
    oikea1.show();
    oikea2.setPixelColor(i, (i),(0),(j/i)*10); 
    oikea2.show();
    oikea2.setPixelColor(j, (i),(0),(j/i*10)); 
    oikea2.show();
    keski1.setPixelColor(i, (i),(0),(j/i)*10); 
    keski1.show();
    keski1.setPixelColor(j, (i),(0),(j/i*10)); 
    keski1.show();
    keski2.setPixelColor(i, (i),(0),(j/i)*10); 
    keski2.show();
    keski2.setPixelColor(j, (i),(0),(j/i*10)); 
    keski2.show();
        
    
    delay(30);
  }
    
  for(int i=0, j=(NUMPIXELS);i<(NUMPIXELS) && j>-1;i++, j--){
    vasen1.setPixelColor(i, black); 
    vasen1.show();
    vasen1.setPixelColor(j, black); 
    vasen1.show();
    vasen2.setPixelColor(i, black); 
    vasen2.show();
    vasen2.setPixelColor(j, black); 
    vasen2.show();
    oikea1.setPixelColor(i, black); 
    oikea1.show();
    oikea1.setPixelColor(j,black); 
    oikea1.show();
    oikea2.setPixelColor(i,black); 
    oikea2.show();
    oikea2.setPixelColor(j,black); 
    oikea2.show();
    keski1.setPixelColor(i,black); 
    keski1.show();
    keski1.setPixelColor(j,black); 
    keski1.show();
    keski2.setPixelColor(i, black); 
    keski2.show();
    keski2.setPixelColor(j,black); 
    keski2.show();
    delay(30);
 }
 }

void downup(uint32_t color){
  for (int i=NUMPIXELS, j=0;i>0,j<NUMPIXELS;i--,j++){
        vasen2.setPixelColor(i, color); 
        oikea2.setPixelColor(i, color); 
        keski1.setPixelColor(i+(j/2), color); 
        keski2.setPixelColor(i+(j/2), color); 
        
        vasen2.show();         
        oikea2.show();
        keski1.show();
        keski2.show();
        delay(10); 
  }
  for (int i=NUMPIXELS,j=0;i>0,j<NUMPIXELS;i--,j++){
        vasen1.setPixelColor(i, color); 
        oikea1.setPixelColor(i, color); 
        keski1.setPixelColor((i/2), color); 
        keski2.setPixelColor((i/2), color); 
        
        vasen1.show();         
        oikea1.show();
        keski1.show();
        keski2.show();
        delay(10);    
  }
  delay(500);
  for (int i=0,j=NUMPIXELS;i<NUMPIXELS,j>0;i++,j--){
        vasen1.setPixelColor(i, black); 
        oikea1.setPixelColor(i, black); 
        keski1.setPixelColor((i/2), black); 
        keski2.setPixelColor((i/2), black); 
        
        vasen1.show();         
        oikea1.show();
        keski1.show();
        keski2.show();
        delay(10);    
  }
  for (int i=0, j=NUMPIXELS;i<NUMPIXELS,j>0;i++,j--){
        vasen2.setPixelColor(i, black); 
        oikea2.setPixelColor(i,black); 
        keski1.setPixelColor(i+(j/2),black); 
        keski2.setPixelColor(i+(j/2),black); 
        
        vasen2.show();         
        oikea2.show();
        keski1.show();
        keski2.show();
        delay(10); 
  }
}
void allBlack(){
  for (int i=0;i<NUMPIXELS;i++){
    vasen1.setPixelColor(i,black);
    vasen2.setPixelColor(i,black);
    oikea2.setPixelColor(i,black);
    oikea1.setPixelColor(i,black);
    keski1.setPixelColor(i,black);
    keski2.setPixelColor(i,black);
  }
  vasen2.show();         
  oikea2.show();
  keski1.show();
  keski2.show();
  vasen1.show();
  oikea1.show();      
}
int amount;
void varahtely(int j){
  amount=120-j*l;
  vasen1.setBrightness(max(min(255,amount),0));
  vasen2.setBrightness(max(min(255,amount),0));
  oikea1.setBrightness(max(min(255,amount),0));
  oikea2.setBrightness(max(min(255,amount),0));
  keski1.setBrightness(max(min(255,amount),0));
  keski2.setBrightness(max(min(255,amount),0));
  vasen1.show();
  vasen2.show();      
  oikea1.show();   
  oikea2.show();
  keski1.show();
  keski2.show();
  delay(10);
  l=l*-1;
}
void rave(){
  for (int i=0;i<NUMPIXELS;i++){
    vasen1.setPixelColor(i,white);
    vasen2.setPixelColor(i,white);
    oikea1.setPixelColor(i,white);
    oikea2.setPixelColor(i,white);
    keski1.setPixelColor(i,white);
    keski2.setPixelColor(i,white);
  }
  vasen1.show();
  vasen2.show();      
  oikea1.show();   
  oikea2.show();
  keski1.show();
  keski2.show();
  delay(random(5,150));
  
  for (int i=0;i<NUMPIXELS;i++){
    vasen1.setPixelColor(i,black);
    vasen2.setPixelColor(i,black);
    oikea1.setPixelColor(i,black);
    oikea2.setPixelColor(i,black);
    keski1.setPixelColor(i,black);
    keski2.setPixelColor(i,black);
  }
  vasen1.show();
  vasen2.show();      
  oikea1.show();   
  oikea2.show();
  keski1.show();
  keski2.show();
  delay(random(5,150));
  }
void circle(){
    for (uint16_t j=0,k=NUMPIXELS; j < NUMPIXELS,k>0; j++,k--) {
      lightOn(oikea1,j,Wheel((j+m)%255));
      lightOn(keski2,j/2,Wheel((j+m)%255));
      lightOn(vasen1,k,black);
      lightOn(keski1,k/2,black);
      delay(10);         
    }
    m=m+NUMPIXELS;
    for (uint16_t j=NUMPIXELS,k=0; j >0,k<NUMPIXELS; j--,k++) {
      lightOn(oikea2,k,Wheel((j+m)%255));
      lightOn(oikea1,k,black);
      lightOn(keski2,k/2+NUMPIXELS/2,Wheel((j+m)%255));
      lightOn(keski2,k/2,black);
      delay(10);         
    }
    m=m+NUMPIXELS;      
    for (uint16_t j=0,k=NUMPIXELS; j < NUMPIXELS,k>0; j++,k--) {
      lightOn(vasen2,k,Wheel((j+m)%255));
      lightOn(oikea2,j,black);
      lightOn(keski1,NUMPIXELS-j/2,Wheel((j+m)%255));
      lightOn(keski2,j/2+NUMPIXELS/2,black);
      delay(10);         
    }
    
    m=m+NUMPIXELS;
    for (uint16_t j=NUMPIXELS,k=0; j >0,k<NUMPIXELS; j--,k++) {
      lightOn(vasen1,j,Wheel((j+m)%255));
      lightOn(vasen2,j,black);
      lightOn(keski1,j/2,Wheel((j+m)%255));
      lightOn(keski1,NUMPIXELS-(k/2),black);
      delay(10);         
    }    
    keski2.setPixelColor(31,black);
    m=m+NUMPIXELS;
 
}
void circleBack(){
  for (uint16_t j=0,k=NUMPIXELS; j < NUMPIXELS,k>0; j++,k--) {
    lightOn(vasen1,j,Wheel((j+m)%255));
    lightOn(keski1,j/2,Wheel((j+m)%255));
    lightOn(oikea1,k,black);
    lightOn(keski2,k/2,black);
    delay(10);         
    }
    m=m+NUMPIXELS;      
    for (uint16_t j=0; j < NUMPIXELS; j++) {
      lightOn(vasen2,j,Wheel((j+m)%255));
      lightOn(vasen1,j,black);
      lightOn(keski1,j/2+NUMPIXELS/2,Wheel((j+m)%255));
      lightOn(keski1,j/2,black);
      delay(10);         
    }
    m=m+NUMPIXELS;
    for (uint16_t j=NUMPIXELS,k=0; j >0,k<NUMPIXELS; j--,k++) {
      lightOn(oikea2,j,Wheel((j+m)%255));
      lightOn(vasen2,k,black);
      lightOn(keski2,NUMPIXELS-(k/2),Wheel((j+m)%255));
      lightOn(keski1,k/2+NUMPIXELS/2,black);
      delay(10);         
    }
    m=m+NUMPIXELS;
    for (uint16_t j=NUMPIXELS,k=0; j >0,k<NUMPIXELS; j--,k++) {
      lightOn(oikea1,j,Wheel((j+m)%255));
      lightOn(oikea2,j,black);
      lightOn(keski2,j/2,Wheel((j+m)%255));
      lightOn(keski2,j/2+NUMPIXELS/2,black);
      delay(10);         
    }    
    keski2.setPixelColor(31,0,0,0);
    m=m+NUMPIXELS;
 
}
void circleHalf(){
    for (uint16_t j=0,k=NUMPIXELS; j < NUMPIXELS,k>0; j++,k--) {
      lightOn(oikea1,j,Wheel((j+m)%255));
      lightOn(keski2,j/2,Wheel((j+m)%255));
      lightOn(vasen2,k,black);
      lightOn(keski1,k/2+NUMPIXELS/2,black);
      delay(10);         
    }
    m=m+NUMPIXELS;
    for (uint16_t j=NUMPIXELS,k=0; j >0,k<NUMPIXELS; j--,k++) {
      lightOn(oikea2,k,Wheel((j+m)%255));
      lightOn(vasen1,j,black);
      lightOn(keski2,k/2+NUMPIXELS/2,Wheel((j+m)%255));
      lightOn(keski1,j/2,black);
      delay(10);         
    }
    m=m+NUMPIXELS;      
    for (uint16_t j=0,k=NUMPIXELS; j < NUMPIXELS,k>0; j++,k--) {
      lightOn(vasen2,k,Wheel((j+m)%255));
      lightOn(oikea1,j,black);
      lightOn(keski1,(NUMPIXELS-(j/2)),Wheel((j+m)%255));
      lightOn(keski2,j/2,black);
      delay(10);         
    }
    
    m=m+NUMPIXELS;
    for (uint16_t j=NUMPIXELS,k=0; j >0,k<NUMPIXELS; j--,k++) {
      lightOn(vasen1,j,Wheel((j+m)%255));
      lightOn(oikea2,k,black);
      lightOn(keski1,j/2,Wheel((j+m)%255));
      lightOn(keski2,(k/2)+(NUMPIXELS/2),black);
      delay(10);         
    }    
    keski2.setPixelColor(31,black);
    m=m+NUMPIXELS;
 
}
void circleHalfBack(){
  for (uint16_t j=0,k=NUMPIXELS; j < NUMPIXELS,k>0; j++,k--) {
      lightOn(vasen1,j,Wheel((j+m)%255));
      lightOn(keski1,j/2,Wheel((j+m)%255));
      lightOn(oikea2,k,black);
      lightOn(keski2,k/2+NUMPIXELS/2,black);
      delay(10);         
    }
    m=m+NUMPIXELS;      
    for (uint16_t j=0,k=NUMPIXELS;k>=0, j < NUMPIXELS; j++,k--) {
      lightOn(vasen2,j,Wheel((j+m)%255));
      lightOn(oikea1,k,black);
      lightOn(keski1,(j/2)+32,Wheel((j+m)%255));
      lightOn(keski2,k/2,black);
      delay(10);         
    }
    m=m+NUMPIXELS;
    for (uint16_t j=NUMPIXELS,k=0; j >0,k<NUMPIXELS; j--,k++) {
      lightOn(oikea2,j,Wheel((j+m)%255));
      lightOn(vasen1,k,black); 
      lightOn(keski2,(NUMPIXELS-(k/2)),Wheel((j+m)%255));
      lightOn(keski1,k/2,black);
      delay(10);         
    }
    m=m+NUMPIXELS;
    for (uint16_t j=NUMPIXELS,k=0; j >0,k<NUMPIXELS; j--,k++) {
      lightOn(oikea1,j,Wheel((j+m)%255));
      lightOn(vasen2,k,black); 
      lightOn(keski2,j/2,Wheel((j+m)%255));
      lightOn(keski1,k/2+NUMPIXELS/2,black);
      delay(10);         
    }    
    keski2.setPixelColor(31,0,0,0);
    m=m+NUMPIXELS;
 
}
void circle34(){
  for (uint16_t j=0,k=NUMPIXELS; j < NUMPIXELS,k>0; j++,k--) {
      lightOn(oikea1,j,Wheel((j+m)%255));
      lightOn(keski2,j/2,Wheel((j+m)%255));
      lightOn(oikea2,j,black);
      lightOn(keski2,j/2+NUMPIXELS/2,black);
      delay(10);         
    }
  m=m+NUMPIXELS;
  for (uint16_t j=NUMPIXELS,k=0; j >0,k<NUMPIXELS; j--,k++) {
    lightOn(oikea2,k,Wheel((j+m)%255));
    lightOn(keski2,k/2+NUMPIXELS/2,Wheel((j+m)%255));
    lightOn(vasen2,j,black);
    lightOn(keski1,NUMPIXELS-k/2,black);
    delay(10);         
  }
  m=m+NUMPIXELS;      
  for (uint16_t j=0,k=NUMPIXELS; j < NUMPIXELS,k>0; j++,k--) {
    lightOn(vasen2,k,Wheel((j+m)%255));
    lightOn(vasen1,k,black);
    lightOn(keski1,(NUMPIXELS-(j/2)),Wheel((j+m)%255));
    lightOn(keski1,k/2,black);
    delay(10);         
  }
  
  m=m+NUMPIXELS;
  for (uint16_t j=NUMPIXELS,k=0; j >0,k<NUMPIXELS; j--,k++) {
    lightOn(vasen1,j,Wheel((j+m)%255));
    lightOn(oikea1,k,black);
    lightOn(keski1,j/2,Wheel((j+m)%255));
    lightOn(keski2,(k/2),black);
    delay(10);         
  }    
    keski2.setPixelColor(31,black);
    m=m+NUMPIXELS;
}

void finishCircle(){
  for (int k=NUMPIXELS;k>=0;k--){
    lightOn(vasen1,k,black);
    lightOn(keski1,k/2,black);
    delay(10);
  }
}
void finishCircleBack(){
  for (int k=NUMPIXELS;k>=0;k--){
    lightOn(oikea1,k,black);
    lightOn(keski2,k/2,black);
    delay(10);
  }
}
void finishCircleHalf(){
  for (int k=NUMPIXELS;k>0;k--){
    lightOn(vasen2,k,black);
    lightOn(keski1,k/2+NUMPIXELS/2,black);
    delay(10);
  }
  finishCircle();
}
void finishCircleHalfBack(){
  for (int k=NUMPIXELS;k>0;k--){
    lightOn(oikea2,k,black);
    lightOn(keski2,k/2+NUMPIXELS/2,black);
    delay(10);
  }
  finishCircleBack();
}
void finish34(){
  for (int j=0;j<NUMPIXELS;j++){
    lightOn(oikea2,j,black);
    lightOn(keski2,j/2+NUMPIXELS/2,black);
    delay(10);
  }
  finishCircleHalf();
}

void lightOn(Adafruit_NeoPixel &strip,int led,uint32_t color){
  strip.setPixelColor(led,color);
  strip.show();
}

void lightsOn(Adafruit_NeoPixel &strip,int led,int howmany,uint32_t color){
  if (howmany<0){
    for (int i=0;i<howmany*-1;i++){
      strip.setPixelColor(led-i,color);
    } 
  }else {
    for (int i=0;i<howmany;i++){
      strip.setPixelColor(led+i,color);
    }
  }
  
  strip.show();
}
