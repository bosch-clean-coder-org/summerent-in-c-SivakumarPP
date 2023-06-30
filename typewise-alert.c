#include "typewise-alert.h"
#include <stdio.h>

BreachType inferLowBreach(double value, double lowerLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  } else {
    return NORMAL;
  }
}

BreachType inferHighBreach(double value, double upperLimit) {
  if(value > upperLimit) {
    return TOO_HIGH;
  } else {
    return NORMAL;
  }
}

int getUpperLimit(CoolingType coolingType)
{
  int upperLimit = 40;

  if(coolingType == PASSIVE_COOLING)
  {
      upperLimit = 35;
  }
  else if(coolingType == HI_ACTIVE_COOLING)
  {
      upperLimit = 45;
  }

  return upperLimit;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  int lowerLimit = 0;
  int upperLimit = getUpperLimit(coolingType);

  BreachType breachType = inferLowBreach(temperatureInC, lowerLimit);

  if(breachType != NORMAL)
  {
    return breachType;
  }
  
  return inferHighBreach(temperatureInC, upperLimit);

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
