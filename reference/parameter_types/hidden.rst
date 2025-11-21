``HiddenType``
==============

+-------------+--------------------------------------------------------+
| Identifier  | ``hidden``                                             |
+-------------+--------------------------------------------------------+
| Class       | ``Netgen\Layouts\Parameters\ParameterType\HiddenType`` |
+-------------+--------------------------------------------------------+
| Valid value | A string                                               |
+-------------+--------------------------------------------------------+

This parameter type represents a hidden value. Sometimes, you need the parameter
to have a dynamically set value in your block or query handler, but you do not
wish to expose the way for user to edit the value. You can then use the
``HiddenType`` for this purpose.
