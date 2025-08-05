#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>
using std::cout, std::flush;
using std::this_thread::sleep_for;
using std::chrono::seconds;

// PURE FUNCTION: Checks whether vitals are OK
enum VitalStatus {
  VITAL_OK,
  TEMP_CRITICAL,
  PULSE_CRITICAL,
  SPO2_CRITICAL
};

VitalStatus checkVitals(float temperature, float pulseRate, float spo2) {
  if (temperature > 102 || temperature < 95) {
    return TEMP_CRITICAL;
  }
  if (pulseRate < 60 || pulseRate > 100) {
    return PULSE_CRITICAL;
  }
  if (spo2 < 90) {
    return SPO2_CRITICAL;
  }
  return VITAL_OK;
}

// I/O FUNCTION: Alert animation
void showAlert(const std::string& message) {
  cout << message << '\n';
  for (int i = 0; i < 6; i++) {
    cout << "\r* " << flush;
    sleep_for(seconds(1));
    cout << "\r *" << flush;
    sleep_for(seconds(1));
  }
}

// MAIN FUNCTION: Orchestrates the above
int vitalsOk(float temperature, float pulseRate, float spo2) {
  VitalStatus status = checkVitals(temperature, pulseRate, spo2);
  switch (status) {
    case TEMP_CRITICAL:
      showAlert("Temperature is critical!");
      return 0;
    case PULSE_CRITICAL:
      showAlert("Pulse Rate is out of range!");
      return 0;
    case SPO2_CRITICAL:
      showAlert("Oxygen Saturation out of range!");
      return 0;
    default:
      return 1;
  }
}
