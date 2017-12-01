#ifndef ENV_H
#define ENV_H

#include "place.h"
#include <vector>
#include "component.h"
#include "managecomp.h"
#include "movcomp.h"
#include "movmanagecomp.h"
#include "manager.h"
#include "sensor.h"
#include "generator.h"
#include "obstacle.h"
#include "ti.h"

namespace robots{

class env
{
private:
    std::vector <std::vector <place*> > pole;
    int n, m;
public:
    env(int nn, int mm);
    env(const env& enn){
        std::vector<std::vector<place*>> ne = enn.getPole();
        std::vector<place*> plcne;
        enn.getRazm(n, m);

        for(int i = 0; i < m; ++i){
            pole.push_back(plcne);
            for(int j = 0; j < n; ++j){
                pole.at(i).push_back(ne.at(i).at(j)->clone());
            }
        }
    }

    env& setRazm(int nn, int mm);
    int getType(int x, int y) const ;
    env& setType(int x, int y, const place& n);
    place* getPlace(int x, int y) const;

    const std::vector <std::vector <place*> > &getPole() const { return pole; }

    //env& addComponent(int x, int y, int maxnmod, int type = 0, int velocity = 0);
    //env& addModule(int x, int y, int type, int energyuse, int cost, int energylevel = 0, int maxnumb = 0, int radius = 0, int angle = 0);
    //env& addDiffPlace(int x, int y, int type);

    virtual env* clone() const{
        return new env(*this);
    }

    void getRazm(int &a, int &b) const;

    friend std::ostream& operator <<(std::ostream &, const env &);

    virtual ~env() {
        //std::cout << "destr env " <<std::endl;
        for (int i = 0; i < m; ++i){
            for (int j = 0; j < n; ++j){
                delete pole.at(i).at(j);
            }
        }
    }
};

}

#endif // ENV_H
