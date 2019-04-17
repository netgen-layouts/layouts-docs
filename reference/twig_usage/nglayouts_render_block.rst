``nglayouts_render_block``
==========================

This function is used to render a block:

.. code-block:: jinja

    {{ nglayouts_render_block(block) }}

This will render the provided block in the view context of the template from
which you called the function or in the ``default`` view context if the calling
template is not rendered by the Netgen Layouts view layer.

You can transfer a list of custom parameters to the function, which will be
injected as variables into the block template:

.. code-block:: jinja

    {# layout.html.twig #}

    {{ nglayouts_render_block(block, {'the_answer': 42}) }}

    {# block.html.twig #}

    {{ the_answer }}

Finally, you can render the block with a view context different from the current
one:

.. code-block:: jinja

    {{ nglayouts_render_block(block, {}, 'my_context') }}
