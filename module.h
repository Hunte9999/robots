#ifndef MODULE_H
#define MODULE_H

#include <iostream>

namespace robots{

enum ModSost{ON, OFF};

struct paircoord {
    int x, y;
};

class module
{
private:
    int energyuse, cost, priority;
    ModSost sost;
protected:
    virtual std::ostream& show(std::ostream &) const = 0;
public:
    module(int enerus, int cst, int prior): energyuse(enerus), cost(cst), priority(prior), sost(OFF) {}

    module& setSost(ModSost st);

    int getCost() const { return cost; }
    int getEnergyUse() const  { return energyuse; }
    int getPriority() const  { return priority; }
    ModSost getSost() const { return sost; }

    virtual int retType() const  = 0;
    virtual module* clone() const = 0;
    friend std::ostream& operator <<(std::ostream &, const module &);
    virtual ~module() {}
};

}
#endif // MODULE_H
