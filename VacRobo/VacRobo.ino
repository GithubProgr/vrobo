/*
  This is a test sketch for the Vaccum cleaning robot
*/

/*
  ---->	http://www.adafruit.com/products/1438
*/

#include <Adafruit_MotorShield.h>
#include <stdlib.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS1(0x61); 
Adafruit_MotorShield AFMS(0x60); 
// Or, create it with a different I2C address (say for stacking)



class Wheel
{
    public : int dir;
    public : int speed;
    Adafruit_DCMotor *M;

    Wheel(int d, int s, int motNumber)
    {
      dir  = d;
     // speed  = s;
      M = AFMS.getMotor(motNumber);
    }

    setSpeed(int s)
    {
      M->setSpeed(s);
    }

    Run()
    {
      M->run(dir);
    }

    Stop()
    {
      M->run(RELEASE);
    }
};


class EBrush 
{
  public: 
  public : int dir;
  public : int speed;
  Adafruit_DCMotor *EM;
  Adafruit_DCMotor *CM;
  public:
    EBrush(int d, int s, int eMotNumber, int cMotNumber)
    {
      dir  = d;
      speed  = s;
      
      EM = AFMS1.getMotor(eMotNumber);
      CM = AFMS1.getMotor(cMotNumber);
  
    }

    void extenderSpeed()
    {
      EM->setSpeed(40);
    }

    void extenderOut()
    {
      dir = FORWARD;
      EM->run(dir);
    }

    void extenderIn()
    {
      dir = BACKWARD;
      EM->run(dir);
    }

    void extenderStop()
    {
      EM->run(RELEASE);
    }

    void cleanSpeed()
    {
      CM->setSpeed(80);
    }
    
    void cleanStart()
    {
      CM->run(dir);
    }

    void cleanStop()
    {
      CM->run(RELEASE);
    }

    void Stop()
    {
      cleanStop();
      extenderStop();
    }
  
};

// object for each wheel
Wheel FL(FORWARD, 50, 1 );
Wheel FR(FORWARD, 50, 2 );
Wheel BL(FORWARD, 50, 3 );
Wheel BR(FORWARD, 50, 4 );


class VRobo
{
  public:
    VRobo()
    {

    }

    Stop()
    {
      FL.Stop();
      FR.Stop();
      BL.Stop();
      BR.Stop();
    }

    Start()
    {
      FL.Run();
      FR.Run();
      BL.Run();
      BR.Run();
    }

    moveF()
    {
      Serial.print("\n calling movefff\n");
      FL.dir = FORWARD;
      FR.dir = FORWARD;
      BL.dir = FORWARD;
      BR.dir = FORWARD;
    }

    moveB()
    {
      Serial.print("\n calling movebbbbb\n");
      FL.dir = BACKWARD;
      FR.dir = BACKWARD;
      BL.dir = BACKWARD;
      BR.dir = BACKWARD;
    }

    moveL()
    {
      FL.dir = BACKWARD;
      FR.dir = FORWARD;
      BL.dir = FORWARD;
      BR.dir = BACKWARD;
    }

    moveR()
    {
      FL.dir = FORWARD;
      FR.dir = BACKWARD;
      BL.dir = BACKWARD;
      BR.dir = FORWARD;
    }

    speed(int s)
    {
      FL.setSpeed(s);
      FR.setSpeed(s);
      BL.setSpeed(s);
      BR.setSpeed(s);
    }

    movefdl()
    {
      FL.dir = RELEASE;
      FR.dir = FORWARD;
      BL.dir = FORWARD;
      BR.dir = RELEASE;
    }

    movefdr()
    {
      FL.dir = FORWARD;
      FR.dir = RELEASE;
      BL.dir = RELEASE;
      BR.dir = FORWARD;
    }

    movebdl()
    {
      FL.dir = RELEASE;
      FR.dir = BACKWARD;
      BL.dir = BACKWARD;
      BR.dir = RELEASE;
      
    }

    movebdr()
    {
      FL.dir = BACKWARD;
      FR.dir = RELEASE;
      BL.dir = RELEASE;
      BR.dir = BACKWARD;
    }

    moverrl()
    {
      FL.dir = BACKWARD;
      FR.dir = FORWARD;
      BL.dir = BACKWARD;
      BR.dir = FORWARD;
    }

