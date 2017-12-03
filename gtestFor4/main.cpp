#include <iostream>
#include "gtest/gtest.h"
#include <ai.h>
#include <env.h>
#include <ti.h>
#include <obstacle.h>
#include <managecomp.h>
#include<movmanagecomp.h>
#include <manager.h>
#include <sensor.h>
#include <generator.h>
#include <module.h>

TEST(Constructors, Places)
{
    robots::place plc(1,5);
    ASSERT_EQ(plc.getSost(), 1);
    ASSERT_EQ(plc.getX(), 1);
    ASSERT_EQ(plc.getY(), 5);
    ASSERT_EQ(plc.retType(), 0);

    robots::place plc1(plc);
    ASSERT_EQ(plc1.getSost(), 1);
    ASSERT_EQ(plc1.getX(), 1);
    ASSERT_EQ(plc1.getY(), 5);
    ASSERT_EQ(plc1.retType(), 0);

    robots::ti tii(10,15);
    ASSERT_EQ(tii.getSost(), 1);
    ASSERT_EQ(tii.getX(), 10);
    ASSERT_EQ(tii.getY(), 15);
    ASSERT_EQ(tii.retType(), 1);

    robots::ti tii1(tii);
    ASSERT_EQ(tii1.getSost(), 1);
    ASSERT_EQ(tii1.getX(), 10);
    ASSERT_EQ(tii1.getY(), 15);
    ASSERT_EQ(tii1.retType(), 1);

    robots::obstacle obst(56, 9);
    ASSERT_EQ(obst.getSost(), 1);
    ASSERT_EQ(obst.getX(), 56);
    ASSERT_EQ(obst.getY(), 9);
    ASSERT_EQ(obst.retType(), 2);

    robots::obstacle obst1(obst);
    ASSERT_EQ(obst1.getSost(), 1);
    ASSERT_EQ(obst1.getX(), 56);
    ASSERT_EQ(obst1.getY(), 9);
    ASSERT_EQ(obst1.retType(), 2);
}

