## Requirements ##

  * CMake (www.cmake.org)
  * Webgen

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


