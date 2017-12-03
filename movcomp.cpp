#include "movcomp.h"

namespace robots{

    std::ostream& movcomp::show(std::ostream &os) const
    {
        os << " movcomp:: velocity: " << velocity;
        component::show(os);
        return os;
    }

    movcomp& movcomp::Move(sides s)
    {
        switch (s){
        case UP:
            setY(getY() + velocity);
            break;
        case DOWN:
            setY(getY() - velocity);
            break;
        case LEFT:
            setX(getX() - velocity);
            break;
        case RIGHT:
            setX(getX() + velocity);
            break;
        }
        return *this;
    }
}
