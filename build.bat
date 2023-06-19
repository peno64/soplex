cmake -Bbuild -H.
cmake --build build --config Release

rem 32-bit
cmake -A Win32 -Bbuild32 -H.
cmake --build build32 --config Release
