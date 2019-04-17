``LocationType``
================

+--------------------+-------------------------------------------------------------+
| Identifier         | ``ezlocation``                                              |
+--------------------+-------------------------------------------------------------+
| Available options  | - `allow_invalid`_                                          |
|                    | - `allowed_types`_                                          |
+--------------------+-------------------------------------------------------------+
| Class              | ``Netgen\Layouts\Ez\Parameters\ParameterType\LocationType`` |
+--------------------+-------------------------------------------------------------+
| Valid value        | ID of an existing eZ Platform location                      |
+--------------------+-------------------------------------------------------------+

This parameter allows to input the ID of an existing eZ Platform location as its
value.

.. note::

    This parameter type is available only if using Netgen Layouts on top of
    eZ Platform.

Available options
-----------------

``allow_invalid``
~~~~~~~~~~~~~~~~~

**type**: ``bool``, **required**: No, **default value**: ``false``

If true, the parameter will allow storing IDs of locations which do not exist in
the system.

``allowed_types``
~~~~~~~~~~~~~~~~~

**type**: ``array``, **required**: No, **default value**: ``[]``

If not empty, only locations which have content with provided content types will
be allowed.
