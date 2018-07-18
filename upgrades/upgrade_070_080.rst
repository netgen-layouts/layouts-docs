Upgrading from 0.7.0 to 0.8.0
=============================

Upgrade ``composer.json``
-------------------------

In your ``composer.json`` file, upgrade the version of ``netgen/block-manager``
package to ``~0.8.0`` and run the ``composer update`` command.

.. note::

    If you have Netgen Layouts installed on eZ Platform, the package name will
    be ``netgen/block-manager-ezpublish``.

.. note::

    Integrations into Netgen Admin UI and eZ Platform UI also have separate
    packages whose versions need to be bumped to ``~0.8.0``.

Activate required bundles
-------------------------

Version 0.8 requires FOS HTTP Cache Bundle to be activated, so if not already
present, activate ``FOS\HttpCacheBundle\FOSHttpCacheBundle`` in your kernel.

Database migration
------------------

Run the following command from the root of your installation to execute
migration to version 0.8 of Netgen Layouts:

.. code-block:: shell

    $ php bin/console doctrine:migrations:migrate --configuration=vendor/netgen/block-manager/migrations/doctrine.yml

Upgrading Netgen Content Browser
--------------------------------

Netgen Content Browser version 0.8 was also automatically installed. Be sure to
read `its upgrade instructions </projects/cb/en/latest/upgrades/upgrade_070_080.html>`_
too, to make sure you custom code keeps working.

Updates to Varnish VCL
----------------------

To enable caching and later cache clearing of block and layout HTTP caches, you
will need to use Varnish. To make the cache clearing work, you need to modify
your Varnish VCL and add the following rules somewhere in your ``vcl_recv``
function. If you're using eZ Platform and the VCL supplied by it, the best place
to put this is in ``ez_purge`` function (which is called from ``vcl_recv``),
right after ``if (req.http.X-Location-Id) { ... }`` block.

For Varnish 3:

.. code-block:: vcl

    if (req.http.X-Layout-Id) {
        ban( "obj.http.X-Layout-Id ~ " + req.http.X-Layout-Id);
        if (client.ip ~ debuggers) {
            set req.http.X-Debug = "Ban done for layout with ID " + req.http.X-Layout-Id;
        }
        error 200 "Banned";
    }

    if (req.http.X-Block-Id) {
        ban( "obj.http.X-Block-Id ~ " + req.http.X-Block-Id);
        if (client.ip ~ debuggers) {
            set req.http.X-Debug = "Ban done for block with ID " + req.http.X-Block-Id;
        }
        error 200 "Banned";
    }

For Varnish 4 and later:

.. code-block:: vcl

    if (req.http.X-Layout-Id) {
        ban("obj.http.X-Layout-Id ~ " + req.http.X-Layout-Id);
        if (client.ip ~ debuggers) {
            set req.http.X-Debug = "Ban done for layout with ID " + req.http.X-Layout-Id;
        }
        return (synth(200, "Banned"));
    }

    if (req.http.X-Block-Id) {
        ban("obj.http.X-Block-Id ~ " + req.http.X-Block-Id);
        if (client.ip ~ debuggers) {
            set req.http.X-Debug = "Ban done for block with ID " + req.http.X-Block-Id;
        }
        return (synth(200, "Banned"));
    }

Breaking changes
----------------

The following breaking changes were made in version 0.8 of Netgen Layouts.
Follow the instructions to upgrade your code to this newer version.

* Some classes and interfaces had their namespaces changed. Update your custom
  code working with these classes and interfaces. The following table lists the
  old and the new interface and class names:

  +-------------------------------------------------------------+--------------------------------------------------------------+
  | Old FQCN                                                    | New FQCN                                                     |
  +=============================================================+==============================================================+
  | ``Netgen\BlockManager\API\Values\Page\Block``               | ``Netgen\BlockManager\API\Values\Block\Block``               |
  +-------------------------------------------------------------+--------------------------------------------------------------+
  | ``Netgen\BlockManager\API\Values\Page\Placeholder``         | ``Netgen\BlockManager\API\Values\Block\Placeholder``         |
  +-------------------------------------------------------------+--------------------------------------------------------------+
  | ``Netgen\BlockManager\API\Values\Page\CollectionReference`` | ``Netgen\BlockManager\API\Values\Block\CollectionReference`` |
  +-------------------------------------------------------------+--------------------------------------------------------------+
  | ``Netgen\BlockManager\API\Values\Page\BlockCreateStruct``   | ``Netgen\BlockManager\API\Values\Block\BlockCreateStruct``   |
  +-------------------------------------------------------------+--------------------------------------------------------------+
  | ``Netgen\BlockManager\API\Values\Page\BlockUpdateStruct``   | ``Netgen\BlockManager\API\Values\Block\BlockUpdateStruct``   |
  +-------------------------------------------------------------+--------------------------------------------------------------+
  | ``Netgen\BlockManager\API\Values\Page\Layout``              | ``Netgen\BlockManager\API\Values\Layout\Layout``             |
  +-------------------------------------------------------------+--------------------------------------------------------------+
  | ``Netgen\BlockManager\API\Values\Page\Zone``                | ``Netgen\BlockManager\API\Values\Layout\Zone``               |
  +-------------------------------------------------------------+--------------------------------------------------------------+
  | ``Netgen\BlockManager\API\Values\Page\LayoutCreateStruct``  | ``Netgen\BlockManager\API\Values\Layout\LayoutCreateStruct`` |
  +-------------------------------------------------------------+--------------------------------------------------------------+
  | ``Netgen\BlockManager\API\Values\Page\LayoutUpdateStruct``  | ``Netgen\BlockManager\API\Values\Layout\LayoutUpdateStruct`` |
  +-------------------------------------------------------------+--------------------------------------------------------------+

  Notable change is the ``Block`` interface since it's used in
  ``Netgen\BlockManager\Block\BlockDefinition\BlockDefinitionHandlerInterface::getDynamicParameters``.
  method. You will need to modify your custom block definition handlers to use
  the new interface.

