``SectionType``
===============

+--------------------+-----------------------------------------------------------------+
| Identifier         | ``ez_section``                                                  |
+--------------------+-----------------------------------------------------------------+
| Available options  | - `multiple`_                                                   |
|                    | - `sections`_                                                   |
+--------------------+-----------------------------------------------------------------+
| Class              | ``Netgen\BlockManager\Ez\Parameters\ParameterType\SectionType`` |
+--------------------+-----------------------------------------------------------------+
| Valid value        | One (or more) of the valid eZ Platform sections                 |
+--------------------+-----------------------------------------------------------------+

This parameter allows to input one or more existing eZ Platform sections as its
value. The parameter automatically shows the list of all sections in
eZ Platform.

This parameter type is available only if using Netgen Layouts on top of
eZ Platform.

Available options
-----------------

``multiple``
~~~~~~~~~~~~

**type**: ``bool``, **required**: No, **default value**: ``false``

Specifies if the parameter type will accept multiple values.

``sections``
~~~~~~~~~~~~

**type**: ``array``, **required**: No, **default value**: ``[]``

Specifies which sections are allowed. The values of the array are the list of
allowed section identifiers.
