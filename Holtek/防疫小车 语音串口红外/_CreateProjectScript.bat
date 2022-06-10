rem @ECHO OFF
REM /*********************************************************************************************************//**
REM * @file    _CreateProjectScript.bat
REM * @version $Rev:: 5234         $
REM * @date    $Date:: 2021-02-01 #$
REM * @brief   Create Project Script.
REM *************************************************************************************************************
REM * @attention
REM *
REM * Firmware Disclaimer Information
REM *
REM * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
REM *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
REM *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
REM *    other intellectual property laws.
REM *
REM * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
REM *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
REM *    other than HOLTEK and the customer.
REM *
REM * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
REM *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
REM *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
REM *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
REM *
REM * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
REM ************************************************************************************************************/

TITLE HT32 Create Project

SET CREATE_CONF_FILE=..\..\..\_CreateProjectConfig.bat
SET IC_NAME_FILE=..\..\..\project_template\Script\_ht32_ic_name.ini

REM Try to Start Create Project Config
REM  ===========================================================================
IF NOT EXIST "%CREATE_CONF_FILE%" (
COPY /Y "..\..\..\project_template\Script\_CreateProjectConfScript.bat"  "." 1> nul 2>&1
IF EXIST "_CreateProjectConfScript.bat" CALL _CreateProjectConfScript.bat
DEL /Q _CreateProjectConfScript.bat 1> nul 2>&1
)


REM Show Create Project Settings
REM  ===========================================================================
IF EXIST %CREATE_CONF_FILE% (
ECHO.
ECHO Load configuration file, "%CREATE_CONF_FILE%" ....
ECHO You can reset the create project IDE/IC configuration anytime by deleting the configuration file.
CALL %CREATE_CONF_FILE%
)

SET IDE1=-
SET IDE2=-
SET IDE3=-
SET IDE4=-
SET IDE5=-
SET IDE6=-
SET IDE7=-

IF (%IDE_KEILv5%) == (Y) SET IDE1=Y
IF (%IDE_KEIL%) == (Y) SET IDE2=Y
IF (%IDE_IARv8%) == (Y) SET IDE3=Y
IF (%IDE_IAR%) == (Y) SET IDE4=Y
IF (%IDE_SES%) == (Y) SET IDE5=Y
IF (%IDE_GNU%) == (Y) SET IDE6=Y
IF (%IDE_SGPP%) == (Y) SET IDE7=Y

IF EXIST %CREATE_CONF_FILE% (
ECHO.
ECHO Create Project Settings:
ECHO   [%IDE1%] Keil MDK-ARM v5
ECHO   [%IDE2%] Keil MDK-ARM v4
ECHO   [%IDE3%] IAR EWARM v8
ECHO   [%IDE4%] IAR EWARM v6/v7
ECHO   [%IDE5%] SEGGER Embedded Studio
ECHO   [%IDE6%] GNU [with Keil and GNU make]
ECHO   [%IDE7%] SourceryG++Lite [with Keil]
ECHO   Y: Enable, -: Disable
ECHO.
ECHO   IC Name: %IC_NAME% [* for all models, XXX* for series]
)


REM Start Copy Files
REM  ===========================================================================
ECHO.
ECHO Creating project. Please wait....

SET "CoIDE_DIR=%cd%"
:1
SET "CoIDE_DIR=%CoIDE_DIR:*\=%"&set "b=%CoIDE_DIR:\=%"
IF "%b%" NEQ "%CoIDE_DIR%" GOTO 1
SET "CoIDE_DIR=CoIDE_%CoIDE_DIR%"

SET PRO_TYPE=%1

IF %PRO_TYPE% == AUTO (
SET PRO_TYPE=Template
IF EXIST "ht32_usbd_descriptor.c" SET PRO_TYPE=Template_USB
)

REM Prepare not override input
ECHO NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN >> dummyn.txt
ECHO NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN >> dummyn.txt
ECHO NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN >> dummyn.txt
ECHO NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN >> dummyn.txt
ECHO NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN >> dummyn.txt
ECHO NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN >> dummyn.txt
ECHO NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN >> dummyn.txt
ECHO NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN >> dummyn.txt

REM No Create Project Config File, default copy all files
IF NOT EXIST %CREATE_CONF_FILE% (
SET IC_NAME=*
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\*"  "." < dummyn.txt 1> nul 2>&1
GOTO COPY_FINISH
) 

