``form\query\type``
===================

Matches on query type of a query which is edited through the Symfony form. Used
in ``form_view`` view.

Example
-------

.. code-block:: yaml

    netgen_block_manager:
        view:
            form_view:
                default:
                    query\my_query\edit:
                        template: '@App/query/my_query/edit.html.twig'
                        match:
                            form\type: Netgen\BlockManager\Collection\Query\Form\FullEditType
                            form\query\type: my_query
