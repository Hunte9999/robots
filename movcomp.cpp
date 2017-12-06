#include "movcomp.h"

namespace robots{

    std::ostream& movcomp::show(std::ostream &os) const
    {
        os << " movcomp:: velocity: " << velocity;
        component::show(os);
        return os;
    }

    movcomp& movcomp::Move(sides s, int steps)
    {
        if(steps > velocity || steps < 0){
            throw std::invalid_argument("This point cant be reached");
        }
        switch (s){
        case UP:
            setY(getY() + steps);
            break;
        case DOWN:
            setY(getY() - steps);
            break;
        case LEFT:
            setX(getX() - steps);
            break;
        case RIGHT:
            setX(getX() + steps);
            break;
        }
        return *this;
    }
}
