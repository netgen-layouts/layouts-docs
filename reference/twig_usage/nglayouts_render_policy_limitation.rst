``nglayouts_render_policy_limitation``
======================================

.. note::

    Available only in Enterprise Edition

This function is used to render a policy limitation:

.. code-block:: twig

    {{ nglayouts_render_policy_limitation(limitation) }}

This will render the provided policy limitation in the view context of the
template from which you called the function or in the ``default`` view context
if the calling template is not rendered by the Netgen Layouts view layer.

You can transfer a list of custom parameters to the function, which will be
injected as variables into the policy limitation template:

.. code-block:: twig

    {# my.html.twig #}

    {{ nglayouts_render_policy_limitation(limitation, {'the_answer': 42}) }}

    {# limitation.html.twig #}

    {{ the_answer }}

Finally, you can render the policy limitation with a view context different from
the current one:

.. code-block:: twig

    {{ nglayouts_render_policy_limitation(limitation, {}, 'my_context') }}
