Upgrading from 0.8.0 to 0.9.0
=============================

Upgrade ``composer.json``
-------------------------

In your ``composer.json`` file, upgrade the version of ``netgen/block-manager``
package to ``~0.9.0`` and run the ``composer update`` command.

.. note::

    If you have Netgen Layouts installed on eZ Platform, the package name will
    be ``netgen/block-manager-ezpublish``.

.. note::

    Integrations into Netgen Admin UI and eZ Platform UI also have separate
    packages whose versions need to be bumped to ``~0.9.0``.

Database migration
------------------

Run the following command from the root of your installation to execute
migration to version 0.9 of Netgen Layouts:

.. code-block:: shell

    $ php app/console doctrine:migrations:migrate --configuration=vendor/netgen/block-manager/migrations/doctrine.yml

Upgrading Netgen Content Browser
--------------------------------

Netgen Content Browser version 0.9 was also automatically installed. Be sure to
read `its upgrade instructions </projects/cb/en/latest/upgrades/upgrade_080_090.html>`_
too, to make sure you custom code keeps working.

Breaking changes
----------------

The following breaking changes were made in version 0.9 of Netgen Layouts.
Follow the instructions to upgrade your code to this newer version.

* ``toHash``, ``fromHash``, ``createValueFromInput`` and ``isValueEmpty``
  methods in ``Netgen\BlockManager\Parameters\ParameterTypeInterface`` interface
  were changed. From now on, they receive an instance of
  ``Netgen\BlockManager\Parameters\ParameterInterface`` object as their first
  parameter. The following shows the difference in signature in one of the
  methods:

  .. code-block:: php

      // Before

      /**
       * Converts the parameter value from a domain format to scalar/hash format.
       *
       * @param mixed $value
       *
       * @return mixed
       */
      public function toHash($value);

  .. code-block:: php

      // After

      /**
       * Converts the parameter value from a domain format to scalar/hash format.
       *
       * @param \Netgen\BlockManager\Parameters\ParameterInterface $parameter
       * @param mixed $value
       *
       * @return mixed
       */
      public function toHash(ParameterInterface $parameter, $value);

* A new method called ``isContextual`` was added to
  ``Netgen\BlockManager\Block\BlockDefinition\BlockDefinitionHandlerInterface``
  interface. The purpose of this method is to signal to the system when the
  block acts as a contextual block, i.e., if it depends on data from current
  request to run. You need to add this method to your custom block definition
  handlers if they depend on data from current request (for example, if they use
  current eZ Platform location or content).

  The following is the method signature:

  .. code-block:: php

      /**
       * Returns if the provided block is dependent on a context, i.e. current request.
       *
       * @param \Netgen\BlockManager\API\Values\Block\Block $block
       *
       * @return bool
       */
      public function isContextual(Block $block);
