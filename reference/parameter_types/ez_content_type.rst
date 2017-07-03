``ContentTypeType``
===================

+--------------------+---------------------------------------------------------------------+
| Identifier         | ``ez_content_type``                                                 |
+--------------------+---------------------------------------------------------------------+
| Available options  | - `multiple`_                                                       |
+--------------------+---------------------------------------------------------------------+
| Class              | ``Netgen\BlockManager\Ez\Parameters\ParameterType\ContentTypeType`` |
+--------------------+---------------------------------------------------------------------+
| Valid value        | One (or more) of the valid eZ Platform content types                |
+--------------------+---------------------------------------------------------------------+

This parameter allows to input one or more existing eZ Platform content types as
its value. The parameter automatically shows the list of all content types in
eZ Platform.

This parameter type is available only if using Netgen Layouts on top of
eZ Platform.

Available options
-----------------

``multiple``
~~~~~~~~~~~~

**type**: ``bool``, **required**: No, **default value**: ``false``

Specifies if the parameter type will accept multiple values.
