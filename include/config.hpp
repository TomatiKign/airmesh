#ifndef CONFIG_H
#define CONFIG_H

/**
 * @brief defines the adafruit io username and key the microcontroller will send to
 * @note this part is edited to the key found on the personal adafruit io profile
 */

#define IO_USERNAME  "aspiringLich"
#define IO_KEY       "aio_VysO9970FyMbi89gwdjjfKuPUUxQ"

/**
 * @brief defines the wifi connection for the microcontroller
 * @warning this MUST work for anything to upload to adafruit io
 */

#define WIFI_SSID "tomatoketchup"
#define WIFI_PASS "ketchuptomato"

#include "AdafruitIO_WiFi.h"

/**
 * @brief sets up adafruit io to connect through WiFi
 * @note if using ethernet look into documentation for section to use in this file
 */

#if defined(USE_AIRLIFT) || defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE) ||         \
    defined(ADAFRUIT_PYPORTAL)
// Configure the pins used for the ESP32 connection
#if !defined(SPIWIFI_SS) // if the wifi definition isnt in the board variant
// Don't change the names of these #define's! they match the variant ones
#define SPIWIFI SPI
#define SPIWIFI_SS 10 // Chip select pin
#define NINA_ACK 9    // a.k.a BUSY or READY pin
#define NINA_RESETN 6 // Reset pin
#define NINA_GPIO0 -1 // Not connected
#endif
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS, SPIWIFI_SS,
                   NINA_ACK, NINA_RESETN, NINA_GPIO0, &SPIWIFI);
#else
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
#endif

#endif