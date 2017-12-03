#include <iostream>
#include <ai.h>

int AddModule(robots::AI&);
int AddComponent(robots::AI&);
int AddUnusualPlace(robots::AI&);
robots::AI CreateRandomMap();
int Start(robots::AI&);
int ShowMap(robots::AI&);
int ShowAll(robots::AI&);
int getInt(int &);
int Dialog();

int main()
{
    robots::AI ai(CreateRandomMap());

    int ch;

    int (*P[])(robots::AI&) = {AddComponent, AddModule, AddUnusualPlace, Start, ShowMap, ShowAll};
    while ((ch = Dialog())){
        if (!(P[ch - 1])(ai)){
            break;
        }
    }

    return 0;
}

int getInt(int &a)
{
    std::cin >> a;
    if (!std::cin.good())
        return -1;
    return 1;
}

int Dialog()
{
    int n, o;
    std::cout << std::endl;
    char s[7][20] = {"0.Exit", "1.AddComponent", "2.AddModule", "3.AddObstacle", "4.Start Finding", "5.Show map", "6.Show components"};
    for (o = 0; o < 7; o++){
        std::cout << s[o] << std::endl;
    }
    std::cout << std::endl;
    do{
        o = getInt(n);
        if (!o){
            return 0;
        }
        if (n > 6){
            std::cout << "Input number must be <7 and >=0" << std::endl;
        }
    }while(n > 6);
    std::cout << std::endl;
    return n;
}

int AddComponent(robots::AI &a)
{
    int type, x, y, maxnmod, velocity = 0, xa, yb;
    a.getEn().getRazm(xa, yb);
    std::cout << "Input type of robot you want to add (0 - simple, 1 - moving, 2 - manager, 3 - moving manager" << std::endl;
    do{
        getInt(type);
        if (type < 0 || type > 3){
            std::cout << "Please, input correct numbers" << std::endl;
        }
    }while(type < 0 || type > 3);
    std::cout << "Input maxnumber of modules for this robot ( > 0) "<< std::endl;
    do{
        getInt(maxnmod);
        if (maxnmod < 0){
            std::cout << "Please, input correct numbers" << std::endl;
        }
    }while(maxnmod < 0);
    std::cout << "Input coordinates for your robot" << std::endl;
    getInt(x);
    getInt(y);
    while(x < 0 || x >= xa){
        std::cout << "Please, input correct x coordinate" << std::endl;
        getInt(x);
    }
    while(y < 0 || y >= yb){
        std::cout << "Please, input correct y coordinate" << std::endl;
        getInt(y);
    }
    if (type == 1 || type == 3){
        std::cout << "Input velocity of your robot" << std::endl;
        getInt(velocity);
        while(velocity < 0){
            std::cout <<"Input correct velocity" << std::endl;
            getInt(velocity);
        }
    }
    try{
        a.addComponent(x, y, maxnmod, type, velocity);
    }catch (std::exception &ex){
        ex.what();
        return -1;
    }
    return 1;
}

