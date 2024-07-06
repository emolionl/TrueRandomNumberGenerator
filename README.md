# True Random Number Generator with Arduino or ESP32, I use ttgo esp32 with display embedded 

A True Random Number Generator (TRNG) exploits physical processes to produce numbers that are completely unpredictable.

There are many ways to get TRUE Random Number Generators. This documentation focuses on how to utilize chip ATECC608B to achieve this.
## I use platform io
you can watch installation of platfrom io on next video: https://youtu.be/5edPOlQQKmo?si=6JyaDQRtyCgFJ0Y5
## Getting Started

To begin using the ATECC608B chip for generating true random numbers, follow the steps outlined below. These steps include hardware setup, wiring instructions, and software configuration.

### Hardware Requirements

To set up your TRNG, you will need the following hardware components:

1. **ESP32 Development Board with TFT Display** - [LilyGO TTGO T-Display V1.1 ESP32 with 1.14 Inch TFT Display](https://www.tinytronics.nl/nl/development-boards/microcontroller-boards/met-wi-fi/lilygo-ttgo-t-display-v1.1-esp32-met-1.14-inch-tft-display)
2. **Cryptography Co-processor** - [ATECC608B-SSHDA Cryptography Co-processor with AES-128, SHA-256, 2.5-5V, SO-8](https://www.reichelt.de/it/en/cryptography-co-processor-aes-128-sha-256-2-5-5-v-so-8-atecc608b-sshda-p307148.html?CCOUNTRY=446&LANGUAGE=en&&r=1)

### Hardware Setup

1. **Wiring Instructions**:
   - A detailed wiring guide is available in this video tutorial: [Wiring Tutorial for ATECC608B with ESP32](https://www.youtube.com/watch?v=vFqVDmxOQjQ&ab_channel=Rudolf). Ensure to follow the instructions carefully to connect your ESP32 development board with the ATECC608B chip.
   - **Note**: A photo guide for all necessary wire connections will be added soon.

### Software Configuration

1. **Install and Lock Configuration**:
   - Navigate to the provided repository and run the `ATECC608B-Install-LOCK-Config` script. This script will install necessary libraries and lock the configuration of the ATECC608B chip, which is a crucial step for security.

2. **Generating Basic Random Numbers**:
   - After successfully locking the configuration, you can start generating true random numbers. Go to the repository and run the `ATECC608B-basic-random` script to begin generating random numbers.

## Additional Resources

- For more information on the ATECC608B chip and its capabilities, refer to the [official datasheet](https://www.microchip.com/wwwproducts/en/ATECC608B).

- If you encounter any issues during the setup or operation, please consult the [FAQ section](#) or reach out to the community forums for assistance.

Thank you for choosing to work with the ATECC608B chip for your true random number generation needs. Follow these steps carefully to ensure a successful setup and operation.
