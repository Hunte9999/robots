#ifndef MOVMANAGECOMP_H
#define MOVMANAGECOMP_H

#include "movcomp.h"
#include "managecomp.h"

namespace robots{

class movmanagecomp:public movcomp, public managecomp
{
protected:
    virtual std::ostream& show(std::ostream &os) const{
        os << "movmanagecomp";
        return this->movcomp::show(os);
    }
public:
    movmanagecomp(int x, int y, int maxnmod, int velct):  component(x, y, maxnmod), movcomp(x, y, maxnmod, velct), managecomp(x, y, maxnmod) {}
    movmanagecomp(const movmanagecomp &mvmc): component(mvmc), movcomp(mvmc), managecomp(mvmc) {}

    component& addModule(const module &n){
        return managecomp::addModule(n);
    }
    component* clone() const{
        return new movmanagecomp(*this);
    }

    int retType() const { return 6; }
    virtual ~movmanagecomp() override {}
};

}

#endif // MOVMANAGECOMP_H
