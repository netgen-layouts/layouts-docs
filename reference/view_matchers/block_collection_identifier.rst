``block\collection\identifier``
===============================

Matches on a collection identifier of the rendered collection page. Used in ``block_view`` view.

.. tip::

    This matcher is usually used in ``ajax`` block view context to specify the
    template for the collection page rendered via AJAX block view controller.

Example
-------

.. code-block:: yaml

    netgen_block_manager:
        view:
            block_view:
                ajax:
                    title\ajax\featured:
                        template: '@App/block/title/ajax/featured.html.twig'
                        match:
                            block\definition: title
                            block\collection\identifier: featured
