#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdint>

#include <unistd.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/bcm.h>

#define MSGID (0x00FF0000)
#define MSGLEN (8)
#define CAN_IFACE "can0"
#define CLASSNAME "can_oct_demo"

#define CYCTIME (100000)

class CanDemo {

private:
  uint8_t _actuateBrake[MSGLEN] = {0x0F, 0x4A, 0xC4, 0x89, 0x00, 0x00, 0x00, 0x00};
  uint8_t _releaseBrake[MSGLEN] = {0x7E, 0x02, 0x12, 0x34, 0x56, 0xAB, 0xCD, 0xEF};
  int _s;
  struct can_msg
  {
    struct bcm_msg_head msg_head;
    struct can_frame frame;
  } _msg;
  struct ifreq _ifr;
  struct sockaddr_can _addr;

public:
  CanDemo();
  ~CanDemo();
  bool ActuateBrake();
  bool ReleaseBrake();
};
