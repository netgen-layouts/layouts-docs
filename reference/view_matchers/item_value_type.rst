``item\value_type``
===================

Matches on the type of rendered item. Used in ``item_view`` view.

Example
-------

.. code-block:: yaml

    netgen_layouts:
        view:
            item_view:
                default:
                    my_item:
                        template: '@App/item/my_item.html.twig'
                        match:
                            item\value_type: my_item
