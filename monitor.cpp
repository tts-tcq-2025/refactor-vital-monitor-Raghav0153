#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <vector>

using namespace std;
using namespace std::chrono;

enum VitalStatus {
  VITAL_OK,
  VITAL_LOW,
  VITAL_HIGH
};

struct VitalCheckResult {
  string name;
  VitalStatus status;
};


VitalStatus evaluateVital(float value, const VitalLimits& limits) {
  if (value < limits.lower) return VITAL_LOW;
  if (value > limits.upper) return VITAL_HIGH;
  return VITAL_OK;
}


vector<VitalCheckResult> checkVitals(float temperature, float pulseRate, float spo2) {
  vector<VitalCheckResult> results;
  results.push_back({"Temperature", evaluateVital(temperature, {95.0f, 102.0f})});
  results.push_back({"Pulse Rate", evaluateVital(pulseRate, {60.0f, 100.0f})});
  results.push_back({"Oxygen Saturation", evaluateVital(spo2, {90.0f, 100.0f})});
  return results;
}


void blinkingAlert() {
  for (int i = 0; i < 6; ++i) {
    cout << "\r* " << flush;
    this_thread::sleep_for(seconds(1));
    cout << "\r *" << flush;
    this_thread::sleep_for(seconds(1));
  }
}

void handleAlerts(const vector<VitalCheckResult>& results) {
  const char* messages[] = {
    "",                 
    " is too low!\n",  
    " is too high!\n"   
  };

  for (const auto& result : results) {
    if (result.status != VITAL_OK) {
      cout << result.name << messages[result.status];
      blinkingAlert();
    }
  }
}

bool vitalsOk(float temperature, float pulseRate, float spo2) {
  auto results = checkVitals(temperature, pulseRate, spo2);
  handleAlerts(results);

  for (const auto& result : results) {
    if (result.status != VITAL_OK) return false;
  }
  return true;
}