REM Copy files according to the Create Project Config File

REM For IC_NAME=*
SET SYSTEM_C_FILE=system_ht32*

REM Read system/startup settings
IF NOT (%IC_NAME%) == (*) (
FOR /F "tokens=1,2,3,4 delims=, " %%i IN (%IC_NAME_FILE%) DO (
  IF "%%i" == "%IC_NAME%" (
  SET SYSTEM_C_FILE=%%j
  SET STARTUP_FILE_PREFIX=%%k
  SET STARTUP_FILE_NUM=%%l
  )
)
)

XCOPY /-Y /Q "..\..\..\project_template\IP\%PRO_TYPE%\*.h"  "." < dummyn.txt 1> nul 2>&1

REM Take care 523* special case
SET STARTUP_FILE_NUM1=NULL
IF (%IC_NAME%) == (523*) (
SET STARTUP_FILE_PREFIX=startup_ht32f5xxxx_
SET STARTUP_FILE_NUM=01
SET STARTUP_FILE_NUM1=03

SET SYSTEM_C_FILE=NULL
XCOPY /-Y /Q "..\..\..\project_template\IP\%PRO_TYPE%\system_ht32f5xxxx_01.c"  "." < dummyn.txt 1> nul 2>&1
XCOPY /-Y /Q "..\..\..\project_template\IP\%PRO_TYPE%\system_ht32f5xxxx_03.c"  "." < dummyn.txt 1> nul 2>&1
)

REM Take care 123* special case
rem IF (%IC_NAME%) == (123*) (
rem )


REM Copy "system.c". May not meanful when IC_NAME = 523* or 123*
XCOPY /-Y /Q "..\..\..\project_template\IP\%PRO_TYPE%\%SYSTEM_C_FILE%.c"  "." < dummyn.txt 1> nul 2>&1

REM For ".mk" files of GNU
SET IC_NAME2=%IC_NAME%

REM Prepare exclude file type for XCOPY *
ECHO .uvprojx>Exclude.txt
ECHO .uvproj>>Exclude.txt
ECHO .dep>>Exclude.txt
ECHO .mk>>Exclude.txt
ECHO .ewd>>Exclude.txt
ECHO .ewp>>Exclude.txt
ECHO .eww>>Exclude.txt
ECHO .emProject>>Exclude.txt
ECHO .bat>>Exclude.txt
ECHO .s>>Exclude.txt

REM IC_NAME != *, not all IC model, XCOPY %IC_NAME% only copy Project_xxxxx.* files
IF NOT %IC_NAME% == * SET IC_NAME=Project_%IC_NAME%.*

IF %IDE_KEILv5% == Y (
XCOPY /-Y /S /Q /EXCLUDE:Exclude.txt "..\..\..\project_template\IP\%PRO_TYPE%\MDK_ARMv5\*"  ".\MDK_ARMv5\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\MDK_ARMv5\%IC_NAME%"  ".\MDK_ARMv5\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\MDK_ARMv5\%STARTUP_FILE_PREFIX%%STARTUP_FILE_NUM%.s"  ".\MDK_ARMv5\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\MDK_ARMv5\%STARTUP_FILE_PREFIX%%STARTUP_FILE_NUM1%.s"  ".\MDK_ARMv5\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\MDK_ARMv5\ht32_op.s"  ".\MDK_ARMv5\" < dummyn.txt 1> nul 2>&1
)

IF %IDE_KEIL% == Y (
XCOPY /-Y /S /Q /EXCLUDE:Exclude.txt "..\..\..\project_template\IP\%PRO_TYPE%\MDK_ARM\*"  ".\MDK_ARM\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\MDK_ARM\%IC_NAME%"  ".\MDK_ARM\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\MDK_ARM\%STARTUP_FILE_PREFIX%%STARTUP_FILE_NUM%.s"  ".\MDK_ARM\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\MDK_ARM\%STARTUP_FILE_PREFIX%%STARTUP_FILE_NUM1%.s"  ".\MDK_ARM\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\MDK_ARM\ht32_op.s"  ".\MDK_ARM\" < dummyn.txt 1> nul 2>&1
)

