``ngbm_collection_page_url``
============================

This function returns the base URL for rendering a collection page via AJAX:

.. code-block:: jinja

    {% set page = ngbm_collection_page_url(pager, block, 'default') %}

This will return the base URL for provided collection (specified by the block
and collection identifier (``default``)). ``pager`` variable is an instance of
``Pagerfanta\Pagerfanta`` class, provided to block view templates automatically
by Netgen Layouts.

You can also provide a page number as the fourth parameter, to render the URL
for that page:

.. code-block:: jinja

    {% set page = ngbm_collection_page_url(pager, block, 'default', 3) %}

This however will throw an exception if page you provide is out of range as
specified by ``pager.nbPages``.
