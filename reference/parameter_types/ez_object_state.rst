``ObjectStateType``
===================

+--------------------+----------------------------------------------------------------+
| Identifier         | ``ez_object_state``                                            |
+--------------------+----------------------------------------------------------------+
| Available options  | - `multiple`_                                                  |
|                    | - `states`_                                                    |
+--------------------+----------------------------------------------------------------+
| Class              | ``Netgen\Layouts\Ez\Parameters\ParameterType\ObjectStateType`` |
+--------------------+----------------------------------------------------------------+
| Valid value        | One (or more) of the valid eZ Platform object states           |
+--------------------+----------------------------------------------------------------+

This parameter allows to input one or more existing eZ Platform object states
as its value. The parameter automatically shows the list of all object states
in eZ Platform.

This parameter type is available only if using Netgen Layouts on top of
eZ Platform.

Available options
-----------------

``multiple``
~~~~~~~~~~~~

**type**: ``bool``, **required**: No, **default value**: ``false``

Specifies if the parameter type will accept multiple values.

``states``
~~~~~~~~~~

**type**: ``array``, **required**: No, **default value**: ``[]``

Specifies which object states are allowed. This parameter is a multidimensional
array, where the keys are group identifiers, and the values are arrays of
object states allowed within the group.

.. code-block:: php

    [
        'state_group1' => ['state1', 'state2'],
        'state_group2' => ['state3'],
    ];

If a group is missing from the array or the value of a group is ``true``, all
object states within that group are allowed.

If the value of a group is set to ``false`` or an empty array, none of the
object states within that group are allowed.

.. code-block:: php

    [
        'state_group1' => true,
        'state_group2' => false,
        'state_group3' => [],
    ];
