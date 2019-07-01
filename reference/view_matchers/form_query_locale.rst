``form\query\locale``
=====================

Matches on locale of a query which is edited through the Symfony form. Used in
``form_view`` view.

Example
-------

.. code-block:: yaml

    netgen_layouts:
        view:
            form_view:
                default:
                    query\my_query\edit\hr_HR:
                        template: '@App/query/my_query/edit/hr_HR.html.twig'
                        match:
                            form\type: Netgen\Layouts\Collection\Form\QueryEditType
                            form\query\type: my_query
                            form\query\locale: hr_HR
