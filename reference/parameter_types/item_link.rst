``ItemLinkType``
================

.. rst-class:: responsive

+--------------------+----------------------------------------------------------+
| Identifier         | ``item_link``                                            |
+--------------------+----------------------------------------------------------+
| Available options  | - `value_types`_                                         |
|                    | - `allow_invalid`_                                       |
+--------------------+----------------------------------------------------------+
| Class              | ``Netgen\Layouts\Parameters\ParameterType\ItemLinkType`` |
+--------------------+----------------------------------------------------------+
| Valid value        | The identifier of an existing value in the form          |
|                    | ``value_type://value``, for example ``ezlocation://42``  |
+--------------------+----------------------------------------------------------+

Available options
-----------------

``value_types``
~~~~~~~~~~~~~~~

**type**: ``array`` of ``string`` values, **required**: No, **default value**: All enabled value types

The list of accepted value types.

``allow_invalid``
~~~~~~~~~~~~~~~~~

**type**: ``bool``, **required**: No, **default value**: ``false``

If true, the parameter will allow storing IDs of items which does not exist or
are invalid.
