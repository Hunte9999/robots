#ifndef MANAGECOMP_H
#define MANAGECOMP_H

#include "component.h"

namespace robots{

class managecomp:virtual public component
{
protected:
    virtual std::ostream& show(std::ostream&) const;
public:
    managecomp(int x, int y, int maxnmod): component(x, y, maxnmod) {}
    managecomp(const managecomp &mc): component(mc) {}
    //component& addModule(const module& n);
    component* clone() const{
        return new managecomp(*this);
    }
    bool canAdd(const module &n);
    int retType() const { return 5; }
    virtual ~managecomp() override {}
};

}

#endif // MANAGECOMP_H
