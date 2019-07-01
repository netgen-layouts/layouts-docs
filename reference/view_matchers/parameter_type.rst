``parameter\type``
==================

Matches on type of the rendered parameter. Used in ``parameter_view`` view.

Example
-------

.. code-block:: yaml

    netgen_layouts:
        view:
            parameter_view:
                default:
                    link:
                        template: '@App/parameter/link.html.twig'
                        match:
                            parameter\type: link
