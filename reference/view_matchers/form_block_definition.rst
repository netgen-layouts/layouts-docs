``form\block\definition``
=========================

Matches on block definition of a block which is edited through the Symfony form.
Used in ``form_view`` view.

Example
-------

.. code-block:: yaml

    netgen_block_manager:
        view:
            form_view:
                default:
                    block\title\edit:
                        template: '@App/block/title/edit.html.twig'
                        match:
                            form\type: Netgen\Layouts\Block\Form\FullEditType
                            form\block\definition: title
