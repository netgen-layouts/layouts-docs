Symfony commands
================

Export/import commands
----------------------

The following is a list of Symfony commands available in Netgen Layouts used for
exporting/importing Netgen Layouts data.

.. rst-class:: responsive

+-----------------+-------------------------------------------------------------------+
| Command name    | Purpose                                                           |
+=================+===================================================================+
| ``ngbm:export`` | This script can be used to export one or more layouts or mappings |
|                 | to a file in JSON format                                          |
+-----------------+-------------------------------------------------------------------+
| ``ngbm:import`` | This script can be used to import one or more layouts from a JSON |
|                 | format stored in a file                                           |
+-----------------+-------------------------------------------------------------------+

``ngbm:export``
~~~~~~~~~~~~~~~

This script can be used to export one or more layouts or mappings to a file in
JSON format.

To specify the type of the entity you wish to export, you need to provide it to
the script as the first argument.

To specify the ID of the entity to export, provide it to the script as the
second argument.

You can also provide the name of the file where to store the export as the third
argument. This argument is optional and if you do not provide it, JSON will be
dumped to the standard output of your terminal.

For example, to export the layout with ID of 1, call the script like this:

.. code-block:: shell

    $ php bin/console ngbm:export layout 1 layout_1.json

Or to export a mapping with an ID of 1, call the script with:

.. code-block:: shell

    $ php bin/console ngbm:export rule 1  rule_1.json

You can also specify the list of IDs which will then be exported together:

.. code-block:: shell

    $ php bin/console ngbm:export layout 1,2,3 layouts.json

``ngbm:import``
~~~~~~~~~~~~~~~

This script can be used to import one or more layouts from a JSON format stored
in a file.

To specify the type of the entity you wish to import, you need to provide it to
the script as the first argument. Currently, only layouts can be imported.

To specify the file from which the JSON data will be read, you need to provide
it to the script as the second argument.

For example, to import all layouts stored in a file called ``layouts.json``,
call the script like this:

.. code-block:: shell

    $ php bin/console ngbm:import layout layouts.json

Migration commands
------------------

These commands are used in upgrade processes between various Netgen Layouts
versions.

.. warning::
    These scripts should not be executed in normal operation since they can
    result in loss of data.

.. rst-class:: responsive

+---------------------------------------+-----------------------------------------------------------+
| Command name                          | Purpose                                                   |
+=======================================+===========================================================+
| ``ngbm:migration:query_offset_limit`` | Migrates query offset and limit parameters to the         |
|                                       | collection. Used when upgrading from version 0.9 to 0.10. |
+---------------------------------------+-----------------------------------------------------------+

``ngbm:migration:query_offset_limit``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This script migrates query offset and limit parameters to the collection. It is
used when upgrading from version 0.9 to 0.10.

The script does not have any parameters and can simply be called with:

.. code-block:: shell

    $ php bin/console ngbm:migration:query_offset_limit

The script will ask you for names of offset and limit parameters for each of
your custom query types and then migrate the offset and limit from the query
to the collection.