IF %IDE_IARv8% == Y (
XCOPY /-Y /S /Q /EXCLUDE:Exclude.txt "..\..\..\project_template\IP\%PRO_TYPE%\EWARMv8\*"  ".\EWARMv8\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\EWARMv8\%IC_NAME%"  ".\EWARMv8\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\EWARMv8\%STARTUP_FILE_PREFIX%iar_%STARTUP_FILE_NUM%.s"  ".\EWARMv8\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\EWARMv8\%STARTUP_FILE_PREFIX%iar_%STARTUP_FILE_NUM1%.s"  ".\EWARMv8\" < dummyn.txt 1> nul 2>&1
)

IF %IDE_IAR% == Y (
XCOPY /-Y /S /Q /EXCLUDE:Exclude.txt "..\..\..\project_template\IP\%PRO_TYPE%\EWARM\*"  ".\EWARM\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\EWARM\%IC_NAME%"  ".\EWARM\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\EWARM\%STARTUP_FILE_PREFIX%iar_%STARTUP_FILE_NUM%.s"  ".\EWARM\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\EWARM\%STARTUP_FILE_PREFIX%iar_%STARTUP_FILE_NUM1%.s"  ".\EWARM\" < dummyn.txt 1> nul 2>&1
)

IF %IDE_SES% == Y (
XCOPY /-Y /S /Q /EXCLUDE:Exclude.txt "..\..\..\project_template\IP\%PRO_TYPE%\emStudiov4\*"  ".\emStudiov4\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\emStudiov4\%IC_NAME%"  ".\emStudiov4\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\emStudiov4\%STARTUP_FILE_PREFIX%es_%STARTUP_FILE_NUM%.s"  ".\emStudiov4\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\emStudiov4\%STARTUP_FILE_PREFIX%es_%STARTUP_FILE_NUM1%.s"  ".\emStudiov4\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\emStudiov4\_MassErase.bat"  ".\emStudiov4\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\emStudiov4\Use Project_xxxxx.bat to open project" ".\emStudiov4\" < dummyn.txt 1> nul 2>&1
)

IF %IDE_GNU% == Y (
XCOPY /-Y /S /Q /EXCLUDE:Exclude.txt "..\..\..\project_template\IP\%PRO_TYPE%\GNU_ARM\*"  ".\GNU_ARM\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\GNU_ARM\%IC_NAME%"  ".\GNU_ARM\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\GNU_ARM\%IC_NAME2%.mk"  ".\GNU_ARM\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\GNU_ARM\%STARTUP_FILE_PREFIX%gcc_%STARTUP_FILE_NUM%.s"  ".\GNU_ARM\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\GNU_ARM\%STARTUP_FILE_PREFIX%gcc_%STARTUP_FILE_NUM1%.s"  ".\GNU_ARM\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\GNU_ARM\afterbuild.bat"  ".\GNU_ARM\" < dummyn.txt 1> nul 2>&1
)

IF %IDE_SGPP% == Y (
XCOPY /-Y /S /Q /EXCLUDE:Exclude.txt "..\..\..\project_template\IP\%PRO_TYPE%\SourceryG++Lite\*"  ".\SourceryG++Lite\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\SourceryG++Lite\%IC_NAME%"  ".\SourceryG++Lite\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\SourceryG++Lite\%STARTUP_FILE_PREFIX%cs3_%STARTUP_FILE_NUM%.s"  ".\SourceryG++Lite\" < dummyn.txt 1> nul 2>&1
XCOPY /-Y /S /Q "..\..\..\project_template\IP\%PRO_TYPE%\SourceryG++Lite\%STARTUP_FILE_PREFIX%cs3_%STARTUP_FILE_NUM1%.s"  ".\SourceryG++Lite\" < dummyn.txt 1> nul 2>&1
)

:COPY_FINISH
DEL Exclude.txt /Q 1> nul 2>&1
DEL dummyn.txt /Q 1> nul 2>&1

RENAME "CoIDE_Template\CoIDE_Template.cob" "%CoIDE_DIR%.cob" 1> nul 2>&1
RENAME CoIDE_Template %CoIDE_DIR% 1> nul 2>&1

COPY "..\..\..\gsar.e_x_e" "." 1> nul 2>&1
RENAME gsar.e_x_e gsar.exe 1> nul 2>&1

REM Process "_ProjectConfig.bat"
REM  ===========================================================================
IF EXIST _ProjectConfig.bat GOTO PROJECT_CONFIG
IF EXIST _ProjectConfigM3.bat GOTO PROJECT_CONFIG
IF EXIST _ProjectConfigM0p.bat GOTO PROJECT_CONFIG
GOTO CREATE_PROJECT_END

