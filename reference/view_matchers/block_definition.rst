``block\definition``
====================

Matches on block definition of the rendered block. Used in ``block_view`` view.

Example
-------

.. code-block:: yaml

    netgen_block_manager:
        view:
            block_view:
                default:
                    title:
                        template: '@App/block/title.html.twig'
                        match:
                            block\definition: title
