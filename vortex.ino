#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 4

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 11
#define CLOCK_PIN 12

// Define the array of leds
CRGB leds[NUM_LEDS];

// Define the bluetooth communication port and buffer
#define Bluetooth Serial2
char buff[256];

class point {
  public:
  point() {
    x = -1;
    y = -1;
  }
  point(float xx, float yy) {
    x = xx;
    y = yy;
  }
  float x;
  float y;
};

class polygon {
  public:
  polygon() {
    n = 0;
  }
  polygon(int nn, int g = 0,
                  point p0 = point(), point p1 = point(),
                  point p2 = point(), point p3 = point(),
                  point p4 = point(), point p5 = point(),
                  point p6 = point(), point p7 = point()) {
    group = g;
    n = nn;
    ps[0] = p0;
    ps[1] = p1;
    ps[2] = p2;
    ps[3] = p3;
    ps[4] = p4;
    ps[5] = p5;
    ps[6] = p6;
    ps[7] = p7;
    
  }
  int n;
  int group;
  point ps[8];
};

class frame {
  public:
  frame() {
    n = 0;
  }
  frame(int nn, polygon p0 = polygon(), polygon p1 = polygon(),
                 polygon p2 = polygon(), polygon p3 = polygon(),
                 polygon p4 = polygon(), polygon p5 = polygon(),
                 polygon p6 = polygon(), polygon p7 = polygon()) {
    n = nn;
    ps[0] = p0;
    ps[1] = p1;
    ps[2] = p2;
    ps[3] = p3;
    ps[4] = p4;
    ps[5] = p5;
    ps[6] = p6;
    ps[7] = p7;
    
  }
  int n;
  polygon ps[8];
};


point led_matrix[NUM_LEDS];


#define PRIMARY 0
#define SECONDARY 1
#define TERTIARY 2
#define QUAD 3
#define animation(x) frame x[]

/*
  ANIMATIONS
  define animation sets here
 */
 
animation(pulse) = {
  frame(1,
    polygon(4, PRIMARY,
      point(0,0),
      point(0,100),
      point(100,100),
      point(100,0)
  )),
  frame(0) 
};

