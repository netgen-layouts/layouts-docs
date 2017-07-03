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
