@echo off

REM Проверяем, был ли передан параметр
if "%~1"=="" (
    echo No file path specified.
    exit /b 1
)

REM Устанавливаем переменную filepath равной первому параметру
set "filepath=%~1"

REM Выводим путь к файлу для проверки
echo File path: "%filepath%"

REM Запускаем ваше приложение с передачей пути к файлу в кавычках
GPS_converter.exe "%filepath%" -24


REM Завершаем скрипт
exit /b 0
