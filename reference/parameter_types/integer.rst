``IntegerType``
===============

+--------------------+--------------------------------------------------------------+
| Identifier         | ``integer``                                                  |
+--------------------+--------------------------------------------------------------+
| Available options  | - `min`_                                                     |
|                    | - `max`_                                                     |
+--------------------+--------------------------------------------------------------+
| Overridden options | - `default_value`_                                           |
+--------------------+--------------------------------------------------------------+
| Class              | ``Netgen\BlockManager\Parameters\ParameterType\IntegerType`` |
+--------------------+--------------------------------------------------------------+
| Valid value        | An integer                                                   |
+--------------------+--------------------------------------------------------------+

Available options
-----------------

``min``
~~~~~~~

**type**: ``int``, **required**: No, **default value**: ``null``

Specifies the minimum value of the parameter.

``max``
~~~~~~~

**type**: ``int``, **required**: No, **default value**: ``null``

Specifies the maximum value of the parameter.

Overridden options
------------------

``default_value``
~~~~~~~~~~~~~~~~~

If the parameter is required, the default parameter value will be equal to the
``min`` option, if not specified otherwise.
