#pragma once

#include "I_BatteryStateOfChargeService.h"

#include "LogFileReader.h"


class BatteryStateOfChargeService : public I_BatteryStateOfChargeService
{
public:
    explicit BatteryStateOfChargeService(double initialStateOfChargePercent);
    virtual ~BatteryStateOfChargeService();

    double totalAmpHoursUsed() const;
    bool isCharging() const;
    QTime timeWhenChargedOrDepleted() const;

    void addData(const BatteryData& batteryData);

private:
    // Convention is to have an _ after private members
    const double initialStateOfChargePercent_;

    // Recommend adding necessary variables here

    QTime previousTime_;
    QTime newTime_;
    double previousCurrent_;
    double deltaTime_;
    double aveCurrent_;

    double ampHours_;
};
