``layout_type_view``
====================

Sometimes, in Block Manager app, it is needed to render an empty template for a
layout type, for example in the interface for changing the layout type of a
layout. This view is used to render layout types. It renders objects of
``Netgen\BlockManager\Layout\Type\LayoutType`` type.

Available variables
-------------------

+-----------------+-----------------------------------------+
| Variable name   | Description                             |
+=================+=========================================+
| ``layout_type`` | The layout type which is being rendered |
+-----------------+-----------------------------------------+

.. warning::

    This view reuses backend templates for layouts to render the types
    themselves. For this reason, those templates sometimes receive the
    ``layout`` variable, and sometimes ``layout_type`` variable, based on what
    is being rendered. Your own templates need to be aware of this and act
    accordingly, i.e. check for existence of both variables prior using them.
