#include "types.h"

class IMU
{
    public:
                                  
    //setup the range and other parameters of the sensor
    void setupSensor(); 

    //push data into CircularBuffer
    void fillCircularBuffer();        

    private:

};