``nglayouts_render_placeholder``
================================

This function is used to render a placeholder of a container block.

To render the placeholder, you need to provide the block from which you want to
render the placeholder, as well as placeholder identifier:

.. code-block:: jinja

    {{ nglayouts_render_placeholder(block, 'left') }}

This will render the provided placeholder in the view context of the template
from which you called the function or in the ``default`` view context if the
calling template is not rendered by the Netgen Layouts view layer.

You can transfer a list of custom parameters to the function, which will be
injected as variables into the placeholder template:

.. code-block:: jinja

    {# block.html.twig #}

    {{ nglayouts_render_placeholder(block, 'left', {'the_answer': 42}) }}

    {# placeholder.html.twig #}

    {{ the_answer }}

Finally, you can render the placeholder with a view context different from the
current one:

.. code-block:: jinja

    {{ nglayouts_render_placeholder(block, 'left', {}, 'my_context') }}
