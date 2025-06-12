@echo off
chcp 65001 > nul
echo === Biên dịch Album Manager ===

g++ main.cpp Album.cpp file_io.cpp -o main.exe
if %errorlevel%==0 (
    echo Biên dịch thành công!
    echo === Chạy chương trình ===
    main.exe
) else (
    echo Biên dịch thất bại!
)

pause
