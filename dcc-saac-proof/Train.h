
class Train {
  private:
    int speed;
    byte id;
    bool func[20];
    char name[9];
    bool configured; // true if the train is configured and usable
    byte moto[26]; // unused maybe
    byte format;
    
  public:
    Train(int idIn, String nameIn, byte formatIn);
    void setSpeed(int inSpeed);
    int getSpeed();
    void toggleFunction(int funcNr);
    char* getName();
    byte getID();
    byte getSpeedMsg();
    bool isConfigured();
    byte getFunctionGroup1();
    byte getFunctionGroup2();
    byte getFunctionGroup3();
    bool getFunction(int funcNr);
    byte* getMotorola();
    byte getFormat();
    byte direction;
};

Train::Train(int idIn, String nameIn, byte formatIn) {
  // Constructor for a train
  if (formatIn != UNCONF) {
    this->configured = true;
    this->id = idIn;
    this->format = formatIn;
    //this->name = nameIn;
    nameIn.toCharArray(this->name, 9);

    this->name[sizeof(this->name)-1] = 0;
    
  } else {
    this->configured = false;
    String banan = "... ";
    banan.toCharArray(this->name, 9);
  }
  
  this->speed = 0;
}



int Train::getSpeed() {
  return this->speed;
}

void Train::setSpeed(int inSpeed) {
  if(inSpeed >127) {
    inSpeed=127;
  }
  if(inSpeed < -126) {
    inSpeed=-126;
  }
  if (this->format == MOTOROLA) {
    if (inSpeed < -10) {
      this->direction = 10; // tell the system to send x nr of direction change messages
      this->speed = 0;
      return;
    }
  }
  this->speed = inSpeed;
}

void Train::toggleFunction(int funcNr) {
  func[funcNr] = !func[funcNr];
}

char* Train::getName() {
  return this->name;
}

byte Train::getSpeedMsg() {
  byte  data;
  byte locoSpeed;
  bool dir;
  if (this->speed >=0) {
    dir = true;
  } else {
    dir = false;
  }
  locoSpeed = abs(this->speed);
  if (locoSpeed == 1)  {  // this would result in emergency stop
    locoSpeed = 0;
  }
   
  // direction info first
  if (dir)  {  // forward
    data = 0b10000000;
  }  else  {
    data = 0;
  }
   
  data |=  locoSpeed;
  return data;
}
byte Train::getID() {
  return this->id;
}

bool Train::isConfigured() {
  return this->configured;
}

byte Train::getFunctionGroup1() {

  //Function Group One Instruction (100)
  //The format of this instruction is 100DDDDD

/*Up to 5 auxiliary functions (functions FL and F1-F4) can be controlled by the Function Group One instruction. Bits
0-3 shall define the value of functions F1-F4 with function F1 being controlled by bit 0 and function F4 being
controlled by bit 3. A value of "1" shall indicate that the function is "on" while a value of "0" shall indicate that the
function is "off". If Bit 1 of CV#29 has a value of one (1), then bit 4 controls function FL, otherwise bit 4 has no meaning. */

  byte data = 0b10000000;

  if (func[0]) {
    bitSet(data,4); 
  }
  if (func[1]) {
    bitSet(data,0); 
  }
  if (func[2]) {
    bitSet(data,1); 
  }
  if (func[3]) {
    bitSet(data,2); 
  }
  if (func[4]) {
    bitSet(data,3); 
  }
  return data;
}
byte Train::getFunctionGroup2() {

  //Function Group Two Instruction (101)
  //The format of this instruction is 101SDDDD

/*
Up to 8 additional auxiliary functions (F5-F12) can be controlled by a Function Group Two instruction. Bit 4
defines the use of Bits 0-3. When bit 4 (S) is ‘1’, Bits 0-3 (DDDD) shall define the value of functions F5-F8 with
 function F5 being controlled by bit 0 and function F8 being controlled by bit 3. When bit 4 (S) is ‘0’, Bits 0-3
(DDDD) shall define the value of functions F9-F12 with function F9 being controlled by bit 0 and function F12
being controlled by bit 3. A value of "1" shall indicate that the function is "on" while a value of "0" shall indicate
that the function is "off".  */

  byte data = 0b10100000;

  if (func[5]) {
    bitSet(data,0); 
  }
  if (func[6]) {
    bitSet(data,1); 
  }
  if (func[7]) {
    bitSet(data,2); 
  }
  if (func[8]) {
    bitSet(data,3); 
  }
  return data;
}
byte Train::getFunctionGroup3() {

  //Function Group Two Instruction (101)
  //The format of this instruction is 101SDDDD

/*
Up to 8 additional auxiliary functions (F5-F12) can be controlled by a Function Group Two instruction. Bit 4
defines the use of Bits 0-3. When bit 4 (S) is ‘1’, Bits 0-3 (DDDD) shall define the value of functions F5-F8 with
 function F5 being controlled by bit 0 and function F8 being controlled by bit 3. When bit 4 (S) is ‘0’, Bits 0-3
(DDDD) shall define the value of functions F9-F12 with function F9 being controlled by bit 0 and function F12
being controlled by bit 3. A value of "1" shall indicate that the function is "on" while a value of "0" shall indicate
that the function is "off".  */

  byte data = 0b10110000;

  if (func[9]) {
    bitSet(data,0); 
  }
  if (func[10]) {
    bitSet(data,1); 
  }
  if (func[11]) {
    bitSet(data,2); 
  }
  if (func[12]) {
    bitSet(data,3); 
  }
  return data;
}

bool Train::getFunction(int funcNr) {
  if (func[funcNr]) {
    return true;
  }
  return false;
}
byte* Train::getMotorola() {
  Serial.print("building Motorola");
  for (int i;i<26;i++) {
    this->moto[i] = 0;
  }
  byte mspeed = abs(this->speed/9);
  if (mspeed == 1) {
    mspeed = 0;
  }
  if (this->direction>0) {
    this->direction--;
    mspeed = 1;
  }

  // address
  if (this->id == 78) {
    this->moto[0] = 0;
    this->moto[1] = 0;

    this->moto[2] = 1;
    this->moto[3] = 0;

    this->moto[4] = 1;
    this->moto[5] = 0;

    this->moto[6] = 1;
    this->moto[7] = 0;
  }
  if (this->id == 72) {
    this->moto[0] = 0;
    this->moto[1] = 0;

    this->moto[2] = 0;
    this->moto[3] = 0;

    this->moto[4] = 1;
    this->moto[5] = 0;

    this->moto[6] = 1;
    this->moto[7] = 0;
  }
  if (this->func[0]) {
    this->moto[8] = 1;
    this->moto[9] = 1;
  }
  // speed
  if (mspeed & 0b00000001) {
    this->moto[10] = 1;
    this->moto[11] = 1;
  }
  if (mspeed & 0b00000010) {
    this->moto[12] = 1;
    this->moto[13] = 1;
  }
  if (mspeed & 0b00000100) {
    this->moto[14] = 1;
    this->moto[15] = 1;
  }
  if (mspeed & 0b00001000) {
    this->moto[16] = 1;
    this->moto[17] = 1;
  }
  this->moto[18] = 2;
  this->moto[19] = 2;
  this->moto[20] = 2;
  this->moto[21] = 2;
  this->moto[22] = 2;
  this->moto[23] = 2;
  this->moto[24] = 2;
  this->moto[25] = 2;
  Serial.println(".");
  return this->moto;
}
byte Train::getFormat() {
  return this->format;
}
