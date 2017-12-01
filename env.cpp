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

}
