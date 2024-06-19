#pragma once
#include "Jath\PID.h"

namespace Jath
{
    class QPID : public PID{
    public:
        QPID();

        double calculate(double error) override;

        double getProportional() override;
    };
} // namespace Jath