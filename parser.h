#pragma once
#include "types.h"

class Parser
{
    public:
        axesArr data;
        parsedAxesArr parsed_data;

        Parser(axesArr d);
        parsedAxesArr run(axesArr d);

    private:
        parsedAxesArr parse();

};
