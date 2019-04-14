module aurorafw.graphics.platform.khr.khrplatform;

alias int   khronos_int32_t;
alias uint  khronos_uint32_t;
alias long  khronos_int64_t;
alias ulong khronos_uint64_t;

alias  byte   khronos_int8_t;
alias  ubyte  khronos_uint8_t;
alias  short  khronos_int16_t;
alias  ushort khronos_uint16_t;
alias  int    khronos_intptr_t;
alias  uint   khronos_uintptr_t;
alias  int    khronos_ssize_t;
alias  uint   khronos_usize_t;

alias float   khronos_float_t;

alias khronos_uint64_t khronos_utime_nanoseconds_t;
alias khronos_int64_t  khronos_stime_nanoseconds_t;

enum KHRONOS_MAX_ENUM = 0x7FFFFFFF;

enum {
	KHRONOS_FALSE                   = 0,
	KHRONOS_TRUE                    = 1,
	KHRONOS_BOOLEAN_ENUM_FORCE_SIZE = KHRONOS_MAX_ENUM
}
