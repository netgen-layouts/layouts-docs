How to quickly render a layout on a single URL
==============================================

Usually, if you wish to render a page with a layout in your CMS, you would need
to create a controller which renders a template which then extends from
``nglayouts.layoutTemplate`` variable for layout to be resolved.

Even worse, you would need to create a page (article, blog post, landing page or
something else) in the CMS just to make the URL available in the system.

Creating a Symfony controller and a page in your CMS just to render an URL with
a layout can be an overkill, and in those cases, you can use a controller built
into Symfony to quickly render a layout on a single URL.

To render the page, you need to create a Symfony route which uses a built in
Symfony controller to render the template available in Netgen Layouts:

.. code-block:: yaml

    my_cool_page:
        path: /my/cool/page
        controller: 'Symfony\Bundle\FrameworkBundle\Controller\TemplateController::templateAction'
        defaults:
            template: '@NetgenLayouts/empty_page.html.twig'

Finally, you need to add a mapping in Netgen Layouts administration to link one
of the layouts to the route you created. Once this is done, you can access the
URL you provided in your route config and see the layout rendered in all its
glory.
