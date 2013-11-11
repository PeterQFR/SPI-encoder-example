import processing.serial.*;

Serial myPort;
int nl=10;
String myString = null;
void setup()
{
  println(Serial.list());
  myPort=new Serial(this, Serial.list()[0], 9600);

  myPort.clear();
  myString = myPort.readStringUntil(nl);
  myString = null;
}

void draw()
{
  while (myPort.available()>0)
  {
    myString = myPort.readStringUntil(nl);
    if (myString != null)
    {
      println(myString);
    }
  }
}
      
  
  
  

