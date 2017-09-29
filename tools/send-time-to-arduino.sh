#!/bin/bash

# Shell script that sends the actual UNIX time to your Arduino
# - You need an arduino-serial binary working & in your PATH
#   1) https://github.com/todbot/arduino-serial
#   2) http://todbot.com/blog/2013/04/29/arduino-serial-updated

TZ_adjust=+2;       # Adjust Timezone.
actualTimeInSeconds=$(echo "T$(($(date +%s)+60*60*$TZ_adjust))")

# Print time
echo "UTC ${TZ_adjust}h time in seconds: ${actualTimeInSeconds}"

# Send time
arduino-serial -b 9600 -p /dev/tty.usbmodem* -s "$actualTimeInSeconds"

# Be nice
if [ $? == 0 ]
  then
    echo "Done."
fi
