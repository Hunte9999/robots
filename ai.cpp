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
        for (component* comp: robots){
            os << *comp << std::endl;
        }
        return os;
    }

    AI& AI::saveIntoFile(char *nameOfFile)
    {
        FILE *fp = fopen(nameOfFile, "w+b");
        int m, n;

        en.getRazm(m, n);

        std::fwrite(&m, sizeof(int), 1, fp);

        std::fwrite(&n, sizeof(int), 1, fp);

        return *this;
    }

    AI& AI::addComponent(int x, int y, int maxnmod, int type, int velocity)
    {
        component* cmp = en.addComponent(x, y, maxnmod, type, velocity);

        robots.push_back(cmp);

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
        /*obstacle *obst = nullptr;
        ti* t = nullptr;
        if (type == 0){
            obst = new obstacle(x, y);
            en.setType(*obst);
            //delete obst;
        }
        else{
            t = new ti(x, y);
            en.setType(*t);
            //delete t;
        }*/
        en.addDiffPlace(x, y, type);

        return *this;
    }

    AI& AI::start(int shag)
    {
        int energy = 0;
        if (shag < -1 || shag == 0){
            throw std::invalid_argument("Incorrect input");
        }

        if (robots.empty()){
            return *this;
        }
        if (shag == -1){
            while (!stop()){
                energy = goRobots(energy);
            }
        }
        else{
            for (int i = 0; i < shag; ++i){
                //if(stop()){
                //    break;
                //}
                //std::cout << i << " shag" << std::endl;
                energy = goRobots(energy);
            }
        }
        return *this;
    }

    int AI::canMove(movcomp* csmv, sides s) const
    {
        int velocity = csmv->getVelocity(), m, n;
        int x = csmv->getX(), y = csmv->getY();
        place *plc = nullptr;

        en.getRazm(m, n);

        switch(s){
        case UP:
            y += velocity;
            break;
        case DOWN:
            y -= velocity;
            break;
        case LEFT:
            x -= velocity;
            break;
        case RIGHT:
            x += velocity;
            break;
        }

        if(x < 0){
            x += n;
        }
        if (x >= n){
            x -= n;
        }
        if(y < 0){
            y += m;
        }
        if (y >= m){
            y -= m;
        }

        plc = en.getPlace(x, y);

        if((plc->retType() == 0 || plc->retType() == 1) && plc->getSost() == CLOSE){
            return 0;
        }

        return 1;
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

        en.getRazm(m ,n);

        for (component *now: robots){
            go = 0;
            go1 = 0;
            energ -= now->getEnergyUse();
            csmv = dynamic_cast<movcomp*>(now);
            y.x = now->getX();
            y.y = now->getY();
            if(!csmv){
                std::cout << "NOT MOVING COMPONENT" << std::endl;
            }
            else{
                if(csmv->getIsManaged() == 0){
                    std::cout << "NOT MANAGED component" << std::endl;
                }
            }
            if(csmv && csmv->getIsManaged() == 1){ //переделать в нормальный поиск пути
                do{
                    go1 = go;
                    switch(rand()%4){
                    case 0:
                        go += canMove(csmv, RIGHT);
                        if(go == go1)
                            csmv->Move(RIGHT);
                        break;
                    case 1:
                        go += canMove(csmv, LEFT);
                        if(go == go1)
                            csmv->Move(LEFT);
                        break;
                    case 2:
                        go += canMove(csmv, UP);
                        if(go == go1)
                            csmv->Move(UP);
                        break;
                    case 3:
                        go += canMove(csmv, DOWN);
                        if(go == go1)
                            csmv->Move(DOWN);
                        break;
                    }
                } while(go != go1 && go1 < 100);
                if(csmv->getX() < 0){
                    csmv->setX(csmv->getX() + m);
                }
                if(csmv->getX() >= n){
                    csmv->setX(csmv->getX() - m);
                }
                if(csmv->getY() < 0){
                    csmv->setY(csmv->getY() + n);
                }
                if(csmv->getY() < 0){
                    csmv->setY(csmv->getY() + n);
                }
                now->setX(csmv->getX());
                now->setY(csmv->getY());
                reMap(y.x, y.y, sch);
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
                            std::cout <<"k: " << k << ", x: " << x[k].x << ", y: " << x[k].y << std::endl;
                        if(x[k].x < 0){
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
                        }
                        std::cout <<"k: " << k << ", x: " << x[k].x << ", y: " << x[k].y << std::endl;
                        en.getPlace(x[k].x, x[k].y)->setSost(OPEN);
                        /*if(!(now->getX() == x[k].x && now->getY() == x[k].y)){
                            place* plc = new place(x[k].x, x[k].y);
                            plc->setSost(OPEN);
                            en.setType(*plc);
                        }*/
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
                        std::cout << "new cmpv: " << cmpv->getX() << " " << cmpv->getY() << std::endl;
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

    bool AI::stop() // доделать варианты остановки алгоритма
    {
        int m, n;
        bool isOpen = true;

        en.getRazm(m, n);
        for (int i = 0; i < m; ++i){
            for (int j = 0; j < n; ++j){
                if(en.getPlace(j, i)->getSost() == CLOSE){
                    isOpen = false;
                    break;
                }
            }
            if (!isOpen){
                break;
            }
        }
        return isOpen;
    }


    AI& AI::reMap(int x, int y, int n)
    {
        component* comp = robots[n];
        place* plc = nullptr;
        if(!(x == comp->getX() && y == comp->getY())){
            en.swap(x, y, comp->getX(), comp->getY());
            plc = new place(x, y);
            plc->setSost(OPEN);
            en.setType(*(plc));
        }
        return *this;
    }
}
