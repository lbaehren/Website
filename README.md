## Requirements ##

  * CMake (www.cmake.org)
  * Webgen (webgen.rubyforge.org)

## Configuration and installation ##

After downloading the sources from Github

    git clone git://github.com/lbaehren/Website.git Website

it is best to create a separate 'build' directory in order not to interfere with the sources:

    mkdir build
    cd build
    cmake ..

At this point the working copy should be bootstrapped, such that you can continue by running

    make

in order to build and process all components or

    make Website

to only run Webgen to generate the website itself.

## Directory structure ##

Basically the files are separated into two categories: input files and output
files. In order to keep the two apart we have

    .
    |-- src
    `-- release

The source directory has the following sub-structure:

    .
     `-- src
         |-- code
         |   |-- apps
         |   |-- external
         |   |-- lib
         |   |-- scripts
         |   `-- tests
         |-- documentation
         |-- images
         |-- pages
         `-- templates
