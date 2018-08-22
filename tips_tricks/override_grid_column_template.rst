How to override the templates for Grid block columns
====================================================

Grid block type uses a nifty little trick to specify the templates for its 2, 3,
4 or 6 columns variants which makes it possible to override the template for
only one of those variants without the need for overriding the entire grid
template.

Basically, it uses a feature from :doc:`the view layer </reference/view_layer>`
which makes it possible to inject custom parameters to Twig templates straight
from the match configuration rule. By default, if no parameter is provided that
specifies the template to use, Grid block uses built in templates for each of
the column variants.

As an example, the following configuration would override the template for 4
column variant of a Grid block:

.. code-block:: yaml

    netgen_block_manager:
        view:
            block_view:
                default:
                    list\grid\override:
                        template: "@NetgenBlockManager/block/list/grid.html.twig"
                        parameters:
                            column_templates:
                                4: "@App/block/grid/4_columns.html.twig"
                        match:
                            block\definition: list
                            block\view_type: grid

Basically, this rule specifies that we want to use the original grid template
available in Netgen Layouts (``@NetgenBlockManager/block/list/grid.html.twig``)
and to also provide a parameter called ``column_templates`` which the original
grid template uses to extract the template names for column variants from.

We only specified that 4 columns template should be overridden by specifying the
key with a value of ``4``, but we can easily add more overrides by specifying
more array keys in the ``column_templates`` parameter.