:PROJECT_CONFIG
IF EXIST MDK_ARM\HT32F5xxxx_01_DebugSupport.ini IF EXIST _ProjectConfigM0p.bat GOTO PROJECT_CFG_M0P
IF EXIST MDK_ARMv5\HT32F5xxxx_01_DebugSupport.ini IF EXIST _ProjectConfigM0p.bat GOTO PROJECT_CFG_M0P
IF EXIST MDK_ARM\HT32F1xxxx_01_DebugSupport.ini IF EXIST _ProjectConfigM3.bat GOTO PROJECT_CFG_M3
IF EXIST MDK_ARMv5\HT32F1xxxx_01_DebugSupport.ini IF EXIST _ProjectConfigM3.bat GOTO PROJECT_CFG_M3
GOTO PROJECT_CFG_ALL

:PROJECT_CFG_M0P
CALL _ProjectConfigM0p.bat 1> nul 2>&1
GOTO PROJECT_CFG_END

:PROJECT_CFG_M3
CALL _ProjectConfigM3.bat 1> nul 2>&1
GOTO PROJECT_CFG_END

:PROJECT_CFG_ALL
CALL _ProjectConfig.bat 1> nul 2>&1

:PROJECT_CFG_END

REM Change RO, RW Based address
REM  ===========================================================================
IF %HT_CHANGE_RO_RW%==1 GOTO BaseSET
GOTO BaseSET_End
:BaseSET
gsar.exe -s"<TextAddressRange>0x00000000</TextAddressRange>" -r"<TextAddressRange>%HT_RO_ADDR%</TextAddressRange>" MDK_ARM\*.uvproj -o 1> nul 2>&1
gsar.exe -s"<TextAddressRange>0x00000000</TextAddressRange>" -r"<TextAddressRange>%HT_RO_ADDR%</TextAddressRange>" MDK_ARMv5\*.uvprojx -o 1> nul 2>&1

gsar.exe -s"<DataAddressRange>0x20000000</DataAddressRange>" -r"<DataAddressRange>%HT_RW_ADDR%</DataAddressRange>" MDK_ARM\*.uvproj -o 1> nul 2>&1
gsar.exe -s"<DataAddressRange>0x20000000</DataAddressRange>" -r"<DataAddressRange>%HT_RW_ADDR%</DataAddressRange>" MDK_ARMv5\*.uvprojx -o 1> nul 2>&1

gsar.exe -s"define symbol __ICFEDIT_region_ROM_start__ = 0x00000000;" -r"define symbol __ICFEDIT_region_ROM_start__ = %HT_RO_ADDR%;" EWARM\*.icf -o 1> nul 2>&1
gsar.exe -s"define symbol __ICFEDIT_region_ROM_start__ = 0x00000000;" -r"define symbol __ICFEDIT_region_ROM_start__ = %HT_RO_ADDR%;" EWARMv8\*.icf -o 1> nul 2>&1

gsar.exe -s"define symbol __ICFEDIT_region_RAM_start__ = 0x20000000;" -r"define symbol __ICFEDIT_region_RAM_start__ = %HT_RW_ADDR%;" EWARM\*.icf -o 1> nul 2>&1
gsar.exe -s"define symbol __ICFEDIT_region_RAM_start__ = 0x20000000;" -r"define symbol __ICFEDIT_region_RAM_start__ = %HT_RW_ADDR%;" EWARMv8\*.icf -o 1> nul 2>&1

gsar.exe -s"ORIGIN = 0x00000000" -r"ORIGIN = %HT_RO_ADDR%" GNU_ARM\*.ld -o 1> nul 2>&1
gsar.exe -s"ORIGIN = 0x00000000" -r"ORIGIN = %HT_RO_ADDR%" SourceryG++Lite\*.ld -o 1> nul 2>&1

gsar.exe -s"ORIGIN = 0x20000000" -r"ORIGIN = %HT_RW_ADDR%" GNU_ARM\*.ld -o 1> nul 2>&1
gsar.exe -s"ORIGIN = 0x20000000" -r"ORIGIN = %HT_RW_ADDR%" SourceryG++Lite\*.ld -o 1> nul 2>&1

