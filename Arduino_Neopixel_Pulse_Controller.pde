import processing.serial.*;
import ddf.minim.*;
import ddf.minim.analysis.*;

Minim minim;
AudioInput in;
color black = color(0);
color back = color(255);
color grey = color(100);
FFT fft;

Serial port;
int bands = 1024;
float max = 0;
int dom = 0;
int lowerbound=512;
int upperbound=0;
int x;
int lowerBound = 0;
boolean on = true;
float frequency;               
float[] avgs = {0.0, 0.0, 0.0, 0.0, 0.0};

void setup() {
  //initialize all the variables
  size(1800, 800, P2D);
  colorMode(HSB, 100);
  minim = new Minim(this);
  minim.debugOn();
  in = minim.getLineIn(Minim.STEREO, bands);
  fft = new FFT(bands, 44100);
  background(0);
  port = new Serial(this, "COM4", 57600);
  fill(0,100,100);
}


void draw() {
  
  background(grey);
  int x = (int)map(in.mix.level(), 0, 1, lowerBound, 255);
  if(on)
    port.write(x + "\n");
  if(!on)
    port.write("0\n");
  if(x>0)
    ellipse(600,200,200,200);
  text(lowerBound + "  ,  " + on + "\n\n" + x + "\n\n" + "s key brings sensitivity down, w sensitivity up;\nbackspace is off, enter is on.\nred circle means light will light up.", 100,100);
  //println(x);
  delay(15);
}


//ending program functions
void stop() {
  in.close();
  minim.stop();
  super.stop();
}

void keyPressed()
{
  if(key == 's')
    lowerBound -= 2;
  if(key == 'w')
    lowerBound += 2;
  if(key == ENTER)
    on = true;
  if(key == BACKSPACE)
    on = false;
}