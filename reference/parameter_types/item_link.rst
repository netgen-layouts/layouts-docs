``ItemLinkType``
================

+--------------------+---------------------------------------------------------------+
| Identifier         | ``item_link``                                                 |
+--------------------+---------------------------------------------------------------+
| Available options  | - `value_types`_                                              |
+--------------------+---------------------------------------------------------------+
| Class              | ``Netgen\BlockManager\Parameters\ParameterType\ItemLinkType`` |
+--------------------+---------------------------------------------------------------+
| Valid value        | The identifier of an existing value in the form               |
|                    | ``value_type://value``, for example ``ezlocation://42``       |
+--------------------+---------------------------------------------------------------+

Available options
-----------------

``value_types``
~~~~~~~~~~~~~~~

**type**: ``array`` of ``string`` values, **required**: No, **default value**: All enabled item types

The list of accepted item types.
