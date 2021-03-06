#pragma once

#include "blargg_common.h"
#include "Spc_Dsp_Register_Map_Interface.h"

//:< Why are these #defines and is there a cleaner way?
#define spc_report_mem_read(addr) do {\
  Spc_Report::obj->report(Spc_Report::Read, addr, 0);\
} while(0)

#define spc_report_mem_echo(addr) do {\
  Spc_Report::obj->report(Spc_Report::Echo, addr, 0);\
} while(0)

#define spc_report_mem_execute(addr, opcode) do {\
  Spc_Report::obj->report(\
    Spc_Report::Execute, addr, opcode);\
} while(0)

#define spc_report_mem_write(addr) do {\
  Spc_Report::obj->report(Spc_Report::Write, addr, 0);\
} while(0)

#define spc_report_tracker(cmd, arg) do {\
	Spc_Report::obj->report(Spc_Report::TrackerCmd, cmd, arg);\
} while(0)

class Spc_Report
{
public:
  //:< is this really necessary?
  Spc_Report() {obj = this;}
  static const int BRR_HEADER_MAX=100;
  static const int SRCN_MAX=0x200;  // the limit for Instrument entries

  static int last_pc; // last PC counter (current executing instruction)
  static int bcolor;  // backup color
  //:< what are these for? need to be more serious about privatizing, creating
  // a public API
  static unsigned char used2[0x101];
  static unsigned char used[0x10006];

  enum Type { Read, Execute, Echo, Write, TrackerCmd };

  //:< having the publish method be virtual is not a proper way to publish the reports
  virtual void report(Type type, unsigned addr, unsigned opcode)=0;

  //:< what is this for? why is it called Src?
  struct Src
  {
    Src();
    uint16_t dir_addr; //unused for now
    uint16_t brr_start;
    uint16_t brr_end;
    uint16_t brr_loop_start;
    uint16_t brr_loop_end;
    bool     brr_loop_active;
  };
  static Src src[MAX_SRCN_ENTRIES];

  static Spc_Report *obj;
};
