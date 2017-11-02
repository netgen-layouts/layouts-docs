Symfony commands
================

Migration commands
------------------

These commands are used in upgrade processes and should not be executed in
normal operation since they can result in loss of data.

.. rst-class:: responsive

+---------------------------------------+-----------------------------------------------------------+
| Command name                          | Purpose                                                   |
+=======================================+===========================================================+
| ``ngbm:migration:query_offset_limit`` | Migrates query offset and limit parameters to the         |
|                                       | collection. Used when upgrading from version 0.9 to 0.10. |
+---------------------------------------+-----------------------------------------------------------+
