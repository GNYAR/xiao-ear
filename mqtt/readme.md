# MQTT

Use the client library, [PubSubClient](https://pubsubclient.knolleary.net/), for MQTT communication.

In Arduino IDE, search and install `PubSubClient` with the library manager. Or check the website https://pubsubclient.knolleary.net/.

Here is an example to use the library. [`mqtt.ino`](mqtt.ino)

For this project, we need to publish KWS result in [`kws.ino`](../kws/kws.ino) and subscribe it in [`display.ino`](../display/display.ino).
