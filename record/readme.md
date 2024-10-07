# Record

Save recorded sound samples as .wav audio files to a microSD card.

1. To use the onboard SD Card reader, set PSRAM to OPI PSRAM.

   `Tools > PSRAM > OPI PSRAM`

2. Compile and upload `record.ino` to XIAO ESP32S3 Sense.
3. Open the serial monitor and follow the hints to record the keywords.

   1. Enter with the label name
   2. Send `rec` for starting recording label
   3. Recording.

      Repeat your keywords several times during each ten-second recording session. (there needs to be some spacing between keywords.)

   4. Send rec for a new sample or enter a new label.

The files will be saved on the SD card as `label.1.wav`, `label.2.wav`, `label.3.wav`, etc.

Next: Keyword Spotting
