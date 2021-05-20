``nglayouts_render_role``
=========================

.. note::

    Available only in Enterprise Edition

This function is used to render a role:

.. code-block:: twig

    {{ nglayouts_render_role(role) }}

This will render the provided role in the view context of the template from
which you called the function or in the ``default`` view context if the calling
template is not rendered by the Netgen Layouts view layer.

You can transfer a list of custom parameters to the function, which will be
injected as variables into the role template:

.. code-block:: twig

    {# my.html.twig #}

    {{ nglayouts_render_role(role, {'the_answer': 42}) }}

    {# role.html.twig #}

    {{ the_answer }}

Finally, you can render the role with a view context different from the current
one:

.. code-block:: twig

    {{ nglayouts_render_role(role, {}, 'my_context') }}
