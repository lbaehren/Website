README
======

\tableofcontents

\section Requirements

  | Status       | Package    | Version            | Comment         |
  |--------------|------------|--------------------|-----------------|
  | (mandatory)  | CMake      | >= 2.8.2           |                 |
  | (mandatory)  | Ruby       |  = 1.8.6 or 1.8.7. |                 |
  | (mandatory)  | cmdparse   | >= 2.0.2           |                 |
  | (mandatory)  | kramdown   |  = 0.10.0          |                 |
  | (mandatory)  | ramaze     |  = 2009.04         | webgui          |
  | (optional)   | launchy    |  = 0.3.2           | webgui        |
  | (optional)   | rake       | >= 0.8.3   |                 |
  | (optional)   | RedCloth   | >= 4.1.9   | Textile support |
  | (optional)   | maruku     | >= 0.6.0   |                 |
  | (optional)   | haml       | >= 3.0.12  | haml, sass and scss support |
  | (optional)   | builder    | >= 2.1.0   | programmatic xml generation support |
  | (optional)   | rdoc       | >= 2.4.3   | RDoc markup support |
  | (optional)   | coderay    | >= 0.8.312 | syntax highlighting |
  | (optional)   | erubis     | >= 2.6.5   | Erubis (enhanced ERB) support |
  | (optional)   | rdiscount  | >= 1.3.5   | fast Markdown support |
  | (optional)   | archive-tar-minitar | >= 0.5.2 | (gzipped) tar archives as sources |

## Configuration and installation

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

## Directory structure

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
