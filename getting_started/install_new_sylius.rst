Install on a new Sylius project
===============================

Netgen provides an uptodate installation of Sylius with Netgen Layouts
pre-installed. The installation is based on `Sylius Standard Edition`__, ready
to be used as a base for your new project.

This installation can later be used to upgrade to future versions of Sylius by
following official upgrade instructions.

Create a database
-----------------

Create a database for your project with:

.. code-block:: mysql

    CREATE DATABASE sylius_dev CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_520_ci;

Use Composer
------------

Install `Composer`__ and execute the following from a directory of your choice:

.. code-block:: shell

    $ composer create-project netgen/layouts-sylius-site my_project
    $ cd my_project

Create a ``.env.local`` file in the project root directory to specify database
connection details:

.. code-block:: shell

    DATABASE_URL=mysql://user:pass@127.0.0.1/sylius_%kernel.environment%

Finally, run the Sylius install wizard:

.. code-block:: shell

    $ php bin/console sylius:install
    $ yarn install
    $ yarn build

Import Netgen Layouts database tables
-------------------------------------

Run the following command from the project root to import Netgen Layouts
database tables:

.. code-block:: shell

    $ php bin/console doctrine:migrations:migrate --configuration=vendor/netgen/layouts-core/migrations/doctrine.yml

Start the app
-------------

You can use the web server included with `Symfony CLI`__ to serve the app:

.. code-block:: shell

    $ symfony server:start

After that, open ``http://127.0.0.1:8000`` in your browser to run the app.

.. include:: what_next.rst.inc

.. _`Sylius Standard Edition`: https://github.com/sylius/Sylius-Standard
.. _`Composer`: https://getcomposer.org/doc/00-intro.md
.. _`Symfony CLI`: https://symfony.com/download

__ `Sylius Standard Edition`_
__ `Composer`_
__ `Symfony CLI`_
