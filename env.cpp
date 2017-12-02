#include "env.h"

namespace robots {

    env::env(int nn, int mm)
    {
        if (nn <= 0 || mm < 0){
            throw std::invalid_argument("NO!");
        }

        std::vector<place*> ne;

        for(int i = 0; i < mm; ++i){
            pole.push_back(ne);
            for(int j = 0; j < nn; ++j){
                pole.at(i).push_back(new place(i, j));
            }
        }
        n = nn;
        m = mm;
    }

    env& env::setRazm(int nn, int mm)
    {
        if (nn <= 0 || mm < 0){
            throw std::invalid_argument("NO!");
        }

        n = nn;
        m = mm;

        return *this;
    }

    int env::getType(int x, int y) const
    {
        if(x < 0 || x >= n){
            throw std::invalid_argument("Invalid x coordinate");
        }
        if(y < 0 || y >= m){
            throw std::invalid_argument("Invalid y coordinate");
        }
        if(pole.at(y).at(x)->getSost() == CLOSE){
            return -1;
        }
        return pole.at(y).at(x)->retType();
    }

    component* env::setType(const place &plc)
    {
        int x = plc.getX(), y = plc.getY();
        if(x < 0 || x >= n){
            throw std::invalid_argument("Invalid x coordinate");
        }
        if(y < 0 || y >= m){
            throw std::invalid_argument("Invalid y coordinate");
        }
        place* del = pole.at(y).at(x);
        if(del->retType() != 0 && plc.retType() != 0){
            throw std::invalid_argument("This place is not for you");
        }
        pole.at(y).at(x) = plc.clone();
        if (plc.retType() == 3){
            pole.at(y).at(x)->setSost(OPEN);
        }
        delete del;
        return dynamic_cast<component*>(pole.at(y).at(x));
    }

    place* env::getPlace(int x, int y) const
    {
        if(x < 0 || x >= n){
            throw std::invalid_argument("Invalid x coordinate");
        }
        if(y < 0 || y >= m){
            throw std::invalid_argument("Invalid y coordinate");
        }
        return pole.at(y).at(x);
    }

    std::ostream& operator<<(std::ostream &os, const env &n)
    {
        os << "NxM: " << n.m << "x" << n.n << std::endl;
        for (int i = 0; i < n.n; ++i){
            for (int j = 0; j < n.m; ++j){
                os << n.pole.at(j).at(i)->retType();
                if(n.pole.at(j).at(i)->retType() < 3){
                    os << ":" << n.pole.at(j).at(i)->getSost() << " ";
                }
                else{
                    os << "   ";
                }
                //os << "next dot(" << j << ", " << i << "): " << *(n.pole.at(j).at(i)) << ": ";
                //os << n.pole.at(j).at(i)->retType();
            }
            os << std::endl;
        }
        return os;
    }

    void env::getRazm(int &a, int &b) const
    {
        a = n;
        b = m;
    }

    component* env::addComponent(int x, int y, int maxnmod, int type, int velocity)
    {
        component* comp = nullptr;
        movcomp* movcom = nullptr;
        managecomp* mancomp = nullptr;
        movmanagecomp* movmancomp = nullptr;
        switch(type){
        case 0:
            comp = new component(x, y, maxnmod);
            return setType(*comp);

            //robots.push_back(comp);
            break;
        case 1:
            movcom = new movcomp(x, y, maxnmod, velocity);
            return setType(*movcom);

            //robots.push_back(movcom);
            break;
        case 2:
            mancomp = new managecomp(x, y, maxnmod);
            return setType(*mancomp);

            //robots.push_back(mancomp);
            break;
        case 3:
            movmancomp = new movmanagecomp(x, y, maxnmod, velocity);
            return setType(*movmancomp);

            //robots.push_back(movmancomp);
            break;
        default:
            throw std::invalid_argument("Wrong type argument");
        }
    }

    env& env::addModule(int x, int y, int type, int energyuse, int cost, int energylevel, int maxnumb, int radius, int angle)
    {

        if(x < 0 || x >= m){
            throw std::invalid_argument("Invalid x coordinate");
        }

        if(y < 0 || y >= n){
            throw std::invalid_argument("Invalid y coordinate");
        }

        place* plc = pole.at(y).at(x);
        if(plc->retType() < 3){
            throw std::invalid_argument("There is no robot in this place");
        }

        component* cmp = dynamic_cast<component*>(plc);

        manager *man = nullptr;
        generator *gen = nullptr;
        sensor *sen = nullptr;


        switch (type){
        case 1:
            gen = new generator(energylevel, cost);
            cmp->addModule(*gen);
            cmp->turnOnMod(cmp->getModules().size());
            break;
        case 2:
            sen = new sensor(radius, angle, energyuse, cost);
            cmp->addModule(*sen);
            cmp->turnOnMod(cmp->getModules().size());
            break;
        case 3:
            man = new manager(maxnumb, radius, cost, energyuse);
            cmp->addModule(*man);
            cmp->turnOnMod(cmp->getModules().size());
            cmp->setIsManaged(1);
            break;
        default:
            throw std::invalid_argument("Wrong type argument");
        }

        return *this;
    }

    env& env::swap(int x1, int y1, int x2, int y2)
    {
        place* plc = pole.at(y1).at(x1);
        pole.at(y1).at(x1) = pole.at(y2).at(x2);
        pole.at(y2).at(x2) = plc;
        return *this;
    }

}
