#ifndef GENERATOR_H
#define GENERATOR_H

#include "module.h"

namespace robots{

class generator:public module
{
private:
    int energylevel;
protected:
    virtual std::ostream& show(std::ostream &) const;
public:
    generator(int energlvl, int cst): module(0, cst, -1), energylevel(energlvl) {}
    generator(const generator &gen): module(0, gen.getCost(), -1), energylevel(gen.getEnergyLevel()) {}

    int getEnergyLevel() const { return energylevel; }
    virtual int retType() const { return 1; }
    virtual generator* clone() const
    {
        return new generator(*this);
    }
    virtual ~generator() override {}
};

}

#endif // GENERATOR_H
