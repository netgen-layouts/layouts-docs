``ngbm_render_parameter``
=========================

This function is used to render a parameter:

.. code-block:: jinja

    {{ ngbm_render_parameter(parameter) }}

This will render the provided parameter in the view context of the template from
which you called the function or in the ``default`` view context if the calling
template is not rendered by the Netgen Layouts view layer.

You can transfer a list of custom parameters to the function, which will be
injected as variables into the parameter template:

.. code-block:: jinja

    {# block.html.twig #}

    {{ ngbm_render_parameter(parameter, {'the_answer': 42}) }}

    {# parameter.html.twig #}

    {{ the_answer }}

Finally, you can render the parameter with a view context different from the
current one:

.. code-block:: jinja

    {{ ngbm_render_parameter(parameter, {}, 'my_context') }}
