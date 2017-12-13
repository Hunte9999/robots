#include "ai.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include "managecomp.h"
#include "movmanagecomp.h"
#include "generator.h"
#include "sensor.h"
#include "manager.h"
#include "obstacle.h"
#include "ti.h"
#include <set>

namespace robots{

    /*AI::AI(char* nameOfFile) // доделать это и запись в файл
    {
        FILE *fp = fopen(nameOfFile, "r+b");
        int m, n;
        env *en1;
        std::fread(&m, sizeof(int), 1, fp);
        std::fread(&n, sizeof(int), 1, fp);
        en1 = new env(m, n);
        en = *en1;
        delete en1;
        //if(!fin.is_open())
        //    throw std::invalid_argument("Invalid file name");
    }*/

    std::ostream& operator <<(std::ostream &os, const AI &n)
    {
        return os << n.en;
    }

    std::ostream& AI::showRobots(std::ostream &os) const
    {
        for(component* comp: robots){
            os << *(comp) << std::endl;
        }
        return os;
    }

    /*AI& AI::saveIntoFile(char *nameOfFile)
    {
        FILE *fp = fopen(nameOfFile, "w+b");
        int m, n;

        en.getRazm(m, n);

        std::fwrite(&m, sizeof(int), 1, fp);

        std::fwrite(&n, sizeof(int), 1, fp);

        return *this;
    }*/

    AI& AI::addComponent(int x, int y, int maxnmod, int type, int velocity)
    {
        component* cmp = en.addComponent(x, y, maxnmod, type, velocity);

        robots.push_back(cmp);
        std::cout << " size of Vector: " << robots.size() << std::endl;

        return *this;
    }

    AI& AI::addModule(int n, int type, int energyuse, int cost, int energylevel, int maxnumb, int radius, int angle)
    {
        if (n > robots.size() || n < 0){
            throw std::invalid_argument("Robots list not so long");
        }
        component *cmp = robots[n];
        en.addModule(cmp->getX(), cmp->getY(), type, energyuse, cost, energylevel, maxnumb, radius, angle);

        return *this;

    }

    AI& AI::addDiffPlace(int x, int y, int type)
    {

        en.addDiffPlace(x, y, type);

        return *this;
    }

    AI& AI::start(int shag)
    {
        int energy = 0, x;
        if (shag < -1 || shag == 0){
            throw std::invalid_argument("Incorrect input");
        }

        if (robots.empty()){
            return *this;
        }
        if (shag == -1){
            while (!en.isFinished()){
                energy = goRobots(energy);
                std::cout << energy << " energy" << std::endl;
                /*while (energy <= 0){
                    x = offModulesEnergyLack();
                    std::cout << x << " x" << std::endl;
                    if(x == 0){
                        throw std::length_error("ADD NEW GENERATORS PLEASE!!");
                    }
                    energy += x;
                }*/
            }
        }
        else{
            for (int i = 0; i < shag; ++i){
                if(en.isFinished()){
                    break;
                }
                //std::cout << i << " shag" << std::endl;
                energy = goRobots(energy);
                std::cout << energy << " energy" << std::endl;
                /*while (energy <= 0){
                    x = offModulesEnergyLack();
                    (std::cout << x << " x" << std::endl;
                    if(x == 0){
                        throw std::length_error("ADD NEW GENERATORS PLEASE!!");
                    }
                    energy += x;
                }*/
            }
        }
        return *this;
    }

