``nglayouts_render_item``
=========================

This function is used to render a block item.

In addition to the item you're rendering, you need to provide the item view type
with which you wish to render the item:

.. code-block:: jinja

    {{ nglayouts_render_item(item, 'overlay') }}

This will render the provided item in the view context of the template from
which you called the function or in the ``default`` view context if the calling
template is not rendered by the Netgen Layouts view layer.

You can transfer a list of custom parameters to the function, which will be
injected as variables into the item template:

.. code-block:: jinja

    {# block.html.twig #}

    {{ nglayouts_render_item(item, 'overlay', {'the_answer': 42}) }}

    {# item.html.twig #}

    {{ the_answer }}

.. tip::

    Normally, parameters provided here are not transferred to content views in
    eZ Platform, but only to the item template, which in case of eZ Platform is
    only a proxy to eZ content view layer. However, you can use a special
    parameter called ``ezparams`` whose contents will be transferred. For
    example:

    .. code-block:: jinja

        {# block.html.twig #}

        {{ nglayouts_render_item(item, 'overlay', {'ezparams': {'the_answer': 42}}) }}

        {# overlay.html.twig from eZ Platform #}

        {{ the_answer }}

Finally, you can render the item with a view context different from the current
one:

.. code-block:: jinja

    {{ nglayouts_render_item(item, 'overlay', {}, 'my_context') }}
