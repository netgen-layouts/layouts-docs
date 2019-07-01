``rule_target\type``
====================

Matches on type of the rendered target. Used in ``rule_target_view`` view.

Example
-------

.. code-block:: yaml

    netgen_layouts:
        view:
            rule_target_view:
                default:
                    route:
                        template: '@App/target/route.html.twig'
                        match:
                            rule\target_type: route