int AddModule(robots::AI &a)
{
    int n, type, energyuse, cost, energylevel = 0, maxnumb = 0, radius = 0, angle = 0;
    std::cout << "Input number of robot you want to input module to ( > 0)" << std::endl;
    getInt(n);
    while(n < 0){
        std::cout <<"Input correct number" << std::endl;
        getInt(n);
    }
    std::cout << "Input type of module you want to input(1 - generator, 2 - sensor, 3 - manager)" << std::endl;
    getInt(type);
    while(type < 1 || type > 3){
        std::cout <<"Input correct number" << std::endl;
        getInt(type);
    }
    std::cout << "Input cost of module( > 0)" << std::endl;
    getInt(cost);
    while(cost < 0){
        std::cout <<"Input correct data" << std::endl;
        getInt(cost);
    }
    switch(type){
    case 1:
        std::cout << "Input energylevel of generator ( >0)" << std::endl;
        getInt(energylevel);
        while(cost < 0){
            std::cout <<"Input correct data" << std::endl;
            getInt(energylevel);
        }
        energyuse = 0;
        break;
    case 2:
        std::cout << "Input radius of sensor ( >0)" << std::endl;
        getInt(radius);
        while(cost < 0){
            std::cout <<"Input correct data" << std::endl;
            getInt(radius);
        }
        std::cout << "Input energyuse of sensor ( >0)" << std::endl;
        getInt(energyuse);
        while(cost < 0){
            std::cout <<"Input correct data" << std::endl;
            getInt(energyuse);
        }
        break;
    case 3:
        std::cout << "Input radius of manager ( >0)" << std::endl;
        getInt(radius);
        while(cost < 0){
            std::cout <<"Input correct data" << std::endl;
            getInt(radius);
        }
        std::cout << "Input energyuse of manager ( >0)" << std::endl;
        getInt(energyuse);
        while(cost < 0){
            std::cout <<"Input correct data" << std::endl;
            getInt(energyuse);
        }
        std::cout << "Input max number of components under this manager control ( >0)" << std::endl;
        getInt(maxnumb);
        while(cost < 0){
            std::cout <<"Input correct data" << std::endl;
            getInt(maxnumb);
        }
        break;
    }
    try{
        a.addModule(n, type, energyuse, cost, energylevel, maxnumb, radius, angle);
    }
    catch(std::exception &ex){
        ex.what();
        return -1;
    }
    return 1;
}

int AddUnusualPlace(robots::AI &a)
{
    int x, y, type, xa, yb;
    a.getEn().getRazm(xa, yb);
    std::cout << "Input type of place you want to add (0 - obstacle, 1 - point of interests)" << std::endl;
    getInt(type);
    while(type < 0 || type > 1){
        std::cout <<"Input correct data" << std::endl;
        getInt(type);
    }
    std::cout << "Input coordinates for your robot" << std::endl;
    getInt(x);
    getInt(y);
    while(x < 0 || x >= xa){
        std::cout << "Please, input correct x coordinate" << std::endl;
        getInt(x);
    }
    while(y < 0 || y >= yb){
        std::cout << "Please, input correct y coordinate" << std::endl;
        getInt(y);
    }
    try{
        a.addDiffPlace(x, y, type);
    } catch(std::exception &ex){
        ex.what();
        return -1;
    }
    return 1;
}

int ShowMap(robots::AI &a)
{
    std::cout << a.getEn() << std::endl;
    return 1;
}

int ShowAll(robots::AI &a)
{
    a.showRobots(std::cout);
    return 1;
}

int Start(robots::AI &a)
{
    int shagi;
    std::cout << "Input number of moves you want robots to do (-1 to move until the end)" << std::endl;
    getInt(shagi);
    while(shagi == 0 || shagi < -1){
        std::cout <<"Input correct number" << std::endl;
        getInt(shagi);
    }
    try{
        a.start(shagi);
    }catch (std::exception &ex)
    {
        //std::cout << " KLKLALS" << std::endl;
        ex.what();
        return -1;
    }
    return 1;
}


robots::AI CreateRandomMap()
{
    int a = rand()%20 + 5, b = rand()%20 + 5, numobst = rand()%10+1, numti = rand()%5 + 1, x, y;
    robots::env en(a, b);
    robots::AI res(en);
    bool da;
    for (int i = 0; i < numobst; ++i){
        da = false;
        do{
            x = rand()%a;
            y = rand()%b;
            //if(res.getEn().getPlace(x, y)->retType() == 0){
                res.addDiffPlace(x, y, 0);
                da = true;
            //}
        }while(!da);
    }
    for (int i = 0; i < numti; ++i){
        da = false;
        do{
            x = rand()%a;
            y = rand()%b;
            //if(res.getEn().getPlace(x, y)->retType() == 0){
                res.addDiffPlace(x, y, 1);
                da = true;
            //}
        }while(!da);
    }
    return res;
}
