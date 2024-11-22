#include <unistd.h> // Required for sleep()
#include "alert.h"

void temperatureAlert(double temperature) {
    if (temperature > 25.0) {
        system("notify-send 'High Temperature Alert!' 'Temperature exceeds 25.0 Celsius'");
        sleep(1); // here i added sleep because there are total two notification to generate so this notification was overcoming by second (report generated) notification. thats why im added sleep so it is delaying the further execution of program for one second
    } else if (temperature < 15.0) {
        system("notify-send 'Low Temperature Alert!' 'Temperature is below 15.0 Celsius'");
        sleep(1);
    } else {
        system("notify-send 'Normal temperature range'");
        sleep(1);
    }
}

