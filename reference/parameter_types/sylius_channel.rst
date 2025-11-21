``ChannelType``
===============

+--------------------+----------------------------------------------------------------+
| Identifier         | ``sylius_channel``                                             |
+--------------------+----------------------------------------------------------------+
| Available options  | - `multiple`_                                                  |
+--------------------+----------------------------------------------------------------+
| Class              | ``Netgen\Layouts\Sylius\Parameters\ParameterType\ChannelType`` |
+--------------------+----------------------------------------------------------------+
| Valid value        | ID of an existing Sylius channel                               |
+--------------------+----------------------------------------------------------------+

This parameter allows to input the ID of an existing Sylius channel as its
value.

Available options
-----------------

``multiple``
~~~~~~~~~~~~

**type**: ``bool``, **required**: No, **default value**: ``false``

Specifies if the parameter type will accept multiple values.

.. note::

    This parameter type is available only if using Netgen Layouts on top of
    Sylius.
