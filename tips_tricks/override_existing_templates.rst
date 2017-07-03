How to override existing templates
==================================

By using the view layer configuration in Netgen Layouts, it is possible to
override any template for built in layout types, block view types and block item
view types.

.. warning::

    View layer works in a way that first configuration which matches the rules is
    used for rendering the entity, so take care to properly use
    `Symfony configuration prepending`_ to make sure your rules are matched before
    the built in ones.

Overriding layout type templates
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You can override a template for any layout type (including built in ones) with
the following example configuration:

.. code-block:: yaml

    netgen_block_manager:
        view:
            layout_view:
                default:
                    layout_4_override:
                        template: "@App/layouts/layout_4.html.twig"
                        match:
                            layout\type: layout_4

This overrides the ``layout_4`` layout type to use
``@App/layouts/layout_4.html.twig`` template.

Overriding block view type templates
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You can override a template for any block view type (including built in ones)
with the following example configuration:

.. code-block:: yaml

    netgen_block_manager:
        view:
            block_view:
                default:
                    simple_title_override:
                        template: "@App/blocks/title/simple_title.html.twig"
                        match:
                            block\definition: title
                            block\view_type: simple_title

This overrides the ``simple_title`` view type of the ``title`` block definition
to use ``@App/blocks/title/simple_title.html.twig`` template.

Overriding block item view type templates
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You can override a template for any block item view type (including built in ones)
with the following example configuration:

.. code-block:: yaml

    netgen_block_manager:
        view:
            item_view:
                default:
                    my_item_standard_override:
                        template: "@App/items/my_item/standard.html.twig"
                        match:
                            item\value_type: my_item
                            item\view_type: standard

This overrides the ``standard`` item view type of the ``my_item`` item type
to use ``@App/items/my_item/standard.html.twig`` template.

.. tip::

    To override item view types for ``ezcontent`` and ``ezlocation`` item types,
    use the regular eZ Platform content view configuration instead of overriding
    the templates in Netgen Layouts.

.. _`Symfony configuration prepending`: https://symfony.com/doc/current/bundles/prepend_extension.html
