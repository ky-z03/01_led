# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/ESP32IDF/frameworks/esp-idf-v5.1.2/components/bootloader/subproject"
  "D:/VScode/ESP32/01_led/build/bootloader"
  "D:/VScode/ESP32/01_led/build/bootloader-prefix"
  "D:/VScode/ESP32/01_led/build/bootloader-prefix/tmp"
  "D:/VScode/ESP32/01_led/build/bootloader-prefix/src/bootloader-stamp"
  "D:/VScode/ESP32/01_led/build/bootloader-prefix/src"
  "D:/VScode/ESP32/01_led/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/VScode/ESP32/01_led/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/VScode/ESP32/01_led/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
