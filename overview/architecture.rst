Architecture
============

Netgen Layouts is a Symfony based application. It can be installed on top of
existing Symfony based apps like eZ Platform, Sylius or any other Symfony
full-stack application (based on website skeleton). It can be a standalone
Symfony app querying the Backend data via REST or SOAP. Making new integrations
is easy for any Symfony/PHP developer.

Layouts do not reinvent the wheel and reuse/inherit Symfony features like
routing and Twig. It should be noted that Layouts don’t have anything to do with
frontend assets, they can be used in any Symfony-friendly way.

Layouts only renders Twig templates and these templates can be easily
overridden, even have different variations/themes.

.. image:: /_images/architecture.svg

Extending
---------

Currently, there are dozen extension points, from custom block view types (Twig
templates) to custom query types (Symfony services), all created to implement
project-specific features. You can:

* extend built-in blocks with Block Plugins and Block Views
* create custom blocks and containers
* add new Layout Types
* create custom query types
* create custom targets and conditions
* `extend Content Browser </projects/cb/en/latest/cookbook/custom_backend.html>`_

How Layouts are connected to a specific page or URL?
----------------------------------------------------

When a Symfony controller renders a Twig template, Layouts are being invoked.
Instead of inheriting the master Twig template, a special Layouts Twig module is
inherited, trying to resolve which layouts should be rendered based on Layout
mappings, a priority list of targeted URLs and conditions. First layout that
matches the target and additional conditions will be rendered with all its
blocks.

What happened to the original Twig you might ask?

It is still available and you can include the output in the layout by using
special Blocks that render Twig code. These Blocks have an identifier which is
used to find the same block identifier in the original Twig template and render
that output as a part of the layout. This is the most powerful and unique
feature of Netgen Layouts.

.. image:: /_images/layouts_request.svg
