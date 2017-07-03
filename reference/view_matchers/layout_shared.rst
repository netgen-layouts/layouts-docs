``layout\shared``
=================

Matches on the shared flag of the rendered layout. Used in ``layout_view`` view.

.. note::

    While this matcher accepts an array as its value as all other matchers do,
    it will discard any other value in the array except the first one. This
    makes sense, since the only valid value for this matcher is a boolean.

Example
-------

.. code-block:: yaml

    netgen_block_manager:
        view:
            layout_view:
                default:
                    all_shared_layouts:
                        template: '@App/layout/shared_layout.html.twig'
                        match:
                            layout\shared: true
