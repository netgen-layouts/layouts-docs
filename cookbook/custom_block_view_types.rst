Adding custom view types to blocks
==================================

Just as you can specify that your own custom blocks have certain view types, you
can extend existing blocks to add your own view types to them. Configuration to
do so is completely the same as with adding a custom block.

When adding a block view type, you need to specify them in block definition
settings, as well as configure the template used for them (both for frontend and
backend).

The following configuration shows an example how to add a custom view type to
existing ``list`` block definition called ``list_numbered`` and how to specify
the templates that will be used:

.. code-block:: yaml

    netgen_layouts:
        block_definitions:
            list:
                view_types:
                    list_numbered:
                        name: 'List (numbered)'
        view:
            block_view:
                default:
                    list\numbered:
                        template: "@App/block/list/list_numbered.html.twig"
                        match:
                            block\definition: list
                            block\view_type: list_numbered
                app:
                    list\numbered:
                        template: "@NetgenLayoutsStandard/app/block/list/list.html.twig"
                        match:
                            block\definition: list
                            block\view_type: list_numbered

Note that template rule for backend (``app`` context) reuses the template for
list view type already available in the ``list`` block. This is to make sure
that both ``list`` and ``list_numbered`` view types are displayed in the same
way in the backend. This is of course optional as you can specify your own
template for the backend.

Adding a custom item view type
------------------------------

You can also add custom item view types to every existing block and its view
types.

The following configuration shows an example how to add a custom item view type
called ``standard_with_intro`` to already existing block view type in ``list``
block definition:

.. code-block:: yaml

    netgen_layouts:
        block_definitions:
            list:
                view_types:
                    list:
                        item_view_types:
                            standard_with_intro:
                                name: 'Standard (with intro)'

You can specified the template to be used like this:

.. code-block:: yaml

    netgen_layouts:
        view:
            item_view:
                default:
                    my_item\standard_with_intro:
                        template: "@App/items/my_item/standard_with_intro.html.twig"
                        match:
                            item\value_type: my_item
                            item\view_type: standard_with_intro
                app:
                    my_item\standard_with_intro:
                        template: "@App/items/app/my_item/standard_with_intro.html.twig"
                        match:
                            item\value_type: my_item
                            item\view_type: standard_with_intro

.. tip::

    If using Netgen Layouts in Ibexa CMS, every content view type is also a
    valid item view type. Because of that, you don't need to duplicate templates
    from Ibexa CMS in Netgen Layouts to display Ibexa locations. For example, if
    you have a ``listitem`` content view type for your content, you can use it
    just by specifying that some of your block view types have a ``listitem``
    item view type and selecting in the block configuration in the right sidebar.

.. note::

    In case of Ibexa CMS, it is always a good idea to specify a fallback
    content view template that will be applied to all content types, since
    Netgen Layouts does not limit which Ibexa content types can be added to
    blocks.

Disabling existing view types in blocks
---------------------------------------

You can disable any existing block view types or item view types to stop them
from showing up in layout editing app.

The following configuration shows an example how to disable a block view type:

.. code-block:: yaml

    netgen_layouts:
        block_definitions:
            list:
                view_types:
                    some_view_type:
                        enabled: false

The following configuration shows an example how to disable an item view type:

.. code-block:: yaml

    netgen_layouts:
        block_definitions:
            list:
                view_types:
                    list:
                        item_view_types:
                            some_item_view_type:
                                enabled: false

Note that when you disable a block view type or an item view type, they will
still be used by the rendering engine. However, you will not be able to save the
block configuration any more in layout editing app until you change the (item)
view type to some other enabled one.
