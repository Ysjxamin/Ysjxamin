@ECHO OFF
REM /*********************************************************************************************************//**
REM * @file    _CreateProject.bat
REM * @version $Rev:: 5229         $
REM * @date    $Date:: 2021-02-01 #$
REM * @brief   Create Project Script user API.
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
TITLE Create Project

SET PRJ_TYPE=Template
IF EXIST "ht32_usbd_descriptor.c" SET PRJ_TYPE=Template_USB

IF EXIST "_CreateProjectScript.bat" GOTO PROJECT_ALREADY_EXIST
IF NOT EXIST "..\..\..\project_template\Script\_CreateProjectScript.bat" GOTO CREATE_PROJECT_ERR
IF EXIST "_ProjectSource.ini" IF NOT EXIST "..\..\..\project_template\Script\_ProjectSource.bat" GOTO CREATE_PROJECT_ERR

COPY /Y "..\..\..\project_template\Script\_CreateProjectScript.bat"  "." 1> nul 2>&1

CALL _CreateProjectScript.bat %PRJ_TYPE%
IF EXIST "..\..\..\project_template\Script\_CreateProjectConfScript.bat" PAUSE
GOTO :EOF

:CREATE_PROJECT_ERR
ECHO.
ECHO "_CreateProjectScript.bat" or "_ProjectSource.bat" is not exist or has incompatible version.
ECHO Please update to the latest Firmware Library.
ECHO.
PAUSE
GOTO :EOF

:PROJECT_ALREADY_EXIST
ECHO.
ECHO The project related files are already exist. Please remove them first.....
ECHO.
PAUSE
GOTO :EOF
