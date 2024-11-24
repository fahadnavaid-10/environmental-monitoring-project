#!/bin/bash
# process_data.sh

# Ensure required parameters are provided
if [ "$#" -ne 4 ]; then
    echo "Usage: $0 <city> <temperature> <weather_data> <humidity_data>"
    exit 1
fi

city=$1
temperature=$2
weather_data=$3
humidity_data=$4

report_file="/home/m-asad-navaid/Desktop/environmental_monitoring_project/report.txt"

# Check if report.txt is writable
if [ ! -w "$report_file" ] && [ -e "$report_file" ]; then
    echo "Error: Cannot write to $report_file. Please check file permissions."
    exit 1
elif [ ! -e "$report_file" ]; then
    # Create the file if it doesn't exist
    touch "$report_file"
    if [ $? -ne 0 ]; then
        echo "Error: Unable to create $report_file."
        exit 1
    fi
fi

# Append report data to report.txt
{
    echo "Processing data for $city on $(date)"
    echo "Weather Report for $city"
    echo "--------------------------"
    echo "Date: $(date)"
    echo "City: $city"
    echo "Temperature: $temperature Celsius"
    echo "Weather: $weather_data"
    echo "Humidity: $humidity_data%"

    # Messages about outdoor activities based on temperature
    if (( $(echo "$temperature > 20" | bc -l) )); then
        echo "The temperature is good for outdoor activities!"
    elif (( $(echo "$temperature > 10" | bc -l) )); then
        echo "The temperature is suitable for moderate outdoor activities."
    else
        echo "Consider indoor activities as the temperature is too cold."
    fi

    # Append a blank line for readability
    printf "\n\n"
} >> "$report_file"

if [ -n "$DISPLAY" ]; then
    # We are in a graphical environment
    if command -v notify-send > /dev/null 2>&1; then
        notify-send "Data Processing Complete" "Data for $city has been processed. Report generated."
    fi
else
    # We're in a non-graphical environment (like cron)
    echo "Data Processing Complete: Data for $city has been processed. Report generated."
fi

