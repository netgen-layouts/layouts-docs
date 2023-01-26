Install on an existing project
==============================

To install Netgen Layouts, you need to have an existing Symfony full stack
installation. For example, Netgen Layouts can be installed on Ibexa CMS,
Sylius or Symfony Demo app or Symfony Website Skeleton.

Use Composer
------------

Execute the following from your installation root:

.. code-block:: shell

    $ composer require netgen/layouts-standard

.. note::

    If you're installing Netgen Layouts on Ibexa CMS, execute the following
    instead:

    .. code-block:: shell

        $ composer require netgen/layouts-standard netgen/layouts-ibexa

Activate the bundles
--------------------

Add the following bundles to your kernel:

.. code-block:: php

    new Knp\Bundle\MenuBundle\KnpMenuBundle(),
    new FOS\HttpCacheBundle\FOSHttpCacheBundle(),
    new Sensio\Bundle\FrameworkExtraBundle\SensioFrameworkExtraBundle(),
    new Doctrine\Bundle\MigrationsBundle\DoctrineMigrationsBundle(),
    new Netgen\Bundle\ContentBrowserBundle\NetgenContentBrowserBundle(),
    new Netgen\Bundle\ContentBrowserUIBundle\NetgenContentBrowserUIBundle(),
    new Netgen\Bundle\LayoutsBundle\NetgenLayoutsBundle(),
    new Netgen\Bundle\LayoutsStandardBundle\NetgenLayoutsStandardBundle(),
    new Netgen\Bundle\LayoutsUIBundle\NetgenLayoutsUIBundle(),
    new Netgen\Bundle\LayoutsAdminBundle\NetgenLayoutsAdminBundle(),

.. note::

    If you're installing Netgen Layouts on Ibexa CMS, activate the following
    bundles too after all of the bundles listed above:

    .. code-block:: php

        new Netgen\Bundle\ContentBrowserIbexaBundle\NetgenContentBrowserIbexaBundle(),
        new Netgen\Bundle\LayoutsIbexaBundle\NetgenLayoutsIbexaBundle(),

Add the following bundle to your kernel **only for dev environment**:

.. code-block:: php

    new Netgen\Bundle\LayoutsDebugBundle\NetgenLayoutsDebugBundle(),

Import database tables
----------------------

Execute the following from your installation root to import Netgen Layouts database tables:

.. code-block:: shell

    # If you use Doctrine Migrations 3
    $ php bin/console doctrine:migrations:migrate --configuration=vendor/netgen/layouts-core/migrations/doctrine.yaml

    # If you use Doctrine Migrations 2
    $ php bin/console doctrine:migrations:migrate --configuration=vendor/netgen/layouts-core/migrations/doctrine2.yaml

.. include:: doctrine_schema_filter.rst.inc

Configuration
-------------

In Ibexa CMS, `there is a configuration`__ that caches 404 pages with a low TTL
to increase performance. This cache interferes with Netgen Layouts REST API
endpoints which return 404 responses in their normal operation workflow.

To disable cache on Netgen Layouts API endpoints, add the following options to
your configuration under the ``match`` keys of ``fos_http_cache`` configuration:

.. code-block:: yaml

    attributes:
        _route: "^(?!nglayouts_app_api_|ngcb_api_)"

Routing and assets
------------------

Add the following routes to your main routing config file:

.. code-block:: yaml

    netgen_layouts:
        resource: "@NetgenLayoutsBundle/Resources/config/routing.yaml"
        prefix: "%netgen_layouts.route_prefix%"

    netgen_content_browser:
        resource: "@NetgenContentBrowserBundle/Resources/config/routing.yaml"
        prefix: "%netgen_content_browser.route_prefix%"

.. note::

    If you're installing Netgen Layouts on Ibexa CMS, you also need to add
    the following routes:

    .. code-block:: yaml

        netgen_layouts_ibexa:
            resource: "@NetgenLayoutsIbexaBundle/Resources/config/routing.yaml"

Run the following from your installation root to symlink assets:

.. code-block:: shell

    $ php bin/console assets:install --symlink --relative

Adjusting your full views
-------------------------

All of your full views need to extend ``nglayouts.layoutTemplate`` variable (see
below for example). If layout was resolved, this variable will hold the name of
the template belonging to the resolved layout. In case when layout was not
resolved, it will hold the name of your main pagelayout template (the one your
full views previously extended). This makes it possible for your full view
templates to be fully generic, that is, not depend whether there is a resolved
layout or not:

.. code-block:: twig

    {% extends nglayouts.layoutTemplate %}

    {% block content %}
        {# My full view code #}
    {% endblock %}

Adjusting your base pagelayout template
---------------------------------------

To be able to render correctly list/grid blocks with paging and gallery blocks
with sliders, you need to add some assets to your page head. All needed assets
are conveniently provided by a single template you can include:

.. code-block:: twig

    {{ include('@NetgenLayoutsStandard/page_head.html.twig', { full: true }) }}

You can also include javascripts and stylesheets separately, in case you wish
to load stylesheets from the page head and javascripts from the end of the body:

.. code-block:: twig

    {{ include('@NetgenLayoutsStandard/stylesheets.html.twig', { full: true }) }}
    {{ include('@NetgenLayoutsStandard/javascripts.html.twig', { full: true }) }}

To actually display the resolved layout template in your page, you need to
modify your main pagelayout template to include a Twig block named layout which
wraps everything between your opening and closing ``<body>`` tag:

.. code-block:: twig

    <body>
        {% block layout %}
            {# Other Twig code #}

            {% block content %}{% endblock %}

            {# Other Twig code #}
        {% endblock %}
    </body>

There are two goals to achieve with the above Twig block:

- If no layout could be resolved for current page, your full view templates will
  just keep on working as before

- If layout is resolved, it will use the ``layout`` block, in which case
  ``content`` Twig block and other Twig code will not be used. You will of
  course need to make sure that in this case, all your layouts have a full view
  block in one of the zones which will display your ``content`` Twig block from
  full view templates

Configuring the pagelayout
--------------------------

As written before, Netgen Layouts replaces the pagelayout in your full views
with its dynamic variable called ``nglayouts.layoutTemplate``. It basically
injects itself between rendering of your full view and your pagelayout. Since
your full views do not extend from your main pagelayout any more, Netgen Layouts
needs to know what was your original full view to fallback to it. You can
configure your pagelayout in Netgen Layouts config like this:

.. code-block:: yaml

    netgen_layouts:
        pagelayout: '@App/pagelayout.html.twig'

.. note::

    If you're installing Netgen Layouts on Ibexa CMS, your main pagelayout is
    taken from existing Ibexa CMS configuration, so you can skip this step.

Rendering block items
---------------------

.. note::

    This section is relevant only if installing on an existing Ibexa CMS
    project.

To render block items, Netgen Layouts by default uses an Ibexa cMS view type
called ``standard``. For every content object that you wish to include in a
Netgen Layouts block, you need to define the ``standard`` view type, e.g.:

.. code-block:: yaml

    ibexa:
        system:
            site_group:
                content_view:
                    standard:
                        article:
                            template: "@ibexadesign/content/standard/article.html.twig"
                            match:
                                Identifier\ContentType: article

.. include:: what_next.rst.inc

.. _`Ibexa CMS pull request #213`: https://github.com/ezsystems/ezplatform/pull/213/files#diff-58ea7cc56899a1bcf3bdb6fc0d9cee247056d8e8ffc845a8ee8648f24ed7c3e8

__ `Ibexa CMS pull request #213`_