SETLOCAL EnableDelayedExpansion
SET HT_RW_ORG_HEX_LENGTH=0x00000000
SET HT_RO_ORG_HEX_LENGTH=0x00000000
SET HT_RW_ORG_DEC_LENGTH=0
SET HT_RO_ORG_DEC_LENGTH=0
SET HT_RW_NEW_LENGTH=0
SET HT_RO_NEW_LENGTH=0

REM Modify RO Data
FOR /f "eol= tokens=2 delims=," %%a IN ('FINDSTR /s "arm_simulator_memory_simulation_parameter" "*.emProject"') DO (
SET HT_RO_ORG_HEX_LENGTH=%%a
SET /A HT_RO_ORG_DEC_LENGTH=0x%%a
)
SET /A HT_RO_NEW_LENGTH=HT_RO_ORG_DEC_LENGTH-HT_RO_ADDR
gsar.exe -s"FLASH RX 0x00000000 0x%HT_RO_ORG_HEX_LENGTH%" -r"FLASH RX %HT_RO_ADDR% %HT_RO_NEW_LENGTH%" emStudiov4\Project_*.emProject -o 1> nul 2>&1

REM Modify RW Data
FOR /f "eol= tokens=4 delims=," %%a IN ('FINDSTR /s "arm_simulator_memory_simulation_parameter" "*.emProject"') DO (
SET HT_RW_ORG_HEX_LENGTH=%%a
SET /A HT_RW_ORG_DEC_LENGTH=0x%%a
)
SET /A HT_RW_NEW_LENGTH=HT_RW_ORG_DEC_LENGTH-(HT_RW_ADDR-0x20000000)
gsar.exe -s"RAM RWX 0x20000000 0x%HT_RW_ORG_HEX_LENGTH%" -r"RAM RWX %HT_RW_ADDR% %HT_RW_NEW_LENGTH%" emStudiov4\Project_*.emProject -o 1> nul 2>&1
:BaseSET_End


REM Change Stack, Heap size
REM  ===========================================================================
IF %HT_CHANGE_STACK_HEAP%==1 GOTO MemSET
GOTO MemSET_End
:MemSET
gsar.exe -s"Stack_Size          EQU     512" -r"Stack_Size          EQU     %HT_STACK_SIZE%" MDK_ARM\startup_ht32f*.s -o 1> nul 2>&1
gsar.exe -s"Stack_Size          EQU     512" -r"Stack_Size          EQU     %HT_STACK_SIZE%" MDK_ARMv5\startup_ht32f*.s -o 1> nul 2>&1
gsar.exe -s"Heap_Size           EQU     0"   -r"Heap_Size           EQU     %HT_HEAP_SIZE%"  MDK_ARM\startup_ht32f*.s -o 1> nul 2>&1
gsar.exe -s"Heap_Size           EQU     0"   -r"Heap_Size           EQU     %HT_HEAP_SIZE%"  MDK_ARMv5\startup_ht32f*.s -o 1> nul 2>&1

gsar.exe -s"define symbol __ICFEDIT_size_cstack__ = 0x200;" -r"define symbol __ICFEDIT_size_cstack__ = %HT_STACK_SIZE%;" EWARM\linker.icf -o 1> nul 2>&1
gsar.exe -s"define symbol __ICFEDIT_size_cstack__ = 0x200;" -r"define symbol __ICFEDIT_size_cstack__ = %HT_STACK_SIZE%;" EWARMv8\linker.icf -o 1> nul 2>&1
gsar.exe -s"define symbol __ICFEDIT_size_heap__   = 0x0;" -r"define symbol __ICFEDIT_size_heap__   = %HT_HEAP_SIZE%;" EWARM\linker.icf -o 1> nul 2>&1
gsar.exe -s"define symbol __ICFEDIT_size_heap__   = 0x0;" -r"define symbol __ICFEDIT_size_heap__   = %HT_HEAP_SIZE%;" EWARMv8\linker.icf -o 1> nul 2>&1

gsar.exe -s".equ    Stack_Size, 512" -r".equ    Stack_Size, %HT_STACK_SIZE%"    GNU_ARM\startup_ht32f*.s -o 1> nul 2>&1
gsar.exe -s".equ    Heap_Size, 0"    -r".equ    Heap_Size, %HT_HEAP_SIZE%"      GNU_ARM\startup_ht32f*.s -o 1> nul 2>&1

