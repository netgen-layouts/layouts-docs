How to inject current Ibexa location and content in blocks and query types
==========================================================================

.. note::

    This tutorial is Ibexa CMS specific.

Often, your custom block definitions and query types need the current
Ibexa CMS location or content to work. While you can extract the information
about the current location and content from the ``Request`` object, the
differences between different versions of Ibexa kernel make it impossible to
create generic block definitions and query types that work on any Ibexa kernel
available.

That's why there is a handy Symfony service called Content Provider in
Netgen Layouts that can be used to retrieve the current location or content in a
generic way. In background, this service uses different implementations of a
service that extracts content and locations from the request for every Ibexa
kernel version available.

Service identifier of the Content Provider is
``netgen_layouts.ibexa.content_provider`` and you can inject it into your
block definitions and query types like any other service.

Content Provider exposes two methods: ``provideLocation`` and ``provideContent``
which return the location and content from the current request and ``null`` if
no location or content exist.

As an example, you can use the Content Provider to inject the location and
content objects into Twig templates for your blocks:

.. code-block:: php

    <?php

    declare(strict_types=1);

    namespace App\Block\BlockDefinition\Handler;

    use Netgen\Layouts\API\Values\Block\Block;
    use Netgen\Layouts\Block\BlockDefinition\BlockDefinitionHandler;
    use Netgen\Layouts\Ibexa\ContentProvider\ContentProviderInterface;

    final class MyBlockHandler extends BlockDefinitionHandler
    {
        private ContentProviderInterface $contentProvider;

        public function __construct(ContentProviderInterface $contentProvider)
        {
            $this->contentProvider = $contentProvider;
        }

        public function getDynamicParameters(DynamicParameters $params, Block $block): void
        {
            $params['content'] = $this->contentProvider->provideContent();
            $params['location'] = $this->contentProvider->provideLocation();
        }
    }
