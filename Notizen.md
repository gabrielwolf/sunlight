Sunlight - Notizen
==================

# Ideen
## Weicher FadeIn mit Zufallswerten
## App-Steuerung: man kann mehrere "Sonnen" (Zonen) durch tippen + ziehen auf den Streifen legen

# ToDo
## Testen, ob man mit Global Brightness noch viel dunkleres Licht machen kann (30min)
## Tests für den bisherigen Code schreiben (evtl. nach Portierung und neuer Entw.Umg.!)
## Dämmerungsproblem
   - Die Morgenröte kommt VIEL zu früh (> evtl. morgenröte trennen und sonnengröße wieder wie früher
                                        > alternative: genaue zeiten von dämmerung und aufgang
                                          über die andere bibliothek einbinden)
   - Die Sonnenaufgangszeit ist um die hälfte der sonne verschoben, inkorrekt!
   - indirektes licht sowieso messen, oder von 16000K langsam runter.
     bei 8:10 waren wir mit 12500 gar nicht schlecht (aufgang war 8:13)

## Portierung auf ESP8266 (1 Tag)
  - Sensor
    - Schaltung testen
    - Kabelverbindungen löten
  - LEDs (wenn Logic Level Shifter da ist)
    - Schaltung testen
```
Flickering problems
With the Adafruit Library brightness values down to 1 are no problem. With NeoPixelBus and NeoPixelBrightnessBus I get a flickering below color values of 80. The more low, the more flickering.

```

# Laufend

# Done

- UNIX time
  T1511341223
  11/22/2017 @ 9:00am (UTC)
  9:00:23 22 11 2017

- My coordinates (Google Maps) 52.5319032, 13.3306613

- Read/Write to the serial bus:
  $ screen /dev/cu.usbmodem641 115200

- HowTo Build & Upload & Send actual time to the arduino in one keystroke in Sublime Text
1. Install Sublime Text Plugin "arduino-cli" (Arduino Build System) via PackageControl
   https://github.com/jacobrosenthal/arduino-cli
2. Install PackageResourceViewer via PackageControl
3. Edit arduino-cli.py (Version 16 Apr 2017) via PackageResourceViewer and add at the very bottom 
        options['shell_cmd'] = "/Users/jibazee/Downloads/Tools/send-time-to-arduino.sh"
        self.window.run_command("exec", options)
    Use the path where you put the script from tools/
4. Download / Make arduino-serial (https://github.com/todbot/arduino-serial/)
5. Select arduino-cli from Menu / Tools / Build System
6. Select Menu / Tools / arduino-cli / Open User Settings and add (in case of Mac)
   {
   "path": "/Applications/Arduino.app/Contents/MacOS/Arduino",
   "board": "arduino:avr:uno",
   "port": "/dev/tty.usbmodem461",
   } 
   Where /dev/tty.usbmodem461 must point to your _actual_ Arduino port. The number changes, if you reconnect the Arduino.
6. Now you can build & upload & send time an open *.ino file with [cmd] + [b]