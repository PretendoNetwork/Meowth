# Meowth - An SSL Patcher

![Meowth](meowth.png?raw=true)

Since NSSL is such hot garbage, a lot of games shipped their own static version of OpenSSL.
Meowth disables the SSL verification in such titles for development purposes.

Based on [Inkay](https://github.com/PretendoNetwork/Inkay).

## Compiling - Docker
Meowth's dependencies and build tooling can be handled as a container, which is generally recommended for WUPS
development.
Using `docker` or `podman`:
```shell
docker build -t meowth .
docker run --rm -v $(pwd):/app meowth make # replace "make" with any other command (make clean, etc.)
```

## Compiling - System
Meowth has the following dependencies:
- [WiiUPluginSystem](https://github.com/wiiu-env/WiiUPluginSystem)
- [libmocha](https://github.com/wiiu-env/libmocha)
- [libkernel](https://github.com/wiiu-env/libkernel/)

Each of these should be `make install`-able, and then Meowth can be compiled with `make`.