Creating a block plugin
=======================

Block plugins are a simple way to extend the behavior of existing blocks,
without having to touch their original implementations. Block plugins can be
used to add new parameters to the block (both normal and dynamic ones) or to
remove or redefine the existing parameters. One block plugin can extend one
block or all existing blocks.

Implementing the block plugin class
-----------------------------------

Implementing a block plugin class is quite similar to implementing a block
handler class itself. Block plugin needs to implement
``Netgen\BlockManager\Block\BlockDefinition\Handler\PluginInterface``, which
provides methods to work with block parameters. You can also extend the provided
abstract class (``Netgen\BlockManager\Block\BlockDefinition\Handler\Plugin``) to
cut down on boilerplate code to write.

If you extend the abstract plugin class, the only required method to implement
is ``getExtendedHandler``, which needs to return fully qualified class name of
the handler you wish to extend.

.. tip::

    You can also return the FQCN of the block handler interface
    (``Netgen\BlockManager\Block\BlockDefinition\BlockDefinitionHandlerInterface``)
    if you wish to extend all existing blocks, or you can return an array of
    FQCNs if you wish to extend a curated list of blocks.

Our plugin would then look like this:

.. code-block:: php

    <?php

    namespace AppBundle\Block\BlockDefinition\Handler;

    use Netgen\BlockManager\Block\BlockDefinition\BlockDefinitionHandlerInterface;

    class MyPlugin extends Plugin
    {
        /**
         * Returns the fully qualified class name of the handler which this
         * plugin extends.
         *
         * @return string|string[]
         */
        public static function getExtendedHandler()
        {
            return BlockDefinitionHandlerInterface::class;
        }
    }

Ofcourse, our plugin is not very useful right now, so let's add some parameters.
Parameters are added by implementing the ``buildParameters`` method, which works
in the exact same way as the ``buildParameters`` method in the block handler:

.. code-block:: php

    /**
     * Builds the parameters by using provided parameter builder.
     *
     * @param \Netgen\BlockManager\Parameters\ParameterBuilderInterface $builder
     */
    public function buildParameters(ParameterBuilderInterface $builder)
    {
        $builder->add('my_param', ParameterType\TextLineType::class);

        // You can even remove existing params
        $builder->remove('existing_param');

        // Or you can modify existing ones
        $builder->get('test')->setDefaultValue('test');
    }

If you wish to add some business logic to the block, you can do that too, by
implementing the ``getDynamicParameters`` method, which, again, works in the
exact same way as the ``getDynamicParameters`` method in the block handler:

.. code-block:: php

    /**
     * Adds the dynamic parameters to the $params object for the provided block.
     *
     * @param \Netgen\BlockManager\Block\DynamicParameters $params
     * @param \Netgen\BlockManager\API\Values\Block\Block $block
     */
    public function getDynamicParameters(DynamicParameters $params, Block $block)
    {
        $params['some_param'] = 'some_value';
    }

.. tip::

    You can ofcourse inject any service into your plugin and use in this method.

Registering the block plugin
----------------------------

To register the block plugin in the system, add it as a Symfony service, and tag
it with ``netgen_block_manager.block.block_definition_handler.plugin`` tag.

.. code-block:: yaml

    app.block.block_definition.handler.plugin.my_plugin:
        class: AppBundle\Block\BlockDefinition\Handler\MyPlugin
        tags:
            - { name: netgen_block_manager.block.block_definition_handler.plugin }

You can also add a ``priority`` attribute to the tag, to control the order in
which your plugins will be executed.
