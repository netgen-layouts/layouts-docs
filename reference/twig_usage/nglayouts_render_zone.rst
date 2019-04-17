``nglayouts_render_zone``
=========================

This tag is used to render an entire layout zone.

To render a zone, you can simply call the tag with the zone in question:

.. code-block:: jinja

    {% nglayouts_render_zone 'left' %}

This will render the zone with the ``left`` identifier from currently rendered
layout and in the ``default`` view context.

You can also render the zone by providing the zone entity directly, taken from
the layout object:

.. code-block:: jinja

    {% nglayouts_render_zone nglayouts.layout.zone('left') %}

You can also render the zone with your own custom view context:

.. code-block:: jinja

    {% nglayouts_render_zone 'left' context='my_context' %}

.. warning::

    When rendering a zone with a custom view context, all blocks and block items
    which do not specify custom view context will be rendered with the view
    context you provided. You need to make sure all your blocks and block items
    have the templates for specified view context, otherwise, you will get an
    exception while rendering the page.
