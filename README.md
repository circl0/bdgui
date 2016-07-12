#bdgui

[![Build Status](https://travis-ci.com/circl0/bdgui.svg?token=qMXgCniH4FekUTrRxT5c&branch=master)](https://travis-ci.com/circl0/bdgui)

bdgui is a kind of embedded ui based on multi-platform.

Now bdgui is only supported on Linux.

### Version
0.1

### Dependencies

* gdsl - c data-structure library


### Compiling

```sh
$ mkdir build && cd build
$ cmake -DCMAKE_TOOLCHAIN_FILE=[crossing-compiling config] ..
$ make
```

### Running & Debugging (Development with Mini2440-QEMU)
You must install python3 first in your pc and ssh server (include sftp) in your mini2440-qemu.
```sh
$ python3 tools/mini2440-qemu-debug/run_program.py -s [source] -d [destination]
```
The setting.json is the config file and you can config ssh connection to the mini2440-qemu.

