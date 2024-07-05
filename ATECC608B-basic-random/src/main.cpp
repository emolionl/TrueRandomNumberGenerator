#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <Wire.h>
#include "TRNG.h"

// Create an instance of the display
TFT_eSPI tft = TFT_eSPI();
TRNG trng;

unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 1000; // Update every second
unsigned long startTime = 0;
const unsigned long ignoreDuration = 3000; // Ignore the first 3 seconds

unsigned long count0 = 0;
unsigned long count1 = 0;

void drawGraph(unsigned long count0, unsigned long count1);
void displayTime();
String formatTime(unsigned long milliseconds);

void setup() {
  Serial.begin(115200);

  // Initialize the display
  tft.init();
  tft.setRotation(1);  // Set the rotation to landscape mode
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);

  startTime = millis(); // Record the start time
}

void loop() {
  if (millis() - startTime < ignoreDuration) {
    // Ignore the first 3 seconds
    return;
  }

  byte singleDigit = trng.getRandomInRange(0, 1);

  if (singleDigit == 0) {
    count0++;
  } else {
    count1++;
  }

  unsigned long currentTime = millis();
  if (currentTime - lastUpdateTime >= updateInterval) {
    lastUpdateTime = currentTime;

    // Clear the previous graph area and update time display
    tft.fillRect(0, 60, tft.width(), tft.height() - 60, TFT_BLACK);
    displayTime();

    // Draw new graph
    drawGraph(count0, count1);
    unsigned long total = count0 + count1;
    float percent0 = (total > 0) ? ((float)count0 / total) * 100 : 0;
    float percent1 = (total > 0) ? ((float)count1 / total) * 100 : 0;

    Serial.println("0s: " + String(count0) + " -> " + String(percent0, 2) + "%  1s: " + String(count1) + " -> " + String(percent1, 2) + "%");
  }
}

void drawGraph(unsigned long count0, unsigned long count1) {
  // Total count
  unsigned long total = count0 + count1;

  // Calculate percentages
  float percent0 = (total > 0) ? ((float)count0 / total) * 100 : 0;
  float percent1 = (total > 0) ? ((float)count1 / total) * 100 : 0;

  // Draw the bars
  int barWidth = tft.width() / 2 - 20;
  int barHeight0 = map(percent0, 0, 100, 0, tft.height() - 130);
  int barHeight1 = map(percent1, 0, 100, 0, tft.height() - 130);

  // Bar for 0s
  tft.fillRect(10, tft.height() - barHeight0 - 30, barWidth, barHeight0, TFT_BLUE);

  // Draw percentage and count inside the bar for 0s
  tft.setTextColor(TFT_WHITE, TFT_BLUE);
  tft.setCursor(15, tft.height() - barHeight0 - 35);
  tft.print("0s " + String(percent0, 1) + "%");
  tft.setCursor(15, tft.height() - barHeight0 - 20);
  tft.print(String(count0));

  // Bar for 1s
  tft.fillRect(tft.width() / 2 + 10, tft.height() - barHeight1 - 30, barWidth, barHeight1, TFT_RED);

  // Draw percentage and count inside the bar for 1s
  tft.setTextColor(TFT_WHITE, TFT_RED);
  tft.setCursor(tft.width() / 2 + 15, tft.height() - barHeight1 - 35);
  tft.print("1s " + String(percent1, 1) + "%");
  tft.setCursor(tft.width() / 2 + 15, tft.height() - barHeight1 - 20);
  tft.print(String(count1));
}

void displayTime() {
  unsigned long elapsedTime = millis() - startTime;
  String formattedTime = formatTime(elapsedTime);

  // Display elapsed time
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setCursor(10, 10);
  tft.print("Elapsed: ");
  tft.println(formattedTime);
}

String formatTime(unsigned long milliseconds) {
  unsigned long seconds = milliseconds / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;
  unsigned long days = hours / 24;

  seconds %= 60;
  minutes %= 60;
  hours %= 24;

  String timeString = String(days) + ":" +
                      (hours < 10 ? "0" + String(hours) : String(hours)) + ":" +
                      (minutes < 10 ? "0" + String(minutes) : String(minutes)) + ":" +
                      (seconds < 10 ? "0" + String(seconds) : String(seconds));
  return timeString;
}

