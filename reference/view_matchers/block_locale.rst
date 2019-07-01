``block\locale``
================

Matches on locale of the rendered block. Used in ``block_view`` view.

.. tip::

    This matcher is usually used with ``block\definition`` matcher to specify
    for which exactly block type will the template be used.

Example
-------

.. code-block:: yaml

    netgen_layouts:
        view:
            block_view:
                default:
                    title\hr_HR:
                        template: '@App/block/title/hr_HR.html.twig'
                        match:
                            block\definition: title
                            block\locale: hr_HR
