``rule_condition\type``
=======================

Matches on type of the rendered condition. Used in ``rule_condition_view`` view.

Example
-------

.. code-block:: yaml

    netgen_block_manager:
        view:
            rule_condition_view:
                default:
                    query_parameter:
                        template: '@App/condition/query_parameter.html.twig'
                        match:
                            rule\condition_type: query_parameter
