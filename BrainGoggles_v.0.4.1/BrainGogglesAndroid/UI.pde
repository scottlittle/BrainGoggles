/*  UI-related functions */


void mousePressed()
{
 
  //keyboard button -- toggle virtual keyboard
  if (mouseY <= 50 && mouseX > 0 && mouseX < width/3)
    KetaiKeyboard.toggle(this);
  else if (mouseY <= 50 && mouseX > width/3 && mouseX < 2*(width/3)) //config button
  {
    isConfiguring=true;
  }
  else if (mouseY <= 50 && mouseX >  2*(width/3) && mouseX < width) // draw button
  {
    if (isConfiguring)
    {
      //if we're entering draw mode then clear canvas
      background(78, 93, 75);
      isConfiguring = false;
    }
  }

}

void mouseDragged()
{
  if (isConfiguring)
    return;

  ellipse(mouseX, mouseY, 20, 20);
}


void keyPressed() {
  if (key =='c')
  {
    //If we have not discovered any devices, try prior paired devices
    if (bt.getDiscoveredDeviceNames().size() > 0)
      klist = new KetaiList(this, bt.getDiscoveredDeviceNames());
    else if (bt.getPairedDeviceNames().size() > 0)
      klist = new KetaiList(this, bt.getPairedDeviceNames());
  }
  else if (key == 'd')
  {
    bt.discoverDevices();
  }
  //else if (key == 'x')
  //  bt.stop();
  else if (key == 'b')
  {
    bt.makeDiscoverable();
  }
  //else if (key == 's')
  //{
  //  bt.start();
  //}
  else if (key == 'w')
  {
    byte[] dataToArduino = {'w'};
    bt.broadcast(dataToArduino);
  }
  else if (key == 'q')
  {
    byte[] dataToArduino = {'q'};
    bt.broadcast(dataToArduino);
  }
    else if (key == 't')
  {
    byte[] dataToArduino = {'t'};
    bt.broadcast(dataToArduino);
  }
  else if (key == 'y')
  {
    byte[] dataToArduino = {'y'};
    bt.broadcast(dataToArduino);
  }
  else if (key == 'z') //zoom in
  {
    zoomY = zoomY*2;
  }
  else if (key == 'x')  //zoom out
  {
    zoomY = zoomY/2;
  }
  else if (key == 'a') //higherY
  {
    offsetY = offsetY + 30;
  }
  else if (key == 's')  //lowerY
  {
    offsetY = offsetY - 30;
  }
  else if (key == 'r')  //reset
  {
    zoomY = 1;
    offsetY = 0;
  }
}

void drawUI()
{
  //Draw top shelf UI buttons

  pushStyle();
  fill(0);
  stroke(255);
  rect(0, 0, width/3, 50);

  if (isConfiguring)
  {
    noStroke();
    fill(78, 93, 75);
  }
  else
    fill(0);

  rect(width/3, 0, width/3, 50);

  if (!isConfiguring)
  {  
    noStroke();
    fill(78, 93, 75);
  }
  else
  {
    fill(0);
    stroke(255);
  }
  rect((width/3)*2, 0, width/3, 50);

  fill(255);
  text("Keyboard", 5, 30); 
  text("Bluetooth", width/3+5, 30); 
  text("Interact", width/3*2+5, 30); 

  popStyle();
}

void onKetaiListSelection(KetaiList klist)
{
  String selection = klist.getSelection();
  bt.connectToDeviceByName(selection);

  //dispose of list for now
  klist = null;
}

void oscilloscope()
{
   int s = millis();
   xDisplay = s % 51200;
   stroke(255);
   line(oldxDisplay/100,1023-(zoomY*olddisplaydata+offsetY),xDisplay/100,1023-(zoomY*displaydata+offsetY));
   oldxDisplay = xDisplay;
   olddisplaydata = displaydata;
   if (xDisplay > 50200){
     background(78, 93, 75);
     oldxDisplay = 0;
     olddisplaydata = 0;
   }

}

