//#define ARDUINO
#define EDISON

volatile int  flow_frequency;  // Measures flow meter pulses
float  l_hour;            // Calculated litres/hour                      
float  total=0;            // litres                      
unsigned char flowmeter = 0;  // Flow Meter Pin number
unsigned long currentTime;
unsigned long cloopTime;

void flow ()                  // Interruot function
{ 
   flow_frequency++;
} 

void printDouble( double val, unsigned int precision){
    /*
       prints val with number of decimal places determine by precision
       NOTE: precision is 1 followed by the number of zeros for the desired number of decimial places
       example: printDouble( 3.1415, 100); // prints 3.14 (two decimal places)
    */
    Serial.print (int(val));  //prints the int part
    Serial.print("."); // print the decimal point
    unsigned int frac;
    if(val >= 0)
        frac = (val - int(val)) * precision;
    else
        frac = (int(val)- val ) * precision;
    Serial.println(frac,DEC) ;
}

void setup()
{ 
   Serial.begin(9600); 

   #ifdef EDISON
       flowmeter = 12;
       pinMode(12, INPUT);
       attachInterrupt(12, flow, RISING); // Setup Interrupt
   #else
      flowmeter = 3;
      pinMode(flowmeter, INPUT);
       // see http://arduino.cc/en/Reference/attachInterrupt
       attachInterrupt(1, flow, RISING);
       sei();                             // Enable interrupts
   #endif

   currentTime = millis();
   cloopTime = currentTime;
} 

void loop ()    
{
   currentTime = millis();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {     
      cloopTime = currentTime;              // Updates cloopTime
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min. (Results in +/- 3% range)
      l_hour = ((float) flow_frequency  / (7.5 * 60.0)); // (Pulse frequency x 60 min) / 7.5Q = flow rate in L/hour 
      int hz = flow_frequency;
      flow_frequency = 0;                   // Reset Counter
      //Serial.println(flow_frequency);

      Serial.println(hz);
      total += l_hour;
      
      Serial.print("Rate:");
      printDouble(l_hour, 10000);
      Serial.println("Liters/Seconds");
      
      Serial.print("Total:");
      printDouble(total, 10);
      Serial.println("Liters");
   }
}

