#ifndef AI_H
#define AI_H

#include "env.h"
#include <iostream>
#include <vector>
#include "component.h"
#include "movcomp.h"
#include "/home/frostic/proglabs/roboti/myvector.h"

namespace robots{

class AI
{
private:
    env en;
    Vector<component*> robots;
protected:
    int goRobots(int energy);
public:
    AI(env& envi): en(envi) {
        int a, b;
        place* plc = nullptr;
        en.getRazm(a, b);
        for (int i = 0; i < a; ++i){
            for (int j = 0; j < b; ++j){
                plc = en.getPlace(i, j);
                if(plc->retType() > 2){
                    robots.push_back(dynamic_cast<component*>(plc));
                }
            }
        }
    }
    AI(const AI& a): en(a.getEn()){
        Vector<component*> robs = a.getRobots();

        for (component* cmp: robs){
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

    const env &getEn() const { return en; }

    AI& setEn(const env& enn) {en = *(enn.clone()); return *this; }

    Vector<component*> getRobots() const { return robots; }

    friend std::ostream& operator <<(std::ostream &, const AI &);

    virtual ~AI(){
        //std::cout << "destr ai " <<std::endl;
        //robots.clear();
    }
};

}

#endif // AI_H
