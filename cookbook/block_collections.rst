Adding collections to blocks
============================

As you are probably aware, blocks can have collections attached to them, which
provide block items to the block. Block definition can control if the block can
have a collection by specifying it in the block definition configuration. By
default, blocks do not use collections, so if you want to allow your custom
block definitions to use collections, configure it like this:

.. code-block:: yaml

    netgen_block_manager:
        block_definitions:
            my_block:
                collections: ~

Once you specify that your block definition can use collections, all blocks will
automatically be created with a manual collection attached to the block.

.. note::

    Currently, every block can have only one collection with an identifier named
    ``default``.

You can also configure which items and query types are valid for a collection.
That way, you can specify, for example, that your collection can only have
manual items or only a dynamic collection, or any combination of two.

To specify which item are allowed within the collection, use the config similar
to this:

.. code-block:: yaml

    netgen_block_manager:
        block_definitions:
            my_block:
                collections:
                    default:
                        # Set to an empty array to disable manual collection
                        valid_item_types: [my_item_type]

To specify which query types are allowed within the collection, use the config
similar to this:

.. code-block:: yaml

    netgen_block_manager:
        block_definitions:
            my_block:
                collections:
                    default:
                        # Set to an empty array to disable dynamic collection
                        valid_query_types: [my_query]

Accessing the collection and items in the template
--------------------------------------------------

The collection provides the block items to the block in form of a collection
result set object (``Netgen\Layouts\Collection\Result\ResultSet``) which is a
collection of result objects (``Netgen\Layouts\Collection\Result\Result``)
which themselves are a simple wrapper around the single item in a collection.

In the Twig templates for your block views, all collection results are
accessible through ``collections`` variable, which you can use to iterate over
the items in a collection and render them:

.. code-block:: jinja

    {% for result in collections.default %}
        {{ nglayouts_render_item(result.item, block.itemViewType) }}
    {% endfor %}

When rendering an item, you need to specify with which item view type it will be
rendered (``block.itemViewType`` in the above example). As with block view types,
item view type is nothing more than an identifier of a template which will be
used to render the item. Every block view type can define which item view types
it supports with the configuration like this:

.. code-block:: yaml

    netgen_block_manager:
        block_definitions:
            my_block:
                name: 'My block'
                view_types:
                    first:
                        name: 'First'
                        item_view_types:
                            item_type_1:
                                name: 'Item type 1'
                            item_type_2:
                                name: 'Item type 2'
                    second:
                        name: 'Second'

With this, we specified that ``first`` block view type supports ``item_type_1``
and ``item_type_2`` item view types, while ``second`` block view type does not
specify any specific item view types.

For every view type, an item view type called ``standard`` will be added
automatically to configuration. This is to make it easier to create item view
type templates for simpler blocks. If you wish to disable this ``standard`` item
view type, you can do so like this:

.. code-block:: yaml

    netgen_block_manager:
        block_definitions:
            my_block:
                view_types:
                    my_view_type:
                        item_view_types:
                            standard:
                                enabled: false

.. tip::

    In your Twig templates for block view types, you can ofcourse choose not to use
    the item view type stored in a block (``block.itemViewType``), but use a
    hardcoded one, or mix the hardcoded item view type with the one stored in a
    block and so on.

