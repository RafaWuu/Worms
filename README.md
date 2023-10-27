# Worms

Instalar SDL: 
```
apt-get install libsdl2-dev
```
Para probar el CMake y que se linkea todo bien ejecutamos el test `hello_world.cpp` de Box2D:
```
sh hello_world.sh
```
O de manera equivalente: 
```
mkdir build
cd build
cmake ..
make
./hello_world
```