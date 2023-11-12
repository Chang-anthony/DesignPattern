@REM get current bat file path
echo System batfilepath: %~dp0

call %~dp0Run\DesignPattern_Test.exe

IF %ERRORLEVEL% EQU 0 (
    ECHO Tests passed successfully.
) ELSE (
    ECHO Tests failed.
)

pause
