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
        component* comp = nullptr;
        movcomp* movcom = nullptr;
        managecomp* mancomp = nullptr;
        movmanagecomp* movmancomp = nullptr;
        switch(type){
        case 0:
            comp = new component(x, y, maxnmod);
            en.setType(*comp);
            robots.push_back(comp);
            break;
        case 1:
            movcom = new movcomp(x, y, maxnmod, velocity);
            en.setType(*movcom);
            robots.push_back(movcom);
            break;
        case 2:
            mancomp = new managecomp(x, y, maxnmod);
            en.setType(*mancomp);
            robots.push_back(mancomp);
            break;
        case 3:
            movmancomp = new movmanagecomp(x, y, maxnmod, velocity);
            en.setType(*movmancomp);
            robots.push_back(movmancomp);
            break;
        }
        return *this;
    }

    AI& AI::addModule(int n, int type, int energyuse, int cost, int energylevel, int maxnumb, int radius, int angle)
    {
        if (n > robots.size() || n < 0){
            throw std::invalid_argument("Robots list not so long");
        }
        component *cmp = robots[n];

        manager *man = nullptr;
        generator *gen = nullptr;
        sensor *sen = nullptr;

        switch (type){
        case 1:
            gen = new generator(energylevel, cost);
            gen->setSost(ON);
            cmp->addModule(*gen);
            cmp->turnOnMod(cmp->getModules().size());
            //delete gen;
            break;
        case 2:
            sen = new sensor(radius, angle, energyuse, cost);
            sen->setSost(ON);
            cmp->addModule(*sen);
            cmp->turnOnMod(cmp->getModules().size());
            //delete sen;
            break;
        case 3:
            man = new manager(maxnumb, radius, cost, energyuse);
            man->setSost(ON);
            cmp->addModule(*man);
            cmp->setIsManaged(1);
            cmp->turnOnMod(cmp->getModules().size());
            //delete man;
            break;
        }

        return *this;

    }

    AI& AI::addDiffPlace(int x, int y, int type)
    {
        obstacle *obst = nullptr;
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
        }
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
                std::cout << i << " shag" << std::endl;
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

    int AI::goRobots(int energy) //доделать ситуацию с отрицательной энергией переданной (отключение модулей)
    {
        std::vector<module*> mod;
        std::vector<int> comps;
        std::vector<paircoord> x;
        component *cst = nullptr;
        movcomp *csmv = nullptr;
        int numpairs, energ = 0, m, n;
        paircoord y;
        sensor *sen = nullptr;
        generator *gen = nullptr;
        manager *man = nullptr;
        int go, go1;

        en.getRazm(m ,n);

        for (component *now: robots){
            go = 0;
            go1 = 0;
            energ -= now->getEnergyUse();
            csmv = dynamic_cast<movcomp*>(now);
            y.x = now->getX();
            y.y = now->getY();
            if(csmv->getIsManaged() == 0){
                std::cout << "NOT MANAGED module " << std::endl;
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
                    csmv->setX(csmv->getX() + n);
                }
                if(csmv->getX() >= n){
                    csmv->setX(csmv->getX() - n);
                }
                if(csmv->getY() < 0){
                    csmv->setY(csmv->getY() + m);
                }
                if(csmv->getY() < 0){
                    csmv->setY(csmv->getY() + m);
                }
                now->setX(csmv->getX());
                now->setY(csmv->getY());
                reMap(y.x, y.y, now);
                std::cout << "Moved component from " << y.x << " " << y.y << " to " << now->getX() << " " << now->getY() << std::endl;
            }
            mod = now->getModules();
            //num = now->getCurrNumMod();

            for(module *mods:mod){
                std::cout << "mod return type = " << mods->retType() << std::endl;
                std::cout << "mod sost is = " << mods->getSost() << std::endl;
                if(mods->retType() == 2 && mods->getSost() == ON){
                    sen = dynamic_cast<sensor*>(mods);
                    x = sen->getData(now->getX(), now->getY(), numpairs);
                    for (int k = 0; k < numpairs; ++k){
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
                        if(!(now->getX() == x[k].x && now->getY() == x[k].y)){
                            place* plc = new place(x[k].x, x[k].y);
                            plc->setSost(OPEN);
                            en.setType(*plc);
                        }
                    }
                }
                if(mods->retType() == 3 && mods->getSost() == ON){
                    std::cout << "i'm here!!!" <<std::endl;
                    man = dynamic_cast<manager*>(mods);
                    comps = man->getTab();
                    for (int cmp: comps){
                        cst = robots[cmp];
                        if(cst->getX() > now->getX() + man->getRadius() || cst->getY() > now->getY() + man->getRadius()){
                            man->delComp(cmp);
                            robots[cmp]->setIsManaged(0);
                            std::cout << "found bad robot and deleted it"<<std::endl;
                        }
                    }
                    int ijk = 0;
                    for (component *cmpv: robots){
                        std::cout << "new cmpv: " << cmpv->getX() << " " << cmpv->getY() << std::endl;
                        if (cmpv->getX() >= now->getX() - man->getRadius() && cmpv->getX() <= now->getX() + man->getRadius()){
                            if(cmpv->getY() >= now->getY() - man->getRadius() && cmpv->getY() <= now->getY() + man->getRadius()){
                                if(!(cmpv->getX() == now->getX() && cmpv->getY() == now->getY())){
                                    if (cmpv->getIsManaged() == 0){
                                        std::cout << "adding component to tab" << std::endl;
                                        man->addComp(ijk);
                                        cmpv->setIsManaged(1);
                                    }
                                }
                            }
                        }
                        ijk++;
                    }
                }
                if(mods->retType() == 1 && mods->getSost() == ON){
                    gen = dynamic_cast<generator*>(mods);
                    energ += gen->getEnergyLevel();
                }
            }
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


    AI& AI::reMap(int x, int y, component* comp)
    {
        place *plc = new place(x, y);
        plc->setSost(OPEN);
        en.setType(*(plc));
        en.setType(*comp);
        return *this;
    }
}
