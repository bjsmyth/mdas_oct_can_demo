#include "can_oct_demo.h"

CanDemo::CanDemo() {
  _s = socket(PF_CAN, SOCK_DGRAM, CAN_BCM);

  strncpy(_ifr.ifr_name, CAN_IFACE, IFNAMSIZ);

  if(ioctl(_s, SIOCGIFINDEX, &_ifr) < 0) {
    perror(CLASSNAME ": ioctl");
  }

  _addr.can_family = AF_CAN;
  _addr.can_ifindex = _ifr.ifr_ifindex;

  if(connect(_s, (struct sockaddr *)&_addr, sizeof(_addr)) < 0) {
    perror(CLASSNAME ": connect");
  }

  _msg.msg_head.can_id = 0;
  _msg.msg_head.nframes = 1;


  _msg.frame.can_id = MSGID | CAN_EFF_FLAG;
  _msg.frame.can_dlc = MSGLEN;
}

bool CanDemo::ActuateBrake() {
  memcpy(&(_msg.frame.data), _actuateBrake, MSGLEN);

  _msg.msg_head.opcode = TX_SETUP;
  _msg.msg_head.flags = SETTIMER | STARTTIMER;
  _msg.msg_head.count = 0;

  /// Set time interval to 100 ms
  _msg.msg_head.ival2.tv_sec = 0;
  _msg.msg_head.ival2.tv_usec = CYCTIME;

  if(write(_s, &_msg, sizeof(_msg)) < 0) {
    perror(CLASSNAME ": write: TX_SETUP");
    return false;
  }

  return true;
}

bool CanDemo::ReleaseBrake() {
  memcpy((&_msg.frame.data), _releaseBrake, MSGLEN);
  _msg.msg_head.opcode = TX_DELETE;
  if(write(_s, &_msg, sizeof(_msg)) < 0) {
  }

  _msg.msg_head.opcode = TX_SEND;
  _msg.msg_head.flags = 0;

  if(write(_s, &_msg, sizeof(_msg)) < 0) {
      perror(CLASSNAME ": write: TX_SEND");
      return false;
  }

  return true;
}

CanDemo::~CanDemo() {
  ReleaseBrake();

  if (close(_s) < 0)
    {
        perror(CLASSNAME ": close");
    }
}
