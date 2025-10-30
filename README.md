# Thetis_MIDI_controller
Control Thetis or deskHPSDR with your own Midi Controller

This project was inspired by another ham, JI1UDD, who had made up his controller with a tuning knob and two switches:
https://github.com/ji1udd/VFO-Controller
From his inspiration I first did a controller with one encoder, two potentiometers and 12 switches. 
What I also learned from his project was that the midi library he used was awesome. https://github.com/tttapa/Control-Surface
Through this library, all things midi became very easy to use.

Among my displays I once had big dreams for my Nextions before I realized they weren't that easy to program. With the Control-Surface library it became super simple to make up a touch screen midi controller
The first one is a 2.5" tochscreen shown here with a 3D printed case found on Thingaverse:

![image](https://github.com/user-attachments/assets/633e06d2-1708-4142-8cc8-09cb2b221b51)
![image](https://github.com/user-attachments/assets/7d6dc8c3-49a5-467d-95a8-bd4e4d9854d2)

For my project I used an Arduino Micro Pro, Nextion 2.5" display, one rotary encoder, and two 10K pots.
You will need the Nextion Editor (Windows only), Arduino IDE and the above mentioned Control-Surface library.
Any processor can be used as long as you can make it appear to Windows as a USB MIDI device. Try getting a Micro Pro with a USB C port so you can power the larger Nextion displays directly from the board.

Into the Nextion "button push" event you are going to enter a midi NOTE ON and into the "button release" event, a NOTE OFF.
The Control-Surface library is going to inform Thetis that a MIDI event has been sent. Thetis, through its Midi interface, is going to tell you what note number it just received and allow you to map that note to a button on the Thetis interface.
An example of that for the mute button:

under the "Touch Press Event": 

printh 91

printh 11

printh 7F


under the "Touch Release Event":

printh 81

printh 11

printh 0

Which is a midi note on event and a midi note off event with the middle printh, the midi note.

note: On the main display window, open the tab "Program.s" and add: baud=31250//Configure baudrate


