#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include "module.h"
#include "place.h"
#include <iostream>

namespace robots{

class component:public place
{
private:
    int energyuse = 0, maxnummod, cost = 0, currnummod = 0, ismanaged = 0;
    std::vector<module*> modules;
   // component(const component &) = delete;
protected:
    virtual std::ostream& show(std::ostream &) const;
public:
    component(int x, int y, int maxnmod): place(x, y), energyuse(0), maxnummod(maxnmod),  cost(0), currnummod(0), ismanaged(0) {setSost(OPEN);}
    component(const component&c): place(c), maxnummod(c.getMaxNumMod()) {
        int n = c.getCurrNumMod();
        std::vector<module*> mods = c.getModules();

        for(int i = 0; i < n; ++i){
            modules.push_back(mods.at(i)->clone());
        }
    }

    component& addModule(const module& n);
    component& delModule(int n);
    component& turnOnMod(int n);
    component& turnOffMod(int n);
    component& setIsManaged(int n);

    const std::vector<module*> &getModules() const { return modules; }
    int getCurrNumMod() const { return currnummod; }
    int getIsManaged() const { return ismanaged; }
    int getEnergyUse() const { return energyuse; }
    int getMaxNumMod() const { return maxnummod; }

    int retType() const override { return 3; }

    virtual bool canAdd(const module& n);

    virtual component* clone() const{
        return new component(*this);
    }

    virtual ~component() override {
        /*for (int i = 0; i < currnummod; ++i){
            delete modules[i];
        }*/
        //std::cout << "destr component " <<std::endl;
        for(module* mod: modules){
            delete mod;
        }
        modules.clear();
    }

};

}

#endif // COMPONENT_H
