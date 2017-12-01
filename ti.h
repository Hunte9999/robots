#ifndef TI_H
#define TI_H

#include "place.h"

namespace robots{

class ti:public place
{
protected:
    virtual std::ostream& show(std::ostream &os) const{
        return os << " :: ti";
    }
public:
    ti(int x, int y): place(x, y) {}
    ti(const ti &a): place(a) {}
    int retType() const { return 1; }
    virtual ti* clone() const{
        return new ti(*this);
    }
    virtual ~ti() override {}
};

}

#endif // TI_H
