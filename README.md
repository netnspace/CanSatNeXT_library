# CanSatNeXT library

CanSat NeXT is an ESP32 development board developed for CanSat competitions in collaboration with ESERO Finland. This library provides easy access to the hardware resources of the development board. The hardware resources include a barometer, an inertial measurement unit, an SD card and a point-to-point communication radio. The library supports both the satellite and the receiver. The receiver can be similar to the CanSat NeXT board but also any other ESP32 development board.

# Getting started

This is an Arduino library, designed to be primarily used through the Arduino IDE. Here are the basic steps to get started with the library:

1. Install the Arduino IDE: Download and install the Arduino IDE from the official website if you haven't already.

2. Install ESP32 Support: 
   - Open the Arduino IDE.
   - Navigate to Tools -> Board -> Boards Manager.
   - In the search bar, type "ESP32" and find the option provided by Espressif.
   - Click on the "Install" button to add ESP32 support to your Arduino IDE.

3. Install the CanSatNeXT Library:
   - In the Arduino IDE, go to Sketch -> Include Library -> Manage Libraries.
   - In the search bar, type "CanSatNeXT" and find the corresponding library.
   - Click on the "Install" button to install the library. If the Arduino IDE asks if you want to install with dependencies - click yes.
   - Alternatively, you can manually add the library by downloading this repository and saving it into the Arduino libraries folder on your computer.

4. Connect the CanSatNeXT Board:
   - Plug the CanSatNeXT board into your PC using a USB cable.
   - Your PC should automatically detect the board, but if it doesn't, you may need to install the necessary drivers.
   - Drivers can be found on the Silicon Labs website: [https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)
   - For additional help with setting up the ESP32, refer to the following tutorial: [https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/establish-serial-connection.html](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/establish-serial-connection.html)

5. Get Started with the CanSatNeXT Board:
   - Once you have installed the Arduino IDE, ESP32 support, and the CanSatNeXT library (and possibly the drivers), you are ready to start using the board.
   - To explore the use of the various hardware resources, go to File -> Examples -> CanSatNeXT in the Arduino IDE.

# Pinout

Here is the full list of pins used by CanSat NeXT board. The internal use refers to the pin being used for the on-board resources, and extension refers to the pins having been routed to the extension interface. Some pins, those for I2C and SPI, are used both internally and externally. The library name refers to a macro name, which can be used instead of the pin number when CanSatNeXT library has been included.

| Pin Number | Library name | Note                                                    | Internal/External   |
|------------|--------------|---------------------------------------------------------|---------------------|
|          0 | BOOT         |                                                         | Used internally     |
|          1 | USB_UART_TX  | Used for USB                                            | Used internally     |
|          3 | USB_UART_RX  | Used for USB                                            | Used internally     |
|          4 | SD_CS        | SD card chip select                                     | Used internally     |
|          5 | LED          | Can be used to blink on-board LED                       | Used internally     |
|         12 | GPIO12       |                                                         | Extension interface |
|         13 | MEAS_EN      | Drive high to enable LDR and thermistor                 | Used internally     |
|         14 | GPIO14       | Can be used to read if SD-card is in place              | Used internally     |
|         15 | GPIO15       |                                                         | Extension interface |
|         16 | GPIO16       | UART2 RX                                                | Extension interface |
|         17 | GPIO17       | UART2 TX                                                | Extension interface |
|         18 | SPI_CLK      | Used by the SD-card, also available externally          | Both                |
|         19 | SPI_MISO     | Used by the SD-card, also available externally          | Both                |
|         21 | I2C_SDA      | Used by the on-board sensors, also available externally | Both                |
|         22 | I2C_SCL      | Used by the on-board sensors, also available externally | Both                |
|         23 | SPI_MOSI     | Used by the SD-card, also available externally          | Both                |
|         25 | GPIO25       |                                                         | Extension interface |
|         26 | GPIO26       |                                                         | Extension interface |
|         27 | GPIO27       |                                                         | Extension interface |
|         32 | GPIO32       | ADC                                                     | Extension interface |
|         33 | GPIO33       | ADC                                                     | Extension interface |
|         34 | LDR          | ADC for the on-board LDR                                | Used internally     |
|         35 | NTC          | ADC for the thermistor                                  | Used internally     |
|         36 | VDD          | ADC used to monitor supply voltage                      | Used internally     |
|         39 | BATT         | ADC used to monitor battery voltage                     | Used internally     |

The picture below shows the pins for using the extension header for adding external electronics to the board.

![image description](https://lh3.googleusercontent.com/drive-viewer/AK7aPaDrKPQzTgqN-vACXaDWKlyC1ZMQ5sLF344OpBNhWeb7bTWGEP2YD6sUS9N-EKQ_dZ4yIQjQIWknBSTpaJIGGBf7yUxEAg=s1600)

# License

This library and the CanSat NeXT board are developed by Samuli Nyman, in collaboration with ESERO Finland and Arctic Astronautics Oy. The development is also supported by the Finnish Physical Society. This software library is licensed under the MIT license.

# Contribution

If you wish to contribute to the library or if you have feedback, please contact me through samuli@kitsat.fi or start a GitHub issue. You are also welcome to create a pull request.

