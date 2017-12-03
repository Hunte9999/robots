#ifndef MANAGER_H
#define MANAGER_H

#include "module.h"
#include "component.h"
#include <vector>

namespace robots {

class manager: public module
{
private:
    int maxnumb, currnumb, radius;
    std::vector<component*> tab;
    int SearchComp(component*) const;
protected:
    virtual std::ostream& show(std::ostream &) const;
public:
    manager(int maxnum, int rad, int cst, int enerus): module(enerus, cst, -1), maxnumb(maxnum), currnumb(0), radius(rad) {}
    manager(const manager &man): module(man.getEnergyUse(), man.getCost(), -1), maxnumb(man.getMaxNumb()), currnumb(man.getTab().size()), radius(man.getRadius()), tab(man.getTab()) {}

    int getCurrNumb() const { return currnumb; }
    int getRadius() const { return radius; }
    int getMaxNumb() const { return maxnumb; }

    manager& addComp(component *n);
    manager& delComp(component *n);

    const std::vector<component*> &getTab() const { return tab; }

    int retType() const { return 3; }
    manager* clone() const{
        return new manager(*this);
    }

    virtual ~manager() override {}
};

}

#endif // MANAGER_H
