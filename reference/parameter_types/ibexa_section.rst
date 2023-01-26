``SectionType``
===============

+--------------------+---------------------------------------------------------------+
| Identifier         | ``ibexa_section``                                             |
+--------------------+---------------------------------------------------------------+
| Available options  | - `multiple`_                                                 |
|                    | - `sections`_                                                 |
+--------------------+---------------------------------------------------------------+
| Class              | ``Netgen\Layouts\Ibexa\Parameters\ParameterType\SectionType`` |
+--------------------+---------------------------------------------------------------+
| Valid value        | One (or more) of the valid Ibexa CMS sections                 |
+--------------------+---------------------------------------------------------------+

This parameter allows to input one or more existing Ibexa CMS sections as its
value. The parameter automatically shows the list of all sections in
Ibexa CMS.

This parameter type is available only if using Netgen Layouts on top of
Ibexa CMS.

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
