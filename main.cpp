#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "can_oct_demo.h"

int main()
{
  CanDemo octDemo;

  octDemo.ActuateBrake();

  sleep(5);

  octDemo.ReleaseBrake();

  sleep(5);

  octDemo.ActuateBrake();

  sleep(5);

  return 0;
}
