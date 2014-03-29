### Coffee Pot ###

This repo is for an Arduino controller for refilling the water tank in a Keurig style coffee pot.

It uses:

 * Float switch input (SENSOR) to detect low water levels.

   This is a float sensor in the tank registered to read HIGH when water is low. This means a broken connection will
   not trigger water flow. A 10k pull down resister is used with this sensor.
 
 * Water valve controlled by a single pin (VALVE) to fill the tank.

   This pin controls a reed relay that connects 9 Volts to the valve's selinoid. This same 9 volt supply powers the
   arduino.

 * Status LED (INDICATOR).

   This standard LED uses a 330 resister for the usual reasons. It's positioned behind the water tank so it can 
   be seen through the clear plastic and water. Using red offsets the Keurig's built in blue nicely.
