``nglayouts_ezlocation_path``
=============================

This function is used to retrieve the names of all parent locations for
eZ Platform location with provided ID.

.. note::

    This function exists because eZ Platform does not provide a way to retrieve
    the location name from its ID. The function is only available if
    Netgen Layouts is installed on top of eZ Platform.

To retrieve the names of parent locations, call the function with the location
ID:

.. code-block:: twig

    {% set names = nglayouts_ezlocation_path(42) %}

    {{ names|join(' / ') }}

This will return the array of parent names, starting from the top most parent.

If the location with provided ID does not exist, ``null`` will be returned.
