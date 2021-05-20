Symfony commands
================

Export/import commands
----------------------

The following is a list of Symfony commands available in Netgen Layouts used for
exporting/importing Netgen Layouts data.

.. rst-class:: responsive

+----------------------+-------------------------------------------------------------------+
| Command name         | Purpose                                                           |
+======================+===================================================================+
| ``nglayouts:export`` | This script can be used to export one or more layouts or mappings |
|                      | to a file in JSON format                                          |
+----------------------+-------------------------------------------------------------------+
| ``nglayouts:import`` | This script can be used to import one or more layouts from a JSON |
|                      | format stored in a file                                           |
+----------------------+-------------------------------------------------------------------+

``nglayouts:export``
~~~~~~~~~~~~~~~~~~~~

This script can be used to export one or more layouts or mappings to JSON format.

To specify the type of the entity you wish to export, you need to provide it to
the script as the first argument.

To specify the ID of the entity to export, provide it to the script as the
second argument.

For example, to export the layout with ID of
``f95c98de-00ba-4890-8074-892565331345``, call the script like this:

.. code-block:: shell

    $ php bin/console nglayouts:export layout f95c98de-00ba-4890-8074-892565331345

Or to export a mapping with an ID of ``f95c98de-00ba-4890-8074-892565331345``,
call the script with:

.. code-block:: shell

    $ php bin/console nglayouts:export rule f95c98de-00ba-4890-8074-892565331345

You can also specify the list of IDs which will then be exported together:

.. code-block:: shell

    $ php bin/console nglayouts:export layout f95c98de-00ba-4890-8074-892565331345,8f9c943b-0c5a-402c-97da-62140e3af25b

If you want to export to file, you can redirect the standard output:

    $ php bin/console nglayouts:export layout f95c98de-00ba-4890-8074-892565331345,8f9c943b-0c5a-402c-97da-62140e3af25b > layouts.json

``nglayouts:import``
~~~~~~~~~~~~~~~~~~~~

This script can be used to import one or more layouts from a JSON format stored
in a file.

To specify the file from which the JSON data will be read, you need to provide
it to the script as the first argument.

For example, to import all layouts stored in a file called ``layouts.json``,
call the script like this:

.. code-block:: shell

    $ php bin/console nglayouts:import layouts.json

Migration commands
------------------

These commands are used in upgrade processes between various Netgen Layouts
versions.

.. warning::
    These scripts should not be executed in normal operation since they can
    result in loss of data.

.. rst-class:: responsive

+--------------------------------------------+-----------------------------------------------------------+
| Command name                               | Purpose                                                   |
+============================================+===========================================================+
| ``nglayouts:migration:query_offset_limit`` | Migrates query offset and limit parameters to the         |
|                                            | collection. Used when upgrading from version 0.9 to 0.10. |
+--------------------------------------------+-----------------------------------------------------------+

``nglayouts:migration:query_offset_limit``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This script migrates query offset and limit parameters to the collection. It is
used when upgrading from version 0.9 to 0.10.

The script does not have any parameters and can simply be called with:

.. code-block:: shell

    $ php bin/console nglayouts:migration:query_offset_limit

The script will ask you for names of offset and limit parameters for each of
your custom query types and then migrate the offset and limit from the query
to the collection.
