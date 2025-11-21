``EnumType``
============

+--------------------+------------------------------------------------------------------------------+
| Identifier         | ``enum``                                                                     |
+--------------------+------------------------------------------------------------------------------+
| Available options  | - `multiple`_                                                                |
|                    | - `expanded`_                                                                |
|                    | - `class`_                                                                   |
|                    | - `option_label_prefix`_                                                     |
+--------------------+------------------------------------------------------------------------------+
| Overridden options | - `default_value`_                                                           |
+--------------------+------------------------------------------------------------------------------+
| Class              | ``Netgen\Layouts\Parameters\ParameterType\EnumType``                         |
+--------------------+------------------------------------------------------------------------------+
| Valid value        | One (or more) instances of backed enums specified by the ``class`` parameter |
+--------------------+------------------------------------------------------------------------------+

Available options
-----------------

``multiple``
~~~~~~~~~~~~

**type**: ``bool``, **required**: No, **default value**: ``false``

Specifies if the parameter type will accept multiple enum values.

``expanded``
~~~~~~~~~~~~

**type**: ``bool``, **required**: No, **default value**: ``false``

If true, the parameter will be rendered as checkbox list or radio button list,
depending if ``multiple`` option is ``true`` or ``false``, respectively.

``class``
~~~~~~~~~

**type**: a ``string`` representing a FQCN of a backed enum, **required**: Yes

Specifies the FQCN of a backed enum that this parameter type will accept as
values.

``option_label_prefix``
~~~~~~~~~~~~~~~~~~~~~~~

**type**: ``string``, **required**: No, **default value**: ``null``

Specifies the prefix that will be used when generating the choice option label.
The resulting label will have the format ``<prefix>.<case>`` where ``<prefix>``
is the value of this option and ``<case>`` is the value of a specific enum case.

Overridden options
------------------

``default_value``
~~~~~~~~~~~~~~~~~

If the parameter is required, the default parameter value will be equal to the
first case available in the backed enum, if not specified otherwise.
