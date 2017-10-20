// Define optional parts and configurations here


//===========================================================================
//================================= Trains  =================================
//===========================================================================



#define MAX_TRAINS 10 // with 10 trains the performance is about 2-3 updates/s
Train trains[MAX_TRAINS] {Train( 1, "RC1    ", UNCONF), 
                  Train( 3, "RC2    ", DCC), 
                  Train( 72, "ST    ", UNCONF), 
                  Train( 24, "Electric", UNCONF), //0220
                  Train( 60, "Railcar", UNCONF),  //0202
                  Train( 72, "Diesel", MOTOROLA),   //0022
                  Train( 78, "Steam", MOTOROLA),    //0222
                  Train( 80, "Delta Pilot", UNCONF), 
                  Train( 0, "noname9", UNCONF), 
                  Train( 0, "noname10", UNCONF), 
                  };


//===========================================================================
//================================= IR Remote  ==============================
//===========================================================================

// Comment / Uncomment #define IRSUPPORT to enable or disable support for IR remote
#define IRSUPPORT

// Look in remotes.h for remote options, or create and map your own remote like in remote_basic1.h
#define IR_REMOTE BASIC1






