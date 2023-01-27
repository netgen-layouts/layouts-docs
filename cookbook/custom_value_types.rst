Creating custom value types
===========================

In Netgen Layouts, (block) item is a generic concept in a way that blocks do not
(and should not) care what kind of items are put inside the blocks. To achieve
this, a block item is a wrapper around a value which comes from your CMS. For
example, in Ibexa CMS integration, Netgen Layouts supports two types of
values: Ibexa location and Ibexa content.

To be able to create block items from your own domain objects, you need to
create and register your own custom **value type**. Value type has three
purposes:

* Loading of your domain object from the CMS by its ID by using a value loader
* Handling the domain objects provided by your custom query types by using a
  value converter
* Generating the URL to the domain object by using a value URL generator

Registering a new value type
----------------------------

To be able to use your domain objects inside Netgen Layouts as block items, you
need to register a new value type in the configuration. To do so, you need to
provide a unique identifier for your value type and a human readable name:

.. code-block:: yaml

    netgen_layouts:
        value_types:
            my_value_type:
                name: 'My value type'

This configuration registers a new value type in the system with
``my_value_type`` identifier.

Implementing a value loader
---------------------------

.. note::

    Support for manual items can be disabled through configuration of value
    types with the following config:

    .. code-block:: yaml

        netgen_layouts:
            value_types:
                my_value_type:
                    name: 'My value type'
                    manual_items: false

    In such cases, implementing a value loader as well as Content Browser
    support is not needed.

A value loader is an object responsible for loading your domain object by its
ID or its remote ID. It is an implementation of
``Netgen\Layouts\Item\ValueLoaderInterface`` which provides two methods,
``load`` and ``loadByRemoteId``.

``load`` method takes the ID of the domain object and should simply return the
object once loaded or null if the object could not be loaded.

``loadByRemoteId`` method takes the remote ID of the domain object and again,
should simply return the object once loaded or null if the object could not be
loaded.

.. note::

    Remote ID of the object is usually an ID which identifies a same domain
    object in different databases (dev, staging, production). For example, since
    regular autoincremented primary keys can be different for the same domain
    object in development and production databases, remote ID would be used to
    uniquely and consistently identify the same object in both databases.

The following is an example implementation of a value loader:

.. code-block:: php

    <?php

    declare(strict_types=1);

    namespace App\Item\ValueLoader;

    use Netgen\Layouts\Item\ValueLoaderInterface;
    use Throwable;

    final class MyValueTypeLoader implements ValueLoaderInterface
    {
        public function load($id)
        {
            try {
                return $this->myBackend->loadMyObject($id);
            } catch (Throwable $t) {
                return null;
            }
        }

        public function loadByRemoteId($remoteId)
        {
            try {
                return $this->myBackend->loadMyObjectByRemoteId($remoteId);
            } catch (Throwable $t) {
                return null;
            }
        }
    }

Once implemented, you need to register the loader in Symfony DI container:

.. code-block:: yaml

   app.layouts.value_loader.my_value_type:
        class: App\Item\ValueLoader\MyValueTypeLoader
        tags:
            - { name: netgen_layouts.cms_value_loader, value_type: my_value_type }

Notice that the service is tagged with ``netgen_layouts.cms_value_loader`` DI
tag which has a ``value_type`` attribute. This attribute needs to have a value
equal to your value type identifier.

.. note::

    If you are using autoconfiguration in your Symfony project on PHP 8.1, you
    don't have to manually create a service configuration in your config.
    Instead, you can use a PHP 8 attribute to mark the value loader class as
    such:

    .. code-block:: php

        <?php

        declare(strict_types=1);

        namespace App\Item\ValueLoader;

        use Netgen\Layouts\Attribute\AsCmsValueLoader;
        use Netgen\Layouts\Item\ValueLoaderInterface;

        #[AsCmsValueLoader('my_value_type')]
        final class MyValueTypeLoader implements ValueLoaderInterface
        {
            ...
        }

Implementing Content Browser support
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To be able to actually select the items from the CMS and add them to your
blocks, you also need to
`implement a Netgen Content Browser backend </projects/cb/en/latest/cookbook/custom_backend.html>`_.

To automatically recognize which backend is responsible for which value types,
you need to make sure that the identifier of the item in the
Netgen Content Browser backend you implemented is the same as the identifier of
the value type you configured above.

Implementing a value converter
------------------------------

As you're probably aware, query types need not worry themselves about returning
PHP objects specific to Netgen Layouts to work. Instead, they simply return
domain objects which are then converted by Netgen Layouts into block items.

Converting the domain objects to Netgen Layouts items is done through so called
value converters and every value type needs to have a value converter
implemented. Value converter should implement
``Netgen\Layouts\Item\ValueConverterInterface``, which provides methods that
return the data used by Netgen Layouts to work with block items, like the ID of
the object, name and if the object is considered visible in your CMS.

Method ``supports`` should return if the value converter supports the given
object. Usually, you will check if the provided object is of correct interface.
This makes it possible to handle different types of objects in the same value
converter. For example, in Ibexa CMS, ``Content`` and ``ContentInfo`` are two
different objects that represent the same piece of content in the CMS, but with
different usecases in mind.

Method ``getValueType`` should simply return the identifier of the value type
you choose when activating the value type in the configuration.

An example implementation of a value converter might look something like this:

.. code-block:: php

    <?php

    declare(strict_types=1);

    namespace App\Item\ValueConverter;

    use App\MyValue;
    use Netgen\Layouts\Item\ValueConverterInterface;

    final class MyValueTypeConverter implements ValueConverterInterface
    {
        public function supports($object): bool
        {
            return $object instanceof MyValue;
        }

        public function getValueType($object): string
        {
            return 'my_value_type';
        }

        public function getId($object)
        {
            return $object->id;
        }

        public function getRemoteId($object)
        {
            return $object->remoteId;
        }

        public function getName($object): string
        {
            return $object->name;
        }

        public function getIsVisible($object): bool
        {
            return $object->isVisible();
        }

        public function getObject($object): object
        {
            $object->param = 'value';

            return $object;
        }
    }

Once implemented, you need to register the converter in Symfony DI container and
tag it with ``netgen_layouts.cms_value_converter`` tag:

.. code-block:: yaml

   app.layouts.value_converter.my_value_type_content:
        class: App\Item\ValueConverter\MyValueTypeConverter
        tags:
            - { name: netgen_layouts.cms_value_converter }

.. note::

    If you are using autoconfiguration in your Symfony project on PHP 8.1, you
    don't have to manually create a service configuration in your config.
    Instead, you can use a PHP 8 attribute to mark the value converter class as
    such:

    .. code-block:: php

        <?php

        declare(strict_types=1);

        namespace App\Item\ValueConverter;

        use Netgen\Layouts\Attribute\AsCmsValueConverter;
        use Netgen\Layouts\Item\ValueConverterInterface;

        #[AsCmsValueConverter]
        final class MyValueTypeConverter implements ValueConverterInterface
        {
            ...
        }


Implementing a value URL generator
----------------------------------

To generate the links to your domain objects in your blocks, you can use
``nglayouts_item_path`` Twig function in your Twig templates. This function
internally forwards the URL generation to the correct value URL generator based
on the value type of the item. To generate the URL for your value type, simply
implement the ``Netgen\Layouts\Item\ValueUrlGeneratorInterface``, which
provides a single method called ``generate`` responsible for generating the
URL.

.. note::

    ``generate`` method should return the full path to the item, including the
    starting slash, not just a slug.

An example implementation might use the Symfony router and generate the URL
based on the object ID:

.. code-block:: php

    <?php

    declare(strict_types=1);

    namespace App\Item\ValueUrlGenerator;

    use Netgen\Layouts\Item\ValueUrlGeneratorInterface;

    final class MyValueTypeUrlGenerator implements ValueUrlGeneratorInterface
    {
        public function generate($object): ?string
        {
            return $this->router->generate(
                'my_custom_route',
                ['id' => $object->id],
            );
        }
    }

Once implemented, you need to register the URL generator in Symfony DI container:

.. code-block:: yaml

   app.layouts.value_url_generator.my_value_type:
        class: App\Item\ValueUrlGenerator\MyValueTypeUrlGenerator
        tags:
            - { name: netgen_layouts.cms_value_url_generator, value_type: my_value_type }

Notice that the service is tagged with
``netgen_layouts.cms_value_url_generator`` DI tag which has a ``value_type``
attribute. This attribute needs to have a value equal to your value type
identifier.

.. note::

    If you are using autoconfiguration in your Symfony project on PHP 8.1, you
    don't have to manually create a service configuration in your config.
    Instead, you can use a PHP 8 attribute to mark the value generator class as
    such:

    .. code-block:: php

        <?php

        declare(strict_types=1);

        namespace App\Item\ValueUrlGenerator;

        use Netgen\Layouts\Attribute\AsCmsValueUrlGenerator;
        use Netgen\Layouts\Item\ValueUrlGeneratorInterface;

        #[AsCmsValueUrlGenerator('my_value_type')]
        final class MyValueTypeUrlGenerator implements ValueUrlGeneratorInterface
        {
            ...
        }

Implementing item templates
---------------------------

Once a custom value type is implemented, it's time to implement Twig templates
that will be used to render the item that holds the value.

Just like with block templates, for rendering an item, you need to implement
two templates, one for backend (layout editing app) and one for frontend.

Implementing a backend template
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A backend template, or rather, template for layout editing app is simple. It
receives the item in question in ``item`` variable and can be used to render
the item name and item image. The basic structure of the template looks like
this:

.. code-block:: twig

    <div class="image">
        <img src="/path/to/image.jpg" />
    </div>

    <div class="name">
        <p><a href="{{ nglayouts_item_path(item, 'admin') }}" target="_blank" rel="noopener noreferrer">{{ item.name }}</a></p>
    </div>

Rendering an item name and URL works for all items, as long as you implemented
proper value URL generators and converters. Rendering an image is left for you,
as often it requires additional steps in contrast to just outputting the image
path.

Registering the backend template is done via the view config:

.. code-block:: yaml

    netgen_layouts:
        view:
            item_view:
                app:
                    my_value:
                        template: "@App/app/item/view/my_value.html.twig"
                        match:
                            item\value_type: my_value

Implementing a frontend template
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Just as with the backend template, frontend template receives the item in
question via ``item`` variable. Frontend templates depend on your design, so
there's little sense in providing an example implementation, but once you
implement your frontend template, you can register it with:

.. code-block:: yaml

    netgen_layouts:
        view:
            item_view:
                default:
                    my_value:
                        template: "@App/item/view/my_value.html.twig"
                        match:
                            item\value_type: my_value
