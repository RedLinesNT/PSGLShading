@echo off
echo Cleaning up stuff...

:: Deleting the working directory
if exist working rmdir /s /q working

:: Deleting PKG files
if exist PSGLShading_RELEASE.pkg del /q PSGLShading_RELEASE.pkg 
if exist PSGLShading_DEBUG.pkg del /q PSGLShading_DEBUG.pkg 

:: Deleting Build results
if exist BuildOutput.txt del /q BuildOutput.txt