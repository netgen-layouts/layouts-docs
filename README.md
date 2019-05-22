# Netgen Layouts documentation

This repository contains documentation for Netgen Layouts. 

## Building the docs

If any of the following steps fail, rerun the commands with `sudo`.

* Install `pip`, Python Package Manager

    On Ubuntu, you can install it with:
    
    ```
    $ apt-get install python-pip
    ```

    Otherwise, check out [official install docs](https://pip.pypa.io/en/stable/installing/).

* Install the documentation dependencies: 

    ```
    $ pip install -r requirements.txt
    ```

* In the root directory of the repo, run the following to build the docs:

    ```
    $ make html
    ```

This will build the documentation and place the generated HTML files in `_build/html` directory.

Licensed under a Creative Commons Attribution-Share Alike 3.0 Unported License
([CC BY-SA 3.0](https://creativecommons.org/licenses/by-sa/3.0/)).
