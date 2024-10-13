# Keyword Spotting

Building a Keyword Spotting (KWS) model and deploying it on the XIAO ESP32S3 Sense and publish the result with MQTT.

1. Initiate a new project at [Edge Impulse](https://edgeimpulse.com/).
2. Upload the sound files. (`Data acquisition > Add data > Upload data`)
3. Split the data into 1s samples to be compatible. (`three dots after the sample name > Split sample`)
4. Creating Impulse (Pre-Process / Model definition) (`Impulse design > Create impulse`)

   1. take the data points with a 1-second window, augmenting the data, sliding that window each 500ms and set `zero-pad data`.
   2. Add `Audio (MFCC)` to processing block.

      Each 1-second audio sample should be pre-processed and converted to an image (for example, 13 x 49 x 1). We will use MFCC, which extracts features from audio signals using Mel Frequency Cepstral Coefficients, which are great for the human voice.

   3. Add `Classification` to learning block.

5. Create the images and generate features. (`Impulse design > MFCC`)

6. Set the convolution neural network (CNN) and train model. (`Impulse design > Classifier`)

7. Deploy to XIAO ESP32S3 Sense. (`Impulse design > Deployment`)

   1. Select the option `Arduino library`.
   2. Select the non-EON version complier. (`TensorFlow Lite`)
   3. Select `Quantized (int8)`.
   4. Click `Build` button. (a zip file will be downloaded)
   5. Download and unzip the [ESP-NN](https://github.com/Mjrovai/XIAO-ESP32S3-Sense/blob/main/ESP-NN.zip).
   6. Replace the ESP-NN folder in the zip file downloaded by the Edge Impulse. (`src/edge-impulse-sdk/porting/espressif/ESP-NN`)
   7. Add zip library in Arduino IDE. (`Sketch > Include Library > Add .ZIP Library...`)
   8. Update the library name in `kws.ino`.

8. MQTT Communication

   Use the client library, [PubSubClient](https://pubsubclient.knolleary.net/), for MQTT communication.

   1. Search and install `PubSubClient` with the library manager in Arduino IDE.
   2. Replace the WiFi and MQTT parameters in `kws.ino`.

9. Compile and upload.

Next: [Display](/display/readme.md)
