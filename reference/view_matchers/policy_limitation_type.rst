``policy_limitation\type``
==========================

.. note::

    Available only in Enterprise Edition

Matches on type of the rendered policy limitation. Used in
``policy_limitation_view`` view.

Example
-------

.. code-block:: yaml

    netgen_layouts:
        view:
            policy_limitation_view:
                default:
                    block_definition:
                        template: '@App/limitation/block_definition.html.twig'
                        match:
                            policy_limitation\type: block_definition
