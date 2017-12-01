#include "manager.h"
#include "component.h"

namespace robots {

    std::ostream& manager::show(std::ostream &os) const
    {
        os << ", currnumb: " << currnumb << ", radius: " << radius << ", tab: ";
        for (int i = 0; i < currnumb; i++){
            os << tab.at(i);
        }
        return os;
    }

    manager& manager::addComp(int n)
    {
        if(currnumb == maxnumb){
            throw std::length_error("Cant manage any more components");
        }

        currnumb++;
        tab.push_back(n);

        return *this;
    }

    manager& manager::delComp(int n)
    {
        if(currnumb == 0){
            throw std::invalid_argument("There are no components handling now");
        }

        std::vector<int>::iterator it = tab.begin() + n - 1;
        tab.erase(it);
        currnumb--;

        return *this;
    }

}
