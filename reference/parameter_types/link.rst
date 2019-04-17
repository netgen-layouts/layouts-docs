``LinkType``
============

.. rst-class:: responsive

+--------------------+---------------------------------------------------------+
| Identifier         | ``link``                                                |
+--------------------+---------------------------------------------------------+
| Available options  | - `value_types`_                                        |
|                    | - `allow_invalid_internal`_                             |
+--------------------+---------------------------------------------------------+
| Class              | ``Netgen\Layouts\Parameters\ParameterType\LinkType``    |
+--------------------+---------------------------------------------------------+
| Valid value        | A structure containing valid URL, e-mail address, phone |
|                    | number or internal link, together with link suffix and  |
|                    | target. This structure is represented by                |
|                    | ``Netgen\Layouts\Parameters\Value\LinkValue`` object.   |
+--------------------+---------------------------------------------------------+

This parameter type represents a link. Multiple link types are supported:

* URL
* E-mail address
* Phone number
* Internal link (link to valid value of an item)

Available options
-----------------

``value_types``
~~~~~~~~~~~~~~~

**type**: ``array`` of ``string`` values, **required**: No, **default value**: All enabled value types

The list of accepted value types.

``allow_invalid_internal``
~~~~~~~~~~~~~~~~~~~~~~~~~~

**type**: ``bool``, **required**: No, **default value**: ``false``

If true and internal link is selected, the parameter will allow storing IDs of
items which does not exist or are invalid.
