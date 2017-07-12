How to inject items to blocks manually
======================================

Usually, block items are provided to blocks with a collection query. But,
sometimes it is useful to provide some specific block items to the block by hand
(meaning in block definition handler). This way, you could reuse block item
templates by calling the ``ngbm_render_item`` function on those items, instead
of duplicating the block item template logic inside the block itself.

To achieve this, you can use a Symfony service from Netgen Layouts called **item
builder** which is an instance of
``Netgen\BlockManager\Item\ItemBuilderInterface``. After that, you can just use
it in your ``getDynamicParameters`` method of the block definition handlers to
build the items and provide them as dynamic parameters to the block.

.. note::

    This service is used by the collection query result building process too,
    so you will be basically using the same principles Netgen Layouts uses when
    building items.

The ID of the item builder Symfony service is
``netgen_block_manager.item.item_builder`` and you can just inject it to your
block definition handlers as usual.

The service provides a single method called ``build`` which receives a single
parameter, your domain object, which will then build the block item. For this to
work, you need to have value converters (instances of
``Netgen\BlockManager\Item\ValueConverterInterface``) for any domain object you
wish to build items from.

For example, to build the item from your domain object, you would write
something like this in your ``getDynamicParameters`` method:

.. code-block:: php

    $myObject = $this->myBackend->loadMyObject(42);

    $item = $this->itemBuilder->build($myObject);
