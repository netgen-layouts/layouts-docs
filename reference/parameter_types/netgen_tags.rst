``TagsType``
============

+--------------------+------------------------------------------------------------+
| Identifier         | ``netgen_tags``                                            |
+--------------------+------------------------------------------------------------+
| Available options  | - `min`_                                                   |
|                    | - `max`_                                                   |
|                    | - `allow_invalid`_                                         |
+--------------------+------------------------------------------------------------+
| Class              | ``Netgen\Layouts\Ibexa\Parameters\ParameterType\TagsType`` |
+--------------------+------------------------------------------------------------+
| Valid value        | Array of IDs of existing tags in Netgen Tags bundle        |
+--------------------+------------------------------------------------------------+

This parameter allows to input the list of existing IDs of tags available in
Netgen Tags.

.. note::

    Requires Ibexa CMS with `Netgen Tags Bundle`_ to be activated work.

Available options
-----------------

``min``
~~~~~~~

**type**: ``int``, **required**: No, **default value**: ``null``

Specifies the minimum number of tags that can be set as value. Use ``null`` to
disable the limit.

``max``
~~~~~~~

**type**: ``int``, **required**: No, **default value**: ``null``

Specifies the maximum number of tags that can be set as value. Use ``null`` to
disable the limit.

``allow_invalid``
~~~~~~~~~~~~~~~~~

**type**: ``bool``, **required**: No, **default value**: ``false``

If true, the parameter will allow storing IDs of tags which do not exist in the
system.

.. _`Netgen Tags Bundle`: https://github.com/netgen/tagsbundle
