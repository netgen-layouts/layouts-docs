``ngbm_render_item``
====================

This function is used to render a block item.

In addition to the item you're rendering, you need to provide the item view type
with which you wish to render the item:

.. code-block:: jinja

    {{ ngbm_render_item(item, 'overlay') }}

This will render the provided item in the view context of the template from
which you called the function or in the ``default`` view context if the calling
template is not rendered by the Netgen Layouts view layer.

You can transfer a list of custom parameters to the function, which will be
injected as variables into the item template:

.. code-block:: jinja

    {# block.html.twig #}

    {{ ngbm_render_item(item, 'overlay', {'the_answer': 42}) }}

    {# item.html.twig #}

    {{ the_answer }}

Finally, you can render the item with a view context different from the current
one:

.. code-block:: jinja

    {{ ngbm_render_item(item, 'overlay', {}, 'my_context') }}
