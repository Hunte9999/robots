#include "place.h"

namespace robots {

    std::ostream& operator<<(std::ostream &os, const place &m)
    {
        return m.show(os);
    }

    std::ostream& place::show(std::ostream &os) const
    {
        return os << "x: " << x << ", y: " << y << ", sost: " << st;
    }


    place& place::setX(int n)
    {
        x = n;
        return *this;
    }

    place& place::setY(int n)
    {
        y = n;
        return *this;
    }

    place& place::setSost(sost n)
    {
        st = n;
        return *this;
    }
}
