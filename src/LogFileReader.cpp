/** 
 *  University of Calgary Solar Car Team New Recruit Exercise
 *  Copyright (C) 2015 University of Calgary Solar Car Team
 *
 *  This file is part of the 
 *  University of Calgary Solar Car Team New Recruit Exercise
 *
 *  The University of Calgary Solar Car Team New Recruit Exercise 
 *  is free software: you can redistribute it and/or modify it 
 *  under the terms of the GNU General Public License as 
 *  published by the Free Software Foundation, either version 3 
 *  of the License, or (at your option) any later version.
 *
 *  The University of Calgary Solar Car Team New Recruit Exercise 
 *  is distributed in the hope that it will be useful, but WITHOUT 
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General 
 *  Public License for more details.
 *
 *  You should have received a copy of the GNU General 
 *  Public License along with the University of Calgary Solar Car 
 *  Team New Recruit Exercise. If not, see 
 *  <http://www.gnu.org/licenses/>.
 *
 *  For further contact, email <software@calgarysolarcar.ca>
 */

#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>


#include "LogFileReader.h"

namespace
{
    const int OK_LENGTH = 32 ;
}

LogFileReader::LogFileReader()
{
}

LogFileReader::~LogFileReader()
{
}

bool LogFileReader::readAll(const QString& fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Unable to open file" << fileName;
        return false;
    }

    QTextStream input(&file);
    while(!input.atEnd())
    {
        QString line = input.readLine();
        BatteryData batteryData;
        if (!parseLine(line, batteryData))
        {
            qDebug() << "Error while parsing" << line;
            // return false;
        }
        else
        {
            // This is how to send out a signal in QT using the emit keyword.
            // This line notifies how any classes listening to this signal
            // that battery data has been received.
            emit batteryDataReceived(batteryData);
        }
    }

    return true;
}

// File input is a csv file in the format of hh:mm:ss:zzz, voltage, current
// & - pass by reference
bool LogFileReader::parseLine(const QString& line, BatteryData& batteryData) const 
{
    // TODO implement this first

    // This is here to the compiler happy. Otherwise the compile
    // will have an error warning about an unused variable. Remove this
    // when you use it.

	
    Q_UNUSED(line);
    Q_UNUSED(batteryData);

    bool validData = true;

    QTime aTime;

	double aVoltage;
	double aCurrent;

	QStringList aList;

    int lineLength;

    lineLength = line.length();

    if (lineLength != OK_LENGTH){
        return false;
    }

    aList = line.split(", ", QString::SkipEmptyParts);

    aTime = QTime::fromString(aList[0],"hh:mm:ss.zzz");

    if (aTime.isValid() == false){
        return false;
    }

    aVoltage = aList[1].toDouble(&validData);

    aCurrent = aList[2].toDouble(&validData);


    if (validData == false)
    {
        return false;
    }
    else{

    batteryData.time = aTime;
    batteryData.voltage = aVoltage;
    batteryData.current = aCurrent;

    return true;
    }
}
