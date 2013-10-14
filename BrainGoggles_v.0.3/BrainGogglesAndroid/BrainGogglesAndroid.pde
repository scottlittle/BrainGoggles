//Scott Little, 2013
//GNU GPLv3
//Built upon Ketai Library and bluetooth example by Daniel Sauter

//required for BT enabling on startup
import android.view.WindowManager;
import android.view.View;
import android.content.Intent;
import android.os.Bundle;
import ketai.net.bluetooth.*;
import ketai.ui.*;
import ketai.net.*;
import oscP5.*;

KetaiBluetooth bt;
String info = "";
KetaiList klist;
PVector remoteMouse = new PVector();

ArrayList<String> devicesDiscovered = new ArrayList();
boolean isConfiguring = true;
String UIText;
/*float j = 0;    //these variables are not relevant to LightSwitch
int raw = 0;
float oldj = 0;
int oldraw = 0;
int attention = 0;
int k = 0;*/
//boolean toggleSwitch = true;
float displaydata = 0;
float olddisplaydata = 0;
float xDisplay = 0;
float oldxDisplay = 0;
float zoomY = 1;
float offsetY = 0;


//********************************************************************
// The following code is required to enable bluetooth at startup.
//********************************************************************
void onCreate(Bundle savedInstanceState) {
  super.onCreate(savedInstanceState);
  bt = new KetaiBluetooth(this);
  // fix so screen doesn't go to sleep when app is active
  getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
}

void onActivityResult(int requestCode, int resultCode, Intent data) {
  bt.onActivityResult(requestCode, resultCode, data);
}
//********************************************************************

void setup()
{   
  orientation(PORTRAIT);
  background(78, 93, 75);
  stroke(255);
  textSize(24);

  //start listening for BT connections
  bt.start();
  
  UIText =  "d - discover devices\n" +
    "b - make this device discoverable\n" +
    "c - connect to device\n     from discovered list.\n" +
    "p - list paired devices\n" +
    "i - Bluetooth info";
}

void draw()
{
  if (isConfiguring)
  {
    ArrayList<String> names;
    background(78, 93, 75);

    //based on last key pressed lets display
    //  appropriately
    if (key == 'i')
      info = getBluetoothInformation();
    else
    {
      if (key == 'p')
      {
        info = "Paired Devices:\n";
        names = bt.getPairedDeviceNames();
      }
      else
      {
        info = "Discovered Devices:\n";
        names = bt.getDiscoveredDeviceNames();
      }

      for (int i=0; i < names.size(); i++)
      {
        info += "["+i+"] "+names.get(i).toString() + "\n";
      }
    }
    text(UIText + "\n\n" + info, 5, 90);
  }
  else
  {
    
    oscilloscope();  //draw voltage output
    
    /*
    // draw in the on position
    pushStyle();     
    if (toggleSwitch == true) {
      fill(0);
    } else {
      fill(255);
    }
    ellipse(256, 256, 200, 200);
    popStyle();
    
    //draw in the off position
    pushStyle();    
    if (toggleSwitch == false) {
      fill(0);
    } else {
      fill(255);
    }
    ellipse(256, 768, 200, 200);
    popStyle();
    */
    
    //draws mouse on screen, artifact from previous iterations ;)
    pushStyle();
    ellipse(mouseX, mouseY, 20, 20);
    fill(0, 255, 0);
    stroke(0, 255, 0);
    ellipse(remoteMouse.x, remoteMouse.y, 20, 20);   
    popStyle();
  }

  drawUI();
}

String getBluetoothInformation()
{
  String btInfo = "Server Running: ";
  btInfo += bt.isStarted() + "\n";
  btInfo += "Device Discoverable: "+bt.isDiscoverable() + "\n";
  btInfo += "\nConnected Devices: \n";

  ArrayList<String> devices = bt.getConnectedDeviceNames();
  for (String device: devices)
  {
    btInfo+= device+"\n";
  }
  return btInfo;
}

//Call back method to manage data received
void onBluetoothDataEvent(String who, byte[] data)
{
  if (isConfiguring)
    return;
  
    int datalength = data.length;
    int integerdata = 0;
    if (datalength == 2){
      integerdata = (data[1]&0xFF|((data[0]&0xFF)<<8));  //get byte data from arduino and turn it into int
    }
    
    /*   int value[] = new int[datalength];
    for (int i=0; i<datalength; i++){
       value[i] = data[i];
       if (value[i] == 1){
         toggleSwitch = true;
       }
       else {
         toggleSwitch = false;
       }    
    } */
    if (integerdata != 0)
    {
      fill(100);  //grey color backgroung
      rect(5,55,300,85);  //background for voltage text
      fill(255);  //white texty
      displaydata = integerdata/4095.0*5.1;  //5.1 volts reference, 4095 is the max for a 12 bit adc
      text("voltage "+ displaydata, 5, 100);
    }
     
    
    //println("length: "+datalength);
//    for (int i=0; i<datalength; i++){
//      value[i] = data[i];
//      if (data[i]<0)
//        value[i] = data[i]+256;
//      //println("data "+i+": "+value[i]); 
//    }
//
//    for (int i=0; i<(datalength-1); i++){
//      if (value[i]==170){
//        if (value[i+1]==170){
//          for (k=i; k<value[i+2]; k++){
//            if (value[i+3]==128){
//              raw = value[i+5]*256+value[i+6];
//              if (raw >= 32768){
//                raw = raw - 65536;
//                //println("raw: "+raw);
//              }
//              i=k;
//              j = j + 0.1;
//              //println(j);
//              if (j>512)
//               j = 0;
//            }
//              if (value[i+3]==4){
//               attention = value[i+4];
//               println(attention);
//              }
//       
//          }
//          
//
//        }
//      }      
//    }
}
