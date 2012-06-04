@echo off

set CWRSYNCHOME=tools\%CWRSYNC
set CYGWIN=nontsec
set HOME=%HOMEDRIVE%%HOMEPATH%
set CWOLDPATH=%PATH%
set PATH=%CWRSYNCHOME%\BIN;%PATH%

set LOCAL_PATH=./ 

rem ------------------------------------------------------------------------
rem Andrey Sidorov settings
if "%COMPUTERNAME%"=="KHAWKS0035" (
	set HOST=andrey.sidorov@10.60.8.214
	set REMOTE_PATH=/Work/sagcg
)
rem ------------------------------------------------------------------------
