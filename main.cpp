/*
 * main.cpp
 * Laos Controller, main function
 *
 * Copyright (c) 2011 Peter Brier & Jaap Vermaas
 *
 *   This file is part of the LaOS project (see: http://wiki.laoslaser.org)
 *
 *   LaOS is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   LaOS is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with LaOS.  If not, see <http://www.gnu.org/licenses/>.
 *
 * This program consists of a few parts:
 *
 * ConfigFile   Read configuration files
 * EthConfig    Initialize an ethernet stack, based on a configuration file (includes link status monitoring)
 * LaosDisplay  User interface functions (read keys, display text and menus on LCD)
 * LaosMenu     User interface stuctures (menu navigation)
 * LaosServer   TCP/IP server, accept connections read/write data
 * LaosMotion   Motion control functions (X,Y,Z motion, homing)
 * LaosIO       Input/Output functions
 * LaosFile     File based jobs (read/write/delete)
 *
 * Program functions:
 * 1) Read config file
 * 2) Enable TCP/IP stack (Fixed ip or DHCP)
 * 3) Instantiate tcp/ip port and accept connections
 * 4) Show menus, peform user actions
 * 5) Controll laser
 * 6) Controll motion
 * 7) Set and read IO, check status (e.g. interlocks)
 *
 */

// init file management
// read config values from program defaults
// overwrite config values with those in config.txt on sd or mbed
// 
// init status thread (= main loop)
// init motion thread, with our without home sequence
// init queing thread
// init display thread
// init TFTP subthread
//
#include "mbed.h"
#include "cmsis_os.h"
#include "SDFileSystem.h" 
#include "FATFileSystem.h" 
#include <string> 
#include <ctype.h>
#include "laosfilesystem.h"
#include "global.h"
#include "laosstatus.h"
#include "pins.h"
#include "laosmotion.h"
#include "EthConfig.h"
#include "TFTPServer.h"

// Filesystems
LocalFileSystem local("local");   //File System
LaosFileSystem sd(p11, p12, p13, p14, "sd");
GlobalConfig *cfg;

LaosStatus *state;
LaosMotion *mot;
EthernetInterface *eth; // Ethernet, tcp/ip
osThreadDef(tftp_thread, osPriorityNormal, DEFAULT_STACK_SIZE);
osThreadDef(queue_thread, osPriorityNormal, DEFAULT_STACK_SIZE);

int main() {
    state = new LaosStatus();
    state->setState(BOOTING);
    if (! check_sd()) mbed_reset();
    if (SDcheckFirmware()) mbed_reset();
    cfg =  new GlobalConfig("config.txt");
    mot = new LaosMotion();
    // wait until cover is closed
    state->setState(WAITFORCOVER);
    while (! mot->isStart() );
    // home
    state->setState(HOMING);
    mot->home(cfg->xhome,cfg->yhome, cfg->zhome);
    // clean sd card?
    if (cfg->cleandir) cleandir();
    // configure network
    eth_speed = 0;
    eth = EthConfig();
    eth_speed = 1;
    // set up TFTP server thread
    osThreadCreate(osThread(tftp_thread), NULL);
    // set up Queue (planner-filler) thread
    osThreadCreate(osThread(queue_thread), NULL);
    
    while (1) {
        if (mot->qstate == IDLE) {
            mot->filename = getLaosFile();
            if (mot->filename) mot->qstate = NEW;
        }
        if (mot->qstate == DONE) {
            removefile(mot->filename);
            delete(mot->filename);
        }
        osDelay(500);
    }
}
