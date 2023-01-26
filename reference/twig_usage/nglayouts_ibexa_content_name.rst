``nglayouts_ibexa_content_name``
================================

This function is used to retrieve the name of a content from Ibexa CMS by its
ID.

.. note::

    This function exists because Ibexa CMS does not provide a way to retrieve
    the content name from its ID. The function is only available if
    Netgen Layouts is installed on top of Ibexa CMS.

To retrieve the content name, call the function with the content ID:

.. code-block:: twig

    {{ nglayouts_ibexa_content_name(42) }}

If the content with provided ID does not exist, an empty string will be
returned.
