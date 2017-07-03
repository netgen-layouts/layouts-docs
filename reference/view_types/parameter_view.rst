``block_view``
==============

This view is used to render entities implementing
``Netgen\BlockManager\Parameters\ParameterValue`` interface.

Available variables
-------------------

+---------------+---------------------------------------+
| Variable name | Description                           |
+===============+=======================================+
| ``parameter`` | The parameter which is being rendered |
+---------------+---------------------------------------+

.. note::

    While rendering other views will throw an exception if there is no template
    match in requested view context, this view will fallback to the ``default``
    view context. This is due to the fact that in most of the cases, rendering
    a block parameter will look exactly the same in the backend and in the
    frontend.

    This makes it possible to only specify one match configuration rule (in the
    ``default`` context) and one template to render the parameter in any view
    context.
