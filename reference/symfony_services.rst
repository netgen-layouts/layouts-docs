Symfony services
================

Netgen Layouts provides a number of Symfony services that you can use to work
in PHP code with layouts, blocks, collections, queries and so on.

API services
------------

The following services are the entry point and central place for all operations
with any entity available in Netgen Layouts. It is used by Netgen Layouts itself
to render the layouts in the frontend, in REST API used in layout editing app
and in the admin interface. Basically, they provide a CRUD interface to work
with layouts, blocks, collections and layout resolver rules.

.. rst-class:: responsive

+------------------------------------------------+-------------------------------------------+
| Service name                                   | Description                               |
+================================================+===========================================+
| ``netgen_layouts.api.service.layout``          | CRUD operations for layouts               |
+------------------------------------------------+-------------------------------------------+
| ``netgen_layouts.api.service.block``           | CRUD operations for blocks                |
+------------------------------------------------+-------------------------------------------+
| ``netgen_layouts.api.service.collection``      | CRUD operations for collections           |
+------------------------------------------------+-------------------------------------------+
| ``netgen_layouts.api.service.layout_resolver`` | CRUD operations for layout resolver rules |
+------------------------------------------------+-------------------------------------------+

View API
--------

The following services can be used to manually render any entity in
Netgen Layouts.

.. rst-class:: responsive

+---------------------------------------+---------------------------------+
| Service name                          | Description                     |
+=======================================+=================================+
| ``netgen_layouts.view.view_builder``  | Used to manually build the view |
|                                       | for the entity.                 |
+---------------------------------------+---------------------------------+
| ``netgen_layouts.view.view_renderer`` | Used to manually render the     |
|                                       | entity view once it has been    |
|                                       | built.                          |
+---------------------------------------+---------------------------------+
| ``netgen_layouts.view.renderer``      | Shortcut service that uses view |
|                                       | builder and view renderer       |
|                                       | services to render the provided |
|                                       | entity.                         |
+---------------------------------------+---------------------------------+

Block items
-----------

The following services can be used to manually load and build block items to
inject them into blocks and link to them.

.. rst-class:: responsive

+---------------------------------------+---------------------------------+
| Service name                          | Description                     |
+=======================================+=================================+
| ``netgen_layouts.item.item_builder``  | Used to manually build the item |
|                                       | from the provided entity.       |
+---------------------------------------+---------------------------------+
| ``netgen_layouts.item.item_loader``   | Used to manually load the item  |
|                                       | from provided value type and    |
|                                       | value.                          |
+---------------------------------------+---------------------------------+
| ``netgen_layouts.item.url_generator`` | Used to generate the URL to the |
|                                       | item.                           |
+---------------------------------------+---------------------------------+

Registries
----------

A number of registries is provided so you can access the list of all available
block definitions, query types and so on.

.. rst-class:: responsive

+------------------------------------------------------------+------------------------------------------------+
| Service name                                               | Description                                    |
+============================================================+================================================+
| ``netgen_layouts.block.registry.block_definition``         | Used to access all available block definitions |
+------------------------------------------------------------+------------------------------------------------+
| ``netgen_layouts.block.registry.block_type``               | Used to access all available block types       |
+------------------------------------------------------------+------------------------------------------------+
| ``netgen_layouts.block.registry.block_type_group``         | Used to access all available block type groups |
+------------------------------------------------------------+------------------------------------------------+
| ``netgen_layouts.collection.registry.query_type``          | Used to access all available query types       |
+------------------------------------------------------------+------------------------------------------------+
| ``netgen_layouts.parameters.registry.parameter_type``      | Used to access all available parameter types   |
+------------------------------------------------------------+------------------------------------------------+
| ``netgen_layouts.item.registry.value_type``                | Used to access all available value types       |
+------------------------------------------------------------+------------------------------------------------+
| ``netgen_layouts.layout.registry.layout_type``             | Used to access all available layout types      |
+------------------------------------------------------------+------------------------------------------------+
| ``netgen_layouts.layout.resolver.registry.target_type``    | Used to access all available target types      |
+------------------------------------------------------------+------------------------------------------------+
| ``netgen_layouts.layout.resolver.registry.condition_type`` | Used to access all available condition types   |
+------------------------------------------------------------+------------------------------------------------+

Shortcut services
-----------------

Some of the entities that can be accessed through one of the above registries
can also be accessed directly by using a unique service name. All of those
service names are in the form of ``<prefix>.<identifier>``. Prefix is the same
for all entities that implement the same interface, while identifier identifies
a single entity.

The following table lists all available service prefixes:

.. rst-class:: responsive

+------------------+--------------------------------------------+
| Entity type      | Service prefix                             |
+==================+============================================+
| Block definition | ``netgen_layouts.block.block_definition.`` |
+------------------+--------------------------------------------+
| Block type       | ``netgen_layouts.block.block_type.``       |
+------------------+--------------------------------------------+
| Block type group | ``netgen_layouts.block.block_type_group.`` |
+------------------+--------------------------------------------+
| Query type       | ``netgen_layouts.collection.query_type.``  |
+------------------+--------------------------------------------+
| Value type       | ``netgen_layouts.item.value_type.``        |
+------------------+--------------------------------------------+
| Layout type      | ``netgen_layouts.layout.layout_type.``     |
+------------------+--------------------------------------------+

As an example, if you wish to load the service for ``title`` block definition,
you would use a service name ``netgen_layouts.block.block_definition.title``.

Other services
--------------

The following lists various other useful services which can be used by client
code:

.. rst-class:: responsive

+----------------------------------------------+-----------------------------------------+
| Service name                                 | Description                             |
+==============================================+=========================================+
| ``netgen_layouts.http_cache.invalidator``    | Provides APIs for invalidating layout   |
|                                              | and block HTTP caches                   |
+----------------------------------------------+-----------------------------------------+
| ``netgen_layouts.configuration``             | Provides a way to access Netgen Layouts |
|                                              | configuration values                    |
+----------------------------------------------+-----------------------------------------+
| ``netgen_layouts.collection.result_builder`` | Generates the collection result (items) |
|                                              | from a provided collection              |
+----------------------------------------------+-----------------------------------------+
| ``netgen_layouts.layout.resolver``           | Exposes APIs to manually run the layout |
|                                              | resolving process on a request          |
+----------------------------------------------+-----------------------------------------+

eZ Platform specific services
-----------------------------

The following lists various useful services available when Netgen Layouts is
installed on top of eZ Platform.

.. rst-class:: responsive

+------------------------------------------------+-----------------------------------------+
| Service name                                   | Description                             |
+================================================+=========================================+
| ``netgen_layouts.ezplatform.content_provider`` | Used to extract current content and     |
|                                                | location for use by contextual blocks   |
|                                                | and queries                             |
+------------------------------------------------+-----------------------------------------+
