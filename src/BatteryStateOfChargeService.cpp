#include "BatteryStateOfChargeService.h"
#include <QTime>
#include <BatteryData.h>
namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double CONVERT_TO_MILLISECONDS = 2.7778e-7;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent), inCurrent(0), SumCurrent(0)
{
    AmpHours = BATTERY_AMP_HOUR_CAPACITY*(initialStateOfChargePercent_/100);
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return BATTERY_AMP_HOUR_CAPACITY-AmpHours;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if (Current < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    double timeRemaining = (BATTERY_AMP_HOUR_CAPACITY-AmpHours)/inCurrent;
    timeRemaining = qAbs(timeRemaining)/CONVERT_TO_MILLISECONDS;
    return QTime(0, 0, 0, 0).addMSecs(timeRemaining);
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{

    QTime currentTime = batteryData.time;
    changeTime = abs(prevTime.msecsTo(currentTime));
    changeTime = changeTime * CONVERT_TO_MILLISECONDS;
    prevTime = currentTime;
    if (Current > 0 || Current < 0 )
    {
        inCurrent = Current;
    }
    Current = batteryData.current;

    if (inCurrent == 0)
    {
        AvgCurrent = 0;
    }
    else
    {
        AvgCurrent = (inCurrent + Current)/2;
    }

    double inVoltage = batteryData.voltage;
    double Voltage = batteryData.voltage;
    double AmpChange = (AvgCurrent * changeTime);

    AmpHours += AmpChange;

    int counter;
    counter++;
    SumCurrent += inCurrent;
    AverageCurrent = SumCurrent/counter;

    dTime = prevTime.msecsTo(currentTime);
    dTime = dTime * CONVERT_TO_MILLISECONDS;
}
