#ifndef PLACE_H
#define PLACE_H

#include <iostream>

namespace robots{

enum sost{OPEN, CLOSE};

class place
{
private:
    int x, y;
    sost st;
protected:
    virtual std::ostream& show(std::ostream&) const;
public:
    place(int x, int y): x(x), y(y), st(CLOSE) {}
    place(const place &pl): x(pl.getX()), y(pl.getY()), st(pl.getSost()) {}
    virtual int retType() const { return 0; }
    virtual place* clone() const { return new place(*this); }
    int getX() const { return x; }
    int getY() const { return y; }
    place& setX(int n);
    place& setY(int n);
    place& setSost(sost n);
    sost getSost() const { return st; }
    friend std::ostream& operator <<(std::ostream&, const place&);
    virtual ~place() {}
};

}

#endif // PLACE_H
