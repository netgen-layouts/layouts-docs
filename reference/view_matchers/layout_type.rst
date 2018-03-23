``layout\type``
===============

Matches on layout type of the rendered layout. Used in ``layout_view``
and ``layout_type_view`` views.

Example
-------

.. code-block:: yaml

    netgen_block_manager:
        view:
            layout_view:
                default:
                    layout_3:
                        template: '@App/layout/layout_3.html.twig'
                        match:
                            layout\type: layout_3
