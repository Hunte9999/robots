#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "place.h"
#include <iostream>

namespace robots{

class obstacle:public place
{
protected:
    virtual std::ostream& show(std::ostream &os) const{
        return os << " :: obstacle";
    }
public:
    obstacle(int x, int y): place(x, y) {}
    obstacle(const obstacle &obst): place(obst) {}
    int retType() const { return 2; }
    virtual obstacle* clone() const{
        return new obstacle(*this);
    }
    virtual ~obstacle() override {}
};

}

#endif // OBSTACLE_H
