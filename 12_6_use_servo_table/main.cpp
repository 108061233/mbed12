#include "mbed.h"

using namespace std::chrono;

#define CENTER_BASE 1500

BufferedSerial pc(USBTX, USBRX);
DigitalIn encoder(D10);
PwmOut servo(D11);

Timer t;
Ticker encoder_ticker;

volatile int steps;
volatile int last;

void servo_control(float speed) {
   if (speed > 200)       speed = 200;
   else if (speed < -200) speed = -200;

   servo=(CENTER_BASE + speed)/20000.0f;
}

void encoder_control() {
   int value = encoder;
   if(!last && value) steps++;
   last = value;
}


int main() {

   pc.set_baud(9600);

   encoder_ticker.attach(&encoder_control, .01);

   servo.period_ms(20);

   int i = 0;
   while(i < 5) {

   //TODO: revise this value according to your result
   servo_control(-30.469);

   steps = 0;
   t.reset();
   t.start();

   ThisThread::sleep_for(1000ms);
   float time = t.read();

   printf("%1.3f\r\n", (float) steps * 6.5 * 3.14 / 32 / time);
   i++;
   }

   i = 0;
   while(i < 4) {

   //TODO: revise this value according to your result
   servo_control(45.3);

   steps = 0;
   t.reset();
   t.start();
   
   ThisThread::sleep_for(1200ms);
   float time = t.read();

   printf("%1.3f\r\n", (float) steps * 6.5 * 3.14 / 32 / time);
   i++;
   }
   servo_control(0);
}