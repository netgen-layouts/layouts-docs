``NumberType``
==============

+--------------------+--------------------------------------------------------+
| Identifier         | ``number``                                             |
+--------------------+--------------------------------------------------------+
| Available options  | - `min`_                                               |
|                    | - `max`_                                               |
|                    | - `scale`_                                             |
+--------------------+--------------------------------------------------------+
| Overridden options | - `default_value`_                                     |
+--------------------+--------------------------------------------------------+
| Class              | ``Netgen\Layouts\Parameters\ParameterType\NumberType`` |
+--------------------+--------------------------------------------------------+
| Valid value        | Any number (integer or float)                          |
+--------------------+--------------------------------------------------------+

Available options
-----------------

``min``
~~~~~~~

**type**: ``number``, **required**: No, **default value**: ``null``

Specifies the minimum value of the parameter.

``max``
~~~~~~~

**type**: ``number``, **required**: No, **default value**: ``null``

Specifies the maximum value of the parameter.

``scale``
~~~~~~~~~

**type**: ``int``, **required**: No, **default value**: 3

The number of digits after the decimal point.

Overridden options
------------------

``default_value``
~~~~~~~~~~~~~~~~~

If the parameter is required, the default parameter value will be equal to the
``min`` option, if not specified otherwise.
