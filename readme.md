# Sleeping Dragon Sign 

Arduino project that illuminates a "Warning, Sleeping Dragon" sign with three different strands of NeoPixels. 

1. 2 NeoPixles to illuminate the Warning symbols
2. 3 NeoPixels to illuminate the "Warning!" text
3. 5 NeoPixels to illuminate the "Sleeping Dragon" text

I'm working on a sleeping dragon in a mailbox project for Halloween this year. As part of this project, I wanted a sign to set outside of the mailbox to warn people not to get too close. Of course, with that plan solidified, I enhanced it with a motion sensor and some LEDs. 

![Sleeping Dragon Sign](images/image-01.jpg)

In normal mode, the warning symbols illuminate alternately, the "warning" text fades up and down in Red, and the "baby dragon sleeping" text illuminates in White.  When the PIR sensor detects someone nearby, everything blinks until the person moves away. 

Next steps are:

1. Add a power switch to the hardware
2. Add a battery to see if this will run on battery power during halloween
3. Build an enclosure for it.

Stay tuned.
