``ContentTypeType``
===================

+--------------------+---------------------------------------------------------------------+
| Identifier         | ``ez_content_type``                                                 |
+--------------------+---------------------------------------------------------------------+
| Available options  | - `multiple`_                                                       |
|                    | - `types`_                                                          |
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

``types``
~~~~~~~~~

**type**: ``array``, **required**: No, **default value**: ``array()``

Specifies which content types are allowed. This parameter is a multidimensional
array, where the keys are group names, and the values are arrays of content
types allowed within the group.

.. warning::

    Group names are case sensitive, while content type identifiers are not.

.. code-block:: php

    array(
        'Group1' => array('image', 'file'),
        'Group2' => array('article', 'blog_post'),
    );

If a group is missing from the array or the value of a group is ``true``, all
content types within that group are allowed.

If the value of a group is set to ``false`` or an empty array, none of the
content types within that group are allowed.

.. code-block:: php

    array(
        'Group1' => true,
        'Group2' => false,
        'Group3' => array(),
    );
