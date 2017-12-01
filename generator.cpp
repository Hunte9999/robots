#include "generator.h"

namespace robots {

    std::ostream& generator::show(std::ostream &os) const
    {
        return os<<" energylevel: " << energylevel;
    }

}
