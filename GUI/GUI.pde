import controlP5.*;
import processing.serial.*;

Serial port;
ControlP5 cp5; 
PFont font;
Textarea myTextArea;

void setup(){
 size(625, 635);    //window size (width, height)
  
  printArray(Serial.list());     //prints all available serial ports
  
  port = new Serial(this, "/dev/cu.usbserial-DA01HA3Y", 9600);   //'COM' is the name of the USB port 
  
  cp5 = new ControlP5(this);
  font = createFont("Arial", 20);
  
  cp5.addButton("up")
  .setPosition(100,35)
  .setSize(100,50)
  .setFont(font);

  cp5.addButton("down")
  .setPosition(100,195)
  .setSize(100,50)
  .setFont(font);
 
  cp5.addButton("left")
  .setPosition(25,115)
  .setSize(100,50)
  .setFont(font);
 
  cp5.addButton("right")
  .setPosition(175,115)
  .setSize(100,50)
  .setFont(font);
 
  cp5.addButton("stop")
  .setPosition(100,275)
  .setSize(100,50)
  .setFont(font)
  .setColorBackground( color( 255,0,0 ) );
  
  cp5.addButton("2")
  .setPosition(500,35)
  .setSize(100,50)
  .setFont(font);
  
  cp5.addButton("3")
  .setPosition(500,95)
  .setSize(100,50)
  .setFont(font);
  
  cp5.addButton("4")
  .setPosition(500,155)
  .setSize(100,50)
  .setFont(font);
  
  cp5.addButton("z")
  .setPosition(500,215)
  .setSize(100,50)
  .setFont(font);
  
  myTextArea = cp5.addTextarea("txt")
  .setPosition(25, 360)
  .setSize(575, 250)
  .setFont(createFont("arial",16))
  .setLineHeight(14)
  .setColor(color(0))
  .setColorBackground(color(255, 255, 255))
  .setColorForeground(color(255, 255, 255));
}

void draw(){
  background(32,178,170); //background color of window (r, g, b)
  fill(0, 255, 0);  //text color(r, g, b)
  textFont(font);
  
  //For receiving/displaying messages from the Zumo
  String message = port.readString();
  if (message != null)
  {
    myTextArea.append(message);
    myTextArea.scroll(1);
  }
}
//Allows use of keypresses whilst inside GUI
void keyPressed() {
  
  switch(key)
  {
    //forwards
    case 'w':
      port.write('w');
      //println("forwards");
      break;
      
    //backwards
    case 's':
      port.write('s');
      //println("backwards");
      break;
      
    //left
    case 'a':
      port.write('a');
      //println("left");
      break;  
    
    //right
    case 'd':
      port.write('d');
      //println("right");
      break; 
    
    //stop  
    case 'f':
      port.write('f');
      //println("stop");
      break; 
    
    //a key
    case 'z':
      port.write('z');
      //println("all");
      break; 
      
    //swarm key
    case 'q':
      port.write('q');
      //println("swarm");
      break; 
     
    //x key
    case '2':
      port.write('2');
      //println("1222");
      break; 
      
    //y key
    case '3':
      port.write('3');
      //println("1223");
      break; 
      
    //b key
    case '4':
      port.write('4');
      //println("1224");
      break; 
  }
}