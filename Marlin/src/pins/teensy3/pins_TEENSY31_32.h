/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * Teensy 3.1 (MK20DX256) and Teensy 3.2 (MK20DX256) Breadboard pin assignments
 * Requires the Teensyduino software with Teensy 3.1 or Teensy 3.2 selected in Arduino IDE!
 * https://www.pjrc.com/teensy/teensyduino.html
 */

#if NOT_TARGET(IS_TEENSY_31_32)
  #error "Oops! Select 'Teensy 3.1' or 'Teensy 3.2' in 'Tools > Board.'"
#endif

#ifndef BOARD_INFO_NAME
  #define BOARD_INFO_NAME "Teensy3.2"
#endif

//
// Limit Switches
//
#define X_STOP_PIN                             2
#define Y_STOP_PIN                             9
#define Z_STOP_PIN                            13
#define I_STOP_PIN                            33
#define J_STOP_PIN                            33
#define K_STOP_PIN                            33

//
// Steppers
//
#define X_STEP_PIN                            32
#define X_DIR_PIN                             31
#define X_ENABLE_PIN                          29

#define Y_STEP_PIN                            30
#define Y_DIR_PIN                             29
#define Y_ENABLE_PIN                          29

#define Z_STEP_PIN                            11
#define Z_DIR_PIN                             14
#define Z_ENABLE_PIN                          16

#define I_STEP_PIN                             4
#define I_DIR_PIN                              3
#define I_ENABLE_PIN                           5

#define J_STEP_PIN                            11
#define J_DIR_PIN                             10
#define J_ENABLE_PIN                          12

//#define K_STEP_PIN                            28
//#define K_DIR_PIN                             27
//#define K_ENABLE_PIN                          31

#define E0_STEP_PIN                           26
#define E0_DIR_PIN                            25
#define E0_ENABLE_PIN                         24

#define E1_STEP_PIN                           26
#define E1_DIR_PIN                            25
#define E1_ENABLE_PIN                         24

//
// Heaters / Fans
//
#define HEATER_0_PIN                          27
#define HEATER_1_PIN                          28
//#define HEATER_BED_PIN                        21
//#ifndef FAN_PIN
//  #define FAN_PIN                             22
//#endif

//
// Temperature Sensors
//
#define TEMP_0_PIN                            6  // Analog Input - Extruder 2 => A2
#define TEMP_1_PIN                            5  // Analog Input
//#define TEMP_BED_PIN                          15  // Analog Input - Bed

//#ifndef FILWIDTH_PIN
//  #define FILWIDTH_PIN                         6  // Analog Input
//#endif

//
// Misc. Functions
//
//#define LED_PIN                               13
//#define SOL1_PIN                            28
//#define SDSS                                16  // 8

//
// LCD / Controller
//

/*
#if HAS_WIRED_LCD
  #define LCD_PINS_RS                         40
  #define LCD_PINS_ENABLE                     41
  #define LCD_PINS_D4                         42
  #define LCD_PINS_D5                         43
  #define LCD_PINS_D6                         44
  #define LCD_PINS_D7                         45
  #define BTN_EN1                             46
  #define BTN_EN2                             47
  #define BTN_ENC                             48
#endif
*/
