#pragma once
#include <cmath>

namespace Rei
{

    // some math function::

    
    inline double rad(double n)
    {
        return M_PI * n / 180;
    }
    
    inline double dgr(double n)
    {
        return 180 * n / (M_PI);
    }
    
    inline int sign(double n)
    {
        if (n > 0)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    
    inline double absolute(double n)
    {
        if (n < 0)
        {
            return -n;
        }
        else
        {
            return n;
        }
    }
    
    inline double capped(double base, double cap)
    {
        if (absolute(base) > cap)
        {
            return sign(base) * cap;
        }
        else
        {
            return base;
        }
    }
    /*d0quo: denominator zero quotient. Attempts to account for the rare case that the divisor is 0.
    might be extraneous due to it only being used once.*/
    
    inline double d0quo(double numer, double denom)
    {
        if (denom == 0)
        {
            if (numer < 0)
            {
                return -99999999;
            }
            else
            {
                return 99999999;
            }
        }
        else
        {
            return numer / denom;
        }
    }
    
    inline double pointdist(double x1, double x2, double y1, double y2)
    {
        return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    }
    
    inline int trunclog10(double n)
    {
        // returns trunc(log10(n)). examples: f(8)=0, f(0.5)=-1.
        n = absolute(n);
        if (n == 0)
        {
            return 0;
        }
        int ans = 0;
        if (n < 1)
        {
            return n;
            for (; n < 1; ans = ans - 1)
            {
                n = n * 10;
            }
        }
        else
        {
            for (; n > 1; ans++)
            {
                n = n / 10;
            }
        }
        return ans;
    }
} // namespace Rei