TEST(Constructors, Components)
{
    robots::component comp(67, 87, 3);
    ASSERT_EQ(comp.getSost(), 0);
    ASSERT_EQ(comp.getX(), 67);
    ASSERT_EQ(comp.getY(), 87);
    ASSERT_EQ(comp.getCurrNumMod(), 0);
    ASSERT_EQ(comp.getMaxNumMod(), 3);
    ASSERT_EQ(comp.retType(), 3);

    robots::component comp1(comp);
    ASSERT_EQ(comp1.getSost(), 0);
    ASSERT_EQ(comp1.getX(), 67);
    ASSERT_EQ(comp1.getY(), 87);
    ASSERT_EQ(comp1.getCurrNumMod(), 0);
    ASSERT_EQ(comp1.getMaxNumMod(), 3);
    ASSERT_EQ(comp1.retType(), 3);

    robots::movcomp mov(90, 56, 2, 3);
    ASSERT_EQ(mov.getSost(), 0);
    ASSERT_EQ(mov.getX(), 90);
    ASSERT_EQ(mov.getY(), 56);
    ASSERT_EQ(mov.getCurrNumMod(), 0);
    ASSERT_EQ(mov.getMaxNumMod(), 2);
    ASSERT_EQ(mov.retType(), 4);
    ASSERT_EQ(mov.getVelocity(), 3);

    robots::movcomp mov1(mov);
    ASSERT_EQ(mov1.getSost(), 0);
    ASSERT_EQ(mov1.getX(), 90);
    ASSERT_EQ(mov1.getY(), 56);
    ASSERT_EQ(mov1.getCurrNumMod(), 0);
    ASSERT_EQ(mov1.getMaxNumMod(), 2);
    ASSERT_EQ(mov1.retType(), 4);
    ASSERT_EQ(mov1.getVelocity(), 3);

    robots::managecomp mancmp(48, 103, 5);
    ASSERT_EQ(mancmp.getSost(), 0);
    ASSERT_EQ(mancmp.getX(), 48);
    ASSERT_EQ(mancmp.getY(), 103);
    ASSERT_EQ(mancmp.getCurrNumMod(), 0);
    ASSERT_EQ(mancmp.getMaxNumMod(), 5);
    ASSERT_EQ(mancmp.retType(), 5);

    robots::managecomp mancmp1(mancmp);
    ASSERT_EQ(mancmp1.getSost(), 0);
    ASSERT_EQ(mancmp1.getX(), 48);
    ASSERT_EQ(mancmp1.getY(), 103);
    ASSERT_EQ(mancmp1.getCurrNumMod(), 0);
    ASSERT_EQ(mancmp1.getMaxNumMod(), 5);
    ASSERT_EQ(mancmp1.retType(), 5);

    robots::movmanagecomp mvmncmp(76, 57, 3, 1);
    ASSERT_EQ(mvmncmp.getSost(), 0);
    ASSERT_EQ(mvmncmp.getX(), 76);
    ASSERT_EQ(mvmncmp.getY(), 57);
    ASSERT_EQ(mvmncmp.getCurrNumMod(), 0);
    ASSERT_EQ(mvmncmp.getMaxNumMod(), 3);
    ASSERT_EQ(mvmncmp.retType(), 6);
    ASSERT_EQ(mvmncmp.getVelocity(), 1);

    robots::movmanagecomp mvmncmp1(mvmncmp);
    ASSERT_EQ(mvmncmp1.getSost(), 0);
    ASSERT_EQ(mvmncmp1.getX(), 76);
    ASSERT_EQ(mvmncmp1.getY(), 57);
    ASSERT_EQ(mvmncmp1.getCurrNumMod(), 0);
    ASSERT_EQ(mvmncmp1.getMaxNumMod(), 3);
    ASSERT_EQ(mvmncmp1.retType(), 6);
    ASSERT_EQ(mvmncmp1.getVelocity(), 1);
}

TEST(Constructors, Modules)
{
    robots::manager man(3, 2, 10, 14);
    ASSERT_EQ(man.getCurrNumb(), 0);
    ASSERT_EQ(man.getEnergyUse(), 14);
    ASSERT_EQ(man.getPriority(), -1);
    ASSERT_EQ(man.getRadius(), 2);
    ASSERT_EQ(man.getSost(), 0);
    ASSERT_EQ(man.getMaxNumb(), 3);
    ASSERT_EQ(man.retType(), 3);
    ASSERT_EQ(man.getCost(), 10);

    robots::manager man1(man);
    ASSERT_EQ(man1.getCurrNumb(), 0);
    ASSERT_EQ(man1.getEnergyUse(), 14);
    ASSERT_EQ(man1.getPriority(), -1);
    ASSERT_EQ(man1.getRadius(), 2);
    ASSERT_EQ(man1.getSost(), 0);
    ASSERT_EQ(man1.getMaxNumb(), 3);
    ASSERT_EQ(man1.retType(), 3);
    ASSERT_EQ(man1.getCost(), 10);

    robots::sensor sen(3, 90, 5, 20);
    ASSERT_EQ(sen.getEnergyUse(), 5);
    ASSERT_EQ(sen.getPriority(), 0);
    ASSERT_EQ(sen.getRadius(), 3);
    ASSERT_EQ(sen.getSost(), 0);
    ASSERT_EQ(sen.retType(), 2);
    ASSERT_EQ(sen.getCost(), 20);
    ASSERT_EQ(sen.getAngle(), 90);

    robots::sensor sen1(sen);
    ASSERT_EQ(sen1.getEnergyUse(), 5);
    ASSERT_EQ(sen1.getPriority(), 0);
    ASSERT_EQ(sen1.getRadius(), 3);
    ASSERT_EQ(sen1.getSost(), 0);
    ASSERT_EQ(sen1.retType(), 2);
    ASSERT_EQ(sen1.getCost(), 20);
    ASSERT_EQ(sen1.getAngle(), 90);

    robots::generator gen(50, 7);
    ASSERT_EQ(gen.getCost(), 7);
    ASSERT_EQ(gen.getEnergyLevel(), 50);
    ASSERT_EQ(gen.getEnergyUse(), 0);
    ASSERT_EQ(gen.getPriority(), -1);
    ASSERT_EQ(gen.getSost(), 0);

    robots::generator gen1(gen);
    ASSERT_EQ(gen1.getCost(), 7);
    ASSERT_EQ(gen1.getEnergyLevel(), 50);
    ASSERT_EQ(gen1.getEnergyUse(), 0);
    ASSERT_EQ(gen1.getPriority(), -1);
    ASSERT_EQ(gen1.getSost(), 0);
}

