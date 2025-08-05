void testEvaluateVital() {
  assert(evaluateVital(98, {95, 102}) == VITAL_OK);
  assert(evaluateVital(94, {95, 102}) == VITAL_LOW);
  assert(evaluateVital(103, {95, 102}) == VITAL_HIGH);
}

