// Demonstation of using a "Passive" pizzo buzzer like the one
// included in the Inland MEGA2560 DIY Kit sold by Micro Center

// The buzzer can be plugged directly into the GND and Digital Pin 11 by
// bending the legs only slightly.  The + leg must be plugged into the
// Digital Pin 11 (- to GND).

// The "active" buzzer sold in the same kit, will self-osscilate and produce
// a constant high freqency tone as long as power is applied to it.  It can
// be wired directly to a digital output as the above, but the output does
// not need to be turned on and off quicly to make it buzz.  It will buzz as
// long as the output is high (1), and stop when it's low (0);

// Curt Welch <curt@kcwc.com> 04-26-2017

void setup() {
  Serial.begin(9600);
  pinMode(11, OUTPUT);
}

void loop() {

  int pin = 11;
  
  tone(pin, 500, .5);
  tone(pin, 2000, .5);
}

void tone(int pin, int32_t hz, double seconds) {
  int32_t cycle_time_us;
  int32_t cycles;
  
  cycle_time_us = 1000000 / hz; // microseconds for one squre wave cyle of tone of hz freq
  cycles = 1000000 * seconds / cycle_time_us; // number cycles to create "seconds" of tone.

  for (int i = 0; i < cycles; i++) {
    digitalWrite(pin, 0);
    delayMicroseconds(cycle_time_us/2);
    digitalWrite(pin, 1);
    delayMicroseconds(cycle_time_us/2);
  }
}

