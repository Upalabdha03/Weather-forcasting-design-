#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_KEY "5bd503ab4f013452a2c50dae4965934c"

int main() {
  // Get the user's location
  char city[100];
  printf("What city would you like to get the weather for? ");
  fgets(city, 100, stdin);
  city[strlen(city) - 1] = '\0';

  // Get the weather data from the API
  char url[200];
  sprintf(url, "https://api.openweathermap.org/data/2.5/weather?q=%s&appid=%s", city, API_KEY);
  FILE *fp = fopen(url, "r");
  if (fp == NULL) {
    printf("Error opening URL.\n");
    return 1;
  }

  // Parse the JSON response
  char json[10000];
  fgets(json, 10000, fp);
  fclose(fp);

  // Display the weather data in a user-friendly format
  struct {
    float temp;
    float humidity;
    float wind_speed;
    float cloud_cover;
  } weather;
  sscanf(json, "{\"main\":{\"temp\":%f,\"humidity\":%f,\"wind_speed\":%f,\"clouds\":{\"all\":%f}}}", &weather.temp, &weather.humidity, &weather.wind_speed, &weather.cloud_cover);
  printf("Weather for %s\n", city);
  printf("----------------\n");
  printf("Temperature: %.2f°F\n", weather.temp * 9 / 5 + 32);
  printf("Humidity: %.2f%%\n", weather.humidity);
  printf("Wind speed: %.2f mph\n", weather.wind_speed);
  printf("Cloud cover: %.2f%%\n", weather.cloud_cover);

  return 0;
}
