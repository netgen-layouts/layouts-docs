``HtmlType``
============

+-------------+------------------------------------------------------+
| Identifier  | ``html``                                             |
+-------------+------------------------------------------------------+
| Class       | ``Netgen\Layouts\Parameters\ParameterType\HtmlType`` |
+-------------+------------------------------------------------------+
| Valid value | A valid HTML markup                                  |
+-------------+------------------------------------------------------+

This parameter type represents a valid HTML markup. The reason why there's a
custom parameter type is HTML filtering. This parameter type will filter all
input to get a valid HTML markup which is free of potential security issues,
like XSS.
