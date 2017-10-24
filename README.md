Sunlight
===================

A LED lighting project based on actual **daylight measurements** and calculations.
> **[Fadecandy](https://github.com/scanlime/fadecandy)** would be a ideal LED driver platform in terms of transition smoothness and color accuracy, but it doesn't support RGBW yet. Let's keep things abstract, use Arduino for now and upgrade later on.

### What is "Sunlight" about?
The idea is to realtime measure colors and intensity of daylight, shining through your windows. Then boost it inside in a subtile manner via a long, digitally controlled NeoPixel LED stripe of SK6812 RGBW LEDs. The stripe is hung about 30cm from the ceiling and pointing towards it, so we should get a decent widespread indirect lightsource. The calculation of colors is both measured from the sensors as calculated theoretically. Sunrise and sunset should be natural and immersive so that the walls seem to *fade away*. We further will be able to guess the actual daytime via the brightest spot on the ceiling. 

### ToDo
- Reorganize Project and combine the various modules
- ✓ Read RGB values from sensor
- ✓ Calculate color temperature
  1. ✓ Map RGB values to their XYZ counterparts of the CIE 1931 color space
  2. ✓ Calculate the chromaticity co-ordinates
  3. ✓ Use McCamy's formula to determine the CCT (Correlated color temperature)

- Sun calculations
  1. Calculate the sun's actual position on the sky as a percentage between sunrise and sunset. Use date, daytime, coordinates and meters above sea level
  2. ✓ Map the calculated position relative to the number of pixels on the stripe (from sunrise 0% to sunset 100%)
  We're assuming that the LED stripe is orientated east to west (or vice versa) to simulate the movement of the star during the day.
  3. ✓ The "width" of the sun in pixels is a percentage of the total pixel length of the stripe
  4. ✓ The intensity of a actual sun pixel should be calculated via cosine: -π/2 (start) to 0 (spot) to π/2 (end)
