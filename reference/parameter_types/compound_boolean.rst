``Compound\BooleanType``
========================

+--------------------+-----------------------------------------------------------------------+
| Identifier         | ``compound_boolean``                                                  |
+--------------------+-----------------------------------------------------------------------+
| Available options  | - `reverse`_                                                          |
+--------------------+-----------------------------------------------------------------------+
| Overridden options | - `default_value`_                                                    |
+--------------------+-----------------------------------------------------------------------+
| Class              | ``Netgen\BlockManager\Parameters\ParameterType\Compound\BooleanType`` |
+--------------------+-----------------------------------------------------------------------+
| Valid value        | A boolean                                                             |
+--------------------+-----------------------------------------------------------------------+

This parameter is a special one in a manner that it can hold other parameters.

The main purpose of the parameter is not functional, but presentational. That
is, it allows building Symfony forms that have parameters which can be shown and
hidden by checking and un-checking the checkbox input.

The value of the parameter is preserved with all other parameters and its
sub-parameters in a flat list, without hierarchy.

Available options
-----------------

``reverse``
~~~~~~~~~~~

**type**: ``bool``, **required**: No, **default value**: ``false``

Specifies that the sub-parameters will be shown in the Symfony form when the
parameter is unchecked, rather than when it's checked.

Overridden options
------------------

``default_value``
~~~~~~~~~~~~~~~~~

If the parameter is required, the default parameter value will be set to
``false``, if not specified otherwise.
