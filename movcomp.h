#ifndef MOVCOMP_H
#define MOVCOMP_H

#include "component.h"

namespace robots{

enum sides {UP, DOWN, LEFT, RIGHT};

class movcomp:virtual public component
{
private:
    int velocity;
protected:
    virtual std::ostream& show(std::ostream &) const;
public:
    movcomp(int x, int y, int maxnmod, int velct): component(x, y, maxnmod), velocity(velct) {}
    movcomp(const movcomp &mvc): component(mvc), velocity(mvc.getVelocity()) {}

    movcomp& Move(sides s);

    int retType() const  { return 4;}

    int getVelocity() const { return velocity; }

    component* clone() const{
        return new movcomp(*this);
    }
    virtual ~movcomp() override {}
};

}

#endif // MOVCOMP_H