animation(spiral) = {
  frame(4,
    polygon(4, PRIMARY,
      point(0,20),
      point(0,0),
      point(20,0),
      point(50,50)
    ),
    polygon(4, TERTIARY,
      point(80,0),
      point(100,0),
      point(100,20),
      point(50,50)
    ),
    polygon(4, SECONDARY,
      point(100,80),
      point(100,100),
      point(80,100),
      point(50,50)
    ),
    polygon(4, QUAD,
      point(20,100),
      point(0,100),
      point(0,80),
      point(50,50)
    )
  ),
  frame(4,
    polygon(3, PRIMARY,
      point(20,0),
      point(35,0),
      point(50,50)
    ),
    polygon(3, TERTIARY,
      point(100,20),
      point(100,35),
      point(50,50)
    ),
    polygon(3, SECONDARY,
      point(80,100),
      point(65,100),
      point(50,50)
    ),
    polygon(3, QUAD,
      point(0,80),
      point(0,65),
      point(50,50)
    )
  ),
  frame(4,
    polygon(3, PRIMARY,
      point(35,0),
      point(50,0),
      point(50,50)
    ),
    polygon(3, TERTIARY,
      point(100,35),
      point(100,50),
      point(50,50)
    ),
    polygon(3, SECONDARY,
      point(65,100),
      point(50,100),
      point(50,50)
    ),
    polygon(3, QUAD,
      point(0,65),
      point(0,50),
      point(50,50)
    )
  ),
  frame(4,
    polygon(3,PRIMARY,
      point(50,0),
      point(65,0),
      point(50,50)
    ),
    polygon(3, TERTIARY,
      point(100,50),
      point(100,65),
      point(50,50)
    ),
    polygon(3, SECONDARY,
      point(50,100),
      point(35,100),
      point(50,50)
    ),
    polygon(3, QUAD,
      point(0,50),
      point(0,35),
      point(50,50)
    )
  ),
  frame(4,
    polygon(3,PRIMARY,
      point(65,0),
      point(80,0),
      point(50,50)
    ),
    polygon(3, TERTIARY,
      point(100,65),
      point(100,80),
      point(50,50)
    ),
    polygon(3, SECONDARY,
      point(35,100),
      point(20,100),
      point(50,50)
    ),
    polygon(3, QUAD,
      point(0,35),
      point(0,20),
      point(50,50)
    )
  ),
  frame(4,
    polygon(4, QUAD,
      point(0,20),
      point(0,0),
      point(20,0),
      point(50,50)
    ),
    polygon(4, PRIMARY,
      point(80,0),
      point(100,0),
      point(100,20),
      point(50,50)
    ),
    polygon(4, TERTIARY,
      point(100,80),
      point(100,100),
      point(80,100),
      point(50,50)
    ),
    polygon(4, SECONDARY,
      point(20,100),
      point(0,100),
      point(0,80),
      point(50,50)
    )
  ),
  frame(4,
    polygon(3, QUAD,
      point(20,0),
      point(35,0),
      point(50,50)
    ),
    polygon(3, PRIMARY,
      point(100,20),
      point(100,35),
      point(50,50)
    ),
    polygon(3, TERTIARY,
      point(80,100),
      point(65,100),
      point(50,50)
    ),
    polygon(3, SECONDARY,
      point(0,80),
      point(0,65),
      point(50,50)
    )
  ),
  frame(4,
    polygon(3, QUAD,
      point(35,0),
      point(50,0),
      point(50,50)
    ),
    polygon(3, PRIMARY,
      point(100,35),
      point(100,50),
      point(50,50)
    ),
    polygon(3, TERTIARY,
      point(65,100),
      point(50,100),
      point(50,50)
    ),
    polygon(3, SECONDARY,
      point(0,65),
      point(0,50),
      point(50,50)
    )
  ),
  frame(4,
    polygon(3,QUAD,
      point(50,0),
      point(65,0),
      point(50,50)
    ),
    polygon(3, PRIMARY,
      point(100,50),
      point(100,65),
      point(50,50)
    ),
    polygon(3, TERTIARY,
      point(50,100),
      point(35,100),
      point(50,50)
    ),
    polygon(3, SECONDARY,
      point(0,50),
      point(0,35),
      point(50,50)
    )
  ),
  frame(4,
    polygon(3,QUAD,
      point(65,0),
      point(80,0),
      point(50,50)
    ),
    polygon(3, PRIMARY,
      point(100,65),
      point(100,80),
      point(50,50)
    ),
    polygon(3, TERTIARY,
      point(35,100),
      point(20,100),
      point(50,50)
    ),
    polygon(3, SECONDARY,
      point(0,35),
      point(0,20),
      point(50,50)
    )
  ),
  frame(4,
    polygon(4, SECONDARY,
      point(0,20),
      point(0,0),
      point(20,0),
      point(50,50)
    ),
    polygon(4, QUAD,
      point(80,0),
      point(100,0),
      point(100,20),
      point(50,50)
    ),
    polygon(4, PRIMARY,
      point(100,80),
      point(100,100),
      point(80,100),
      point(50,50)
    ),
    polygon(4, TERTIARY,
      point(20,100),
      point(0,100),
      point(0,80),
      point(50,50)
    )
  ),
  frame(4,
    polygon(3, SECONDARY,
      point(20,0),
      point(35,0),
      point(50,50)
    ),
    polygon(3, QUAD,
      point(100,20),
      point(100,35),
      point(50,50)
    ),
    polygon(3, PRIMARY,
      point(80,100),
      point(65,100),
      point(50,50)
    ),
    polygon(3, TERTIARY,
      point(0,80),
      point(0,65),
      point(50,50)
    )
  ),
  frame(4,
    polygon(3, SECONDARY,
      point(35,0),
      point(50,0),
      point(50,50)
    ),
    polygon(3, QUAD,
      point(100,35),
      point(100,50),
      point(50,50)
    ),
    polygon(3, PRIMARY,
      point(65,100),
      point(50,100),
      point(50,50)
    ),
    polygon(3, TERTIARY,
      point(0,65),
      point(0,50),
      point(50,50)
    )
  ),
  frame(4,
    polygon(3,SECONDARY,
      point(50,0),
      point(65,0),
      point(50,50)
    ),
    polygon(3, QUAD,
      point(100,50),
      point(100,65),
      point(50,50)
    ),
    polygon(3, PRIMARY,
      point(50,100),
      point(35,100),
      point(50,50)
    ),
    polygon(3, TERTIARY,
      point(0,50),
      point(0,35),
      point(50,50)
    )
  ),
  frame(4,
    polygon(3,SECONDARY,
      point(65,0),
      point(80,0),
      point(50,50)
    ),
    polygon(3, QUAD,
      point(100,65),
      point(100,80),
      point(50,50)
    ),
    polygon(3, PRIMARY,
      point(35,100),
      point(20,100),
      point(50,50)
    ),
    polygon(3, TERTIARY,
      point(0,35),
      point(0,20),
      point(50,50)
    )
  ),
  frame(4,
    polygon(4, TERTIARY,
      point(0,20),
      point(0,0),
      point(20,0),
      point(50,50)
    ),
    polygon(4, SECONDARY,
      point(80,0),
      point(100,0),
      point(100,20),
      point(50,50)
    ),
    polygon(4, QUAD,
      point(100,80),
      point(100,100),
      point(80,100),
      point(50,50)
    ),
    polygon(4, PRIMARY,
      point(20,100),
      point(0,100),
      point(0,80),
      point(50,50)
    )
  ),
  frame(4,
    polygon(3, TERTIARY,
      point(20,0),
      point(35,0),
      point(50,50)
    ),
    polygon(3, SECONDARY,
      point(100,20),
      point(100,35),
      point(50,50)
    ),
    polygon(3, QUAD,
      point(80,100),
      point(65,100),
      point(50,50)
    ),
    polygon(3, PRIMARY,
      point(0,80),
      point(0,65),
      point(50,50)
    )
  ),
  frame(4,
    polygon(3, TERTIARY,
      point(35,0),
      point(50,0),
      point(50,50)
    ),
    polygon(3, SECONDARY,
      point(100,35),
      point(100,50),
      point(50,50)
    ),
    polygon(3, QUAD,
      point(65,100),
      point(50,100),
      point(50,50)
    ),
    polygon(3, PRIMARY,
      point(0,65),
      point(0,50),
      point(50,50)
    )
  ),
  frame(4,
    polygon(3,TERTIARY,
      point(50,0),
      point(65,0),
      point(50,50)
    ),
    polygon(3, SECONDARY,
      point(100,50),
      point(100,65),
      point(50,50)
    ),
    polygon(3, QUAD,
      point(50,100),
      point(35,100),
      point(50,50)
    ),
    polygon(3, PRIMARY,
      point(0,50),
      point(0,35),
      point(50,50)
    )
  ),
  frame(4,
    polygon(3,TERTIARY,
      point(65,0),
      point(80,0),
      point(50,50)
    ),
    polygon(3, SECONDARY,
      point(100,65),
      point(100,80),
      point(50,50)
    ),
    polygon(3, QUAD,
      point(35,100),
      point(20,100),
      point(50,50)
    ),
    polygon(3, PRIMARY,
      point(0,35),
      point(0,20),
      point(50,50)
    )
  ),
  frame(0)
};