    moverrr()
    {
      FL.dir = FORWARD;
      FR.dir = BACKWARD;
      BL.dir = FORWARD;
      BR.dir = BACKWARD;
    }

    movercl()
    {
      FL.dir = RELEASE;
      FR.dir = FORWARD;
      BL.dir = RELEASE;
      BR.dir = FORWARD;
    }

    movercr()
    {
      FL.dir = FORWARD;
      FR.dir = RELEASE;
      BL.dir = FORWARD;
      BR.dir = RELEASE;
      
    }
    
};



//Extender & cleaner object
EBrush EC1(FORWARD, 50, 1,2 );

// complete Robo
VRobo VR;


void setup() {
  
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  if (!AFMS.begin() || !AFMS1.begin()) 
  {         // create with the default frequency 1.6KHz
    // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1)
    {
      delay(500);
      Serial.println("Could not find Motor Shield. Check wiring.\n");
    }
  }
  
  Serial.println("Motor Shield found.");
}

String str = "";

void loop() 
{
  int s = 0;

  const int BUFFER_SIZE = 4;
  char buf[BUFFER_SIZE+1];
  int len = 0;


 if (Serial.available())
 {
    memset(buf, 0, BUFFER_SIZE+1 );
    len = Serial.readBytes(buf, BUFFER_SIZE);

    // prints the received data
    Serial.print("\nSerial bytes Received: ");
    for (int i = 0; i < len; i++)
      Serial.print(buf[i]);

    switch (buf[0])
    {
      case 'h': //Stop all bots
        VR.Stop();
        EC1.Stop();
        break;

      case '1': //Front left
        FL.dir = ( buf[1] == '1' ) ? FORWARD : BACKWARD;
        FL.Run();
        break;

      case '2': //Front right
        FR.dir = ( buf[1] == '1' ) ? FORWARD : BACKWARD;
        FR.Run();
        break;

      case '3': //Back left
        BL.dir = ( buf[1] == '1' ) ? FORWARD : BACKWARD;
        BL.Run();
        break;

      case '4'://Back right
        BR.dir = ( buf[1] == '1' ) ? FORWARD : BACKWARD;
        BR.Run();
        break;

      case 'r': //Start
        VR.Start();
        break;

      case 's': //Speed

     str = "";

      for ( int i = 1;  i<len ; i++)
       str += buf[i];

       s = str.toInt();

       Serial.print ( "\n" );
       Serial.print ( s );

       if ( s <=0 ) s = 50;
      
        VR.speed(s);
        break;

      case 'v': //Robo control
        
          Serial.print("\n INSIDE VVVVV --->\n");
          switch (buf[1])
          {
            case 'f': // front
              VR.moveF();
              break;

            case 'b': // back
              VR.moveB();
              break;

            case 'l': // left
              VR.moveL();
              break;

            case 'r':// right
              VR.moveR();
              break;

              case '1': // fdl
              VR.movefdl();
              break;

              case '2': // fdr
              VR.movefdr();
              break;

              case '3': // bdl
              VR.movebdl();
              break;

              case '4':// bdr
              VR.movebdr();
              break;

              case '5': // rrl
              VR.moverrl();
              break;

              case '6': // rrr
              VR.moverrr();
              break;

              case '7': // rcl
              VR.movercl();
              break;

              case '8':// rcr
              VR.movercr();
              break;

            case 'h':// Stop bot movement
              VR.Stop();
              break;
        }

        break;

        case 'e': //Extender control
        
          Serial.print("\n INSIDE eeee --->\n");
          switch (buf[1])
          {
             case 's': // extender speed
              EC1.extenderSpeed();
              break;  
              
            case 'f': // extend
              EC1.extenderOut();
              break;

            case 'b': // retract
              EC1.extenderIn();
              break;

            case 'h': // extender stop
              EC1.extenderStop();
              break;  
        }   
        break;
        
         case 'c': //Extender control
        
          Serial.print("\n INSIDE cccc --->\n");
          switch (buf[1])
          {
            case 's': // extender stop
              EC1.cleanSpeed();
              break;
              
            case 'h': // extender stop
              EC1.cleanStop();
              break;

            case 'r':// right
              EC1.cleanStart();
              break;
        }
        break;

        default:
        Serial.print("\nSome error");
        break;

    };
  }
  else
  {

  }



}