    int AI::goRobots(int energy)
    {
        std::vector<module*> mod;
        std::vector<component*> comps;
        std::vector<paircoord> x;
        //component *cst = nullptr;
        movcomp *csmv = nullptr;
        int energ = 0, m, n;
        paircoord y;
        sensor *sen = nullptr;
        generator *gen = nullptr;
        manager *man = nullptr;
        int go, go1, sch = 0;
        int ars[4];
        sides a, a1;

        en.getRazm(n ,m);

        for (component *now: robots){
            //std::cout << *now << std::endl;
            go = 0;
            energ -= now->getEnergyUse();
            csmv = dynamic_cast<movcomp*>(now);
            y.x = now->getX();
            y.y = now->getY();
            /*if(!csmv){
                std::cout << "NOT MOVING COMPONENT" << std::endl;
            }
            else{
                if(csmv->getIsManaged() == 0){
                    std::cout << "NOT MANAGED component" << std::endl;
                }
            }*/
            if(csmv && csmv->getIsManaged() == 1){
                /*ars[0] = en.howManyStepsCanBeMoved(csmv, UP, csmv->getVelocity());
                ars[1] = en.howManyStepsCanBeMoved(csmv, DOWN, csmv->getVelocity());
                ars[2] = en.howManyStepsCanBeMoved(csmv, LEFT, csmv->getVelocity());
                ars[3] = en.howManyStepsCanBeMoved(csmv, RIGHT, csmv->getVelocity());
                go = ars[0];
                a = UP;

                if(ars[1] > go){
                    go = ars[1];
                    a = DOWN;
                }

                if(ars[2] > go){
                    go = ars[2];
                    a = LEFT;
                }

                if(ars[3] > go){
                    go = ars[3];
                    a = RIGHT;
                }

                if(a == UP){
                    a1 = DOWN;
                    go1 = ars[1];
                }
                else{
                    a1 = UP;
                    go1 = ars[0];
                }

                if(ars[0] > go1 && a != UP){
                    a1 = UP;
                    go1 = ars[0];
                }

                if(ars[1] > go1 && a != DOWN){
                    a1 = DOWN;
                    go1 = ars[1];
                }

                if(ars[2] > go1 && a != LEFT){
                    a1 = LEFT;
                    go1 = ars[2];
                }

                if(ars[3] > go1 && a != RIGHT){
                    a1 = RIGHT;
                    go1 = ars[3];
                }

                std::map<component*, paircoord>::iterator it = lastPlaces.find(csmv);
                if(it != lastPlaces.end()){
                    int x2 = y.x, y2 = y.y;
                    switch (a){
                    case RIGHT:
                        x2 += go;
                        break;
                    case LEFT:
                        x2 -= go;
                        break;
                    case UP:
                        y2 += go;
                        break;
                    case DOWN:
                        y2 -= go;
                        break;
                    }
                    if (it->second.x == x2 && it->second.y == y2){
                        go = go1;
                        a = a1;
                    }
                }
                //std::cout << "go = " << go << ", a = " << a << std::endl;
                if(go > 0){
                    bool isMoved = en.Move(csmv, a, go);
                    if(isMoved){
                        if (it != lastPlaces.end()){
                            lastPlaces.erase(it);
                        }
                        paircoord z;
                        z.x = csmv->getX();
                        z.y = csmv->getY();
                        lastPlaces.insert(std::pair<component*, paircoord>(csmv, z));
                        now->setX(csmv->getX());
                        now->setY(csmv->getY());
                        std::cout << "Moved component from " << y.x << " " << y.y << " to " << now->getX() << " " << now->getY() << std::endl;
                    }
                }*/

                switch(rand()%4){
                case 0:
                    en.Move(csmv, RIGHT, en.howManyStepsCanBeMoved(csmv, RIGHT, csmv->getVelocity()));
                    break;
                case 1:
                    en.Move(csmv, LEFT, en.howManyStepsCanBeMoved(csmv, LEFT, csmv->getVelocity()));
                    break;
                case 2:
                    en.Move(csmv, UP, en.howManyStepsCanBeMoved(csmv, UP, csmv->getVelocity()));
                    break;
                case 3:
                    en.Move(csmv, DOWN, en.howManyStepsCanBeMoved(csmv, DOWN, csmv->getVelocity()));
                    break;
                }

                now->setX(csmv->getX());
                now->setY(csmv->getY());
                std::cout << "Moved component from " << y.x << " " << y.y << " to " << now->getX() << " " << now->getY() << std::endl;

            }
            mod = now->getModules();
            //num = now->getCurrNumMod();

            for(module *mods:mod){
                std::cout << "mod return type = " << mods->retType() << std::endl;
                std::cout << "mod sost is = " << mods->getSost() << std::endl;
                if(mods->retType() == 2 && mods->getSost() == ON){
                    sen = dynamic_cast<sensor*>(mods);
                    x = sen->getData(now->getX(), now->getY());
                    for (int k = 0; k < x.size(); ++k){
                         //std::cout <<"k: " << k << ", x: " << x[k].x << ", y: " << x[k].y << std::endl;
                        /*if(x[k].x < 0){
                            x[k].x += m;
                        }
                        if(x[k].y < 0){
                            x[k].y += n;
                        }
                        if(x[k].x >= m){
                            x[k].x -= m;
                        }
                        if(x[k].y >= n){
                            x[k].y -= n;
                        }*/
                        if(x[k].x >=0 && x[k].x < n && x[k].y >= 0 && x[k].y < m){
                            std::cout <<"k: " << k << ", x: " << x[k].x << ", y: " << x[k].y << std::endl;
                            en.getPlace(x[k].x, x[k].y)->setSost(OPEN);
                        }
                    }
                }
                if(mods->retType() == 3 && mods->getSost() == ON){
                    man = dynamic_cast<manager*>(mods);
                    comps = man->getTab();
                    for (component* cst: comps){

                        if(cst->getX() > now->getX() + man->getRadius() || cst->getY() > now->getY() + man->getRadius()){
                            man->delComp(cst);
                            cst->setIsManaged(0);
                            std::cout << "found bad robot and deleted it"<<std::endl;
                        }
                    }

                    for (component *cmpv: robots){
                        //std::cout << "new cmpv: " << cmpv->getX() << " " << cmpv->getY() << std::endl;
                        if (cmpv->getX() >= now->getX() - man->getRadius() && cmpv->getX() <= now->getX() + man->getRadius()){
                            if(cmpv->getY() >= now->getY() - man->getRadius() && cmpv->getY() <= now->getY() + man->getRadius()){
                                if(!(cmpv->getX() == now->getX() && cmpv->getY() == now->getY())){
                                    if (cmpv->getIsManaged() == 0){
                                        std::cout << "adding component to tab" << std::endl;
                                        man->addComp(cmpv);
                                        cmpv->setIsManaged(1);
                                    }
                                }
                            }
                        }

                    }
                }
                if(mods->retType() == 1 && mods->getSost() == ON){
                    gen = dynamic_cast<generator*>(mods);
                    energ += gen->getEnergyLevel();
                }
            }
            sch++;
        }

        return energ + energy;
    }

    /*int AI::offModulesEnergyLack()
    {
        int robot = 0, modul = 0, cmprior = robots[0]->getModules()[0]->getPriority();
        bool flag = false;
        std::vector<module*> mod;
        for(int i = 0; i < robots.size(); ++i){
            mod = robots[i]->getModules();
            for (int j = 0; j < mod.size(); ++j){
                std::cout << i << " i, " << j << " j" << std::endl;
                if(mod[j]->getSost() == ON && (mod[j]->getPriority() < cmprior || cmprior < 0) && mod[j]->getPriority() >= 0){
                    robot = i;
                    modul = j;
                    cmprior = mod[j]->getPriority();
                }
                if(mod[j]->getPriority() >= 0){
                    flag = true;
                }
            }
        }

        if(flag){
            std::cout << robot << " robot, " << modul << " modul" << std::endl;
            //robots[robot]->getModules()[modul]->setSost(OFF);
            robots[robot]->turnOffMod(modul);
            return robots[robot]->getModules()[modul]->getEnergyUse();
        }

        return 0;
    }

    int AI::onModulesEnoughEnergy(int energy)
    {

    }*/
}
