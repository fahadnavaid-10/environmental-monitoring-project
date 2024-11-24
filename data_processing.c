#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include "data_processing.h"
#include "alert.h"

static size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    strcat(userdata, ptr);
    return size * nmemb;
}

int parseWeatherData(const char *json, struct WeatherData *data) {
    cJSON *root = cJSON_Parse(json);
    if (root == NULL) return -1;

    cJSON *current = cJSON_GetObjectItem(root, "current");
    if (current == NULL) return -1;

    data->temperature = cJSON_GetObjectItem(current, "temp_c")->valuedouble;
    data->humidity = cJSON_GetObjectItem(current, "humidity")->valuedouble;

    cJSON *condition = cJSON_GetObjectItem(current, "condition");
    if (condition != NULL) {
        strcpy(data->weather, cJSON_GetObjectItem(condition, "text")->valuestring);
    }
    cJSON_Delete(root);
    return 0;
}

void retrieveEnvironmentalData(const char *city) {
    CURL *curl;
    CURLcode res;
    struct WeatherData *weather = malloc(sizeof(struct WeatherData));
    char json_buffer[2048] = {0};

    curl = curl_easy_init();
    if (curl) {
        const char *api_key = "506171663e334909a3395047242710"; // API Key

        // Encode spaces in the city name
        char city_encoded[100];
        snprintf(city_encoded, sizeof(city_encoded), "%s", city);
        for (int i = 0; city_encoded[i]; i++) {
            if (city_encoded[i] == ' ') {
                city_encoded[i] = '%';
                city_encoded[++i] = '2';
                city_encoded[++i] = '0';
            }
        }

        // Construct the URL with the encoded city name
        char url[256];
        snprintf(url, sizeof(url), "http://api.weatherapi.com/v1/current.json?key=%s&q=%s&aqi=yes", api_key, city_encoded);
        
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, json_buffer);

        res = curl_easy_perform(curl);
        
        // Check if the request was successful
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return;
        }

        // Try to parse the weather data
        if (parseWeatherData(json_buffer, weather) == 0) {
            
            temperatureAlert(weather->temperature);

            // Prepare the command to call the shell script with data arguments
            char command[512];
            snprintf(command, sizeof(command), "/home/m-asad-navaid/Desktop/environmental_monitoring_project/process_data.sh '%s' %.2f '%s' %.2f",
                     city, weather->temperature, weather->weather, weather->humidity);
            
            // Run the script with system()
            system(command);
        } else {
            fprintf(stderr, "Failed to parse JSON data.\n");
        }

        curl_easy_cleanup(curl);
    }
    free(weather);
}