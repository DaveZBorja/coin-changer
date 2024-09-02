# Coin Changer Machine

## Overview

This project implements a coin changer machine using an Arduino. The machine accepts paper bills and provides change using servos to dispense coins of different denominations. It uses an LCD display and a keypad for user interaction.

**Warning:** 
* When I wrote this code, only God and I knew how it worked. Now, only God knows it!*
* If you are trying to optimize this routine and it fails (most surely), please increase this counter as a warning for the next person:*
*`total_hours_wasted_here = 96`*

By: Dave Borja

## Components

- Arduino board
- LCD display (16x2) with I2C
- Keypad (4x4)
- 3 Servos
- Relay
- Various resistors and wiring

## Libraries

- `LiquidCrystal_I2C`: For LCD display control.
- `Keypad`: For keypad input.
- `Wire`: For I2C communication.
- `SPI`: For communication with peripherals.
- `Servo`: For controlling servos.

## Pin Configuration

- **Cash Input**: Pin 2 (Digital Input)
- **LCD**: I2C address 0x27
- **Servos**: Pins 11, 12, 13
- **Relay**: Pin A0 (Digital Output)
- **Keypad**: Rows (3, 4, 5, 6) and Columns (7, 8, 9, 10)

## Usage

1. **Setup**: 
   - The machine initializes and displays a splash screen on the LCD.
   - A relay is turned on to start the system.
   - Servos are attached and set to their initial positions.

2. **Operation**:
   - Insert a paper bill.
   - The machine will recognize the bill and update the amount.
   - When the total amount reaches 100 PHP, the machine will prompt you to select a denomination (10, 20, 50 PHP) or custom options.

3. **Selection**:
   - Use the keypad to select a coin denomination or enter custom amounts.
   - The servos will dispense the required number of coins.
   - The LCD will show the transaction details and a thank you message.

4. **Reset**:
   - After each transaction, the machine resets to the initial state and displays a prompt to insert a new bill.

## Functions

- `setup()`: Initializes the machine, sets up components, and displays a splash screen.
- `loop()`: Main function that handles bill insertion and amount accumulation.
- `displays()`: Resets the display to prompt for bill insertion.
- `changer()`: Handles coin selection and dispenses the coins.
- `Aselect()`, `Bselect()`, `Cselect()`, `Dselect()`: Functions to handle different coin denominations and custom options.
- `displaycustom()`, `displaycustomB()`: Display functions for custom coin selection.

## Notes

- Make sure to wire the components correctly according to the pin configuration.
- Adjust the `delay()` times in the servo control functions as needed for your specific hardware.
- Ensure the servos are properly calibrated to dispense the correct amount of coins.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Author

Dave Borja


