``layout_view``
===============

This view is used to render entities implementing
``Netgen\BlockManager\API\Values\Layout\Layout`` interface.

Available variables
-------------------

+---------------+------------------------------------+
| Variable name | Description                        |
+===============+====================================+
| ``layout``    | The layout which is being rendered |
+---------------+------------------------------------+

.. warning::

    Frontend templates for layouts (``default`` context) are an exception and
    are not rendered through the Netgen Layouts view layer. Instead, they are
    rendered by extending from a special ``ngbm.layoutTemplate`` variable,
    available in your full view templates. Because of that, in frontend layout
    templates, ``layout`` variable is not available. Instead, the rendered
    layout is accessed by using ``ngbm.layout`` variable.

.. warning::

    This view reuses backend templates for layout types to render the layouts
    themselves. For this reason, those templates sometimes receive the
    ``layout`` variable, and sometimes ``layout_type`` variable, based on what
    is being rendered. Your own templates need to be aware of this and act
    accordingly, i.e. check for existence of both variables prior using them.
