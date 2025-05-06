unit InitUnit;

{$mode objfpc}{$H+}

{ Advanced example - LVGL Demo                                                 }

interface

uses
  GlobalConst,
  GlobalConfig;

implementation
 
initialization
  // Global Configuration Options
  FRAMEBUFFER_CONSOLE_AUTOCREATE := False; // Don't create a framebuffer console

  // Logging Configuration Options
  LOGGING_INCLUDE_COUNTER := True;
  LOGGING_INCLUDE_TICKCOUNT := True;  

  // Serial Logging Options
  SERIAL_REGISTER_LOGGING := True;    // Register the default serial device for log output
  SERIAL_LOGGING_DEFAULT := False;    // But don't make it the default logging device
end.
