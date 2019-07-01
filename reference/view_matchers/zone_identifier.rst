``zone\identifier``
===================

Matches on zone identifier of the rendered zone. Used in ``zone_view`` view.

Example
-------

.. code-block:: yaml

    netgen_layouts:
        view:
            zone_view:
                default:
                    left:
                        template: '@App/zone/left.html.twig'
                        match:
                            zone\identifier: left
