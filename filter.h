#ifndef FILTER_H_
#define FILTER_H_

#include "types.h"


class Filter
{
   public:
        COEFFICIENTS LOW_0_HZ ={{1, -1.979133761292768, 0.979521463540373},{0.000086384997973502, 0.000172769995947004, 0.000086384997973502}};
        COEFFICIENTS LOW_5_HZ = {{1, -1.80898117793047, 0.827224480562408},{0.095465967120306, -0.172688631608676, 0.095465967120306}};
        COEFFICIENTS HIGH_1_HZ = {{1, -1.905384612118461, 0.910092542787947},{0.953986986993339, -1.907503180919730, 0.953986986993339}};

        //split xl into x_xl and g_xl
        void low_0_hz(CB &data);

        //low_5_hz(data)
        void low_5_hz(CB&  data);

        //high_1_hz(data)
        void high_1_hz(CB& data);

        //split xl into x_xl and g_xl
        
        void low_0_hz(double* data,double* filteredData);

        //low_5_hz(data)
        
        void low_5_hz(double* data,double* filteredData);

        //high_1_hz(data)
        void high_1_hz(double* data,double* filteredData);


    private:
        //filter the axes data based on passed COEFFICIENTS;
        void filter(CB &data, COEFFICIENTS &coefficents);         //TODO : rewite to not use global variable
        void filter(double* data, COEFFICIENTS &coefficients,double* filteredData); 
};



#endif
