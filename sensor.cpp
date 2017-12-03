#include "sensor.h"
#include <cmath>

namespace robots {

    std::ostream& sensor::show(std::ostream &os) const
    {
        return os<<", radius: " << radius << ", angle: " << angle << ", napr: " << napr;
    }

    std::vector<paircoord> sensor::getData(const int x0, const int y0) const
    {

        paircoord xy;
        std::vector<paircoord> res;

        for (xy.y = y0 - radius; xy.y <= y0 + radius; ++xy.y){
            for(xy.x = x0 - radius; xy.x <= x0 + radius; ++xy.x){
                res.push_back(xy);

            }
        }

        return res;
    }

}

