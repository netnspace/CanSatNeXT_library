#include "baro.h"
#include "Arduino.h"
#include "LPS35HW.h"
#include "Wire.h"

LPS35HW lps;

uint8_t initBaro(TwoWire *wire)
{if 

    (!lps.begin(wire)) { 
        return 1;
    }
    
    lps.setLowPassFilter(LPS35HW::LowPassFilter_ODR20); 
    lps.setOutputRate(LPS35HW::OutputRate_75Hz); 
    return 0;
}

float readPressure()
{
    return lps.readPressure();
}

float readTemperature()
{
    return lps.readTemp();
}

