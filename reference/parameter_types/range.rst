``RangeType``
=============

+--------------------+------------------------------------------------------------+
| Identifier         | ``range``                                                  |
+--------------------+------------------------------------------------------------+
| Available options  | - `min`_                                                   |
|                    | - `max`_                                                   |
+--------------------+------------------------------------------------------------+
| Overridden options | - `default_value`_                                         |
+--------------------+------------------------------------------------------------+
| Class              | ``Netgen\BlockManager\Parameters\ParameterType\RangeType`` |
+--------------------+------------------------------------------------------------+
| Valid value        | An integer                                                 |
+--------------------+------------------------------------------------------------+

This parameter type represents a range. While in ``IntegerType``, ``min`` and
``max`` options are optional, here, they are required.

Available options
-----------------

``min``
~~~~~~~

**type**: ``int``, **required**: Yes

Specifies the minimum value of the parameter.

``max``
~~~~~~~

**type**: ``int``, **required**: Yes

Specifies the maximum value of the parameter.

Overridden options
------------------

``default_value``
~~~~~~~~~~~~~~~~~

If the parameter is required, the default parameter value will be equal to the
``min`` option, if not specified otherwise.
