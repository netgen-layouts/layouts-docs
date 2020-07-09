``nglayouts_render_rule_target``
================================

This function is used to render a rule target:

.. code-block:: twig

    {{ nglayouts_render_rule_target(target) }}

This will render the provided target in the view context of the template from
which you called the function or in the ``default`` view context if the calling
template is not rendered by the Netgen Layouts view layer.

You can transfer a list of custom parameters to the function, which will be
injected as variables into the target template:

.. code-block:: twig

    {# my.html.twig #}

    {{ nglayouts_render_rule_target(target, {'the_answer': 42}) }}

    {# target.html.twig #}

    {{ the_answer }}

Finally, you can render the target with a view context different from the
current one:

.. code-block:: twig

    {{ nglayouts_render_rule_target(target, {}, 'my_context') }}
