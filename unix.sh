if [ $(uname) == "Darwin" ]; then
  echo "MacOS detected"
  brew install make cmake avrdude avr-libc
else
  echo "Debian based linux detected"
  sudo apt-get update
  sudo apt-get install gcc-avr binutils-avr avr-libc cmake make gdb-avr avrdude
fi
