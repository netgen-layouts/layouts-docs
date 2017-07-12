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

* Block plugins are implemented. This led to changing the signature of
  ``BlockDefinitionHandlerInterface::getDynamicParameters`` method. This method
  now receives a second parameter (in the first place) which is an instance of
  ``Netgen\BlockManager\Block\DynamicParameters`` which is used to collect the
  dynamic parameters, instead of returning them from the method. This object
  implements ``ArrayAccess`` interface, so you can use array notation when
  adding the parameters. The following code blocks show the example of the
  method before the change and after:

  .. code-block:: php

      // Before

      /**
       * Returns the array of dynamic parameters provided by this block definition.
       *
       * @param \Netgen\BlockManager\API\Values\Block\Block $block
       *
       * @return array
       */
      public function getDynamicParameters(Block $block)
      {
          return array(
              'param' => 'value',
          );
      }

  .. code-block:: php

      // After

      /**
       * Adds the dynamic parameters to the $params object for the provided block.
       *
       * @param \Netgen\BlockManager\Block\DynamicParameters $params
       * @param \Netgen\BlockManager\API\Values\Block\Block $block
       */
      public function getDynamicParameters(DynamicParameters $params, Block $block)
      {
          $params['param'] = 'value';
      }

* ``buildCommonParameters`` method in the ``BlockDefinitionHandler`` abstract
  class is removed and replaced with a block plugin which adds the common
  parameters to every block. Remove the call from your handlers if it exists.

  If one of your blocks did not call this method (and thus did not add the
  common parameters to your block), implement a block plugin which removes any
  parameter from the block which has a ``common`` group:

  .. code-block:: php

        /**
         * Builds the parameters by using provided parameter builder.
         *
         * @param \Netgen\BlockManager\Parameters\ParameterBuilderInterface $builder
         */
        public function buildParameters(ParameterBuilderInterface $builder)
        {
            foreach ($builder->all('common') as $parameter) {
                $builder->remove($parameter->getName());
            }
        }

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

* ``mapOptions`` method in target type interface
  (``Netgen\BlockManager\Layout\Resolver\Form\TargetType\MapperInterface``) was
  replaced with ``getFormOptions`` method which does not take any parameters.
  If you needed the target type in this method, inject it into the mapper
  via constructor. The contents of the method can be migrated verbatim.

* ``mapOptions`` method in condition type interface
  (``Netgen\BlockManager\Layout\Resolver\Form\ConditionType\MapperInterface``)
  was replaced with ``getFormOptions`` method which does not take any
  parameters. If you needed the condition type in this method, inject it into
  the mapper via constructor. The contents of the method can be migrated
  verbatim.

* Second parameter of ``handleForm`` method in target type interface
  (``Netgen\BlockManager\Layout\Resolver\Form\TargetType\MapperInterface``) was
  removed. If you needed the target type in this method, inject it into the
  mapper via constructor.

* Second parameter of ``handleForm`` method in condition type interface
  (``Netgen\BlockManager\Layout\Resolver\Form\ConditionType\MapperInterface``)
  was removed. If you needed the condition type in this method, inject it into
  the mapper via constructor.