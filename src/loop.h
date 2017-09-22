#pragma once
#include "Arduino.h"
#include "states.h"
#include "DHT.h"

void sensor_loop();
void battery_loop();
void recording_loop();
void init_loop();
