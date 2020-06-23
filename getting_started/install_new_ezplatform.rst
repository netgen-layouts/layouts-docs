Install on a new eZ Platform project
====================================

Netgen provides an uptodate installation of eZ Platform with Netgen Layouts
pre-installed. The installation is based on a `clean eZ Platform install`__,
ready to be used as a base for your new project.

This installation can later be used to upgrade to future versions of eZ Platform
by following official eZ Systems upgrade instructions.

Create a database
-----------------

Create a database for your project with:

.. code-block:: mysql

    CREATE DATABASE my_project CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_520_ci;

Use Composer
------------

Install `Composer`__ and execute the following from a directory of your choice
and specify the database connection info when asked:

.. code-block:: shell

    $ composer create-project netgen/layouts-ezplatform-site my_project
    $ cd my_project

Install the database
--------------------

Run the following commands from the project root to install eZ Platform database
together with Netgen Layouts database tables:

.. code-block:: shell

    $ php bin/console ezplatform:install clean

    # If you use Doctrine Migrations 3
    $ php bin/console doctrine:migrations:migrate --configuration=vendor/netgen/layouts-core/migrations/doctrine.yaml

    # If you use Doctrine Migrations 2
    $ php bin/console doctrine:migrations:migrate --configuration=vendor/netgen/layouts-core/migrations/doctrine2.yaml

Rendering block items
---------------------

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

Start the app
-------------

You can use the web server included with `Symfony CLI`__ to serve the app:

.. code-block:: shell

    $ symfony server:ca:install # For HTTPS support, only needs to be ran once
    $ symfony server:start

After that, open ``https://127.0.0.1:8000`` in your browser to run the app.

.. include:: what_next.rst.inc

.. _`eZ Platform`: https://github.com/ezsystems/ezplatform
.. _`Composer`: https://getcomposer.org/doc/00-intro.md
.. _`Symfony CLI`: https://symfony.com/download

__ `eZ Platform`_
__ `Composer`_
__ `Symfony CLI`_
