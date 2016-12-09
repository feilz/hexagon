#include <Adafruit_NeoPixel.h>

//Naming principle: Stripname+"n" (Number of Pixels).

#define mid1n 60 
#define mid2n 57
#define leftn 71
#define rightn 68
#define botn 73



Adafruit_NeoPixel bot = Adafruit_NeoPixel(botn, 8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel left = Adafruit_NeoPixel(leftn, 11, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel right = Adafruit_NeoPixel(rightn, 10, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel mid1 = Adafruit_NeoPixel(mid1n, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel mid2 = Adafruit_NeoPixel(mid2n, 12, NEO_GRB + NEO_KHZ800);

//pointers to pass around these strings between functions.
Adafruit_NeoPixel *botp = &bot;
Adafruit_NeoPixel *rightp = &right;
Adafruit_NeoPixel *leftp = &left;
Adafruit_NeoPixel *mid1p = &mid1;
Adafruit_NeoPixel *mid2p = &mid2;

//Naming principle: Where it's located on the hexagon, when at it from the arduino side.


//Helping variables, to control rainbow colors.
int i=0,m=0;


//A couple of premade colors, for easier use later.
uint32_t ranCo(){
  return left.Color(random(0,200),random(0,200),random(0,200));
}
uint32_t black = left.Color(0,0,0);
uint32_t white = left.Color(255,255,255);
uint32_t magenta = left.Color(255,0,255);
uint32_t purple = left.Color(204,102,153);
uint32_t yellow = left.Color(255,204,0);
uint32_t gray = left.Color(153,153,102);
uint32_t lblue = left.Color(102,153,255);
uint32_t dgreen = left.Color(0,102,0);
uint32_t turq = left.Color(0,255,204);
uint32_t dblue = left.Color(0,0,102);
uint32_t red = left.Color(240,0,0);
uint32_t green = left.Color(0,240,0);
uint32_t blue = left.Color(0,0,240);
uint32_t rgb[3]={red, green,blue};


//a new addition, using linked lists to make iterating through the strips easier. Some error still exists.
namespace Node{
  struct Pixel {
  Adafruit_NeoPixel *strip;
  int location;
  Pixel *next;
  Pixel *prev;
  };
  
  bool isEmpty(Pixel *head){
    if (head==NULL)return true;
    return false;
  }
  void insertFirst(Pixel *&head,Pixel *&tail, Adafruit_NeoPixel *&band, int loc){
    Pixel *temp = new Pixel;
    temp->strip = band; 
    temp->location = loc;
    temp->next = tail;
    temp->prev = head;
    head=temp;
    tail=temp;
  }
  void appendPixel(Pixel *&head,Pixel *&tail, Adafruit_NeoPixel *&band, int loc){
    if (isEmpty(head)) insertFirst(head,tail,band,loc);
    else {
      Pixel *temp = new Pixel;
      temp->strip = band;
      temp->location = loc;
      temp->next=head;
      temp->prev=tail;
      tail->next=temp;
      head->prev=temp;
      tail=temp;
    }
  }  
  Pixel findPixel(Pixel *&head, int locToFind){
    Pixel *temp = new Pixel;
    temp=head;
    int x=0;
    while (x<locToFind){
      temp=temp->next;
      x+=1;
    }
    return *temp;
  }
}
//Helper head and tail nodes.
Node::Pixel *headOuter=NULL;
Node::Pixel *tailOuter = NULL;
Node::Pixel *headInner =NULL;
Node::Pixel *tailInner=NULL;

void setup() {
  // Initialize all lights, and set their brightness to ~ half of normal. 
  //Half of normal due to power consumption.
  left.begin();
  right.begin();
  bot.begin();
  mid1.begin();
  mid2.begin();
  left.setBrightness(120);
  right.setBrightness(120);
  bot.setBrightness(120);
  mid2.setBrightness(120);
  mid1.setBrightness(120);
  //adding all pixels into the linked list. Used in the circle function
  for (int i = 0;i<leftn;i++){
    Node::appendPixel(headOuter,tailOuter,leftp,i);
  }
  for (int i = botn;i>=0;i--){
    Node::appendPixel(headOuter,tailOuter,botp,i);
  }
  for (int i = rightn;i>=0;i--){
    Node::appendPixel(headOuter,tailOuter,rightp,i);
  }
  for (int i=0;i<mid1n;i++){
    Node::appendPixel(headInner,tailInner,mid1p,i);
  }
  for (int i=mid2n;i>=0;i--){
    Node::appendPixel(headInner,tailInner,mid2p,i);
  }
}

void loop() {
  //the variable 'i' here controls the Rainbow colors in a couple of functions.
  i++;
  redWhite(); //every second white, every second red light.
  
  downup(ranCo()); //up and down on the hexagon.
  slowLights(); // slowly light up in one color.
  //rave(); //care for your eyes though.
  Stack(); //stacks another color on top of the white.
  sumfin(); //a blueish color from both ends, meeting in the middle 

  //circle();  //The light runs around the circle using a linked list. Doesn't work atm. I will try to fix asap.
  
  //reset the counter
  if (i>2000){
  i=0;
 }
 //another controlling variable, to help with the rainbow.
 if (m>2500){
  m=0;
 }
}

//The function that creates the rainbow colors.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return left.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return left.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return left.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


//Functions that makes turning lights on and off less tedious.
void lightOn(Adafruit_NeoPixel &strip,int led,uint32_t color){
  strip.setPixelColor(led,color);
  strip.show();
}

void lightsOn(Adafruit_NeoPixel &strip,int led,int howmany,uint32_t color){
  if (howmany<0){
    for (int i=0;i<howmany-1;i++){
      strip.setPixelColor(led-i,color);
    } 
  }else {
    for (int i=0;i<howmany;i++){
      strip.setPixelColor(led+i,color);
    }
  }
  
  strip.show();
}

int * leds = new int [botn];
void slowLights(){
  
  for (int i=0;i<botn;i++){
    leds[i]=0;
  }
  for (int i=1;i<=botn;i++){
    for (int j=0;j<=i;j++){     
      if (leds[j]<=200) leds[j]+=4;
      //Serial.println(leds[8],leds[15]);  
    }
    for (int i=0;i<botn;i++){
      right.setPixelColor(i,(leds[i],0,0));
      left.setPixelColor(leftn-i,(leds[i],0,0));
      bot.setPixelColor(i,(leds[i],0,0));
      mid2.setPixelColor(i,(leds[i],0,0));
      lightOn(*mid1p,mid1n-i,(leds[i],0,0));
      
    }
    right.show();
    left.show();
    bot.show();
    mid1.show();
    mid2.show();
    delay(50);
  }
  while (leds[botn-1]<150){
    for (int i=0;i<botn;i++){
      if (leds[i]<=220) leds[i]+=1;
      
    }
    for (int i=0;i<botn;i++){
      right.setPixelColor(i,leds[i],0,0);
      left.setPixelColor(leftn-i,leds[i],0,0);
      bot.setPixelColor(i,leds[i],0,0);
      mid2.setPixelColor(i,leds[i],0,0);
      mid1.setPixelColor(mid1n-i,leds[i],0,0);
      }
    right.show();
    left.show();
    bot.show();
    mid1.show();
    mid2.show();
    delay(50);
  }
}


void redWhite(){
  for (int i=0; i<botn;i=i+2){
    lightOn(left,i,red);
    lightOn(right,i,red);
    lightOn(bot,i,red);
    lightOn(mid2,i,red);
    lightOn(mid1,i,red);
    lightOn(left,i+1,white);
    lightOn(right,i+1,white);
    lightOn(bot,i+1,white);
    lightOn(mid2,i+1,white);
    lightOn(mid1,i+1,white);    
  }
  delay(1000);
}


void Stack(){
  for (int i=0;i<botn;i++){
    lightOn(left,i,white);
    lightOn(right,rightn-i,white);
    lightOn(bot,botn-i,white);
    lightOn(mid1,i,white);
    lightOn(mid2,mid2n-i,white);
    delay(30);
  }
  for (int j=botn;j>=0;j=j-4){
    for (int i=0;i<j;i++){
      lightOn(left,i,red);
      lightOn(right,rightn-i,yellow);
      lightOn(bot,botn-i,turq);
      lightOn(mid1,i,blue);
      lightOn(mid2,mid2n-i,green);
      lightOn(left,i-4,white);
      lightOn(right,rightn-i+4,white);
      lightOn(bot,botn-i+4,white);
      lightOn(mid1,i-4,white);
      lightOn(mid2,mid2n-i+4,white);
      delay(10);
    }
  }
  for (int i=0;i<botn;i++){
    lightOn(left,i,black);
    lightOn(right,rightn-i,black);
    lightOn(bot,botn-i,black);
    lightOn(mid1,i,black);
    lightOn(mid2,mid2n-i,black);
    delay(30);
  }
}

void wave(){
  for (int q=0;q<3;q++){
    for (int j=0;j<leftn;j+=3){
      lightOn(left,j+q,Wheel((j+m)%255));
      lightOn(right,j+q,Wheel((j+m)%255));
      lightOn(bot,j+q,Wheel((j+m)%255));
      lightOn(mid1,j+q,Wheel((j+m)%255));
      lightOn(mid2,j+q,Wheel((j+m)%255));
    }
  }
  delay(25);
}

void sumfin(){
   for (int i=0,j=botn;i<botn/2,j>botn/2;i++,j--){
    lightOn(left,i,(i,j,(j/i)*10));
    lightOn(left,j,(i,j,(j/i)*10));
    lightOn(bot,i,(i,j,(j/i)*10));
    lightOn(bot,j,(i,j,(j/i)*10));
    lightOn(right,i,(i,j,(j/i)*10));
    lightOn(right,j,(i,j,(j/i)*10));
    lightOn(mid1,i,(i,j,(j/i)*10));
    lightOn(mid1,j,(i,j,(j/i)*10));
    lightOn(mid2,i,(i,j,(j/i)*10));
    lightOn(mid2,j,(i,j,(j/i)*10));
    delay(50);
   }
  for (int i=0,j=botn;i<botn/2,j>botn/2;i++,j--){
    lightOn(left,i,black);
    lightOn(left,j,black);
    lightOn(bot,i,black);
    lightOn(bot,j,black);
    lightOn(right,i,black);
    lightOn(right,j,black);
    lightOn(mid1,i,black);
    lightOn(mid1,j,black);
    lightOn(mid2,i,black);
    lightOn(mid2,j,black);
    delay(50);
   }
   
}

void downup(uint32_t color){
  for (int i=botn/2, j=botn/2; i>=0,j<=botn;i--,j++){
    lightOn(bot,i,color);
    lightOn(bot,j,color);
    delay(10);
  }
  for (int i=leftn;i>=0;i--){
    lightOn(left,i,color);
    lightOn(right,i,color);
    lightOn(mid1,i,color);
    lightOn(mid2,i,color);
    delay(10);
  }
  delay(1000);
  for (int i=0;i<=rightn;i++){
    lightOn(left,i,black);
    lightOn(right,i,black);
    lightOn(mid1,i,black);
    lightOn(mid2,i,black);
    delay(10);
  }
  for (int i=0,j=botn;i<=botn/2, j>=botn/2;i++,j--){
    lightOn(bot,i,black);
    lightOn(bot,j,black);
    delay(10);
  }
  
}

//helper function, intended to occasionally turn off all lights.
void allBlack(){
  for (int i=0;i<botn;i++){
    lightOn(left,i,black);
    lightOn(right,i,black);
    lightOn(bot,i,black);
    lightOn(mid1,i,black);
    lightOn(mid2,i,black);
    }
}

void rave(){
  for (int i=0;i<leftn;i++){
    lightOn(left,i,white);
    lightOn(right,i,white);
    lightOn(bot,i,white);
    lightOn(mid1,i,white);
    lightOn(mid2,i,white);
  }
  delay(random(5,350));
  for (int i=0;i<leftn;i++){
    lightOn(left,i,black);
    lightOn(bot,i,black);
    lightOn(right,i,black);
    lightOn(mid1,i,black);
    lightOn(mid2,i,black);
    }
  delay(random(5,350));
}
void circle(){
    int x=0;
    Node::Pixel *currOuterOn=headOuter;
    Node::Pixel *currInnerOn=headInner;
    Node::Pixel *currOuterOff=headOuter->prev->prev->prev->prev->prev->prev->prev->prev->prev->prev->prev->prev;
    Node::Pixel *currInnerOff=headInner->prev->prev->prev->prev->prev->prev->prev->prev->prev->prev->prev->prev;
    while (x<200000){
      lightOn(*currOuterOn->strip,currOuterOn->location,Wheel((i+x)%255));
      lightOn(*currInnerOn->strip,currInnerOn->location,Wheel((i+x)%255));
      lightOn(*currOuterOff->strip,currOuterOff->location,black);
      lightOn(*currInnerOff->strip,currInnerOff->location,black);
      currOuterOn=currOuterOn->next;
      currInnerOn=currInnerOn->next;
      currOuterOff=currOuterOff->next;
      currInnerOff=currInnerOff->next;
      x++;
    }   
    /*for (uint16_t j=0,k=leftn; j < rightn,k>=0; j++,k--) {
      lightOn(right,j,Wheel((j+m)%255));
      lightOn(mid2,j,Wheel((j+m)%255));
      lightOn(left,k,black);
      lightOn(mid1,k,black);
      delay(10);         
    }
    m=m+leftn;      
    for (uint16_t j=0; j < botn; j++) {
      lightOn(bot,j,Wheel((j+m)%255));
      lightOn(right,j,black);
      lightOn(mid2,j,black);
      delay(10);         
    }
    
    m=m+leftn;
    for (uint16_t j=leftn,k=0; j>=0,k<botn; j--,k++) {
      lightOn(left,j,Wheel((j+m)%255));
      lightOn(bot,k,black);
      lightOn(mid1,k,Wheel((j+m)%255));
      delay(10);         
    }    
    m=m+leftn;*/
}


