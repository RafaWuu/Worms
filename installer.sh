#!/bin/bash
help() {
  echo "Options:"
  echo "i: install"
  echo "u: unistall"
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
  cmake -DCMAKE_BUILD_TYPE=Release .
  sudo make install
}
uninstall(){
  clear
  sudo rm /usr/bin/client /usr/bin/server
  sudo rm /etc/worms/scenarios.yaml /etc/worms/configuration.yaml
  sudo rm -rf /etc/worms/assets
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
  u)
    uninstall
    ;;
  q)
    clear
    exit 0
    ;;
  *)
    clear
    echo "Error: invalid option"
    help
    ;;
  esac
  echo
  printf "Enter an option: "
done