#include "typewise-alert.h"
#include <stdio.h>

BreachType inferLowBreach(double value, double lowerLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  } else {
    return NORMAL;
  }
}

BreachType inferBreach(double value, double upperLimit) {
  if(value > upperLimit) {
    return TOO_HIGH;
  } else {
    return NORMAL;
  }
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  int lowerLimit = 0;
  int upperLimit = 0;

  if(coolingType == PASSIVE_COOLING)
  {
      upperLimit = 35;
  }
  else if(coolingType == HI_ACTIVE_COOLING)
  {
      upperLimit = 45;
  }
  else if(coolingType == MED_ACTIVE_COOLING)
  {
      upperLimit = 40;
  }

  BreachType breachType = inferLowBreach(double value, double lowerLimit);

  if(breachType != NORMAL)
  {
    return breachType;
  }
  
  return inferHighBreach(value, upperLimit);

//  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  if(alertTarget == TO_CONTROLLER)
  {
      sendToController(breachType);
  }
  else if (alertTarget == TO_EMAIL)
  {
      sendToEmail(breachType);
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";

  if(breachType == TOO_LOW)
  {
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
  }
  else if (breachType == TOO_HIGH)
  {
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
  }

}
