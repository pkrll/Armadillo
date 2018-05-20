#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

char *exceptions[13] = {
	"0",
	"1",
	"2",
	"3",
	"Addrl exception! (Cause 4) Load from illegal address exception",
	"Addrs exception! (Cause 5) Store to illegal address exception",
	"Ibus exception! (Cause 6) Bus error on instruction fetch",
	"Dbus exception! (Cause 7) Bus error on data reference",
	"8",
	"Bkpt exception! (Cause 9) Break instruction executed",
	"Ri exception! (Cause 10) Reserved instruction",
	"11",
	"Ovf exception! (Cause 12) Arithmetic overflow"
};

#endif
