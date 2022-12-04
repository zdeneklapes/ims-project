## IMS-PROJECT: Pastry Production

## Authors:

* Zdeněk Lapeš <lapes.zdenek@gmail.com> (xlapes02)
* Andrej Binovsky <todo> (xbinov00)

## QUESTION

#### What is the most efficient way to produce specified loaves of bread?

## REQUIREMENTS

- SIMLIB
- Linux OS

## INSTALLATION

### LOCAL

```bash
# 1.
./start.sh -bc # Prepare Cmake
./start.sh -bm # Build project
./start.sh -r  # Run program
```

or

```bash
make
make run
```

### VIRTUAL MACHINE (DOCKER)

```bash
./start.sh --download-third-party # Download third party libraries (SIMLIB)
docker build -t clion/remote-cpp-env:0.5 -f Dockerfile .
docker run -itd --cap-add sys_ptrace -p 127.0.0.1:2222:22 -v (pwd):/home/user/project clion/remote-cpp-env:0.5

#... next you go into docker container and run:
./start.sh -bc -bm -r
```