TEST(Constructors, AI_and_ENV)
{
    robots::env enn(90, 60);
    int a, b;
    enn.getRazm(a, b);
    ASSERT_EQ(a, 90);
    ASSERT_EQ(b, 60);

    for (int i = 0; i < 60; ++i){
        for(int j = 0; j < 90; ++j){
            ASSERT_EQ(enn.getPlace(j, i)->retType(), 0);
        }
    }

    robots::AI ai(enn);
    ai.getEn().getRazm(a, b);
    ASSERT_EQ(a, 90);
    ASSERT_EQ(b, 60);
    ASSERT_EQ(ai.getRobots().size(), 0);
    robots::env enn1(ai.getEn());

    for (int i = 0; i < 60; ++i){
        for(int j = 0; j < 90; ++j){
            ASSERT_EQ(enn1.getPlace(j, i)->retType(), 0);
        }
    }
}

TEST(Methods, Components_and_Modules)
{
    robots::component comp(67, 98, 5);
    robots::movcomp movcomp(89, 30, 4, 2);
    robots::managecomp mancomp(78, 45, 5);
    robots::movmanagecomp movmancomp(3, 2, 4, 1);
    robots::generator gen(5, 3);
    robots::manager man(3, 5, 2, 3);
    robots::sensor sen(1, 0, 3, 3);

    comp.addModule(sen);
    ASSERT_EQ(comp.getCurrNumMod(), 1);
    ASSERT_EQ(comp.getModules()[0]->getSost(), 0);
    comp.turnOffMod(1);
    ASSERT_EQ(comp.getModules()[0]->getSost(), 1);
    comp.turnOnMod(1);
    ASSERT_EQ(comp.getModules()[0]->getSost(), 0);

    movcomp.addModule(gen);
    ASSERT_EQ(movcomp.getCurrNumMod(), 1);
    ASSERT_EQ(movcomp.getModules()[0]->getSost(), 0);
    movcomp.turnOffMod(1);
    ASSERT_EQ(movcomp.getModules()[0]->getSost(), 1);
    movcomp.turnOnMod(1);
    ASSERT_EQ(movcomp.getModules()[0]->getSost(), 0);
    movcomp.Move(robots::LEFT);
    ASSERT_EQ(movcomp.getX(), 87);
    movcomp.Move(robots::UP);
    ASSERT_EQ(movcomp.getY(), 32);
    movcomp.Move(robots::RIGHT);
    ASSERT_EQ(movcomp.getX(), 89);
    movcomp.Move(robots::DOWN);
    ASSERT_EQ(movcomp.getY(), 30);


    mancomp.addModule(man);
    ASSERT_EQ(mancomp.getCurrNumMod(), 1);
    ASSERT_EQ(mancomp.getModules()[0]->getSost(), 0);
    mancomp.turnOffMod(1);
    ASSERT_EQ(mancomp.getModules()[0]->getSost(), 1);
    mancomp.turnOnMod(1);
    ASSERT_EQ(mancomp.getModules()[0]->getSost(), 0);

    movmancomp.addModule(gen);
    ASSERT_EQ(movmancomp.getCurrNumMod(), 1);
    ASSERT_EQ(movmancomp.getModules()[0]->getSost(), 0);
    movmancomp.turnOffMod(1);
    ASSERT_EQ(movmancomp.getModules()[0]->getSost(), 1);
    movmancomp.turnOnMod(1);
    ASSERT_EQ(movmancomp.getModules()[0]->getSost(), 0);
    movmancomp.Move(robots::LEFT);
    ASSERT_EQ(movmancomp.getX(), 2);
    movmancomp.Move(robots::UP);
    ASSERT_EQ(movmancomp.getY(), 3);
    movmancomp.Move(robots::RIGHT);
    ASSERT_EQ(movmancomp.getX(), 3);
    movmancomp.Move(robots::DOWN);
    ASSERT_EQ(movmancomp.getY(), 2);

    ASSERT_ANY_THROW(comp.addModule(man));
    ASSERT_ANY_THROW(movcomp.addModule(man));

    std::vector<robots::paircoord> x = sen.getData(3, 5);

    for(int i = 4; i < 7; ++i){
        for(int j = 2; j < 5; ++j){
            ASSERT_EQ(x[(i - 4) * 3 + (j - 2)].x, j);
            ASSERT_EQ(x[(i - 4) * 3 + (j - 2)].y, i);
        }
    }
    sen.setSost(robots::OFF);
    ASSERT_EQ(sen.getSost(), 1);

    gen.setSost(robots::OFF);
    ASSERT_EQ(gen.getSost(), 1);

    man.addComp(&movcomp);
    ASSERT_EQ(man.getCurrNumb(), 1);
    std::vector<robots::component*> tab = man.getTab();
    ASSERT_EQ(tab[0], &movcomp);
    ASSERT_EQ(tab.size(), 1);
}

