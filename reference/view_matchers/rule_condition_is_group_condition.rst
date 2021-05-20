``rule_condition\is_group_condition``
=====================================

Matches on the fact that the rendered condition is a group condition or not.
Used in ``rule_condition_view`` view.

Example
-------

.. code-block:: yaml

    netgen_layouts:
        view:
            rule_condition_view:
                default:
                    query_parameter:
                        template: '@App/condition/query_parameter.html.twig'
                        match:
                            rule_condition\type: query_parameter
                            rule_condition\is_group_condition: true
