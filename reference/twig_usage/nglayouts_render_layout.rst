``nglayouts_render_layout``
===========================

.. warning::

    Since all frontend templates for layouts use ``nglayouts.layout`` variable
    to access the layout instead of the default ``layout`` variable, this
    function cannot be used by default to render the layouts in the frontend
    (i.e. in ``default`` view context). Instead, it is available for usage in
    Netgen Layouts administration interface and for rendering the layout with
    custom view contexts.

This function is used to render a layout:

.. code-block:: jinja

    {{ nglayouts_render_layout(layout) }}

This will render the provided layout in the view context of the template from
which you called the function or in the ``default`` view context if the calling
template is not rendered by the Netgen Layouts view layer.

You can transfer a list of custom parameters to the function, which will be
injected as variables into the layout template:

.. code-block:: jinja

    {# my.html.twig #}

    {{ nglayouts_render_layout(layout, {'the_answer': 42}) }}

    {# layout.html.twig #}

    {{ the_answer }}

Finally, you can render the layout with a view context different from the
current one:

.. code-block:: jinja

    {{ nglayouts_render_layout(layout, {}, 'my_context') }}
