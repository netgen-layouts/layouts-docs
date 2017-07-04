``ngbm_ezcontent_name``
=======================

This function is used to retrieve the name of a content from eZ Platform by its
ID.

.. note::

    This function exists because eZ Platform does not provide a way to retrieve
    the content name from its ID. The function is only available if
    Netgen Layouts is installed on top of eZ Platform.

To retrieve the content name, call the function with the content ID:

.. code-block:: jinja

    {{ ngbm_ezcontent_name(42) }}

If the content with provided ID does not exist, an empty string will be
returned.
