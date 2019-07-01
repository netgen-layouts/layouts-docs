``item\view_type``
==================

Matches on item view type of the rendered item. Used in ``item_view`` view.

.. tip::

    This matcher is usually used with ``item\value_type`` matcher to specify
    for which exactly item and item view type will the template be used.

Example
-------

.. code-block:: yaml

    netgen_layouts:
        view:
            item_view:
                default:
                    my_item\standard_with_intro:
                        template: '@App/item/my_item.html.twig'
                        match:
                            item\value_type: my_item
                            item\view_type: standard_with_intro