// ANIMATION LIBRARY FUNCTIONS

// adopted from code on StackOverflow
int pnpoly(int nvert, float *vertx, float *verty, float testx, float testy) {
  int i, j, c = 0;
  for (i = 0, j = nvert-1; i < nvert; j = i++) {
    if ( ((verty[i]>testy) != (verty[j]>testy)) &&
     (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
       c = !c;
  }
  return c;
}

int rev;

// count the number of frames in an animation
int frames(animation(x)) {
  int k = 0;
  frame ps;
  while ((ps = x[k++]).n > 0);
  return k-1;
}

void animate(animation(x), int duration, CRGB c0 = CRGB::Black,
                                         CRGB c1 = CRGB::Black,
                                         CRGB c2 = CRGB::Black,
                                         CRGB c3 = CRGB::Black,
                                         CRGB c4 = CRGB::Black,
                                         CRGB c5 = CRGB::Black,
                                         CRGB c6 = CRGB::Black,
                                         CRGB c7 = CRGB::Black) {
                                           
  Bluetooth.println("Begin animation");

  int frs = frames(x);
  int del = duration / frs;
  
  // execute each frame
  
  Bluetooth.print("Found this many frames: ");
  Bluetooth.println(frs);
  for (int k = 0; k < frs; ++k) { // for each frame
    frame ss = x[(rev*(frs-1 -k-k)+k)];
    Bluetooth.print("frame: ");
    Bluetooth.println(k);
    
    // clear leds from last frame
    for(int i = 0; i < NUM_LEDS; ++i)
        leds[i] = CRGB::Black;
        
    for(int s = 0; s < ss.n; ++s) {  // for each shape
      polygon ps = ss.ps[s];
      for(int i = 0; i < NUM_LEDS; ++i) {  // for each led
        float testx = led_matrix[i].x;
        float testy = led_matrix[i].y;
        float xs[8];
        float ys[8];
        for (int j = 0; j < 8; ++j) {
          xs[j] = ps.ps[j].x;
          ys[j] = ps.ps[j].y;
        }
        
        if (pnpoly(ps.n, xs, ys, testx, testy)) {
          
          Bluetooth.print("Point (");
          Bluetooth.print(testx);
          Bluetooth.print(",");
          Bluetooth.print(testy);
          Bluetooth.print(") --> ");
          // turn this led on
          switch(ps.group) {
            case PRIMARY:
              leds[i] = c0;        
              Bluetooth.println("PRIMARY");
              break;
            case SECONDARY:
              leds[i] = c1;
              Bluetooth.println("SECONDARY");
              break;
            case TERTIARY:
              leds[i] = c2;
              Bluetooth.println("TERTIARY");
              break;
            case QUAD:
              leds[i] = c3;
              Bluetooth.println("QUAD");
              break;
          }         

        }
      }
    }
    FastLED.show();
    delay(del);
  }
  
  Bluetooth.println("End animation");

  
  // turn off leds
  for(int i = 0; i < NUM_LEDS; ++i) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  
  
}

// repeat state variables
int repeat;
int times;
String commands[16];


void setup() { 
      // Uncomment/edit one of the following lines for your leds arrangement.
      // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
       FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
      //  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS);
      
      // FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, RGB>(leds, NUM_LEDS);

      // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      
      Bluetooth.begin(9600);
      repeat = 0;
      rev = 0;
      
    /*
      LED_MATRIX
      define led locations here
     */
    led_matrix[0] = point(1,1);
    led_matrix[1] = point(80,80);
    led_matrix[2] = point(5,5);
    led_matrix[3] = point(80,10);
      
}

String getline(String& line, char delim = ' ') {
    int ch = line.indexOf(delim);
    String result = line.substring(0,ch);

    if (ch <= 0) {
      line = "";
      return result;
    }
    
    String xs = line.substring(ch+1);
    line = xs;
    return result;
}

CRGB to_color(String col) {
  if (col.equalsIgnoreCase("red"))    
    return CRGB::Red;
  if (col.equalsIgnoreCase("green"))
    return CRGB::Green;
  if (col.equalsIgnoreCase("blue"))    
    return CRGB::Blue;
  if (col.equalsIgnoreCase("orange"))
    return CRGB::Orange;
  if (col.equalsIgnoreCase("yellow"))    
    return CRGB::Yellow;
  if (col.equalsIgnoreCase("purple"))
    return CRGB::Purple;
  
  String trash = getline(col,'(');
  String p1 = getline(col,',');
  String p2 = getline(col, ',');
  String p3 = getline(col,')');
  
  
  if (!p3.equals("")) {
    int r = p1.toInt();
    int g = p2.toInt();
    int b = p3.toInt();
    
    CRGB color;
    Bluetooth.print("Got custom color R:");
    Bluetooth.print(r);
    Bluetooth.print(", G:");
    Bluetooth.print(g);
    Bluetooth.print(", B:");
    Bluetooth.println(b);
  
    color.setRGB(r,g,b);
    
    return color;
  }
  
  return CRGB::Black;
    
}


// some macros to make inserting animations easier
#define xstr(s) str(s)
#define str(s) #s
#define check_animation(name) else if (comm.equalsIgnoreCase(str(name))) {\
    Bluetooth.print("Received ");\
    Bluetooth.println(str(name));\
    if (repeat)\
      commands[repeat++-1] = original;\
    else\
      animate(name, duration, colors[0], colors[1], colors[2], colors[3]);\
  }

// take a string and execute its command
void execute(String commline) {
  String original = commline;
  String comm = getline(commline);
  String temp;
  String args[8];
  int argc = 1;
  for(args[0] = getline(commline); !args[argc-1].equals(""); ++argc)
    args[argc] = getline(commline);
  --argc;
  
  
  // take in information for common protocol syntax:
  // COMMAND duration primary_color secondary_color tertiary_color quad_color
  int duration = args[0].toInt();
  CRGB colors[4];
  for (int i = 1; i < argc; ++i)
    colors[i-1] = to_color(args[i]);

  // check command and do appropriate action
  if (comm.equals("nop")) {
    Bluetooth.println("Received nop");
    return;
  }
  
  else if (comm.equalsIgnoreCase("repeat")) {
    if (repeat) {
      int num_actions = repeat-1;
      int num_repeats = times;
      repeat = 0;
      
      Bluetooth.println("Executing repeat sequence");
      for(int i = 0; i < num_repeats; ++i) {
        Bluetooth.print("Repetition: ");
        Bluetooth.println(i);
        for(int j = 0; j < num_actions; ++j)
          execute(commands[j]);
      }
      Bluetooth.println("Finish executing repeat");
    }
    else {
      Bluetooth.println("Starting repeat sequence");
      times = duration;
      repeat = 1;
    }
  }
  else if (comm.equalsIgnoreCase("reverse")) {
    String param = original;
    getline(param); // remove the word 'reverse'
    rev ^= 1;
    execute(param);
    rev ^= 1;
  }
  
  check_animation(pulse)
  check_animation(spiral)
  
  else {
    Bluetooth.println("Received unknown command");
  }
    
}

void loop() { 
  
  if (Bluetooth.available() > 0) {

    Bluetooth.readBytesUntil(10, buff, 255);
    Bluetooth.print("Received line: ");
    Bluetooth.println(buff);
    
    String buffer = String(buff);
    
    execute(buffer);
    
  }
  
}
