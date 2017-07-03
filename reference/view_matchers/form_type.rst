``form\type``
=============

Matches on type of the Symfony form which is rendered. Used in ``form_view``
view.

.. tip::

    This matcher is usually used with other ``form\*`` matchers if you wish, for
    example, to separate templates for rendering block create and block edit
    forms.

Example
-------

.. code-block:: yaml

    netgen_block_manager:
        view:
            form_view:
                default:
                    layout\edit:
                        template: '@App/layout/edit.html.twig'
                        match:
                            form\type: Netgen\BlockManager\Layout\Form\EditType
