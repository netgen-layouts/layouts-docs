``TagsType``
============

+--------------------+--------------------------------------------------------------+
| Identifier         | ``eztags``                                                   |
+--------------------+--------------------------------------------------------------+
| Available options  | - `min`_                                                     |
|                    | - `max`_                                                     |
+--------------------+--------------------------------------------------------------+
| Class              | ``Netgen\BlockManager\Ez\Parameters\ParameterType\TagsType`` |
+--------------------+--------------------------------------------------------------+
| Valid value        | Array of IDs of existing tags in Netgen Tags bundle          |
+--------------------+--------------------------------------------------------------+

This parameter allows to input the list of existing IDs of tags available in
Netgen Tags.

Requires `Netgen Tags Bundle`_ to be activated work.

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

.. _`Netgen Tags Bundle`: https://github.com/netgen/tagsbundle
