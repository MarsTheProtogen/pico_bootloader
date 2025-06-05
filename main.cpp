#include <Arduino.h>

/*
  PicoUSBtoUART.ino
  -----------------
  Turns a Raspberry Pi Pico (Arduino‐Pico core) into a USB ↔ UART(TTL) bridge
  with LED feedback whenever the USB serial is open or data is actively forwarded.

  Wiring (assuming UART0 on Pico):
    Pico GP0 (TX0)  →  STM32 PA10 (RX)
    Pico GP1 (RX0)  ←  STM32 PA9 (TX)

  Make sure STM32 BOOT0=HIGH to enter its UART bootloader.

  Onboard LED (GPIO 25) is ON whenever Serial is open / data is flowing.
*/

const uint32_t UART_BAUD = 115200; // STM32F1 bootloader default
const int LED_PIN = 25;            // Pico’s onboard LED

void setup()
{
  // Configure LED pin
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Initialize USB Serial (Serial) at a matching baud
  Serial.begin(UART_BAUD);

  // show the device is alive
  digitalWrite(LED_PIN, HIGH);

  // Initialize Pico UART0 (Serial1) for 115200 baud to STM32
  Serial1.begin(UART_BAUD);
}

void loop()
{
  // 1) If host → Pico has data, forward to STM32 UART
  if (Serial.available() > 0)
  {
    // LED stays on while forwarding
    int incoming = Serial.read();
    Serial1.write((uint8_t)incoming);
  }

  // 2) If STM32 (UART1) → Pico has data, forward back to host
  if (Serial1.available() > 0)
  {
    int incoming = Serial1.read();
    Serial.write((uint8_t)incoming);
  }

  // 3) If host disconnected (closed the USB‐Serial), turn LED off and wait until reopened
  if (!Serial)
  {
    digitalWrite(LED_PIN, LOW);
    // Wait for reconnection
    while (!Serial)
    {
      delay(10);
    }
    // Once reconnected, turn LED back on
    digitalWrite(LED_PIN, HIGH);
  }
}
