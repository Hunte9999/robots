#ifndef SENSOR_H
#define SENSOR_H

#include "module.h"
#include "place.h"
#include "movcomp.h"

namespace robots {

class sensor:public module
{
private:
    int radius, angle;
    sides napr;
    //int defin[11] = {1, 5, 13, 29, 49, 81, 113, 149, 197, 253, 317};
protected:
    virtual std::ostream& show(std::ostream &) const;
public:
    sensor(int radius, int angle, int energyuse, int cost): module(energyuse, cost, 0), radius(radius), angle(angle), napr(UP) {}
    sensor(const sensor &sen): module(sen.getEnergyUse(), sen.getCost(), 0), radius(sen.getRadius()), angle(sen.getAngle()), napr(sen.getNapr()) {}

    int getRadius() const { return radius; }
    int getAngle() const { return angle; }
    sides getNapr() const {return napr; }

    std::vector<paircoord> getData(const int x0, const int y0, int &k) const;

    sensor& setNapr(sides napr);

    virtual int retType() const { return 2; }
    virtual sensor* clone() const{
        return new sensor(*this);
    }
    virtual ~sensor() override {}
};

}

#endif // SENSOR_H
