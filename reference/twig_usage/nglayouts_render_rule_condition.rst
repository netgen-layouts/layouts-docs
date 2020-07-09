``nglayouts_render_rule_condition``
===================================

This function is used to render a rule condition:

.. code-block:: twig

    {{ nglayouts_render_rule_condition(condition) }}

This will render the provided condition in the view context of the template from
which you called the function or in the ``default`` view context if the calling
template is not rendered by the Netgen Layouts view layer.

You can transfer a list of custom parameters to the function, which will be
injected as variables into the condition template:

.. code-block:: twig

    {# my.html.twig #}

    {{ nglayouts_render_rule_condition(condition, {'the_answer': 42}) }}

    {# condition.html.twig #}

    {{ the_answer }}

Finally, you can render the condition with a view context different from the
current one:

.. code-block:: twig

    {{ nglayouts_render_rule_condition(condition, {}, 'my_context') }}
