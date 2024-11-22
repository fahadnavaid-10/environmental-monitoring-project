#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H

#include "cJSON.h"

struct WeatherData {
    double temperature;
    char weather[50];
    double humidity;
};

int parseWeatherData(const char *json, struct WeatherData *data);
void retrieveEnvironmentalData(const char *city);

#endif
