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

    manager& manager::addComp(component *n)
    {
        if(currnumb == maxnumb){
            throw std::length_error("Cant manage any more components");
        }

        currnumb++;
        tab.push_back(n);
        n->setIsManaged(1);

        return *this;
    }

    manager& manager::delComp(component *n)
    {
        int a = SearchComp(n);
        if(a == -1){
            throw std::invalid_argument("There are no such component in current table");
        }

        tab[a]->setIsManaged(0);

        std::vector<component*>::iterator it = tab.begin() + a;
        tab.erase(it);
        currnumb--;

        return *this;
    }

    int manager::SearchComp(component *n) const
    {

        for(int i = 0; i < tab.size(); ++i){
            if(tab[i] == n){
                return i;
            }
        }
        return -1;
    }

}
