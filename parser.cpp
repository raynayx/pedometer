#include "parser.h"
#include "filter.h"


Filter fp;


        Parser::Parser(axesArr d)
        {
            data = d;
        }
        parsedAxesArr Parser::run(axesArr d)
        {
            // create object and call parse on it
            Parser p(d);
            p.parse();
        }

        parsedAxesArr Parser::parse()
        {
           // get acceleration in direction of gravity from  by calling Filter.low_0_hz
           axesArr a = fp.low_0_hz(data);
            for(int i=0; i< 50; i++)
            {
                parsed_data.gArr[i] = a.arr[i];
            }
             
            for(int i = 0;i < 50;i++)
            {
                // get user acceleration by subtracting gravity from total 
                parsed_data.uArr[i].x = data.arr[i].x - parsed_data.gArr[i].x;
                parsed_data.uArr[i].y = data.arr[i].y - parsed_data.gArr[i].y;
                parsed_data.uArr[i].z = data.arr[i].z - parsed_data.gArr[i].z;
            }
            return parsed_data;
        }
