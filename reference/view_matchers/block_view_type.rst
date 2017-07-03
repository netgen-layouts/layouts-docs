``block\view_type``
===================

Matches on view type of the rendered block. Used in ``block_view`` view.

.. tip::

    This matcher is usually used with ``block\definition`` matcher to specify
    for which exactly block and view type will the template be used.

Example
-------

.. code-block:: yaml

    netgen_block_manager:
        view:
            block_view:
                default:
                    title\title:
                        template: '@App/block/title.html.twig'
                        match:
                            block\definition: title
                            block\view_type: title
