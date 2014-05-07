/*
 * laosstatus.cpp
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
 */
#include "laosstatus.h"

LaosStatus::LaosStatus()
{
}

LaosStatus::~LaosStatus()
{
}

position LaosStatus::getPos()
{
    return pos;
}

bool LaosStatus::isHome()
{
    return true;
}

bool LaosStatus::isRest()
{
    return true;
}

void LaosStatus::moveto(position pos)
{
}

position LaosStatus::getOffset()
{
    return offset;
}

position LaosStatus::restPos()
{
    position restpos;
    restpos.x = cfg->xrest;
    restpos.y = cfg->xrest;
    restpos.z = cfg->xrest;
    return restpos;
}

void LaosStatus::setOrigin()
{
}

void LaosStatus::setOrigin(position pos)
{
}

char* LaosStatus::getrunningFileName()
{
    return NULL;
}

int LaosStatus::getrunningFileSize()
{
    return 0;
}

int LaosStatus::getrunningFilePercent()
{
    return 0;
}

char* LaosStatus::getCurrentFileName()
{
    return NULL;
}

char* LaosStatus::getFirstFileName()
{
    return NULL;
}

char* LaosStatus::getNextFileName()
{
    return NULL;
}

char* LaosStatus::getPrevFileName()
{
    return NULL;
}

char* LaosStatus::getLastFileName()
{
    return NULL;
}

void LaosStatus::deleteFile(char *filename)
{
}

void LaosStatus::deleteAllFiles()
{
}

machineStatus LaosStatus::getState()
{
    return state;
}

char* LaosStatus::getStateName() {
    string name;
    switch (state)
    {
    case RUNNING:
        name = "running";
        break;
    case READY:
        name = "ready";
        break;
    case ERROR:
        name = "error";
        break;
    case HOMING:
        name = "homing";
        break;
    case BOOTING:
        name = "booting";
        break;
    case WAITFORCOVER:
        name = "Wait for cover";
        break;
    case RECEIVING:
        name = "Receiving file";
        break;
    case WAITFORFILE:
        name = "Wait for file";
        break;
    default:
        name = "State unknown";
        break;
    }
    char *result = new char[name.size()+1];
    strcpy(result,name.c_str());
    return result;
}

void LaosStatus::setState(machineStatus newstate) 
{
    state = newstate;
    printf("New state: %s\n\r", getStateName());
}

char* LaosStatus::getErrorMessage()
{
    char* copy = new char[strlen(errormsg)+1];
    strcpy(copy, errormsg);
    return copy;
}

void LaosStatus::setErrorMessage(const std::string& msg)
{
    if (errormsg != NULL) delete(errormsg);
    char *newmsg = new char[msg.size()+1];
    strcpy(newmsg, msg.c_str());
    errormsg = newmsg;
}

char* LaosStatus::getVersionString()
{
    return NULL;
}

void LaosStatus::setVersionString(char *msg)
{
  
}

void LaosStatus::startjob()
{
}

void LaosStatus::home()
{
}

void LaosStatus::reboot()
{
}

void LaosStatus::cancel()
{
}

char* LaosStatus::getNetIP()
{
    return  NULL;
}

char* LaosStatus::getNetMask()
{
    return NULL;
}

char* LaosStatus::getNetGateway()
{
    return NULL;
}

char* LaosStatus::getNetDNS()
{
    return NULL;
}
