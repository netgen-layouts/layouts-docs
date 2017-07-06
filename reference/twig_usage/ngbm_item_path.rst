``ngbm_item_path``
==================

This function is used to generate an URL to an item from your CMS.

.. note::

    To be able to generate the URL, you need to implement an instance of
    ``Netgen\BlockManager\Item\ValueUrlBuilderInterface`` for your item.

To generate the URL, you can simply call the function with the item in question:

.. code-block:: html+jinja

    <a href="{{ ngbm_item_path(item) }}">{{ item.name }}</a>

If you do not have access to the item object, you can generate the URL with ID
and value type of the item:

.. code-block:: html+jinja

    <a href="{{ ngbm_item_path(42, 'ezlocation') }}">{{ 'My item' }}</a>

Alternatively, you can use a special format used by Netgen Layouts in the form
of an URI scheme ``value_type://value_id``:

.. code-block:: html+jinja

    <a href="{{ ngbm_item_path('ezlocation://42') }}">{{ 'My item' }}</a>
