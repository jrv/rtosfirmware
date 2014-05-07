/**
 * laosstatus.h
 * Status reporting routines
 *
 * Copyright (c) 2011 Peter Brier & Jaap Vermaas
 *
 *   This file is part of the LaOS project (see: http://wiki.laoslaser.org/)
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
 *
 @code 
 --code--
 @endcode
 */
#ifndef _LAOSSTATUS_H_
#define _LAOSSTATUS_H_

#include "laosfilesystem.h"
#include "global.h"
extern "C" void mbed_reset();

struct position {
    float x,y,z;
};
typedef enum { RUNNING, READY, ERROR, HOMING, BOOTING, WAITFORCOVER, RECEIVING, WAITFORFILE } machineStatus;

class LaosStatus {
public:
    LaosStatus();
    ~LaosStatus();

    position getPos();
    bool isHome();
    bool isRest();
    void moveto(position pos);
    position getOffset();
    position restPos();
    void setOrigin();
    void setOrigin(position pos);

    char* getrunningFileName();
    int getrunningFileSize();
    int getrunningFilePercent();

    char* getCurrentFileName();
    char* getFirstFileName();
    char* getNextFileName();
    char* getPrevFileName();
    char* getLastFileName();
    void deleteFile(char *filename);
    void deleteAllFiles();

    machineStatus getState();
    char* getStateName();
    void setState(machineStatus state);
    char* getErrorMessage();
    void setErrorMessage(const std::string& msg);

    char* getVersionString();
    void setVersionString(char *msg);

    void startjob();
    void home();
    void reboot();
    void cancel();

    char* getNetIP();
    char* getNetMask();
    char* getNetGateway();
    char* getNetDNS();
        
private:
    machineStatus state;    
    position pos;
    position offset;
    char *errormsg;
};

#endif
