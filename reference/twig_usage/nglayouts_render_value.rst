``nglayouts_render_value``
==========================

This function is used to render any value supported by Netgen Layouts view
layer. All other rendering extensions reuse this function in one form or
another.

To render the value (for example, a block), just transfer it to the function:

.. code-block:: jinja

    {{ nglayouts_render_value(block) }}

This will render the provided value in the view context of the template from
which you called the function or in the ``default`` view context if the calling
template is not rendered by the Netgen Layouts view layer.

You can transfer a list of custom parameters to the function, which will be
injected as variables into the template:

.. code-block:: jinja

    {# my.html.twig #}

    {{ nglayouts_render_value(block, {'the_answer': 42}) }}

    {# block.html.twig #}

    {{ the_answer }}

Finally, you can render the value with a view context different from the current
one:

.. code-block:: jinja

    {{ nglayouts_render_value(block, {}, 'my_context') }}
