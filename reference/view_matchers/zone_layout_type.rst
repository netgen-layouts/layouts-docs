``zone\layout_type``
====================

Matches on the layout type of the layout where rendered zone is located. Used in
``zone_view`` view, in most cases together with ``zone\layout_type`` matcher.

Example
-------

.. code-block:: yaml

    netgen_block_manager:
        view:
            zone_view:
                default:
                    layout_4:
                        template: '@App/zone/layout_4_left.html.twig'
                        match:
                            zone\layout_type: layout_4
                            zone\identifier: left
