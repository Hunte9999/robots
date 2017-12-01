#ifndef AI_H
#define AI_H

#include "env.h"
#include <iostream>
#include <vector>
#include "component.h"
#include "movcomp.h"

namespace robots{

class AI
{
private:
    env en;
    std::vector<component*> robots;
protected:
    int goRobots(int energy);
    int canMove(movcomp* csmv, sides s) const;
    AI& reMap(int x, int y, component* comp);
public:
    AI(env envi): en(envi) {}
    AI(const AI& a): en(a.getEn()){
        std::vector<component*> robs = a.getRobots();

        for (component* &cmp: robs){
            robots.push_back(cmp->clone());
        }
    }

    //загрузка из файла начального положения
    AI(char *nameOfFile);

    AI& start(int shag = -1);

    std::ostream& showRobots(std::ostream&) const;

    AI& addComponent(int x, int y, int maxnmod, int type = 0, int velocity = 0);

    AI& addModule(int n, int type, int energyuse, int cost, int energylevel = 0, int maxnumb = 0, int radius = 0, int angle = 0);

    AI& addDiffPlace(int x, int y, int type);

    AI& saveIntoFile(char *nameOfFile);

    bool stop();

    env getEn() const { return en; }

    AI& setEn(env enn) {en = *(enn.clone()); return *this; }

    std::vector<component*> getRobots() const { return robots; }

    friend std::ostream& operator <<(std::ostream &, const AI &);

    virtual ~AI(){
        for (component* &cmp: robots){
            delete cmp;
        }
        //std::cout << "destr ai " <<std::endl;
        robots.clear();
    }
};

}

#endif // AI_H
