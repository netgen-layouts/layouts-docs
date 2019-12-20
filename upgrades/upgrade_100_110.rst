Upgrading from 1.0.0 to 1.1.0
=============================

Upgrade ``composer.json``
-------------------------

In your ``composer.json`` file, upgrade the version of ``netgen/layouts-core``
package and all other related packages (like ``netgen/layouts-standard``,
``netgen/layouts-ezplatform`` and others) to ``~1.1.0`` and run the
``composer update`` command.

Upgrading Netgen Content Browser
--------------------------------

Netgen Content Browser version 1.1 was also automatically installed. Be sure to
read `its upgrade instructions </projects/cb/en/latest/upgrades/upgrade_100_110.html>`_
too.

Changelog
---------

Major features
~~~~~~~~~~~~~~

* Implemented previewing your site from layout editing interface (Enterprise only)

Other changes
~~~~~~~~~~~~~

* Added support for PHP 7.4
* Added support for Symfony 5
* Added support for eZ Platform 3
* Added comments on mappings
* Added an option to duplicate mappings
* Added an option to manually specify mapping priorities when reordering them
* Added an option to see what layouts are using a specific shared layout
* Layout editing interface will now remind you that changes might not be saved if you reload or close the layout editing app
* The item type in the block is now displayed along side its name in layout editing app
* Content type of the eZ content object is now displayed along side its name in layout editing app

Breaking changes
----------------

There were no breaking changes in 1.1 version of Netgen Layouts.
