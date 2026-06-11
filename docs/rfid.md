# Arduino / RFID wiring

QtVoyager reads RFID cards through an **Arduino** connected over USB serial.
The desktop app auto-detects the board by USB vendor/product id, opens the
port at **9600 baud, 8N1, no flow control**, and exchanges card data with the
sketch.

## How it works

1. `Arduino::connect_arduino()` scans `QSerialPortInfo::availablePorts()` for
   the configured Arduino Uno vendor/product id and opens it at 9600 baud.
2. When a card is tapped, the sketch sends the card serial (the app reads the
   **last 11 characters** as the `RFID_CARD` value).
3. `MainWindow::update_label()` looks the card up in `VOYAGEURS` using a
   **parameterized** query and writes the matched traveler info back to the
   Arduino (e.g. to drive an LCD/LED).

!!! note "Vendor / product id"
    The expected ids live in `config/arduino.h` (`arduino_uno_vendor_id`,
    `arduino_uno_producy_id`). Adjust them for your board (a genuine Uno is
    `0x2341`; clones with a CH340 differ).

## Hardware

Typical setup with an **MFRC522** RC522 RFID reader (SPI):

| RC522 pin | Arduino Uno pin |
|-----------|-----------------|
| SDA (SS)  | D10             |
| SCK       | D13             |
| MOSI      | D11             |
| MISO      | D12             |
| RST       | D9              |
| 3.3V      | 3.3V            |
| GND       | GND             |

!!! warning
    The RC522 is **3.3 V** — do not power it from 5 V.

## Sketch contract

The Arduino sketch should:

- Print the card UID/serial over `Serial` at **9600 baud** when a card is read,
  ending with a newline; the app keeps the last 11 characters.
- Optionally read a line back from the app (the traveler name) and display it.

## Permissions (Linux)

Add your user to the serial group so the app can open the port:

```bash
sudo usermod -aG dialout "$USER"   # log out / back in
```