gsar.exe -s".equ    Stack_Size, 512" -r".equ    Stack_Size, %HT_STACK_SIZE%"    SourceryG++Lite\startup_ht32f*.s -o 1> nul 2>&1
gsar.exe -s".equ    Heap_Size, 0"    -r".equ    Heap_Size, %HT_HEAP_SIZE%"      SourceryG++Lite\startup_ht32f*.s -o 1> nul 2>&1

gsar.exe -s"arm_linker_stack_size=:x22512:x22" -r"arm_linker_stack_size=:x22%HT_STACK_SIZE%:x22"    emStudiov4\Project_*.emProject -o 1> nul 2>&1
gsar.exe -s"arm_linker_heap_size=:x220:x22" -r"arm_linker_heap_size=:x22%HT_HEAP_SIZE%:x22"    emStudiov4\Project_*.emProject -o 1> nul 2>&1
:MemSET_End


REM Change include path
REM  ===========================================================================
IF %HT_CHANGE_INCLUDE%==1 GOTO IncludeSET
GOTO IncludeSET_End
:IncludeSET
gsar.exe -s"..\..\..\..\utilities</IncludePath>" -r"..\..\..\..\utilities;%HT_EXTRA_INCLUDE%</IncludePath>" MDK_ARM\*.uvproj -o 1> nul 2>&1
gsar.exe -s"..\..\..\..\utilities</IncludePath>" -r"..\..\..\..\utilities;%HT_EXTRA_INCLUDE%</IncludePath>" MDK_ARMv5\*.uvprojx -o 1> nul 2>&1
gsar.exe -s"<state>$PROJ_DIR$\..\..\..\..\utilities</state>" -r"<state>$PROJ_DIR$\..\..\..\..\utilities</state>:x0d:x0a          <state>$PROJ_DIR$\%HT_EXTRA_INCLUDE_IAR5%</state>" EWARM\*.ewp -o 1> nul 2>&1
gsar.exe -s"<state>$PROJ_DIR$\..\..\..\..\utilities</state>" -r"<state>$PROJ_DIR$\..\..\..\..\utilities</state>:x0d:x0a          <state>$PROJ_DIR$\%HT_EXTRA_INCLUDE_IAR4%</state>" EWARM\*.ewp -o 1> nul 2>&1
gsar.exe -s"<state>$PROJ_DIR$\..\..\..\..\utilities</state>" -r"<state>$PROJ_DIR$\..\..\..\..\utilities</state>:x0d:x0a          <state>$PROJ_DIR$\%HT_EXTRA_INCLUDE_IAR3%</state>" EWARM\*.ewp -o 1> nul 2>&1
gsar.exe -s"<state>$PROJ_DIR$\..\..\..\..\utilities</state>" -r"<state>$PROJ_DIR$\..\..\..\..\utilities</state>:x0d:x0a          <state>$PROJ_DIR$\%HT_EXTRA_INCLUDE_IAR2%</state>" EWARM\*.ewp -o 1> nul 2>&1
gsar.exe -s"<state>$PROJ_DIR$\..\..\..\..\utilities</state>" -r"<state>$PROJ_DIR$\..\..\..\..\utilities</state>:x0d:x0a          <state>$PROJ_DIR$\%HT_EXTRA_INCLUDE_IAR1%</state>" EWARM\*.ewp -o 1> nul 2>&1
gsar.exe -s"<state>$PROJ_DIR$\..\..\..\..\utilities</state>" -r"<state>$PROJ_DIR$\..\..\..\..\utilities</state>:x0d:x0a                    <state>$PROJ_DIR$\%HT_EXTRA_INCLUDE_IAR5%</state>" EWARMv8\*.ewp -o 1> nul 2>&1
gsar.exe -s"<state>$PROJ_DIR$\..\..\..\..\utilities</state>" -r"<state>$PROJ_DIR$\..\..\..\..\utilities</state>:x0d:x0a                    <state>$PROJ_DIR$\%HT_EXTRA_INCLUDE_IAR4%</state>" EWARMv8\*.ewp -o 1> nul 2>&1
gsar.exe -s"<state>$PROJ_DIR$\..\..\..\..\utilities</state>" -r"<state>$PROJ_DIR$\..\..\..\..\utilities</state>:x0d:x0a                    <state>$PROJ_DIR$\%HT_EXTRA_INCLUDE_IAR3%</state>" EWARMv8\*.ewp -o 1> nul 2>&1
gsar.exe -s"<state>$PROJ_DIR$\..\..\..\..\utilities</state>" -r"<state>$PROJ_DIR$\..\..\..\..\utilities</state>:x0d:x0a                    <state>$PROJ_DIR$\%HT_EXTRA_INCLUDE_IAR2%</state>" EWARMv8\*.ewp -o 1> nul 2>&1
gsar.exe -s"<state>$PROJ_DIR$\..\..\..\..\utilities</state>" -r"<state>$PROJ_DIR$\..\..\..\..\utilities</state>:x0d:x0a                    <state>$PROJ_DIR$\%HT_EXTRA_INCLUDE_IAR1%</state>" EWARMv8\*.ewp -o 1> nul 2>&1
gsar.exe -s"          <state>$PROJ_DIR$\</state>:x0d:x0a" -r"" EWARM\*.ewp -o 1> nul 2>&1
gsar.exe -s"                    <state>$PROJ_DIR$\</state>:x0d:x0a" -r"" EWARMv8\*.ewp -o 1> nul 2>&1
gsar.exe -s"..\..\..\..\utilities</IncludePath>" -r"..\..\..\..\utilities;%HT_EXTRA_INCLUDE%</IncludePath>" GNU_ARM\*.uvprojx -o 1> nul 2>&1
gsar.exe -s"INCLUDE_PATH += -I./../../../../utilities" -r"INCLUDE_PATH += -I./../../../../utilities:x0d:x0a<HTGSARCONT>" GNU_ARM\*.mk -o 1> nul 2>&1
gsar.exe -s"<HTGSARCONT>" -r"INCLUDE_PATH += -I./%HT_EXTRA_INCLUDE_IAR1%:x0d:x0a<HTGSARCONT>" GNU_ARM\*.mk -o 1> nul 2>&1
gsar.exe -s"<HTGSARCONT>" -r"INCLUDE_PATH += -I./%HT_EXTRA_INCLUDE_IAR2%:x0d:x0a<HTGSARCONT>" GNU_ARM\*.mk -o 1> nul 2>&1
gsar.exe -s"<HTGSARCONT>" -r"INCLUDE_PATH += -I./%HT_EXTRA_INCLUDE_IAR3%:x0d:x0a<HTGSARCONT>" GNU_ARM\*.mk -o 1> nul 2>&1
gsar.exe -s"<HTGSARCONT>" -r"INCLUDE_PATH += -I./%HT_EXTRA_INCLUDE_IAR4%:x0d:x0a<HTGSARCONT>" GNU_ARM\*.mk -o 1> nul 2>&1
gsar.exe -s"<HTGSARCONT>" -r"INCLUDE_PATH += -I./%HT_EXTRA_INCLUDE_IAR5%:x0d:x0a<HTGSARCONT>" GNU_ARM\*.mk -o 1> nul 2>&1
gsar.exe -s":x0d:x0a<HTGSARCONT>" -r"" GNU_ARM\*.mk -o 1> nul 2>&1
gsar.exe -s"INCLUDE_PATH += -I./:x0d:x0a" -r"" GNU_ARM\*.mk -o 1> nul 2>&1
gsar.exe -s"..\..\..\..\utilities</IncludePath>" -r"..\..\..\..\utilities;%HT_EXTRA_INCLUDE%</IncludePath>" SourceryG++Lite\*.uvprojx -o 1> nul 2>&1

