#include <assert.h>

void testVitalsChecker() {
  assert(checkVitals(98.6, 75, 95) == VITAL_OK);
  assert(checkVitals(103, 75, 95) == TEMP_CRITICAL);
  assert(checkVitals(98.6, 50, 95) == PULSE_CRITICAL);
  assert(checkVitals(98.6, 75, 85) == SPO2_CRITICAL);
}
