#!/bin/bash
help() {
  clear
  echo "Options:"
  echo "i: install"
  echo "q: close"
}
install(){
# instalamos dependencias o lo avisamos en el readme sdl, qt, etc
# sudo apt-get install cmake
# sudo apt-get install libsdl2-dev
# sudo apt-get install libsdl2-image-dev
# sudo apt-get install libsdl2-mixer-dev
# sudo apt-get install qtcreator
# sudo apt-get install qt5-default
git submodule init
git submodule update
    clear
    cmake .
    sudo make install
}
# main 
clear
help
printf "Enter an option: "

while true; do
  read option
  clear
  echo ""
  case $option in
  i)
    install
    ;;
  q)
    clear
    exit 0
    ;;
  *)
    echo "Error: invalid option"
    ;;
  esac
  echo
  printf "Enter an option: "
done