TEST(Methods, Places_Env)
{
    robots::place plc(78, 3);
    plc.setSost(robots::OPEN);
    ASSERT_EQ(plc.getSost(), robots::OPEN);

    robots::env enn(45, 15);
    enn.addDiffPlace(5, 10, 0);
    robots::place *plc1 = enn.getPlace(5, 10);
    ASSERT_EQ(plc1->retType(), 2);
    enn.addDiffPlace(10, 5, 1);
    plc1 = enn.getPlace(10, 5);
    ASSERT_EQ(plc1->retType(), 1);
    ASSERT_ANY_THROW(enn.addDiffPlace(-1, 4, 2));
    ASSERT_ANY_THROW(enn.addDiffPlace(1, 20, 2));
    ASSERT_ANY_THROW(enn.addDiffPlace(1, 4, 2));
    enn.addComponent(10, 10, 2, 3, 1);
    plc1 = enn.getPlace(10, 10);
    ASSERT_EQ(plc1->retType(), 6);
    robots::movmanagecomp *comp = dynamic_cast<robots::movmanagecomp*>(plc1);
    ASSERT_EQ(comp->getX(), 10);
    ASSERT_EQ(comp->getY(), 10);

    enn.addModule(10, 10, 3, 1, 1, 0, 2, 2, 0);
    ASSERT_EQ(comp->getCurrNumMod(), 1);

    enn.addComponent(8, 9, 1, 1, 2);
    plc1 = enn.getPlace(8, 9);
    ASSERT_EQ(plc1->retType(), 4);
    robots::movcomp *comp1 = dynamic_cast<robots::movcomp*>(plc1);
    ASSERT_EQ(comp1->getX(), 8);
    ASSERT_EQ(comp1->getY(), 9);

    enn.addModule(8, 9, 2, 1, 1, 0, 0, 1, 0);
    ASSERT_EQ(comp1->getCurrNumMod(), 1);
}

int main(int argc, char*argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

