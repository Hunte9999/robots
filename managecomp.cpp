#include "managecomp.h"
#include "manager.h"

namespace robots{

    bool managecomp::canAdd(const module &n)
    {
        if (n.retType() == 3){
            return true;
        }
        return component::canAdd(n);
    }

    std::ostream& managecomp::show(std::ostream &os) const
    {
        os << " managing component ";
        component::show(os);
        return os;
    }

}
