unit InitUnit;

{$mode objfpc}{$H+}

{ API Project Init Unit                                                        }
{                                                                              }
{  Because this unit is included first in the project file it can be used to   }
{  update default settings used during boot and enable or disable certain      }
{  optional functionality and drivers.                                         }
{                                                                              }
{  See the GlobalConfig unit for more information and details of many of the   }
{  items that can be configured here.                                          }
{                                                                              }

interface

uses
  GlobalConst,
  GlobalConfig;

implementation

initialization
  {Global Configuration Options}
  //FRAMEBUFFER_CONSOLE_AUTOCREATE := False; {Uncomment to remove the default console}

  //TIMEZONE_DEFAULT_NAME := 'Greenwich Standard Time'; {Set the default timezone}

  //KEYMAP_DEFAULT := 'US'; {Set the default keymap (US is built in, others need to be included)}

  //CODEPAGE_OEM_DEFAULT := 437;   {Set the default OEM code page (437 is built in, others need to be included)}
  //CODEPAGE_ANSI_DEFAULT := 1252; {Set the default ANSI code page (1252 is built in, others need to be included)}

  //CODEPAGE_CONSOLE_INPUT := 1252;  {Set the default console input code page (1252 is built in, others need to be included)}
  //CODEPAGE_CONSOLE_OUTPUT := 1252; {Set the default console output code page (1252 is built in, others need to be included)}

  //NTP_SERVER_DEFAULT := 'pool.ntp.org' {Set the default server for NTP client requests}

  {Logging Configuration Options}
  LOGGING_INCLUDE_COUNTER := True;
  //LOGGING_INCLUDE_DATETIME := True;
  LOGGING_INCLUDE_TICKCOUNT := True;

  {Serial Logging Options}
  SERIAL_REGISTER_LOGGING := True;    {Register the default serial device for logging output}
  //SERIAL_LOGGING_DEFAULT := True;   {Make it the default logging device}

  {Console Logging Options}
  //CONSOLE_REGISTER_LOGGING := True;   {Register the default console device for logging output}
  //CONSOLE_LOGGING_DEFAULT := True;   {Make it the default logging device}
  //CONSOLE_LOGGING_POSITION := CONSOLE_POSITION_BOTTOM; {Place the console logging at the bottom of the screen}

  {Syslog Logging Options}
  //SYSLOG_REGISTER_LOGGING := True;   {Register the syslog client for logging output}
  //SYSLOG_LOGGING_DEFAULT := True;    {Make it the default logging device}
  //SYSLOG_SERVER_DEFAULT := '192.168.1.1'; {Set the address for syslog output}

end.