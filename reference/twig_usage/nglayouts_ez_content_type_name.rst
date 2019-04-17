``nglayouts_ez_content_type_name``
==================================

This function is used to retrieve the name of a content type from eZ Platform by
its identifier.

.. note::

    This function exists because eZ Platform does not provide a way to retrieve
    the content type name from its identifier. The function is only available if
    Netgen Layouts is installed on top of eZ Platform.

To retrieve the content type name, call the function with the content type
identifier:

.. code-block:: jinja

    {{ nglayouts_ez_content_type_name('article') }}

If the content type with provided identifier does not exist, an empty string
will be returned.
