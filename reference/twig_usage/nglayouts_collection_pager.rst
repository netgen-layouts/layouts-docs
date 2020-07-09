``nglayouts_collection_pager``
==============================

This function is used to render a pager for a collection:

.. code-block:: twig

    {{ nglayouts_collection_pager(pager, block, 'default') }}

This will render the pager for provided collection (specified by the block and
collection identifier (``default``)). ``pager`` variable is an instance of
``Pagerfanta\Pagerfanta`` class, provided to block view templates automatically
by Netgen Layouts.

The default template is ``@NetgenLayouts/collection/default_pager.html.twig``
and you can override it by providing a fourth parameter which is a hash of
configuration options:

.. code-block:: twig

    {{ nglayouts_collection_pager(pager, block, 'default', {template: '@App/my_pager.html.twig'}) }}
