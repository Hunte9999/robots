#include "module.h"

namespace robots {

    std::ostream& operator <<(std::ostream &os, const module &m)
    {
        os << "sost: " << m.sost << ", priority: " << m.priority << ", energyuse: " << m.energyuse << ", cost: " << m.cost;
        return m.show(os);
    }

    module& module::setSost(ModSost st)
    {
        if (st != ON && st != OFF){
            throw std::invalid_argument("invalid argument");
        }

        sost = st;

        return *this;
    }

}
