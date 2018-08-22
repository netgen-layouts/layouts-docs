``ChoiceType``
==============

+--------------------+-------------------------------------------------------------+
| Identifier         | ``choice``                                                  |
+--------------------+-------------------------------------------------------------+
| Available options  | - `multiple`_                                               |
|                    | - `expanded`_                                               |
|                    | - `options`_                                                |
+--------------------+-------------------------------------------------------------+
| Overridden options | - `default_value`_                                          |
+--------------------+-------------------------------------------------------------+
| Class              | ``Netgen\BlockManager\Parameters\ParameterType\ChoiceType`` |
+--------------------+-------------------------------------------------------------+
| Valid value        | One (or more) of the values specified in ``options`` option |
+--------------------+-------------------------------------------------------------+

Available options
-----------------

``multiple``
~~~~~~~~~~~~

**type**: ``bool``, **required**: No, **default value**: ``false``

Specifies if the parameter type will accept multiple values.

``expanded``
~~~~~~~~~~~~

**type**: ``bool``, **required**: No, **default value**: ``false``

If true, the parameter will be rendered as checkbox list or radio button list,
depending if ``multiple`` option is ``true`` or ``false``, respectively.

``options``
~~~~~~~~~~~

**type**: non empty ``array`` or ``callable``, **required**: Yes

Specifies the list of values allowed in the parameter. The list of values needs
to be a hash where keys represent option label and value represents option value.

If callback is used, the callback needs to return the array in the same format.

Overridden options
------------------

``default_value``
~~~~~~~~~~~~~~~~~

If the parameter is required, the default parameter value will be equal to the
first value in the list of allowed values, if not specified otherwise.
