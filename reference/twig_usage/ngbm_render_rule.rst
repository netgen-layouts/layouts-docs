``ngbm_render_rule``
====================

This function is used to render a rule:

.. code-block:: jinja

    {{ ngbm_render_rule(rule) }}

This will render the provided rule in the view context of the template from
which you called the function or in the ``default`` view context if the calling
template is not rendered by the Netgen Layouts view layer.

You can transfer a list of custom parameters to the function, which will be
injected as variables into the rule template:

.. code-block:: jinja

    {# my.html.twig #}

    {{ ngbm_render_rule(rule, {'the_answer': 42}) }}

    {# rule.html.twig #}

    {{ the_answer }}

Finally, you can render the rule with a view context different from the current
one:

.. code-block:: jinja

    {{ ngbm_render_rule(rule, {}, 'my_context') }}
