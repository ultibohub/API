program pwm_sound;

{$mode objfpc}{$H+}

{ Sample 20 PWM Sound                                                        }
{                                                                              }
{  The project simply calls a "main" function in the C/C++ project and passes  }
{  all command line arguments to it. The main function can then do anything it }
{  requires by calling Ultibo API functions, standard C library funtions or    }
{  other libraries.                                                            }
{                                                                              }
{  Note that you can call your main function anything you like except main.    }
{  Free Pascal has an internal alias of MAIN that refers to the begin/end      }
{  section of the project file below (also known as PASCALMAIN).               }
{                                                                              }
{  You are also not limited to just calling a single main function from the    }
{  Free Pascal project, you can include other Free Pascal functionality such   }
{  as creating additional threads and including optional units. You can also   }
{  call directly to multiple functions within your C/C++ project from multiple }
{  threads which can be created here or created inside you C/C++ project.      }
{                                                                              }
{  To compile the project use the template Makefile from the command line.     }
{                                                                              }
{  Once compiled copy the kernel image file to an SD card along with the       }
{  firmware files and use it to boot your Raspberry Pi.                        }

{Include the standard Ultibo units}
uses
 {$IFDEF RPIB}
  RaspberryPi,     {Include RaspberryPi to make sure all standard drivers are available}
  {$DEFINE BOARD_DEFINED}
 {$ENDIF}
 {$IFDEF RPI2B}
  RaspberryPi2,    {Include RaspberryPi2 to make sure all standard drivers are available}
  {$DEFINE BOARD_DEFINED}
 {$ENDIF}
 {$IFDEF RPI3B}
  RaspberryPi3,    {Include RaspberryPi3 to make sure all standard drivers are available}
  {$DEFINE BOARD_DEFINED}
 {$ENDIF}
 {$IFDEF RPI4B}
  RaspberryPi4,    {Include RaspberryPi4 to make sure all standard drivers are available}
  {$DEFINE BOARD_DEFINED}
 {$ENDIF}
 {$IFDEF QEMUVPB}
  QEMUVersatilePB, {Include QEMUVersatilePB to make sure all standard drivers are available}
  {$DEFINE BOARD_DEFINED}
 {$ENDIF}
 {$IFNDEF BOARD_DEFINED}
  RaspberryPi2,    {Include RaspberryPi2 if nothing else was defined (eg Building from Lazarus)}
 {$ENDIF}
 API,              {Include the API unit to export the Ultibo API}
 GlobalTypes,
 GlobalConfig,
 Platform,
 Threads,
 Syscalls,         {Include the Syscalls unit for standard C library support}
 UltiboUtils,
 {$IFDEF RPIB}
 BCM2708;          {Include BCM2708 drivers for exported functions below}
 {$ENDIF}
 {$IFDEF RPI2B}
 BCM2709;          {Include BCM2709 drivers for exported functions below}
 {$ENDIF}
 {$IFDEF RPI3B}
 BCM2710;          {Include BCM2710 drivers for exported functions below}
 {$ENDIF}
 {$IFDEF RPI4B}
 BCM2711;          {Include BCM2711 drivers for exported functions below}
 {$ENDIF}

{Link our C/C++ object files by including the autogenerated include files}
{$INCLUDE __linklib.inc}
{$INCLUDE __link.inc}

{Import the main function of the project so we can call it from Ultibo}
function APIMain(argc: int; argv: PPChar): int; cdecl; external name 'apimain';

{Export helper functions to provide access to BCM27XX driver units}
function bcm27xx_pwm_clock_enabled(pwm: PPWM_DEVICE): BOOL; stdcall; public name 'bcm27xx_pwm_clock_enabled';
begin
 {$IFDEF RPIB}
 Result:=BCM2708PWMClockEnabled(pwm);
 {$ENDIF}
 {$IFDEF RPI2B}
 Result:=BCM2709PWMClockEnabled(pwm);
 {$ENDIF}
 {$IFDEF RPI3B}
 Result:=BCM2710PWMClockEnabled(pwm);
 {$ENDIF}
 {$IFDEF RPI4B}
 Result:=BCM2711PWM0ClockEnabled(pwm);
 {$ENDIF}
end;

function bcm27xx_pwm_clock_stop(pwm: PPWM_DEVICE): uint32_t; stdcall; public name 'bcm27xx_pwm_clock_stop'; 
begin
 {$IFDEF RPIB}
 Result:=BCM2708PWMClockStop(pwm);
 {$ENDIF}
 {$IFDEF RPI2B}
 Result:=BCM2709PWMClockStop(pwm);
 {$ENDIF}
 {$IFDEF RPI3B}
 Result:=BCM2710PWMClockStop(pwm);
 {$ENDIF}
 {$IFDEF RPI4B}
 Result:=BCM2711PWM0ClockStop(pwm);
 {$ENDIF}
end;

{Variables to hold argc and argv to pass to our C/C++ project}
var
 argc:int;
 argv:PPChar;

begin
 {Allocate the command line arguments}
 argv:=AllocateCommandLine(SystemGetCommandLine,argc);

 {Call the "main" function of our C/C++ project}
 APIMain(argc,argv);

 {Release the command line}
 ReleaseCommandLine(argv);

 {Halt the main thread if we return}
 ThreadHalt(0);
end.