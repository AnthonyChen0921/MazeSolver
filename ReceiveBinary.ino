// program to test receiving data from PC
// works with SendBinary.py

// the demo was developed to explore how to receive the
//     data needed to define a move for 3 stepper motors

//  in this demo no attempt is made to use it to drive any motors
//  the received data is just echoed back to the Python program

  // this is the data needed to control the motors
struct moveItem {
    unsigned long totalMicros; // 4 bytes
    int xInterval;              // 2
    int yInterval;              // 2
    int zInterval;              // 2
    byte xorVal;                // 1
};

  // and the struct is overlaid on an array to make it easy to receive data from the PC
  // the received data is copied byte by byte into pcLine
  //   and can then be used as, e.g. moveData.totalMicros
union inputFromPC {
   moveItem moveData;
   byte pcLine[11];
};

 // this creates a working instance of the Union
 // elements in it are referred to as, e.g. inputData.moveData.totalMicros
inputFromPC inputData;

byte pcData[11];
boolean newData = false;
boolean askForData = true;


void setup() {
  Serial.begin(9600);
  Serial.println("<Arduino is ready>>");
}

void loop() {

  requestData();
  receiveData();
  displayData();
  delay(100);
}

void requestData() {
   if (askForData) {
      Serial.print("<M>");
      askForData = false;
   }
}

void receiveData() {
   
   if (Serial.available() < 11) {
     // error
     return;
   }
   for (byte n = 0; n < 11; n++) {
      pcData[n] = Serial.read();
   }
   // TODO check CRC
   for (byte n = 0; n < 11; n++) {
     inputData.pcLine[n] = pcData[n];
   }
   newData = true;
}

void displayData() {
  if (newData == false) {
     return;
  }
  Serial.print("<Here it is ... ");
  Serial.print(inputData.moveData.totalMicros);
  Serial.print(" ");
  Serial.print(inputData.moveData.xInterval);
  Serial.print(" ");
  Serial.print(inputData.moveData.yInterval);
  Serial.print(" ");
  Serial.print(inputData.moveData.zInterval);
  Serial.print(" ");
  Serial.print(inputData.moveData.xorVal);
  Serial.println('>');
  newData = false;
  askForData = true;
}
