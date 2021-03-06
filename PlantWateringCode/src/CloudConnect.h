#ifndef _CLOUD_CONNECT_H_
#define _CLOUD_CONNECT_H_

#include "EnvData.h"
#include "credentials.h"
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT/Adafruit_MQTT.h>
#include <Adafruit_MQTT/Adafruit_MQTT_SPARK.h>

/* The cloud connect is used for all connections to Adafruit.io.
 * It includes:
 * - creating the necessary objects to connect effectively
 * - Re-establishing the connection
 * - Pushing envData objects
 * - publishing water time stamps
 * - fetching the adafruit dashboard button press
 */
class CloudConnect {
private:
    TCPClient myClient;
    Adafruit_MQTT_SPARK mqtt;
    Adafruit_MQTT_Subscribe buttonSubscriber;

public:
    // Create all my subobjects and subscribe my button
    CloudConnect() : myClient(),
                     mqtt(&myClient, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY),
                     buttonSubscriber(&mqtt, AIO_USERNAME "/feeds/forceWater") {
        mqtt.subscribe(&buttonSubscriber);
    }

    // Checks if the adafrit.io button was pressed.
    // It also does read all the subscriptions, so if the code 
    // freezes up for 10 seconds, and there were like 15 button presses,
    // Only one would be read (hopefully)
    bool buttonPressed() {
        bool wasPressed = false;
        Adafruit_MQTT_Subscribe *subscription;
        while ((subscription = mqtt.readSubscription(100))) {
            if (subscription == &buttonSubscriber) {
                int onState = atoi((char *)buttonSubscriber.lastread);
                if (onState) {
                    wasPressed = true;
                }
            }
        }
        return wasPressed;
    }


// Publishes an EnvData struct to the cloud
    void publish(EnvData *data) {
        static Adafruit_MQTT_Publish temperatureFeed(&mqtt, AIO_USERNAME "/feeds/temperature");
        static Adafruit_MQTT_Publish humidityFeed(&mqtt, AIO_USERNAME "/feeds/humidity");
        static Adafruit_MQTT_Publish soilMoistureFeed(&mqtt, AIO_USERNAME "/feeds/soilMoisture");
        static Adafruit_MQTT_Publish airQualityFeed(&mqtt, AIO_USERNAME "/feeds/airQuality");
        static Adafruit_MQTT_Publish dustFeed(&mqtt, AIO_USERNAME "/feeds/dust");

        reconnect();

        temperatureFeed.publish(data->temperature);
        humidityFeed.publish(data->humidity);
        soilMoistureFeed.publish(data->soilMoisture);
        airQualityFeed.publish(data->airQuality);
        dustFeed.publish(data->dustDensity);

        Serial.printf("Published data to cloud\n");
    }

    // Sends a 1 to the water stamp feed. Since timestamps are already included, don't needa worry about that
    void sendWaterStamp() {
        static Adafruit_MQTT_Publish waterStamp(&mqtt, AIO_USERNAME "/feeds/waterStamp");

        reconnect();

        waterStamp.publish(1);
    }


    // Reconnects to the cloud
    void reconnect() {

        int8_t ret;

        // Stop if already connected.
        if (mqtt.connected()) {
            return;
        }

        Serial.print("Connecting to MQTT... ");

        while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
            Serial.printf("%s\n", (char *)mqtt.connectErrorString(ret));
            Serial.printf("Retrying MQTT connection in 5 seconds..\n");
            mqtt.disconnect();
            delay(5000); // wait 5 seconds
        }
        Serial.printf("MQTT Connected!\n");
    }
};

#endif