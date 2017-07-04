``ngbm_render_zone``
====================

This tag is used to render an entire layout zone. Since zones do not have their
own template, this tag simply renders all blocks one after another.

.. note::

    Examples below show usage as if the tag is used in frontend layout templates
    which load the zone from ``ngbm.layout`` variable available in those
    templates. This does not mean you can't transfer an instance of
    ``Netgen\BlockManager\API\Values\Layout\Zone`` object manually.

To render a zone, you can simply call the tag with the zone in question:

.. code-block:: jinja

    {% ngbm_render_zone ngbm.layout.zone('left') %}

This will render the provided zone in the ``default`` view context.

You can also render the zone with your own custom view context:

.. code-block:: jinja

    {% ngbm_render_zone ngbm.layout.zone('left') context='my_context' %}

.. warning::

    When rendering a zone with a custom view context, all blocks and block items
    which do not specify custom view context will be rendered with the view
    context you provided. You need to make sure all your blocks and block items
    have the templates for specified view context, otherwise, you will get an
    exception while rendering the page.
