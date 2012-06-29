Introduction                                                    {#mainpage}
============

This project started as the porting to C++ of my master thesis project
developed with Matlab.


How to build
============

The project is mantained in a git repository. The stable version is
in the `master` branch, while the currently developed version is in the
`develop` branch.

Requirements
------------

The build tool used is CMake.

The following libraries are required:

- Boost
  * filesystem
  * program-options
  * signals2
  * system
  * test (for tests only)
  * thread
- IT++
- libSVM
- Rlog
- JACK

Compile
-------

First clone the project, using the stable version:

    $ git clone git@git.assembla.com:svmacs.git

or use the `develop` branch for the latest bleeding edge version:

    $ git clone git@git.assembla.com:svmacs.git -b develop

Then create the build directory:

    $ cd svmacs
    $ mkdir build && cd build

and configure the project:

    $ cmake -i ..

Finally build the project:

    $ make

If you have more than one core/processor you can use the `-j` option:

    $ make -j 2

Optionally, you can run all the tests (if enabled during the configuration):

    $ make test

Install
-------

You can install with:

    $ make install

The install path can be configured using the
`CMAKE_INSTALL_PATH` variable or directly passed to make:

    $ make install DESTDIR=/my/custom/path

Uninstall with:

    $ make uninstall

or, if `DESTDIR` has been used:

    $ make uninstall DESTDIR=/my/custom/path

It is also possible to build a zip package:

    $ make package


How to run
==========

First, launch JACK with a sample rate of 22050 and **NO** realtime
(there is a bug that causes the JACK client to zombify when realtime is enabled).

Then launch the program:

    $ ./svmacs

and make the connection to JACK.
You can use the sample audio file `online-5db.wav` provided with sources.

Default parameters can be overridden either using the command line
or defined in the configuration file.
Please launch with the `--help` or `-h` option for details.


Additional Information
======================

For any questions and comments, please email me at:
<paolo.dapice@gmail.com>
