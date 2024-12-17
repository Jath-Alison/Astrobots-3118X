#pragma once

namespace Jath
{
    template <typename T>
    inline T cap(T input, T limit)
    {
        if (input > limit)
        {
            return limit;
        }
        else
        {
            return input;
        }
    }

    template <typename T>
    inline T floor(T input, T limit)
    {
        if (input < limit)
        {
            return limit;
        }
        else
        {
            return input;
        }
    }

    inline int getSign(double in)
    {
        if (in < 0)
        {
            return -1;
        }
        if (in > 0)
        {
            return 1;
        }
        return 0;
    }
}