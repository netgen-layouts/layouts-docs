``nglayouts_render_result``
===========================

This function is used to render a single result after running a collection.

In addition to the result you're rendering, you need to provide either the
fallback view type (used if no view type overrides on slot or item level are
set) or the override view type (used to override the view type of the result
unconditionally):

.. code-block:: jinja

    {{ nglayouts_render_result(result, null, 'fallback_type') }}

This will render the provided result with the view type set either on item
or slot level. If none of those view types are set, ``fallback_type`` will
be used to render the result.

.. code-block:: jinja

    {{ nglayouts_render_result(result, 'override_type') }}

This will render the provided result with the ``override_type`` view type,
ignoring the view type set on item or slot level.

You can transfer a list of custom parameters to the function, which will be
injected as variables into the result template:

.. code-block:: jinja

    {# block.html.twig #}

    {{ nglayouts_render_result(result, null, 'overlay', {'the_answer': 42}) }}

    {# item.html.twig #}

    {{ the_answer }}

.. tip::

    Normally, parameters provided here are not transferred to content views in
    eZ Platform, but only to the item template, which in case of eZ Platform is
    only a proxy to eZ content view layer. However, you can use a special
    parameter called ``ezparams`` whose contents will be transferred. For
    example:

    .. code-block:: jinja

        {# block.html.twig #}

        {{ nglayouts_render_result(result, null, 'overlay', {'ezparams': {'the_answer': 42}}) }}

        {# overlay.html.twig from eZ Platform #}

        {{ the_answer }}

Finally, you can render the result with a view context different from the current
one:

.. code-block:: jinja

    {{ nglayouts_render_result(result, null, 'overlay', {}, 'my_context') }}
