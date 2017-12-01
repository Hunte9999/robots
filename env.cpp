#include "env.h"

namespace robots {

    env::env(int nn, int mm)
    {
        if (nn <= 0 || mm < 0){
            throw std::invalid_argument("NO!");
        }

        std::vector<place*> ne;

        for (int i =0; i < mm; ++i){
           pole.push_back(ne);
        }
        pole.reserve(mm);
        for(int i = 0; i < mm; ++i){
            pole.at(i).reserve(nn);
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
        if(pole.at(y).at(x)->getSost() == CLOSE){
            return -1;
        }
        return pole.at(y).at(x)->retType();
    }

    env& env::setType(int x, int y, const place &n)
    {
        place* del = pole.at(y).at(x);
        pole.at(y).at(x) = n.clone();
        if (n.retType() == 3){
            pole.at(y).at(x)->setSost(OPEN);
        }
        delete del;
        return *this;
    }

    place* env::getPlace(int x, int y) const
    {
        return pole.at(y).at(x)->clone();
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

    env& env::addComponent(int x, int y, int maxnmod, int type, int velocity)
    {
        component* comp = nullptr;
        movcomp* movcom = nullptr;
        managecomp* mancomp = nullptr;
        movmanagecomp* movmancomp = nullptr;
        place *plc = getPlace(x, y);
        if (plc->retType() != 0){
            throw std::invalid_argument("this place is not for you");
        }
        switch(type){
        case 0:
            comp = new component(x, y, maxnmod);
            setType(x, y, *comp);
            break;
        case 1:
            movcom = new movcomp(x, y, maxnmod, velocity);
            setType(x, y, *movcom);
            break;
        case 2:
            mancomp = new managecomp(x, y, maxnmod);
            setType(x, y, *mancomp);
            break;
        case 3:
            movmancomp = new movmanagecomp(x, y, maxnmod, velocity);
            setType(x, y, *movmancomp);
            break;
        }
        return *this;
    }

    env& env::addModule(int x, int y, int type, int energyuse, int cost, int energylevel, int maxnumb, int radius, int angle)
    {
        if(x >= n || x < 0){
            throw std::invalid_argument("Invalid x coordinate");
        }
        if(y >= m || y < 0){
            throw std::invalid_argument("Invalid y coordinate");
        }

        place* plc = pole.at(y).at(x);
        component* cmp = nullptr;

        if(plc->retType() != 3){
            throw std::invalid_argument("There is no robot in this place");
        }
        cmp = dynamic_cast<component*>(plc);

        manager *man = nullptr;
        generator *gen = nullptr;
        sensor *sen = nullptr;

        switch (type){
        case 1:
            gen = new generator(energylevel, cost);
            gen->setSost(ON);
            cmp->addModule(*gen);
            break;
        case 2:
            sen = new sensor(radius, angle, energyuse, cost);
            sen->setSost(ON);
            cmp->addModule(*sen);
            break;
        case 3:
            man = new manager(maxnumb, radius, cost, energyuse);
            man->setSost(ON);
            cmp->addModule(*man);
            cmp->setIsManaged(1);
            break;
        }

        return *this;

    }

    env& env::addDiffPlace(int x, int y, int type)
    {
        //int a, b;
        //en.getRazm(a, b);
        if (x < 0 || x > n){
            throw std::invalid_argument("Invalid x value");
        }
        if (y < 0 || y > m){
            throw std::invalid_argument("Invalid y value");
        }
        obstacle *obst = nullptr;
        ti* t = nullptr;
        if (type == 0){
            obst = new obstacle(x, y);
            setType(x, y, *obst);
        }
        else{
            t = new ti(x, y);
            setType(x, y, *t);
        }
        return *this;
    }

}
