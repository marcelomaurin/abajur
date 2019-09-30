// A basic everyday NeoPixel strip test program.

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#include <Adafruit_NeoPixel.h>
#include <Servo.h>
#include <HCSR04.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

Servo myservo;  // create servo object to control a servo
// twelve servo objects can                                                                                                                                                                                                                                    be created on most boards
UltraSonicDistanceSensor distanceSensor(10, 11);  // Initialize sensor that uses digital pins 13 and 12.

int pos = 0;    // variable to store the servo position

int distancia=20;

int desligado =0;

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    13

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 60


// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


// setup() function -- runs once at startup --------------------------------

int tempo =4;
int faixa = 0;

void setup()
{
  Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
  Start_Led(); 
  Start_Servo();
}



void Start_Led(){
    // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void Start_Servo(){
  myservo.attach(4);  // attaches the servo on pin 9 to the servo object
}



// loop() function -- runs repeatedly as long as board is on ---------------

void Led() {
  if (!desligado) {
  //uint32_t rgb = distancia*15;
  if(distancia>20){
    if (faixa != 7){
      //colorWipe(strip.Color(255,255,255),tempo);
      Serial.println("faixa 7");
      faixa = 6;
    }
  }
 if((distancia<20)&&(distancia>=17)){
    if (faixa != 6){
      colorWipe(strip.Color(255,255,255),tempo);
      Serial.println("faixa 6");
      faixa = 6;
    }
  }
  if((distancia<17)&&(distancia>=15)){
    if (faixa != 5){
      colorWipe(strip.Color(255,0,255),tempo);
      Serial.println("faixa 5");
      faixa = 5;
    }
  }
  if((distancia<15)&&(distancia>=13)){
    if (faixa != 4){

    colorWipe(strip.Color(255,255,0),tempo);
    Serial.println("faixa 4");
    faixa = 4;
    }
  }
  if((distancia<13)&&(distancia>=10)){
    if (faixa != 3){
      colorWipe(strip.Color(0,255,255),tempo);
      Serial.println("FAIXA 3");
      faixa = 3;
    }
  }
  if((distancia<10)&&(distancia>=7)){
    if (faixa != 2){
    colorWipe(strip.Color(255,0,0),tempo);
    Serial.println("FAIXA 2");
    faixa =2;
    }
  }
  if((distancia<7)&&(distancia>=5)){
    if (faixa != 1){
      colorWipe(strip.Color(0,255,0),tempo);
      Serial.println("faixa 1");
      faixa =1;
    }
  }

 if((distancia<5)&&(distancia>=2)){
    if (faixa != 0){
      colorWipe(strip.Color(0,0,255),tempo);
      Serial.println("faixa 0");
      faixa = 0;    
    }
 }
  }
 if(distancia<2){
        colorWipe(strip.Color(0,0,0),tempo);
         Serial.println("desligou");
        desligado = !desligado;
        delay(1000);
    
  }
  

}


// Some functions of our own for creating animated effects -----------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void servo(){
  /*
  for (pos = 0; pos <= 80; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 80; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  */
    myservo.write((distancia*6)); 
    delay(30); 
}

void Distancia(){
    // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
    Serial.println(distanceSensor.measureDistanceCm());
    distancia = (int)distanceSensor.measureDistanceCm();
    //delay(500);
}

void loop(){
    
    Led();
    Distancia();
    servo();
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}
