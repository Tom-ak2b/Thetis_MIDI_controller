  /** 
 * This example demonstrates how to group together two or more MIDI interfaces,
 * so you can send the MIDI output over both MIDI USB and 5-pin DIN MIDI, for 
 * example. MIDI input is received from all interfaces as well.
 * 
 * The @ref midi-tutorial has an entire section dedicated to MIDI routing:
 * @ref midi_md-routing.
 * Also have a look at the @ref MIDI_Pipes-Routing.ino example, the
 * @ref MIDI_Routing module and the @ref MIDI_Pipe documentation for more 
 * information about MIDI routing.  
 * Control Surface can be used as both a MIDI sink and a MIDI source.
 * 
 * When you call `Control_Surface.begin()`, it automatically connects itself to 
 * the default MIDI interface (@ref MIDI_Interface::getDefault()).  
 * If you want to route everything manually, you have to connect it before 
 * calling `Control_Surface.begin()`, or you have to disconnect the default 
 * pipes before connecting your own, using 
 * @ref Control_Surface_::disconnectMIDI_Interfaces().
 *
 * @boards  AVR USB, Nano Every, Due, Teensy 3.x
 * 
 * Connections
 * -----------
 * 
 * - A0: wiper of a potentiometer
 * 
 * Connect the left terminal of the potentiometer to ground, and the right one
 * to V<sub>CC</sub>.
 * 
 * Behavior
 * --------
 * 
 * - When you turn the potentiometer, you should receive MIDI Control Change
 *   events on both the Serial MIDI interface and the USB MIDI interface.
 * - When a MIDI Note event for middle C is received on either MIDI interface,
 *   the state of the built-in LED will change accordingly.
 * 
 * Mapping
 * -------
 * 
 * - None
 * 
 * Written by PieterP, 2019-08-22  
 * https://github.com/tttapa/Control-Surface
 */
#include <Control_Surface.h>

// Create two MIDI interfaces
USBMIDI_Interface usbmidi;
HardwareSerialMIDI_Interface serialmidi {Serial1, MIDI_BAUD};

// Create a MIDI pipe factory to connect the MIDI interfaces to Control Surface
BidirectionalMIDI_PipeFactory<3> pipes;
#define PIN_ENC_A   (3) // GPIO3
#define PIN_ENC_B   (2) // GPIO2
// Add some MIDI elements to show that the MIDI interfaces actually work
//CCPotentiometer potA {A0, MIDI_CC::General_Purpose_Controller_1};
CCPotentiometer potentiometers[] {
  {A0,        // Analog pin connected to potentiometer 1
   0x14},     // Controller number of the first potentiometer
  {A1,        // Analog pin connected to potentiometer 2
   0x15},     // Controller number of the second potentiomete  
};
CCRotaryEncoder enc {
  {PIN_ENC_A, PIN_ENC_B},           // pins
  MCU::V_POT_1,                     // MIDI address (CC number + optional channel)
  1,                                // optional multiplier if the control isn't fast enough
};
                                     
  
NoteLED led {LED_BUILTIN, 0x3C};

void setup() {
  RelativeCCSender::setMode(relativeCCmode::TWOS_COMPLEMENT);
  // Manually connect the MIDI interfaces to Control Surface
  Control_Surface | pipes | usbmidi;
  Control_Surface | pipes | serialmidi;
  serialmidi | pipes | usbmidi;
  // Initialize Control Surface _after_ connecting the interfaces
  Control_Surface.begin();
}

void loop() {
  Control_Surface.loop();
}

/*
 * The vertical pipe operator (|) is used to make a bidirectional connection 
 * between a MIDI sink or source and a MIDI pipe.
 * You can also use unidirectional pipes. These can be connected using the 
 * stream operators (<< and >>).
 * 
 * For example:
 * 
 *     MIDI_PipeFactory<2> pipes;
 *     ...
 *       Control_Surface >> pipes >> usbmidi;    // Output to usbmidi
 *       Control_Surface << pipes << serialmidi; // Input from serialmidi
 */