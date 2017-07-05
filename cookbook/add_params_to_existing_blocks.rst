Adding parameters to existing blocks
====================================

Currently, there is no straightforward and official way to add parameters to
existing blocks in Netgen Layouts.

However, if really needed, you can always override the class for an existing
block definition handler by using a compiler pass in Symfony, or redefining the
Symfony service for the handler. Overriden class can then extend from the
original handler class and add new parameters or modify the existing ones.

For example, to add a new parameter to a Title block, you would create a new
class which extends from the original one:

.. code-block:: php

    <?php

    namespace AppBundle\Block\BlockDefinition\Handler;

    use Netgen\BlockManager\Block\BlockDefinition\Handler\TitleHandler as BaseTitleHandler;
    use Netgen\BlockManager\Parameters\ParameterBuilderInterface;
    use Netgen\BlockManager\Parameters\ParameterType\TextLineType;

    class TitleHandler extends BaseTitleHandler
    {
        public function buildParameters(ParameterBuilderInterface $builder)
        {
            parent::buildParameters($builder);

            $builder->add('my_param', TextLineType::class);
        }
    }

You can ofcourse override the ``getDynamicParameters`` method too if needed:

.. code-block:: php

    public function getDynamicParameters(Block $block)
    {
        $params = parent::getDynamicParameters($block);

        $params['my_dynamic_param'] = 42;

        return $params;
    }

After that, you need to create a compiler pass which sets the new class to
``TitleHandler`` Symfony service:

.. code-block:: php

    <?php

    namespace AppBundle\DependencyInjection\CompilerPass;

    use AppBundle\Block\BlockDefinition\Handler\TitleHandler;
    use Symfony\Component\DependencyInjection\Compiler\CompilerPassInterface;
    use Symfony\Component\DependencyInjection\ContainerBuilder;

    class TitleHandlerPass implements CompilerPassInterface
    {
        const SERVICE_NAME = 'netgen_block_manager.block.block_definition.handler.title';

        public function process(ContainerBuilder $container)
        {
            if (!$container->has(static::SERVICE_NAME)) {
                return;
            }

            $container
                ->findDefinition(static::SERVICE_NAME)
                ->setClass(TitleHandler::class);
        }
    }

And finally, you need to register the compiler pass in your bundle class:

.. code-block:: php

    <?php

    namespace AppBundle;

    use AppBundle\DependencyInjection\CompilerPass;
    use Symfony\Component\DependencyInjection\ContainerBuilder;
    use Symfony\Component\HttpKernel\Bundle\Bundle;

    class AppBundle extends Bundle
    {
        public function build(ContainerBuilder $container)
        {
            $container->addCompilerPass(new CompilerPass\TitleHandlerPass());
        }
    }
