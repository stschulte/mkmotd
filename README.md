mkmotd
======

Create a message of the day based on multiple
inputfiles in `/etc/motd.d`.

Purpose
-------

The message of day is compiled out of multiple source
files which allows packages and administrators to easily
add sections to the message of the day file.

This makes it possible to create a comprehensive guide
in form of a message of a day, that can instruct every user
that logs in on a box.

Possible examples to put in your message of the day:

- provide a link to image information and hardening
  information
- provide information/links about compliance topics
- provide helpful links to order additional software
  elevated rights, etc.

How to use
----------

1. Place your files in the directory `/etc/motd.d`
2. Run mkmotd

How to build mkmotd
-------------------

## Build and install from source

To build the software from source follow these steps

Clone the repository:
```
$ git clone https://github.com/stschulte/mkmotd.git
$ cd mkmotd
```

Build from source:
```
mkdir build
cd build
cmake ..
make
make install
```

## Build and install through package

### Build debian package

Simply run `dpkg-buildpackage`

### Build redhat package

Run `redhat/build.sh` to build an RPM package
