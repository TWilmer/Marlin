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

#include "../core/serial.h"
#include "../inc/MarlinConfigPre.h"

#if ENABLED(ETHERNET_SUPPORT)

#include "ethernet.h"

EthernetServer server(23);    // telnet server

EthernetClient telnetClient;  // connected client

enum linkStates {UNLINKED, LINKING, LINKED, CONNECTING, CONNECTED, NO_HARDWARE} linkState;

#ifdef __IMXRT1062__
  static void teensyMAC(uint8_t *mac) {
    uint32_t m1 = HW_OCOTP_MAC1;
    uint32_t m2 = HW_OCOTP_MAC0;
    mac[0] = m1 >> 8;
    mac[1] = m1 >> 0;
    mac[2] = m2 >> 24;
    mac[3] = m2 >> 16;
    mac[4] = m2 >> 8;
    mac[5] = m2 >> 0;
  }

#else
  byte mac[] = { MAC_ADDRESS };
#endif

IPAddress ip;
IPAddress myDns;
IPAddress gateway;
IPAddress subnet;

bool ethernet_hardware_enabled = false; // from EEPROM
bool have_telnet_client = false;

void ethernet_init() {
  if (!ethernet_hardware_enabled) return;

  SERIAL_ECHO_MSG("Starting network...");

  // initialize the Ethernet device
  #ifdef __IMXRT1062__
    uint8_t mac[6];
    teensyMAC(mac);
  #endif
  if (!ip) { Ethernet.begin(mac); }  // use DHCP
  else {
    if (!gateway) {
      gateway = ip;
      gateway[3] = 1;
      myDns = gateway;
      subnet = IPAddress(255,255,255,0);
    }
    if (!myDns) myDns = gateway;
    if (!subnet) subnet = IPAddress(255,255,255,0);
    Ethernet.begin(mac, ip, myDns, gateway, subnet);
  }

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    SERIAL_ERROR_MSG("Ethernet hardware was not found.  Sorry, can't run without hardware. :(");
    linkState = NO_HARDWARE;
    return;
  }

  linkState = UNLINKED;

  if (Ethernet.linkStatus() == LinkOFF) {
    SERIAL_ERROR_MSG("Ethernet cable is not connected.");
  }

  return;

}

bool newClient=0;
void ethernet_check() {
  if (!ethernet_hardware_enabled) return;

  switch (linkState) {
    case NO_HARDWARE:
      break;

    case UNLINKED:
      if (Ethernet.linkStatus() == LinkOFF) {
        break;
      }
      SERIAL_ECHOLN("Ethernet cable connected");
      server.begin();
      linkState = LINKING;
      break;

    case LINKING:
      if (!Ethernet.localIP()) break;

      SERIAL_ECHO("Successfully started telnet server with IP ");
      MYSERIAL0.println(Ethernet.localIP());

      linkState = LINKED;
      break;

    case LINKED:
      if (Ethernet.linkStatus() == LinkOFF) {
        SERIAL_ERROR_MSG("Ethernet cable is not connected.");
        linkState = UNLINKED;
        break;
      }
      telnetClient = server.accept();
      if (telnetClient) {
        linkState = CONNECTING;
      }
      break;

    case CONNECTING:
      telnetClient.println("Marlin " SHORT_BUILD_VERSION);
      #if defined(STRING_DISTRIBUTION_DATE) && defined(STRING_CONFIG_H_AUTHOR)
        telnetClient.println(
          " Last Updated: " STRING_DISTRIBUTION_DATE
          " | Author: " STRING_CONFIG_H_AUTHOR
        );
      #endif
      telnetClient.println("Compiled: " __DATE__);

      SERIAL_ECHOLN("Client connected");
      have_telnet_client = true;
      linkState = CONNECTED;
      break;

    case CONNECTED:
      if (telnetClient && !telnetClient.connected()) {
        SERIAL_ECHOLN("Client disconnected");
        telnetClient.stop();
        have_telnet_client = false;
        linkState = LINKED;
      }
      if (Ethernet.linkStatus() == LinkOFF) {
        SERIAL_ERROR_MSG("Ethernet cable is not connected.");
        if (telnetClient) telnetClient.stop();
        linkState = UNLINKED;
      }
      break;

    default:
      break;
  }
    return;
}

#endif // ETHERNET_SUPPORT