``ContentType``
===============

+--------------------+---------------------------------------------------------------+
| Identifier         | ``ibexa_content``                                             |
+--------------------+---------------------------------------------------------------+
| Available options  | - `allow_invalid`_                                            |
|                    | - `allowed_types`_                                            |
+--------------------+---------------------------------------------------------------+
| Class              | ``Netgen\Layouts\Ibexa\Parameters\ParameterType\ContentType`` |
+--------------------+---------------------------------------------------------------+
| Valid value        | ID of an existing Ibexa CMS content                           |
+--------------------+---------------------------------------------------------------+

This parameter allows to input the ID of an existing Ibexa CMS content as its
value.

.. note::

    This parameter type is available only if using Netgen Layouts on top of
    Ibexa CMS.

Available options
-----------------

``allow_invalid``
~~~~~~~~~~~~~~~~~

**type**: ``bool``, **required**: No, **default value**: ``false``

If true, the parameter will allow storing IDs of content which does not exist in
the system.

``allowed_types``
~~~~~~~~~~~~~~~~~

**type**: ``array``, **required**: No, **default value**: ``[]``

If not empty, only content with provided content types will be allowed.
