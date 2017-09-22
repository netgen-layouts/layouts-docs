``form\block\locale``
=====================

Matches on block locale of a block which is edited through the Symfony form.
Used in ``form_view`` view.

Example
-------

.. code-block:: yaml

    netgen_block_manager:
        view:
            form_view:
                default:
                    block\title\edit\hr_HR:
                        template: '@App/block/title/edit/hr_HR.html.twig'
                        match:
                            form\type: Netgen\BlockManager\Block\Form\FullEditType
                            form\block\definition: title
                            form\block\locale: hr_HR