* In ``Netgen\BlockManager\Block\BlockDefinition\BlockDefinitionHandlerInterface::getDynamicParameters``
  method, a second, unused, parameter called ``$parameters`` was removed from
  the interface. Remove it from your custom block definition handlers.

* A new method called ``isContextual`` was added to
  ``Netgen\BlockManager\Collection\QueryType\QueryTypeHandlerInterface``
  interface. The purpose of this method is to signal to the system when the
  query acts as a contextual query, i.e., if it depends on data from current
  page to run. You need to add this method to your custom query type handlers.

  The following is the method signature as well as an example implementation:

  .. code-block:: php

      /**
       * Returns if the provided query is dependent on a context, i.e. currently displayed page.
       *
       * @param \Netgen\BlockManager\API\Values\Collection\Query $query
       *
       * @return bool
       */
      public function isContextual(Query $query);

  .. code-block:: php

      public function isContextual(Query $query)
      {
          return $query->getParameter('use_current_location')->getValue() === true;
      }

* ``BlockDefinitionHandlerInterface::hasCollection`` method has been removed.
  From now on, specifying that the block has a collection is done through
  configuration. The following shows the old and new way of specifying that the
  block has a collection:

  .. code-block:: php

      // Old way

      <?php

      namespace MyApp\Block\BlockDefinition\Handler;

      use Netgen\BlockManager\Block\BlockDefinition\BlockDefinitionHandler;

      class MyBlockHandler extends BlockDefinitionHandler
      {
          /**
           * Returns if this block definition should have a collection.
           *
           * @return bool
           */
          public function hasCollection()
          {
              return true;
          }
      }

  .. code-block:: yaml

      # New way

      netgen_block_manager:
          block_definitions:
              my_block:
                  collections: ~

* ``Netgen\BlockManager\Layout\Resolver\TargetTypeInterface::provideValue``
  method has a changed signature. From now on, Symfony ``Request`` object is
  provided as a parameter to the method, so there's no need to manually fetch
  the current request from the request stack. The new interface looks like this:

  .. code-block:: php

      /**
       * Provides the value for the target to be used in matching process.
       *
       * @param \Symfony\Component\HttpFoundation\Request $request
       *
       * @return mixed
       */
      public function provideValue(Request $request);

* ``Netgen\BlockManager\Layout\Resolver\ConditionTypeInterface::matches``
  method has a changed signature. From now on, Symfony ``Request`` object is
  provided as a first parameter to the method, so there's no need to manually
  fetch the current request from the request stack. The new interface looks like
  this:

  .. code-block:: php

      /**
       * Returns if this request matches the provided value.
       *
       * @param \Symfony\Component\HttpFoundation\Request $request
       * @param mixed $value
       *
       * @return bool
       */
      public function matches(Request $request, $value);

* ``Netgen\BlockManager\Traits\RequestStackAwareTrait`` trait has been removed.
  Inject the request stack service directly into the constructor.

* If using Netgen Layouts with eZ Publish 5, instead of redefining the alias for
  the content provider service, you now have to redefine the alias for newly
  introduced content extractor service.

  .. code-block:: yaml

      # Before

      netgen_block_manager.ezpublish.content_provider:
          alias: netgen_block_manager.ezpublish.content_provider.ez5_request

  .. code-block:: yaml

      # After

      netgen_block_manager.ezpublish.content_extractor:
          alias: netgen_block_manager.ezpublish.content_extractor.ez5_request

* ``netgen_block_manager.google_maps_api_key`` configuration was renamed to
  ``netgen_block_manager.api_keys.google_maps``. The following shows an example
  of the old and new configs:

  .. code-block:: yaml

      # Old config

      netgen_block_manager:
          google_maps_api_key: MY_API_KEY

  .. code-block:: yaml

      # New config

      netgen_block_manager:
          api_keys:
              google_maps: MY_API_KEY

* ``standard`` item view type is always added to all view types automatically.
  However, this was not true for view types that specified custom item view
  types. You had to specify ``standard`` item view type manually if you wanted
  to use it. From now on, ``standard`` item view type will be added in those
  cases too. If you wish to disable it, you can do so like this:

  .. code-block:: yaml

      netgen_block_manager:
          block_definitions:
              my_block:
                  view_types:
                      my_view_type:
                          item_view_types:
                              standard:
                                  enabled: false

* User policies are introduced. To be able to manage user policies in legacy
  administration interface of eZ Platform, you need to activate the provided
  ``nglayouts`` legacy extension. If you're using eZ Platform UI, policy
  management is available automatically.

* Custom items can now be added to blocks manually, instead of just being able
  to return them from query types. Make sure to implement the
  ``Netgen\BlockManager\Item\ValueLoaderInterface`` for your custom items,
  as well as Content Browser backend, and then activate the value type in
  configuration:

  .. code-block:: yaml

      netgen_block_manager:
          items:
              value_types:
                  my_value_type:
                      name: 'My value type'
