//#include <Arduino.h>
#include <Arduino.h>


// Grove TM1637 display module connection pins (Digital Pins)
#define CLK 2
#define DIO 4


volatile int flow_frequency; // Measures flow sensor pulses
float vol = 0.0,l_minute;
unsigned char flowsensor = 3; // YF-S201 water sensor input
unsigned long currentTime;
unsigned long cloopTime;


void flow () // Interrupt function
{
   flow_frequency++;
}

void setup()
{
   
   pinMode(flowsensor, INPUT);
   digitalWrite(flowsensor, HIGH);
   Serial.begin(9600);

   attachInterrupt(digitalPinToInterrupt(flowsensor), flow, RISING); // Setup Interrupt

   Serial.println("Water Flow Meter");

   currentTime = millis();
   cloopTime = currentTime;
}

void loop ()
{
   currentTime = millis();
   
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {
    cloopTime = currentTime; // Updates cloopTime
    if(flow_frequency != 0){
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      l_minute = (flow_frequency / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour

      Serial.print("Rate: ");
      Serial.print(l_minute);
      Serial.println(" L/M");

      l_minute = l_minute/60;
      vol = vol + l_minute;

      Serial.print("Vol:");
      Serial.print(vol);
      Serial.println(" L");

      flow_frequency = 0; // Reset Counter

      Serial.print(l_minute, DEC); // Print litres/hour
      Serial.println(" L/Sec");

     
    }
    else {
      Serial.println(" flow rate = 0 ");

      Serial.print("Rate: ");
      Serial.print( flow_frequency );
      Serial.println(" L/Min");

      Serial.print("Rate: ");
      Serial.print( flow_frequency / 60000 );
      Serial.println(" Cubic Meters/Sec");


      Serial.print("Vol:");
      Serial.print(vol);
      Serial.println(" L");
    }
   }
}

//
//volatile int flow_frequency; // Measures flow sensor pulses
//float vol = 0.0,l_minute;
//unsigned char flowsensor = 3; // YF-S201 water sensor input
//unsigned long currentTime;
//unsigned long cloopTime;
//
//
//void flow () // Interrupt function
//{
//   flow_frequency++;
//}
//
//void setup()
//{
//   
//
//   pinMode(flowsensor, INPUT);
//   digitalWrite(flowsensor, HIGH);
//   Serial.begin(9600);
//
//   attachInterrupt(digitalPinToInterrupt(flowsensor), flow, RISING); // Setup Interrupt
//
//   Serial.println("Water Flow Meter");
//
//   currentTime = millis();
//   cloopTime = currentTime;
//}
//
//void loop ()
//{
//   currentTime = millis();
//   
//   // A cada segundo é mostrado litros/hora
//   if(currentTime >= (cloopTime + 1000))
//   {
//    cloopTime = currentTime; // Update no cloopTime
//    if(flow_frequency != 0){
//      // Frequencia de pulso (Hz) = 7.5Q, Q é o fluxo em L/min.
//      l_minute = (flow_frequency / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
//
//      Serial.print("Rate: ");
//      Serial.print(l_minute);
//      Serial.println(" L/M");
//
//      l_minute = l_minute/60;
//      vol = vol + l_minute;
//
//      Serial.print("Vol:");
//      Serial.print(vol);
//      Serial.println(" L");
//
//      flow_frequency = 0; // Reset Counter
//
//      Serial.print(l_minute, DEC); // Print litres/hour
//      Serial.println(" L/Sec");
//    } 
//    else
//    {
//      Serial.println(" flow rate = 0 ");
//
//      Serial.print("Rate: ");
//      Serial.print( flow_frequency );
//      Serial.println(" L/M");
//
//     
//
//      Serial.print("Vol:");
//      Serial.print(vol);
//      Serial.println(" L");
//
//      
//      // 1 Litros por minuto [l/min] = 0,000 016 666 666 666 667 Metros cúbicos por segundo [m³/s]
//    }
//   }
//}
