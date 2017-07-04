``LinkType``
============

.. rst-class:: responsive

+--------------------+------------------------------------------------------------+
| Identifier         | ``link``                                                   |
+--------------------+------------------------------------------------------------+
| Available options  | - `value_types`_                                           |
+--------------------+------------------------------------------------------------+
| Class              | ``Netgen\BlockManager\Parameters\ParameterType\LinkType``  |
+--------------------+------------------------------------------------------------+
| Valid value        | A structure containing valid URL, e-mail address, phone    |
|                    | number or internal link, together with link suffix and     |
|                    | target. This structure is represented by                   |
|                    | ``Netgen\BlockManager\Parameters\Value\LinkValue`` object. |
+--------------------+------------------------------------------------------------+

This parameter type represents a link. Multiple link types are supported:

* URL
* E-mail address
* Phone number
* Internal link (link to valid value of an item)

Available options
-----------------

``value_types``
~~~~~~~~~~~~~~~

**type**: ``array`` of ``string`` values, **required**: No, **default value**: All enabled item types

The list of accepted item types.
