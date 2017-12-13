#include "component.h"
#include "generator.h"
#include "sensor.h"

namespace robots {

    std::ostream& component::show(std::ostream &os) const
    {
        os << ", currnummod: " << currnummod << ", energyuse: " << energyuse << ", cost: " << cost;
        for (int i = 0; i < currnummod; ++i){
            os << *(modules[i]);
        }
        return os;
    }

    bool component::canAdd(const module &n)
    {
        if(n.retType() == 1 || n.retType() == 2){
            return true;
        }
        return false;
    }

    component& component::addModule(const module &n)
    {
        if(currnummod == maxnummod){
            std::invalid_argument("Cant add. Full.");
        }

        if (canAdd(n)){
            currnummod++;
            if(n.getSost() == ON){
                energyuse += n.getEnergyUse();
            }
            modules.push_back(n.clone());
        }
        else{
            throw std::invalid_argument("Manager module cannot be installed in non-managing component.");
        }

        return *this;
    }

    component& component::delModule(int n)
    {
        if(n > currnummod || n < 0){
            throw std::invalid_argument("NO!");
        }

        if(modules[n]->getSost() == ON){
            energyuse -= modules[n]->getEnergyUse();
        }

        std::vector<module*>::iterator it;
        it = modules.begin() + n - 1;
        modules.erase(it);

        return *this;
    }

    component& component::turnOnMod(int n)
    {
        if(n >= currnummod || n < 0){
            throw std::invalid_argument("NO!");
        }

        if(modules[n]->getSost() != ON){
            modules[n]->setSost(ON);
            energyuse += modules[n]->getEnergyUse();
        }

        return *this;
    }

    component& component::turnOffMod(int n)
    {
        if(n >= currnummod || n < 0){
            throw std::invalid_argument("NO!");
        }

        if(modules[n]->getSost() != OFF){
            modules[n]->setSost(OFF);
            energyuse -= modules[n]->getEnergyUse();
        }

        return *this;
    }

    component& component::setIsManaged(int n)
    {
        if(n == 0 || n == 1){
            ismanaged = n;
        }
        else{
            throw std::invalid_argument("Invalid arg ismanged");
        }
        return *this;
    }

}
