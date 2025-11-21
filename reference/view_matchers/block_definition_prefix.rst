``block\definition\prefix``
===========================

Matches on block definition prefix of the rendered block. Used in ``block_view``
view.

Example
-------

.. code-block:: yaml

    netgen_layouts:
        view:
            block_view:
                default:
                    my_block:
                        template: '@App/block/my_block.html.twig'
                        match:
                            block\definition\prefix: my_