SETLOCAL ENABLEDELAYEDEXPANSION
SET TMPVAL=%HT_EXTRA_INCLUDE%
SET TMPVAL=!TMPVAL:\=\\!
gsar.exe -s"..\\..\\..\\..\\utilities:x22" -r"..\\..\\..\\..\\utilities;%TMPVAL%:x22" emStudiov4\Project_*.emProject -o 1> nul 2>&1
:IncludeSET_End


REM Change C define
REM  ===========================================================================
IF %HT_CHANGE_CDEFINE%==1 GOTO CdefineSET
GOTO CdefineSET_End
:CdefineSET
gsar.exe -s"<Define>USE_HT32_DRIVER," -r"<Define>USE_HT32_DRIVER, %HT_EXTRA_CDEFINE%" MDK_ARM\*.uvproj -o 1> nul 2>&1
gsar.exe -s"<Define>USE_HT32_DRIVER," -r"<Define>USE_HT32_DRIVER, %HT_EXTRA_CDEFINE%" MDK_ARMv5\*.uvprojx -o 1> nul 2>&1
gsar.exe -s"<name>CCDefines</name>" -r"<name>CCDefines</name>:x0d:x0a          <state>%HT_EXTRA_CDEFINE_IAR5%</state>" EWARM\*.ewp -o 1> nul 2>&1
gsar.exe -s"<name>CCDefines</name>" -r"<name>CCDefines</name>:x0d:x0a          <state>%HT_EXTRA_CDEFINE_IAR4%</state>" EWARM\*.ewp -o 1> nul 2>&1
gsar.exe -s"<name>CCDefines</name>" -r"<name>CCDefines</name>:x0d:x0a          <state>%HT_EXTRA_CDEFINE_IAR3%</state>" EWARM\*.ewp -o 1> nul 2>&1
gsar.exe -s"<name>CCDefines</name>" -r"<name>CCDefines</name>:x0d:x0a          <state>%HT_EXTRA_CDEFINE_IAR2%</state>" EWARM\*.ewp -o 1> nul 2>&1
gsar.exe -s"<name>CCDefines</name>" -r"<name>CCDefines</name>:x0d:x0a          <state>%HT_EXTRA_CDEFINE_IAR1%</state>" EWARM\*.ewp -o 1> nul 2>&1
gsar.exe -s"<name>CCDefines</name>" -r"<name>CCDefines</name>:x0d:x0a                    <state>%HT_EXTRA_CDEFINE_IAR5%</state>" EWARMv8\*.ewp -o 1> nul 2>&1
gsar.exe -s"<name>CCDefines</name>" -r"<name>CCDefines</name>:x0d:x0a                    <state>%HT_EXTRA_CDEFINE_IAR4%</state>" EWARMv8\*.ewp -o 1> nul 2>&1
gsar.exe -s"<name>CCDefines</name>" -r"<name>CCDefines</name>:x0d:x0a                    <state>%HT_EXTRA_CDEFINE_IAR3%</state>" EWARMv8\*.ewp -o 1> nul 2>&1
gsar.exe -s"<name>CCDefines</name>" -r"<name>CCDefines</name>:x0d:x0a                    <state>%HT_EXTRA_CDEFINE_IAR2%</state>" EWARMv8\*.ewp -o 1> nul 2>&1
gsar.exe -s"<name>CCDefines</name>" -r"<name>CCDefines</name>:x0d:x0a                    <state>%HT_EXTRA_CDEFINE_IAR1%</state>" EWARMv8\*.ewp -o 1> nul 2>&1
gsar.exe -s"<Define>USE_HT32_DRIVER," -r"<Define>USE_HT32_DRIVER, %HT_EXTRA_CDEFINE%" GNU_ARM\*.uvprojx -o 1> nul 2>&1
gsar.exe -s"<Define>USE_HT32_DRIVER," -r"<Define>USE_HT32_DRIVER, %HT_EXTRA_CDEFINE%" SourceryG++Lite\*.uvprojx -o 1> nul 2>&1

SETLOCAL ENABLEDELAYEDEXPANSION
SET TMPVAL=%HT_EXTRA_CDEFINE%
SET TMPVAL=!TMPVAL:,=;!
gsar.exe -s"USE_HT32_DRIVER;" -r"USE_HT32_DRIVER;%TMPVAL%;" emStudiov4\Project_*.emProject -o 1> nul 2>&1
:CdefineSET_End

:CREATE_PROJECT_END


REM Process "_ProjectSource.ini"
REM  ===========================================================================
IF EXIST "_ProjectSource.ini" (
  ECHO Success!
  ECHO Processing "_ProjectSource.ini". It may take a while....
  ECHO N > dummyn.txt
  COPY /-Y "..\..\..\project_template\Script\_ProjectSource.bat"  "." <dummyn.txt 1> nul 2>&1
  DEL dummyn.txt /Q
  CALL _ProjectSource.bat 1> nul 2>&1
  rem CALL _ProjectSource.bat
  DEL _ProjectSource.bat /Q 1> nul 2>&1
)

REM All finished
REM  ===========================================================================
DEL gsar.exe /Q 1> nul 2>&1
ECHO Success!
ECHO.
