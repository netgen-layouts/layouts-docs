Install on a new Symfony project
================================

Netgen provides an uptodate installation of Symfony with Netgen Layouts
pre-installed. The installation is based on a `Symfony Website Skeleton`__,
ready to be used as a base for your new project.

.. note::

    Since this project does not come pre-installed with any kind of backend,
    you will only be able to use simple blocks like title, rich text, markdown
    and so on. You will need to provide your own
    :doc:`implementation of a backend </cookbook/custom_value_types>` to use
    grid and gallery blocks.

Create a database
-----------------

Create a database for your project with:

.. code-block:: mysql

    CREATE DATABASE my_project CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_520_ci;

Use Composer
------------

Install `Composer`__ and execute the following from a directory of your choice:

.. code-block:: shell

    $ composer create-project netgen/layouts-symfony-site my_project
    $ cd my_project

Create a ``.env.local`` file in the project root directory to specify database
connection details:

.. code-block:: shell

    DATABASE_URL=mysql://user:pass@127.0.0.1/my_project

Install the database
--------------------

Run the following command from the project root to install Netgen Layouts
database tables:

.. code-block:: shell

    # If you use Doctrine Migrations 3
    $ php bin/console doctrine:migrations:migrate --configuration=vendor/netgen/layouts-core/migrations/doctrine.yaml

    # If you use Doctrine Migrations 2
    $ php bin/console doctrine:migrations:migrate --configuration=vendor/netgen/layouts-core/migrations/doctrine2.yaml

Start the app
-------------

You can use the web server included with `Symfony CLI`__ to serve the app:

.. code-block:: shell

    $ symfony server:ca:install # For HTTPS support, only needs to be ran once
    $ symfony server:start

After that, open ``https://127.0.0.1:8000`` in your browser to run the app.
Netgen Layouts admin interface is available at
``https://127.0.0.1:8000/nglayouts/admin`` and you can use ``admin`` as the
username and password to access it.

.. include:: what_next.rst.inc

.. _`Symfony Website Skeleton`: https://github.com/symfony/website-skeleton
.. _`Composer`: https://getcomposer.org/doc/00-intro.md
.. _`Symfony CLI`: https://symfony.com/download

__ `Symfony Website Skeleton`_
__ `Composer`_
__ `Symfony CLI`_
