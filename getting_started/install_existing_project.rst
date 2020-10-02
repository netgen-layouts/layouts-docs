Install on an existing project
==============================

To install Netgen Layouts, you need to have an existing Symfony full stack
installation. For example, Netgen Layouts can be installed on eZ Platform,
Sylius or Symfony Demo app or Symfony Website Skeleton.

Use Composer
------------

Execute the following from your installation root:

.. code-block:: shell

    $ composer require netgen/layouts-standard

.. note::

    If you're installing Netgen Layouts on eZ Platform, execute the following
    instead:

    .. code-block:: shell

        $ composer require netgen/layouts-standard netgen/layouts-ezplatform

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

    If you're installing Netgen Layouts on eZ Platform, activate the following
    bundles too after all of the bundles listed above:

    .. code-block:: php

        new Netgen\Bundle\ContentBrowserEzPlatformBundle\NetgenContentBrowserEzPlatformBundle(),
        new Netgen\Bundle\LayoutsEzPlatformBundle\NetgenLayoutsEzPlatformBundle(),

    To be able to manage user policies in legacy administration interface of
    eZ Platform, you need to activate the provided ``nglayouts`` legacy
    extension. If you're using eZ Platform Admin UI, policy management is
    available automatically.

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

Configuration
-------------

Starting from version 1.12 of eZ Platform, `there is a configuration`__ that
caches 404 pages with a low TTL to increase performance. This cache interferes
with Netgen Layouts REST API endpoints which return 404 responses in their
normal operation workflow.

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

    If you're installing Netgen Layouts on eZ Platform, you also need to add
    the following routes (added in 1.1.4 release of
    ``netgen/layouts-ezplatform`` package):

    .. code-block:: yaml

        netgen_layouts_ezplatform:
            resource: "@NetgenLayoutsEzPlatformBundle/Resources/config/routing.yaml"

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

    {% include '@NetgenLayoutsStandard/page_head.html.twig' with { full: true } %}

You can also include javascripts and stylesheets separately, in case you wish
to load stylesheets from the page head and javascripts from the end of the body:

.. code-block:: twig

    {% include '@NetgenLayoutsStandard/stylesheets.html.twig' with { full: true } %}
    {% include '@NetgenLayoutsStandard/javascripts.html.twig' with { full: true } %}

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

    If you're installing Netgen Layouts on eZ Platform, your main pagelayout is
    taken from existing eZ Platform configuration, so you can skip this step.

Rendering block items
---------------------

.. note::

    This section is relevant only if installing on an existing eZ Platform
    project.

To render block items, Netgen Layouts by default uses an eZ Platform view type
called ``standard``. For every content object that you wish to include in a
Netgen Layouts block, you need to define the ``standard`` view type, e.g.:

.. code-block:: yaml

    ezpublish:
        system:
            site_group:
                content_view:
                    standard:
                        article:
                            template: "@ezdesign/content/standard/article.html.twig"
                            match:
                                Identifier\ContentType: article

.. include:: what_next.rst.inc

.. _`eZ Platform pull request #213`: https://github.com/ezsystems/ezplatform/pull/213/files#diff-bf0e70bcef1a5d5b2f87289220a51108

__ `eZ Platform pull request #213`_
